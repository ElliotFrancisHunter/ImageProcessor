#pragma once
#include <gdiplusheaders.h>
#include <gdipluseffects.h>
#include <filesystem>

// Perhaps have a struct that contains all the item info such as the dimension etc - EH


class ImageManager
{
private:

	const std::string mSourcePath = "/Source/";
	const std::string mDestPath = "/Destination/";

	std::vector<std::string> mFileNames;
	std::vector<Gdiplus::Image*> mImages; // Contains image objects derived from filenames - EH

protected:
	ImageManager();
public:
	// Needs a method to get all files from a folder
	void ExtractFiles();
	// Needs a method to convert jpgs to pngs(Use the Image::Save method, perhaps create a method of keeping the same file name but changing extension to png.
	void SaveAsPNG(const std::vector<Gdiplus::Image*>& images);
	// With Image::Save you can literally write a new PNG image by typing imageName.png and it'll do it for you
	// Rotate method using Image::RotateFlip
	void RotateImage(std::vector<Gdiplus::Image*> images);
	// For Greyscale you can create a Gdiplus::ColorMatrix and apply the matrix to Gdiplus::ImageAttributes
	void ApplyGreyScale(std::vector<Gdiplus::Image*> images);
	// To adjust brightness, add a constant to the rgb fields within each image 
	// ensuring they don't go below zero or above the maximum bit depth
	// (Once again, gdi plus has a BrightnessContrast Class
	void BrightenImage(std::vector<Gdiplus::Image*> images);

	void LinearScaleImage(std::vector<Gdiplus::Image*> images);

	int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
};

