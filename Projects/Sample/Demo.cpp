#include "pch.h"
#include "Demo.h"
#include "engine/Shader.h"

void Demo::Init()
{
	_shader = make_shared<Shader>(L"Triangle.fx");
	{
		_vertices.resize(3);

		_vertices[0].position = Vec3{ -0.5f, 0.f, 0.f };
		_vertices[1].position = Vec3{ 0.f, 0.5f, 0.f };
		_vertices[2].position = Vec3{ 0.5f, 0.f, 0.f };
	}
	_buffer = make_shared<VertexBuffer>();
	_buffer->CreateVertexBuffer(_vertices);
}

void Demo::Update()
{
}

void Demo::Render()
{
	uint32 stride = _buffer->GetStride();
	uint32 offset = _buffer->GetOffset();

	DC()->IASetVertexBuffers(0, 1, _buffer->GetBuffer().GetAddressOf(), &stride, &offset);

	_shader->Draw(1,0,3);
}
