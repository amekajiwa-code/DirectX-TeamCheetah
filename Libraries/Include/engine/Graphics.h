#pragma once
#define MAX_SIZE_RTV_DSV 2;
#include "Viewport.h"

class Graphics
{
private:
	static Graphics* _instance;
public:
	static Graphics* GetInstance()
	{
		if (_instance == nullptr)
		{
			_instance = new Graphics();
		}

		return _instance;
	}
private:
	Graphics();
	~Graphics();
private:
	HWND		_hwnd;
	uint32		_width = 0;
	uint32		_height = 0;
private:
	//Device SwapChain
	ComPtr<ID3D11Device>		_device;
	ComPtr<ID3D11DeviceContext>	_deviceContext;
	ComPtr<IDXGISwapChain>		_swapChain;
	//RTV
	vector<ComPtr<ID3D11Texture2D>>			_backBuffers;
	vector<ComPtr<ID3D11RenderTargetView>>	_renderTargetViews;
	//DSV
	vector<ComPtr<ID3D11Texture2D>>			_depthStancilTextures;
	vector<ComPtr<ID3D11DepthStencilView>>	_depthStancilViews;
	//Blend
	ComPtr<ID3D11BlendState> _blendState;
	//Misc
	Viewport	_viewPort;
	float		_clearColor[4] = { 0.f,0.f,0.f,0.f };
	float		_clearColor2[4] = { 0.5f,0.5f,0.5f,1.f };
public:
	ComPtr<ID3D11Device>		GetDevice() { return _device; }
	ComPtr<ID3D11DeviceContext> GetDeviceContext() { return _deviceContext; }
	ComPtr<IDXGISwapChain>		GetSwapChain() { return _swapChain; }
	ComPtr<ID3D11RenderTargetView> GetRenderTargetView(uint16 num)
	{ 
		if (num < _renderTargetViews.size())
		{
			return _renderTargetViews[num];
		}
		return nullptr;
	}
	ComPtr<ID3D11Texture2D> GetRenderTexture(uint16 num) 
	{ 
		if (num < _backBuffers.size())
		{
			return _backBuffers[num];
		}
		return nullptr;
	}
	ComPtr<ID3D11DepthStencilView> GetDepthStencilView(uint16 num = 0) 
	{ 
		if (num < _depthStancilViews.size())
		{
			return _depthStancilViews[num];
		}
		return nullptr;
	}
	Viewport& GetViewport() { return _viewPort; }
private:
	void CreateDeviceAndSwapChain();
	void CreateRenderTargetView();
	void CreateDepthStencilView();
	void CreateBlendState();
	void CreateRenderTexture(UINT width, UINT height, ComPtr<ID3D11Texture2D>& texture);
public:
	void SetViewPort(float width, float height, float x, float y, float minDepth, float maxDepth);
public:
	void Init();
	void RenderBegin();
	void RenderEnd();
};

