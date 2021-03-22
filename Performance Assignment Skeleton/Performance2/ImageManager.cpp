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
