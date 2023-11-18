#pragma once
class InputLayout
{
private:
	ComPtr<ID3D11Device>		_device;
	ComPtr<ID3D11InputLayout>	_inputLayout;
public:
	InputLayout();
	InputLayout(ComPtr<ID3D11Device> device);
	~InputLayout();
public:
	ComPtr<ID3D11InputLayout> GetLayout() { return _inputLayout; }
public:
	void CreateInputLayout(const vector<D3D11_INPUT_ELEMENT_DESC>& descs, ComPtr<ID3DBlob> blob);
};

