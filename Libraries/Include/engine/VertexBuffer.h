#pragma once
#define CHECK(p)	assert(SUCCEEDED(p))

class VertexBuffer
{
private:
	ComPtr<ID3D11Device>	_device;
	ComPtr<ID3D11Buffer>	_vertexBuffer;
private:
	uint32 _stride = 0;
	uint32 _offset = 0;
	uint32 _count = 0;
public:
	VertexBuffer();
	VertexBuffer(ComPtr<ID3D11Device> device);
	~VertexBuffer();
public:
	ComPtr<ID3D11Buffer> GetBuffer() { return _vertexBuffer; }
	uint32 GetStride() const  { return _stride; }
	uint32 GetOffset() const { return _offset; }
	uint32 GetCount() const { return _count; }
public:
	template<typename T>
	void CreateVertexBuffer(const std::vector<T>& vertices)
	{
		_stride = sizeof(T);
		_count = static_cast<uint32>(vertices.size());

		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.ByteWidth = (uint32)(_stride * _count);

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(data));
		data.pSysMem = vertices.data();

		HRESULT hr = _device->CreateBuffer(&desc, &data, _vertexBuffer.GetAddressOf());
		CHECK(hr);
	}
};

