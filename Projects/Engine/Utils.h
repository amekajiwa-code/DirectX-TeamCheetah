#pragma once
#include <dxgi1_2.h>
#include <wincodec.h>
#include <dxtk/ScreenGrab.h>
#include <dxtk/WICTextureLoader.h>

namespace Utils
{
	static void ScreenShot(ComPtr<ID3D11DeviceContext> context, const wstring& fileName = L"")
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
}