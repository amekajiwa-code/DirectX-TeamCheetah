#include "pch.h"
#include "InstancingBuffer.h"

InstancingBuffer::InstancingBuffer()
{
	CreateBuffer(MAX_MESH_INSTANCE);
}

InstancingBuffer::~InstancingBuffer()
{

}

void InstancingBuffer::ClearData()
{
	_data.clear();
}

void InstancingBuffer::AddData(InstancingData& data)
{
	_data.push_back(data);
}

void InstancingBuffer::PushData()
{
	const uint32 dataCount = GetCount();
	if (dataCount > _maxCount)
		CreateBuffer(dataCount);

	D3D11_MAPPED_SUBRESOURCE subResource;

	DC()->Map(_instanceBuffer->GetBuffer().Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
	{
		::memcpy(subResource.pData, _data.data(), sizeof(InstancingData) * dataCount);
	}
	DC()->Unmap(_instanceBuffer->GetBuffer().Get(), 0);

	_instanceBuffer->PushData();
}

void InstancingBuffer::CreateBuffer(uint32 maxCount /*= MAX_MESH_INSTANCE*/)
{
	_maxCount = maxCount;
	_instanceBuffer = make_shared<VertexBuffer>();

	vector<InstancingData> temp(maxCount);
	_instanceBuffer->CreateVertexBuffer(temp, /*slot*/1, /*cpuWrite*/true);
}