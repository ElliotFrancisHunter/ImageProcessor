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
		std::wstring filename = file.path();
		const WCHAR* file = filename.c_str();
		mImages.push_back(Gdiplus::Bitmap::FromFile(file));		
	}
}

/// <summary>
/// 
/// </summary>
/// <param name="images"></param>
void ImageManager::SaveAsPNG()
{
	
	CLSID encoderClsid;
	Gdiplus::Status stat;
	int result;
	WCHAR strGuid[39];

	GetEncoderClsid(L"image/png", &encoderClsid);

	int imgCount = 1;

	for (const auto& image : mImages)
	{
		std::wstring convFileName = std::wstring(L"test.png");;
		stat = image->Save(convFileName.c_str(), &encoderClsid, NULL);
		++imgCount;
	}
}

/// <summary>
/// 
/// </summary>
/// <param name="images"></param>
void ImageManager::RotateImage()
{
	for (auto& image : mImages)
	{
		image->RotateFlip(Gdiplus::Rotate90FlipNone);
	}
}

/// <summary>
/// 
/// </summary>
/// <param name="images"></param>
void ImageManager::ApplyGreyScale()
{
	for (auto& image : mImages)
	{
		UINT width = image->GetWidth();
		UINT height = image->GetHeight();
		Gdiplus::Color pixColour;
		for (int x = 0; x < width; ++x)
		{
			for (int y = 0; y < height; ++y)
			{
				image->GetPixel(x, y, &pixColour);
				UINT grey = pixColour.GetRed() + pixColour.GetGreen() + pixColour.GetBlue();
				grey *= 0.3;
				pixColour.SetFromCOLORREF(RGB(grey, grey, grey));
				image->SetPixel(x, y, pixColour);
			}
		}
	}
	std::cout << "finished";
}

/// <summary>
/// 
/// </summary>
/// <param name="images"></param>
void ImageManager::BrightenImage()
{
	for (auto& image : mImages)
	{
		UINT width = image->GetWidth();
		UINT height = image->GetHeight();
		Gdiplus::Color pixColour;
		
		for (int x = 0; x < width; ++x)
		{
			for (int y = 0; y < height; ++y)
			{
				image->GetPixel(x, y, &pixColour);
				UINT bright = pixColour.GetRed() + pixColour.GetGreen() + pixColour.GetBlue();
				bright *= 1.1;
				pixColour.SetFromCOLORREF(RGB(bright, bright, bright));
				image->SetPixel(x, y, pixColour);
			}
		}
	}
}

/// <summary>
/// 
/// </summary>
/// <param name="images"></param>
void ImageManager::LinearScaleImage()
{
	for (auto& image : mImages)
	{		
		Gdiplus::Graphics* graphic = Gdiplus::Graphics::FromImage(image);
		graphic->SetInterpolationMode(Gdiplus::InterpolationMode::InterpolationModeBilinear);
		graphic->ScaleTransform(2,2, Gdiplus::MatrixOrderAppend);		
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
	UINT  encoderCount = 0;           // number of image encoders
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
