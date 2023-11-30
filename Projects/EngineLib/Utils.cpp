#include "pch.h"
#include "Utils.h"

bool Utils::StartsWith(string str, string comp)
{
	wstring::size_type index = str.find(comp);
	if (index != wstring::npos && index == 0)
		return true;

	return false;
}

bool Utils::StartsWith(wstring str, wstring comp)
{
	wstring::size_type index = str.find(comp);
	if (index != wstring::npos && index == 0)
		return true;

	return false;
}

std::wstring Utils::ToWString(string value)
{
	return wstring(value.begin(), value.end());
}

std::string Utils::ToString(wstring value)
{
	return string(value.begin(), value.end());
}

void Utils::ScreenShot(ComPtr<ID3D11DeviceContext> context, const wstring& fileName)
{
	HRESULT hr;
	ComPtr<ID3D11Texture2D> backbuffer;
	hr = GRAPHICS()->GetSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)backbuffer.GetAddressOf());
	CHECK(hr);

	wstring path = DATA_ADDR_SCREENSHOT;
	if (!fileName.empty())
	{
		path += fileName;
		path += L".png";
	}
	else
	{
		tm lt = MANAGER_TIME()->GetLocalTimeInfo()._tm;
		wstring lstring;
		lstring += L"£¯";
		lstring += ::to_wstring(lt.tm_year);
		lstring += L"£¯";
		lstring += ::to_wstring(lt.tm_mon);
		lstring += L"£¯";
		lstring += ::to_wstring(lt.tm_mday);
		lstring += L"£¯";
		lstring += ::to_wstring(lt.tm_hour);
		lstring += L"£¯";
		lstring += ::to_wstring(lt.tm_min);
		lstring += L"£¯";
		lstring += ::to_wstring(lt.tm_sec);
		lstring += L"£¯.png";

		path += lstring;
	}
	hr = DirectX::SaveWICTextureToFile(context.Get(), backbuffer.Get(), GUID_ContainerFormatPng, path.c_str());
	CHECK(hr);
}


