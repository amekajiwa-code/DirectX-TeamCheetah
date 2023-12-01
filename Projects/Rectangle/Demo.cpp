#include "pch.h"
#include "Demo.h"
#include "engine/Shader.h"
#include "engine/GeometryHelper.h"

void Demo::Init()
{
	_shader = make_shared<Shader>(L"Rectangle.fx");

	_geometry = make_shared<Geometry<VertexColorData>>();
	GeometryHelper::CreateQuad(_geometry, Color(1.0f, 0.f, 0.f, 1.f));

	_vtxbuffer = make_shared<VertexBuffer>();
	_vtxbuffer->CreateVertexBuffer(_geometry->GetVertices());

	_idxbuffer = make_shared<IndexBuffer>();
	_idxbuffer->CreateIndexBuffer(_geometry->GetIndices());
}

void Demo::Update()
{
}

void Demo::Render()
{
	uint32 stride = _vtxbuffer->GetStride();
	uint32 offset = _vtxbuffer->GetOffset();

	DC()->IASetVertexBuffers(0, 1, _vtxbuffer->GetBuffer().GetAddressOf(), &stride, &offset);
	DC()->IASetIndexBuffer(_idxbuffer->GetBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);
	//Normal Color
	_shader->DrawIndexed(0, 0, _idxbuffer->GetCount(), 0, 0);
	//Wireframe mode
	//_shader->DrawIndexed(0, 0, _idxbuffer->GetCount(), 0, 0);

}
