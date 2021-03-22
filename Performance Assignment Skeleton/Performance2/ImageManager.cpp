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