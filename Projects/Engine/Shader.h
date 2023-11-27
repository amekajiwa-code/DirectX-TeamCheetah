#pragma once
#include "ResourceBase.h"

class Shader : public ResourceBase
{
	using Super = ResourceBase;
public:
	Shader();
	virtual ~Shader();
private:
	shared_ptr<InputLayout>		_inputLayout;
	shared_ptr<VertexShader>	_vertexShader;
	shared_ptr<PixelShader>		_pixelShader;
public:
	shared_ptr<VertexShader> GetVertexShader() { return _vertexShader; }
	shared_ptr<PixelShader> GetPixelShader() { return _pixelShader; }
	shared_ptr<InputLayout> GetInputLayout() { return _inputLayout; }
public:
	void SetVertexShader(shared_ptr<VertexShader> vShader) { _vertexShader = vShader; }
	void SetPixelShader(shared_ptr<PixelShader> pShader) { _pixelShader = pShader; }
	void SetInputLayout(shared_ptr<InputLayout> layout) { _inputLayout = layout; }

};

