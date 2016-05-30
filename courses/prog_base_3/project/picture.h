#ifndef PICTURE_H_INCLUDED
#define PICTURE_H_INCLUDED

#include <SFML/Graphics.hpp>

//SFML: CLASS OF SPRITE
class Picture {
	float imgX;	//appear coordinate X
	float imgY;	//appear coordinate Y
	float imgHeight; //height of img
	float imgWidth;	//width of image
	sf::String File;	//name of file with img
	sf::Image image;	//image
	sf::Texture texture;	//texture
public:
	sf::Sprite sprite;	//sprite

	Picture();
	// imageFileName - must be stored in images/ folder
	Picture(sf::String imageFileName, float imgX, float imgY, float imgWidth, float imgHeight);

};

#endif // PICTURE_H_INCLUDED
