#include "picture.h"

using namespace sf;

Picture::Picture() {
	File = "shadowOfNothing.png";
	image.loadFromFile("images/" + File);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	imgWidth = 286;
	imgHeight = 395;
	imgX = 0;
	imgY = 0;
	sprite.setTextureRect(IntRect(0, 0, (int)imgWidth, (int)imgHeight));
}

// imageFileName - must be stored in images/ folder
Picture::Picture(String imageFileName, float imgX, float imgY, float imgWidth, float imgHeight) {
	File = imageFileName;
	image.loadFromFile("images/" + File);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	this->imgWidth = imgWidth;
	this->imgHeight = imgHeight;
	this->imgX = imgX;
	this->imgY = imgY;
	sprite.setTextureRect(IntRect(0, 0, (int)imgWidth, (int)imgHeight));
}