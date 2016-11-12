/*
 * Font.hpp
 *
 *  Created on: November 6th, 2016
 *  Author: Daniel Gerendasy
 */

#ifndef FONT_HPP_
#define FONT_HPP_

#include <Mini2D/Mini2D.hpp>				// Class definition
#include <Mini2D/Units.hpp>					// SizeF

class Font {
public:
	typedef enum _fontLoadStatus_t {
		FONT_SUCCESS = 0,
		FONT_INVALID_ARG,
		FONT_INVALID_TTF,
		FONT_LIBRARY_INIT_FAILED,
		FONT_INVALID_MINI2D
	} FontLoadStatus;

	typedef enum _fontPrintAlign_t {
		PRINT_ALIGN_TOPLEFT = 0,
		PRINT_ALIGN_TOPCENTER,
		PRINT_ALIGN_TOPRIGHT,
		PRINT_ALIGN_CENTERLEFT,
		PRINT_ALIGN_CENTER,
		PRINT_ALIGN_CENTERRIGHT,
		PRINT_ALIGN_BOTTOMLEFT,
		PRINT_ALIGN_BOTTOMCENTER,
		PRINT_ALIGN_BOTTOMRIGHT
	} FontPrintAlign;

	// Constructors
	Font(Mini2D * mini);
	virtual ~Font();

	/*
	 * Load:
	 *		Load TTF font
	 * 
	 * filepath:
	 *		Path to TTF
	 * 
	 * Return:
	 * 		Result of load operation
	 */
	FontLoadStatus Load(char * filepath);

	/*
	 * Load:
	 *		Load TTF font
	 * 
	 * buffer:
	 *		Buffer containing TTF font
	 * size:
	 * 		Size of buffer
	 * 
	 * Return:
	 *		Result of load operation
	 */
	FontLoadStatus Load(void * buffer, unsigned int size);

	/*
	 * Print:
	 *		Print a string onto the frame buffer
	 * 
	 * string:
	 *		Buffer containing string to print
	 * location:
	 * 		Where to print text
	 * size:
	 * 		Width and height of each character
	 * rgba:
	 * 		RGBA color
	 * align:
	 * 		Text alignment
	 * layer:
	 *		Z coordinate
	 */
	void Print(char * string, Vector2 location, Vector2 size, unsigned int rgba = 0x000000FF, FontPrintAlign align = PRINT_ALIGN_TOPLEFT, float layer = 0);

private:
	Mini2D * _mini;

	// Load font
	FontLoadStatus loadFont(char * path, void * buffer, int size);
	// Draw character to frame
	float printChar(char c, float x, float y, float z, unsigned int rgba);
	// Get width of string
	float getWidth(char * string);
};

#endif /* FONT_HPP_ */