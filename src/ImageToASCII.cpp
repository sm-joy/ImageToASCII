//#define STB_IMAGE_WRITE_IMPLEMENTATION // for saving any image
//#include"../include/stb_image_write.h"
#define STB_IMAGE_IMPLEMENTATION
#include"../include/stb_image.h"
#include<iostream>
//#include<cmath> //needed for the std::pow


int main()
{
	const char* ascii  = ".,-:;=!*#@";
	float ts[10] = {0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f};

	const char* imagePath = "../testImages/tiger.jpeg";
	int width, height, channels;
	unsigned char* image = stbi_load(imagePath, &width, &height, &channels, STBI_rgb);

	if(!image) return -1;
	
	unsigned char* grayImage = new unsigned char[width*height];
	for(int y = 0; y < height; y++)
	{
		for(int x = 0; x < width; x++)
		{
			int i = (y * width + x) * channels;
			float s = 0;
			//doesnt work for some reason and im too lazy to fix it
			//int r = image[i+0];
			//int g = image[i+1];
			//int b = image[i+2];
			//Convert RGB to Linear Space
			//float rL = (float)r / 255;
			//float gL = (float)g / 255;
			//float bL = (float)b / 255;

			//Apply Luminance Weights
			//s = (0.2126 *rL + 0.7152 * gL + 0.0722 * bL);

			//Convert Grayscale to Gamma Space
			//if(s > 0.0031308) s *= 12.92;
			//else s = 1.055 * std::pow(s, (1.0f/2.4f)) - 0.055;

			//works and its very simple

			s = 0.299f * image[i+0] + 0.587f * image[i+1] + 0.114f * image[i+2];
			//grayImage[y * width + x] = s; // for maybe saving the grayscalled image or maybe saving the ascii image i dont know
			
			s /= 255; // normalize

			int ci = 0; 
			while(ci < 9 && s > ts[ci]) ci++;
			std::cout<<*(ascii+ci);
	
		}
		std::cout<<"\n";
	}
	
	//for saving any image
	//if(stbi_write_jpg("../testImages/tiger_gray.jpeg", width, height, 1, grayImage, 100)) std::cout<<"Image Saved Successfully!\n";
	//else std::cout<<"Unsuccessful!\n";

	delete [] grayImage;
	stbi_image_free(image);

	std::cin.get();

	return 0;
}



//wrokds but a problem arrised 
//the even with small images it wont fit in my terminal how to fix it
//for now just set your font size less then 5 it will work, its a feature not a bug
