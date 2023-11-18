#include "pch.h"


VertexBuffer::VertexBuffer()
{
	_device = GRAPHICS()->GetDevice();
}

VertexBuffer::VertexBuffer(ComPtr<ID3D11Device> device) : _device(device)
{
}

VertexBuffer::~VertexBuffer()
{
}
