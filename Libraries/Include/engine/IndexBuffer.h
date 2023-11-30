#pragma once
class IndexBuffer
{
private:
	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11Buffer> _indexBuffer;
private:
	uint32 _stride = 0;
	uint32 _offset = 0;
	uint32 _count = 0;
public:
	IndexBuffer();
	IndexBuffer(ComPtr<ID3D11Device> device);
	~IndexBuffer();
public:
	ComPtr<ID3D11Buffer> GetBuffer() { return _indexBuffer; }
	uint32 GetStride() const { return _stride; }
	uint32 GetOffset() const { return _offset; }
	uint32 GetCount() const { return _count; }
public:
	void CreateIndexBuffer(const vector<uint32>& indices);
};

