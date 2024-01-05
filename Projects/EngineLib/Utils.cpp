#include "pch.h"
#include "Utils.h"

bool Utils::StartsWith(std::string str, std::string comp)
{
	std::wstring::size_type index = str.find(comp);
	if (index != std::wstring::npos && index == 0)
		return true;

	return false;
}

bool Utils::StartsWith(std::wstring str, std::wstring comp)
{
	std::wstring::size_type index = str.find(comp);
	if (index != std::wstring::npos && index == 0)
		return true;

	return false;
}

void Utils::Replace(OUT string& str, string comp, string rep)
{
	string temp = str;

	size_t start_pos = 0;
	while ((start_pos = temp.find(comp, start_pos)) != wstring::npos)
	{
		temp.replace(start_pos, comp.length(), rep);
		start_pos += rep.length();
	}

	str = temp;
}

void Utils::Replace(OUT wstring& str, wstring comp, wstring rep)
{
	wstring temp = str;

	size_t start_pos = 0;
	while ((start_pos = temp.find(comp, start_pos)) != wstring::npos)
	{
		temp.replace(start_pos, comp.length(), rep);
		start_pos += rep.length();
	}

	str = temp;
}

std::wstring Utils::ToWString(std::string value)
{
	return std::wstring(value.begin(), value.end());
}

std::string Utils::ToString(std::wstring value)
{
	return std::string(value.begin(), value.end());
}

void Utils::ScreenShot(ComPtr<ID3D11DeviceContext> context, const std::wstring& fileName)
{
	HRESULT hr;
	ComPtr<ID3D11Texture2D> backbuffer;
	hr = GRAPHICS()->GetSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)backbuffer.GetAddressOf());
	CHECK(hr);

	std::wstring path = DATA_ADDR_SCREENSHOT;
	if (!fileName.empty())
	{
		path += fileName;
		path += L".png";
	}
	else
	{
		tm lt = MANAGER_TIME()->GetLocalTimeInfo()._tm;
		std::wstring lstring = ::to_wstring(lt.tm_year);
		lstring += L"/";
		lstring += ::to_wstring(lt.tm_mon);
		lstring += L"£¯";
		lstring += ::to_wstring(lt.tm_mday);
		lstring += L"£¯";
		lstring += ::to_wstring(lt.tm_hour);
		lstring += L"£¯";
		lstring += ::to_wstring(lt.tm_min);
		lstring += L"£¯";
		lstring += ::to_wstring(lt.tm_sec);
		lstring += L".png";

		path += lstring;
	}
	hr = DirectX::SaveWICTextureToFile(context.Get(), backbuffer.Get(), GUID_ContainerFormatPng, path.c_str());
	CHECK(hr);
}


