#pragma once
#include <dxgi1_2.h>
#include <wincodec.h>
#include <dxtk/ScreenGrab.h>
#include <dxtk/WICTextureLoader.h>

class Utils
{
public:
	static bool StartsWith(std::string str, std::string comp);
	static bool StartsWith(std::wstring str, std::wstring comp);

	static std::wstring ToWString(std::string value);
	static std::string ToString(std::wstring value);

	static void ScreenShot(ComPtr<ID3D11DeviceContext> context, const wstring& fileName);
};