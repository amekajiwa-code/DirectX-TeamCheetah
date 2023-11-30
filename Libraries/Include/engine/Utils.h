#pragma once
#include <dxgi1_2.h>
#include <wincodec.h>
#include <dxtk/ScreenGrab.h>
#include <dxtk/WICTextureLoader.h>

class Utils
{
public:
	static bool StartsWith(string str, string comp);
	static bool StartsWith(wstring str, wstring comp);

	static wstring ToWString(string value);
	static string ToString(wstring value);

	static void ScreenShot(ComPtr<ID3D11DeviceContext> context, const wstring& fileName = L"");
};