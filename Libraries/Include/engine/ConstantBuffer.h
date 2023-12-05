#pragma once

template<typename T>
class ConstantBuffer
{
private:
	ComPtr<ID3D11Device>			_device;
	ComPtr<ID3D11DeviceContext>		_deviceContext;
private:
	ComPtr<ID3D11Buffer>			_constantBuffer;
public:
	ConstantBuffer() { _device = GRAPHICS()->GetDevice(); _deviceContext = GRAPHICS()->GetDeviceContext(); }
	ConstantBuffer(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext) : _device(device), _deviceContext(deviceContext) {}
	~ConstantBuffer() {}
public:
	ComPtr<ID3D11Buffer> GetBuffer() const { return _constantBuffer; }
public:
	void CreateConstantBuffer()
	{
		HRESULT hr;

		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.ByteWidth = sizeof(T);
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		hr = _device->CreateBuffer(&desc, nullptr, _constantBuffer.GetAddressOf());
		CHECK(hr);
	}
	void CopyData(const T& data)
	{
		HRESULT hr;

		D3D11_MAPPED_SUBRESOURCE sub;
		ZeroMemory(&sub, sizeof(sub));

		hr = _deviceContext->Map(_constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &sub);
		CHECK(hr);

		::memcpy(sub.pData, &data, sizeof(data));
		_deviceContext->Unmap(_constantBuffer.Get(), 0);
	}
};

