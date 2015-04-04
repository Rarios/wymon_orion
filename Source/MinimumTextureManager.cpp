#include <iostream>
#include <cstdlib>
#include <array>
#include <string>
#include "Sprite.hpp"

int main(int argC, char** argV) {

	std::array<wo::gfx::Sprite, 10> SpriteArray;
	std::array<std::string, 10> StringArray({"a", "b", "c", "d", "e", "f", "g", "h", "i", "j"});

	// Load textures into manager and put them into sprites.
	for (int i = 0; i < SpriteArray.size(); ++i) {
	
		if (!wo::gfx::TextureManager::loadFromFile("Resources/background.jpg", StringArray[i])) {
		
			std::cerr << "Could not load file!";
		
		}

		SpriteArray[i].setTexture(wo::gfx::TextureManager::getTexture(StringArray[i]));
	
	}

	return EXIT_SUCCESS;

}
