#include "pch.h"

Graphics* Graphics::_instance = nullptr;

Graphics::Graphics()
{
	Init();
}

Graphics::~Graphics()
{
}

void Graphics::CreateDeviceAndSwapChain()
{
	HRESULT hr;
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	{
		desc.BufferDesc.Width = _width;
		desc.BufferDesc.Height = _height;
		desc.BufferDesc.RefreshRate.Numerator = 60;
		desc.BufferDesc.RefreshRate.Denominator = 1;
		desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.BufferCount = 2;
		desc.OutputWindow = _hwnd;
		desc.Windowed = true;
		desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	}

	hr = ::D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&desc,
		_swapChain.GetAddressOf(),
		_device.GetAddressOf(),
		nullptr,
		_deviceContext.GetAddressOf()
	);

	CHECK(hr);
}

void Graphics::CreateRenderTargetView()
{
	HRESULT hr;

	UINT size = MAX_SIZE_RTV_DSV;

	_backBuffers.resize(size);
	_renderTargetViews.resize(size);

	//Main BackBuffer
	hr = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
		(void**)_backBuffers[0].GetAddressOf());
	CHECK(hr);

	for (int i = 1; i < _backBuffers.size(); i++)
	{
		CreateRenderTexture(g_gameDesc.width, g_gameDesc.height, _backBuffers[i]);
	}

	for (int i = 0; i < _renderTargetViews.size(); i++)
	{
		hr = _device->CreateRenderTargetView(_backBuffers[i].Get(), nullptr,
			_renderTargetViews[i].GetAddressOf());
		CHECK(hr);
	}
}

void Graphics::SetViewPort(float width, float height, float x = 0, float y = 0, float minDepth = 0, float maxDepth = 1)
{
	_viewPort.SetViewport(width, height);
}

void Graphics::CreateRenderTexture(UINT width, UINT height, ComPtr<ID3D11Texture2D>& texture)
{
	HRESULT hr;

	//desc
	{
		D3D11_TEXTURE2D_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Width = width;
		desc.Height = height;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;

		hr = _device->CreateTexture2D(&desc, nullptr, texture.GetAddressOf());
		CHECK(hr);
	}
}

void Graphics::CreateDepthStencilView()
{

	UINT size = MAX_SIZE_RTV_DSV;
	_depthStancilTextures.resize(size);
	_depthStancilViews.resize(size);

	HRESULT hr;
	//Create DepthStencilTexture
	{
		D3D11_TEXTURE2D_DESC desc = { 0 };
		desc.Width = static_cast<uint32>(g_gameDesc.width);
		desc.Height = static_cast<uint32>(g_gameDesc.height);
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;

		for (int i = 0; i < _depthStancilTextures.size(); i++)
		{
			hr = _device->CreateTexture2D(&desc, nullptr, _depthStancilTextures[i].GetAddressOf());
			CHECK(hr);
		}
	}
	//Create DepthStencilView
	{
		D3D11_DEPTH_STENCIL_VIEW_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		desc.Texture2D.MipSlice = 0;

		for (int i = 0; i < _depthStancilViews.size(); i++)
		{
			hr = _device->CreateDepthStencilView(_depthStancilTextures[i].Get(), &desc,
				_depthStancilViews[i].GetAddressOf());
			CHECK(hr);
		}
	}
}

void Graphics::CreateBlendState()
{
	HRESULT hr;
	D3D11_BLEND_DESC desc = { 0 };
	desc.RenderTarget[0].BlendEnable = true;
	desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	hr = _device->CreateBlendState(&desc, _blendState.GetAddressOf());
	CHECK(hr);
}

void Graphics::Init()
{
	_hwnd = g_gameDesc.hWnd;
	_width = g_gameDesc.width;
	_height = g_gameDesc.height;

	_clearColor[0] = g_gameDesc.clearColor.x;
	_clearColor[1] = g_gameDesc.clearColor.y;
	_clearColor[2] = g_gameDesc.clearColor.z;
	_clearColor[3] = g_gameDesc.clearColor.w;

	CreateDeviceAndSwapChain();
	CreateRenderTargetView();
	CreateDepthStencilView();
	CreateBlendState();
	SetViewPort(g_gameDesc.width, g_gameDesc.height);
}

void Graphics::RenderBegin()
{
	_deviceContext->OMSetRenderTargets(1, _renderTargetViews[0].GetAddressOf(), _depthStancilViews[0].Get());
	_deviceContext->ClearRenderTargetView(_renderTargetViews[0].Get(), _clearColor);
	_deviceContext->ClearDepthStencilView(_depthStancilViews[0].Get(),
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
	_viewPort.RSSetViewport();
	//_deviceContext->OMSetBlendState(_blendState.Get(), 0, 1);
}

void Graphics::RenderEnd()
{
	HRESULT hr = _swapChain->Present(1, 0);
	CHECK(hr);
}
