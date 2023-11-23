#include "pch.h"
#include "InputLayout.h"

InputLayout::InputLayout()
{
	_device = GRAPHICS()->GetDevice();
}

InputLayout::InputLayout(ComPtr<ID3D11Device> device)
{
	_device = device;
}

InputLayout::~InputLayout()
{
}

void InputLayout::CreateInputLayout(const vector<D3D11_INPUT_ELEMENT_DESC>& descs, ComPtr<ID3DBlob> blob)
{
	HRESULT hr;
	const int32 count = static_cast<int32>(descs.size());

	hr = _device->CreateInputLayout(
		descs.data(),
		count,
		blob->GetBufferPointer(),
		blob->GetBufferSize(),
		_inputLayout.GetAddressOf()
	);

	//CHECK(hr);
}
