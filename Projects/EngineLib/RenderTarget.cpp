#include "pch.h"
#include "RenderTarget.h"

RenderTarget::RenderTarget()
{
	renderTargetView = nullptr;
	depthStencilView = nullptr;
	render_SRV = nullptr;
	render_Texture = nullptr;
	render_DSFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
}
void RenderTarget::Set(ComPtr<ID3D11Device> device, FLOAT TopLeftX, FLOAT TopLeftY, FLOAT Width, FLOAT Height,
	FLOAT MinDepth, FLOAT MaxDepth)
{
	ref_device = device;
	render_vp.TopLeftX = TopLeftX;
	render_vp.TopLeftY = TopLeftY;
	render_vp.Width = Width;
	render_vp.Height = Height;
	render_vp.MinDepth = MinDepth;
	render_vp.MaxDepth = MaxDepth;
	render_matProj = Camera::S_MatProjection;
}
HRESULT RenderTarget::CreateCubeMap(ComPtr<ID3D11Device> device, FLOAT Width, FLOAT Height)
{
	HRESULT hr;
	Set(device, 0, 0, Width, Height, 0.0f, 1.0f);

	// 랜더타켓용 텍스처 생성
	D3D11_TEXTURE2D_DESC TexDesc;
	ZeroMemory(&TexDesc, sizeof(D3D11_TEXTURE2D_DESC));
	TexDesc.Width = (UINT)Width;
	TexDesc.Height = (UINT)Height;
	TexDesc.MipLevels = 1;
	TexDesc.SampleDesc.Count = 1;
	TexDesc.ArraySize = 6;
	TexDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	TexDesc.Usage = D3D11_USAGE_DEFAULT;
	TexDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	TexDesc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;
	device->CreateTexture2D(&TexDesc, NULL, render_Texture.GetAddressOf());
	if (render_Texture != nullptr)
	{
		render_Texture->GetDesc(&render_TexDesc);
	}

	// 랜더타켓용 뷰 생성
	D3D11_RENDER_TARGET_VIEW_DESC RtvDesc;
	ZeroMemory(&RtvDesc, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
	RtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	RtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
	RtvDesc.Texture2DArray.ArraySize = 6;
	device->CreateRenderTargetView(render_Texture.Get(), &RtvDesc,renderTargetView.GetAddressOf());

	// 쉐이더 리소스 뷰 생성
	D3D11_SHADER_RESOURCE_VIEW_DESC SrvDesc;
	ZeroMemory(&SrvDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	SrvDesc.Format = TexDesc.Format;
	SrvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
	SrvDesc.Texture2DArray.MipLevels = 1;
	device->CreateShaderResourceView(render_Texture.Get(), &SrvDesc, render_SRV.GetAddressOf());


	// 깊이 스텐실 뷰 텍스처 생성
	ComPtr<ID3D11Texture2D> pDSTexture = nullptr;
	D3D11_TEXTURE2D_DESC DSDesc;
	ZeroMemory(&DSDesc, sizeof(D3D11_TEXTURE2D_DESC));
	DSDesc.Width = (UINT)Width;
	DSDesc.Height = (UINT)Height;
	DSDesc.MipLevels = 1;
	DSDesc.ArraySize = 6;
	DSDesc.Format = DXGI_FORMAT_D32_FLOAT;
	DSDesc.SampleDesc.Count = 1;
	DSDesc.SampleDesc.Quality = 0;
	DSDesc.Usage = D3D11_USAGE_DEFAULT;
	DSDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	DSDesc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;
	device->CreateTexture2D(&DSDesc, NULL, pDSTexture.GetAddressOf());

	// 깊이 스텐실 뷰 생성
	D3D11_DEPTH_STENCIL_VIEW_DESC DsvDesc;
	ZeroMemory(&DsvDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	DsvDesc.Format = DSDesc.Format;
	DsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DARRAY;
	DsvDesc.Texture2DArray.ArraySize = 6;
	device->CreateDepthStencilView(pDSTexture.Get(), &DsvDesc, &depthStencilView);
	return S_OK;
}
HRESULT RenderTarget::Create(ComPtr<ID3D11Device> device, FLOAT Width, FLOAT Height)
{
	HRESULT hr = S_OK;
	Set(device, 0, 0, Width, Height, 0.0f, 1.0f);

	render_TexDesc.Width = (UINT)Width;
	render_TexDesc.Height = (UINT)Height;
	render_TexDesc.MipLevels = 1;
	render_TexDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	render_TexDesc.SampleDesc.Count = 1;
	render_TexDesc.SampleDesc.Quality = 0;
	render_TexDesc.Usage = D3D11_USAGE_DEFAULT;
	render_TexDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	render_TexDesc.CPUAccessFlags = 0;
	render_TexDesc.MiscFlags = 0;
	render_TexDesc.ArraySize = 1;

	if (FAILED(hr = ref_device->CreateTexture2D(&render_TexDesc, NULL, render_Texture.GetAddressOf())))
	{
		return hr;
	}
	if (FAILED(hr = ref_device->CreateShaderResourceView(render_Texture.Get(), NULL, render_SRV.GetAddressOf())))
	{
		return hr;
	}
	if (FAILED(hr = ref_device->CreateRenderTargetView(render_Texture.Get(), NULL, renderTargetView.GetAddressOf())))
	{
		return hr;
	}


	// 백버퍼의 크기가 변경되면 반드시 깊이스텐실 뷰어도 다시 작성되어야 한다.		
	if (FAILED(hr = UpdateDepthStencilView( (UINT)Width, (UINT)Height)))
	{
		return hr;
	}
	return hr;
}
HRESULT RenderTarget::UpdateDepthStencilView( UINT Width, UINT Height)
{
	HRESULT hr;
	render_vp.Width = (FLOAT)Width;
	render_vp.Height = (FLOAT)Height;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> render_DSTexture = nullptr;
	D3D11_TEXTURE2D_DESC DescDepth;
	ZeroMemory(&DescDepth, sizeof(D3D11_TEXTURE2D_DESC));
	DescDepth.Width = Width;
	DescDepth.Height = Height;
	DescDepth.MipLevels = 1;
	DescDepth.ArraySize = 1;
	if (render_DSFormat == DXGI_FORMAT_D24_UNORM_S8_UINT)
		DescDepth.Format = DXGI_FORMAT_R24G8_TYPELESS;
	else
		DescDepth.Format = DXGI_FORMAT_R32_TYPELESS;
	DescDepth.SampleDesc.Count = 1;
	DescDepth.SampleDesc.Quality = 0;
	DescDepth.CPUAccessFlags = 0;
	DescDepth.MiscFlags = 0;

	DescDepth.Usage = D3D11_USAGE_DEFAULT;
	// 백 버퍼 깊이 및 스텐실 버퍼 생성
	DescDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	if (DescDepth.Format == DXGI_FORMAT_R24G8_TYPELESS || DescDepth.Format == DXGI_FORMAT_R32_TYPELESS)
	{
		// 깊이맵 전용 깊이맵 생성
		DescDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	}


	if (FAILED(hr = ref_device->CreateTexture2D(&DescDepth, NULL, render_DSTexture.GetAddressOf())))
	{
		return hr;
	}

	///// 쉐이더 리소스 생성 : 깊이 맵 쉐도우에서 사용한다. ///
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&dsvDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	ZeroMemory(&srvDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));

	switch (DescDepth.Format)
	{
	case DXGI_FORMAT_R32_TYPELESS:
		dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
		srvDesc.Format = DXGI_FORMAT_R32_FLOAT;
		break;
	case DXGI_FORMAT_R24G8_TYPELESS:
		dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		srvDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
		break;
	}


	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	if (FAILED(hr = ref_device->CreateDepthStencilView(render_DSTexture.Get(), &dsvDesc, depthStencilView.ReleaseAndGetAddressOf())))
	{
		return hr;
	}
	depthStencilView->GetDesc(&render_DepthStencilDesc);

	/*D3D11_SHADER_RESOURCE_VIEW_DESC dsrvd =
	{
		srvDesc.Format,
		D3D11_SRV_DIMENSION_TEXTURE2D,
		0,
		0
	};
	dsrvd.Texture2D.MipLevels = 1;*/

	if (srvDesc.Format == DXGI_FORMAT_R32_FLOAT || srvDesc.Format == DXGI_FORMAT_R24_UNORM_X8_TYPELESS)
	{
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = 1;
		if (FAILED(hr = ref_device->CreateShaderResourceView(render_DSTexture.Get(), &srvDesc, render_DsvSRV.ReleaseAndGetAddressOf())))
		{
			return hr;
		}
	}
	return hr;
}
void RenderTarget::Apply(ID3D11DeviceContext* pImmediateContext,
	ID3D11RenderTargetView* pRTV,
	ID3D11DepthStencilView* pDepthStencilView,
	bool bDepthClear, bool bStencilClear)
{
	assert(pImmediateContext);
	assert(pRTV);
	ID3D11RenderTargetView* pNullRTV = NULL;
	pImmediateContext->OMSetRenderTargets(1, &pNullRTV, NULL);

	if (pRTV != NULL)
	{
		if (pDepthStencilView != NULL)
			pImmediateContext->OMSetRenderTargets(1, &pRTV, pDepthStencilView);
		else
			pImmediateContext->OMSetRenderTargets(1, &pRTV, depthStencilView.Get());
	}
	else
	{
		if (pDepthStencilView != NULL)
			pImmediateContext->OMSetRenderTargets(1,renderTargetView.GetAddressOf(), pDepthStencilView);
		else
			pImmediateContext->OMSetRenderTargets(1, renderTargetView.GetAddressOf(),depthStencilView.Get());
	}
	if (bDepthClear)
	{
		if (pDepthStencilView != NULL)
			pImmediateContext->ClearDepthStencilView(pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0, 0);
		else
			pImmediateContext->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0, 0);

	}
	if (bStencilClear)
	{
		if (pDepthStencilView != NULL)
			pImmediateContext->ClearDepthStencilView(pDepthStencilView, D3D11_CLEAR_STENCIL, 1.0, 0);
		else
			pImmediateContext->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_STENCIL, 1.0, 0);
	}
	pImmediateContext->RSSetViewports(1, &render_vp);
}
bool	RenderTarget::Begin(ID3D11DeviceContext* deviceContext, SimpleMath::Vector4 vColor,
	bool bTargetClear, bool bDepthClear, bool bStencilClear)
{
	render_ViewPortcounts = 1;
	deviceContext->RSGetViewports(&render_ViewPortcounts, render_ViewPortOld);
	deviceContext->OMGetRenderTargets(1, &render_OldRTV, &render_OldDSV);

	ID3D11RenderTargetView* pNullRTV = NULL;
	deviceContext->OMSetRenderTargets(1, &pNullRTV, NULL);
	deviceContext->OMSetRenderTargets(1,renderTargetView.GetAddressOf(),depthStencilView.Get());

	Clear(deviceContext, vColor, bTargetClear, bDepthClear, bStencilClear);
	deviceContext->RSSetViewports(1, &render_vp);
	return true;
}
bool	RenderTarget::Clear(ID3D11DeviceContext* deviceContext, SimpleMath::Vector4 vColor,
	bool bTargetClear, bool bDepthClear, bool bStencilClear)
{
	if (bTargetClear)
	{
		const FLOAT color[] = { vColor.x, vColor.y, vColor.z, vColor.w };
		deviceContext->ClearRenderTargetView(renderTargetView.Get(), color);
	}
	if (bDepthClear)
	{
		deviceContext->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0, 0);
	}
	if (bStencilClear)
	{
		deviceContext->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_STENCIL, 1.0, 0);
	}
	deviceContext->RSSetViewports(1, &render_vp);
	return true;
}
bool	RenderTarget::End(ID3D11DeviceContext* deviceContext)
{
	deviceContext->RSSetViewports(render_ViewPortcounts, render_ViewPortOld);
	deviceContext->OMSetRenderTargets(1, &render_OldRTV, render_OldDSV);
	if (render_OldRTV) render_OldRTV->Release();
	if (render_OldDSV) render_OldDSV->Release();
	return true;
}