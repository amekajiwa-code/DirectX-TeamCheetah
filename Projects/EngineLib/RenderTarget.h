#pragma once
class RenderTarget
{
public:
	ComPtr<ID3D11Device>					ref_device;
	ComPtr<ID3D11RenderTargetView>			renderTargetView;
	ComPtr<ID3D11DepthStencilView>			depthStencilView;
	ComPtr<ID3D11ShaderResourceView>		render_SRV;
	ComPtr<ID3D11ShaderResourceView>		render_DsvSRV;// ±Ì¿Ãπˆ∆€ ∏Æº“Ω∫∫‰
	ComPtr<ID3D11Texture2D>					render_Texture;
	D3D11_DEPTH_STENCIL_VIEW_DESC			render_DepthStencilDesc;
	D3D11_TEXTURE2D_DESC					render_TexDesc;
	DXGI_FORMAT								render_DSFormat;
	D3D11_VIEWPORT							render_vp;
	Matrix									render_matProj;

	// Store the old render targets
	D3D11_VIEWPORT			render_ViewPortOld[D3D11_VIEWPORT_AND_SCISSORRECT_MAX_INDEX];
	UINT					render_ViewPortcounts;
	ID3D11RenderTargetView* render_OldRTV;
	ID3D11DepthStencilView* render_OldDSV;
public:
	HRESULT	Create(ComPtr<ID3D11Device> device, FLOAT Width = 1024, FLOAT Height = 1024);
	HRESULT CreateCubeMap(ComPtr<ID3D11Device> device, FLOAT fWidth = 1024, FLOAT fHeight = 1024);
	ID3D11ShaderResourceView* GetDsvSRV() { return render_DsvSRV.Get(); };

	void	Set(ComPtr<ID3D11Device> device, FLOAT TopLeftX, FLOAT TopLeftY, FLOAT Width, FLOAT Height,
		FLOAT MinDepth = 0, FLOAT MaxDepth = 1);
	HRESULT UpdateDepthStencilView( UINT dwWidth, UINT dwHeight);
	void	Apply(ID3D11DeviceContext* pImmediateContext,
		ID3D11RenderTargetView* pRTV = NULL,
		ID3D11DepthStencilView* pDepthStencilView = NULL,
		bool bDepthClear = true, bool bStencilClear = true);
	bool	Begin(ID3D11DeviceContext* pImmediateContext, SimpleMath::Vector4 vColor,
		bool bTargetClear = true, bool bDepthClear = true, bool bStencilClear = true);
	bool	Clear(ID3D11DeviceContext* pImmediateContext, SimpleMath::Vector4 vColor,
		bool bTargetClear = true, bool bDepthClear = true, bool bStencilClear = true);
	bool	End(ID3D11DeviceContext* pImmediateContext);
	RenderTarget();
	~RenderTarget() {};
};
