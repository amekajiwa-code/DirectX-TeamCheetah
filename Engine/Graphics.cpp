#include "pch.h"

Graphics* Graphics::_instance = nullptr;

Graphics::Graphics()
{
	_hwnd = g_hWnd;
	_width = g_winSizeX;
	_height = g_winSizeY;

	CreateDeviceAndSwapChain();
	CreateRenderTargetView();
	SetViewPort();
}

Graphics::Graphics(HWND hwnd)
{
	_hwnd = hwnd;
	_width = g_winSizeX;
	_height = g_winSizeY;

	CreateDeviceAndSwapChain();
	CreateRenderTargetView();
	SetViewPort();
}

Graphics::~Graphics()
{
}

void Graphics::SetHwnd(HWND hwnd)
{
	_hwnd = hwnd;
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
		desc.BufferCount = 1;
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
	ComPtr<ID3D11Texture2D> backBuffer = nullptr;

	hr = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
		(void**)backBuffer.GetAddressOf());
	CHECK(hr);

	hr = _device->CreateRenderTargetView(backBuffer.Get(), nullptr,
		_renderTargetView.GetAddressOf());
	CHECK(hr);
}

void Graphics::SetViewPort()
{
	_viewPort.TopLeftX = 0.f;
	_viewPort.TopLeftY = 0.f;
	_viewPort.Width = static_cast<float>(_width);
	_viewPort.Height = static_cast<float>(_height);
	_viewPort.MinDepth = 0.f;
	_viewPort.MaxDepth = 1.f;
}

void Graphics::Init()
{
	_hwnd = g_hWnd;
	_width = g_winSizeX;
	_height = g_winSizeY;

	CreateDeviceAndSwapChain();
	CreateRenderTargetView();
	SetViewPort();
}

void Graphics::RenderBegin()
{
	_deviceContext->OMSetRenderTargets(1, _renderTargetView.GetAddressOf(), nullptr);
	_deviceContext->ClearRenderTargetView(_renderTargetView.Get(), _clearColor);
	_deviceContext->RSSetViewports(1, &_viewPort);
}

void Graphics::RenderEnd()
{
	HRESULT hr = _swapChain->Present(1, 0);
	CHECK(hr);
}
