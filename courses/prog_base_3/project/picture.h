#ifndef PICTURE_H_INCLUDED
#define PICTURE_H_INCLUDED

#include <SFML/Graphics.hpp>

//SFML: CLASS OF SPRITE
class Picture {
	float imgX;
	float imgY;
	float imgHeight;
	float imgWidth;
	sf::String File;
	sf::Image image;
	sf::Texture texture;
public:
	sf::Sprite sprite;

	Picture();
	// imageFileName - must be stored in images/ folder
	Picture(sf::String imageFileName, float imgX, float imgY, float imgWidth, float imgHeight);

};

#endif // PICTURE_H_INCLUDED
