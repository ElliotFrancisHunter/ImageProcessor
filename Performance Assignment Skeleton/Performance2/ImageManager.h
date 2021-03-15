#pragma once
#include <gdiplusheaders.h>
#include <gdipluseffects.h>
#include <filesystem>

// Perhaps have a struct that contains all the item info such as the dimension etc

class ImageManager
{
private:
	// Needs a vector of strings for the file names
	// Needs a vector of Images that is populated from said file names
protected:

public:
	// Needs a method to get all files from a folder
	// Needs a method to create image objects(Can use the Image::FromFile method)
	// Needs a method to convert jpgs to pngs(Use the Image::Save method, perhaps create a method of keeping the same file name but changing extension to png.
	// With Image::Save you can literally write a new PNG image by typing imageName.png and it'll do it for you
	// Rotate method using Image::RotateFlip
	// For Greyscale you can create a Gdiplus::ColorMatrix and apply the matrix to Gdiplus::ImageAttributes
	// To adjust brightness, add a constant to the rgb fields within each image ensuring they don't go below zero or above the maximum bit depth(Once again, gdi plus has a BrightnessContrast Class
};

