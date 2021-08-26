#pragma once
#include <gdiplusheaders.h>
#include <gdipluseffects.h>
#include <filesystem>
#include <vector>

// Perhaps have a struct that contains all the item info such as the dimension etc - EH


class ImageManager
{
private:

	

	std::vector<std::string> mFileNames;
	std::vector<Gdiplus::Bitmap*> mImages; // Contains image objects derived from filenames - EH

protected:
	
public:
	ImageManager();
	// Needs a method to get all files from a folder
	void ExtractFiles();
	// Needs a method to convert jpgs to pngs(Use the Image::Save method, perhaps create a method of keeping the same file name but changing extension to png.
	void SaveAsPNG();
	// With Image::Save you can literally write a new PNG image by typing imageName.png and it'll do it for you
	// Rotate method using Image::RotateFlip
	void RotateImage();
	// For Greyscale you can create a Gdiplus::ColorMatrix and apply the matrix to Gdiplus::ImageAttributes
	void ApplyGreyScale();
	// To adjust brightness, add a constant to the rgb fields within each image 
	// ensuring they don't go below zero or above the maximum bit depth
	// (Once again, gdi plus has a BrightnessContrast Class
	void BrightenImage();

	void LinearScaleImage();

	int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
};

