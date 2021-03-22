#include "stdafx.h"
#include "ImageManager.h"

ImageManager::ImageManager()
{
	


}

/// <summary>
///		
/// </summary>
void ImageManager::ExtractFiles()
{
	for (const auto& file : std::filesystem::directory_iterator(mSourcePath))
	{
		std::cout << file.path() << std::endl;
		mFileNames.push_back(file.path().string());
		mImages.push_back(Gdiplus::Image::FromFile(file.path().filename().wstring().c_str()));
	}
}

/// <summary>
/// 
/// </summary>
/// <param name="images"></param>
void ImageManager::SaveAsPNG(const std::vector<Gdiplus::Image*>& images)
{
	Gdiplus::GdiplusStartupInput input;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &input, NULL);

	CLSID encoderClsid;
	Gdiplus::Status stat;
	int result;
	WCHAR strGuid[39];

	GetEncoderClsid(L"image/png", &encoderClsid);

	int imgCount = 1;

	for (const auto& image : images)
	{
		std::wstring convFileName = std::wstring(imgCount + L".png");;
		image->Save(convFileName.c_str(), &encoderClsid, NULL);
		++imgCount;
	}
}

/// <summary>
/// 
/// </summary>
/// <param name="images"></param>
void ImageManager::RotateImage(std::vector<Gdiplus::Image*> images)
{
	for (const auto& image : images)
	{
		image->RotateFlip(Gdiplus::Rotate90FlipNone);
	}
}


/// <summary>
/// 
/// </summary>
/// <param name="format"></param>
/// <param name="pClsid"></param>
/// <returns></returns>
int ImageManager::GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	UINT  encoderCount = 0;          // number of image encoders
	UINT  encoderArrSize = 0;         // size of the image encoder array in bytes

	Gdiplus::ImageCodecInfo* pImageCodecInfo = NULL;

	Gdiplus::GetImageEncodersSize(&encoderCount, &encoderArrSize);

	if (encoderArrSize == 0)
	{
		return -1;  // Failure
	}

	pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(encoderArrSize));

	if (pImageCodecInfo == NULL)
	{
		return -1;  // Failure
	}

	GetImageEncoders(encoderCount, encoderArrSize, pImageCodecInfo);

	for (UINT j = 0; j < encoderCount; ++j)
	{
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;  // Success
		}
	}

	free(pImageCodecInfo);
	return -1;  // Failure
}
