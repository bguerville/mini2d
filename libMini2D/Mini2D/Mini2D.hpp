/*
 * Mini2D.hpp
 *
 *  Created on: November 4th, 2016
 *  Author: Daniel Gerendasy
 */

#ifndef MINI2D_HPP_
#define MINI2D_HPP_

#include <io/pad.h>							// Pad functions
#include <sys/time.h>							// For FPS / deltaTime calculation


class Mini2D {
public:
	typedef enum _padChangedInfo_t {
		UNCHANGED = 						0,
		BTN_CHANGED_LEFT = 					1 << 0,
		BTN_CHANGED_RIGHT = 				1 << 1,
		BTN_CHANGED_UP = 					1 << 2,
		BTN_CHANGED_DOWN = 					1 << 3,
		BTN_CHANGED_R1 = 					1 << 4,
		BTN_CHANGED_L1 = 					1 << 5,
		BTN_CHANGED_R2 = 					1 << 6,
		BTN_CHANGED_L2 = 					1 << 7,
		BTN_CHANGED_CROSS = 				1 << 8,
		BTN_CHANGED_SQUARE = 				1 << 9,
		BTN_CHANGED_TRIANGLE = 				1 << 10,
		BTN_CHANGED_CIRCLE = 				1 << 11,
		BTN_CHANGED_START = 				1 << 12,
		BTN_CHANGED_SELECT = 				1 << 13,
		BTN_CHANGED_L3 = 					1 << 14,
		BTN_CHANGED_R3 = 					1 << 15,
		ANA_CHANGED_R_H =					1 << 16,
		ANA_CHANGED_R_V	=					1 << 17,
		ANA_CHANGED_L_H	=					1 << 18,
		ANA_CHANGED_L_V	=					1 << 19,

		// groups
		DPAD_CHANGED =						0x0000F,
		TRIGGER_CHANGED =					0x000F0,
		SYMBOLS_CHANGED = 					0x00F00,
		START_SELECT_R3_L3_CHANGED = 		0x0F000,
		ANA_CHANGED =						0xF0000,
	} PadChangedInfo;

	/*
	 * PadCallback_f: 
	 * 		Callback when pad updates or changes
	 * 
	 * int:
	 * 		What has changed (if any). Perform an AND operation with Mini2D::PadChangedInfo enum elements
	 * int:
	 *		Pad port
	 * padData:
	 * 		The pad data
	 */
	typedef void (*PadCallback_f) (int, int, padData);

	/* 
	 * DrawCallback_f:
	 * 		Callback when on draw (user should insert draw logic here)
	 * 
	 * float:
	 * 		Delta time. Amount of time passed since last frame
	 * unsigned int:
	 * 		Frame.
	 * 
	 * Return:
	 * 		If return is less than 0 the draw loop stops
	 */
	typedef int (*DrawCallback_f) (float, unsigned int);

	/*
	 * ExitCallback_f:
	 * 		Callback when program exits
	 */
	typedef void (*ExitCallback_f) ();

	// Constructor
	Mini2D(Mini2D::PadCallback_f pCallback, Mini2D::DrawCallback_f dCallback, Mini2D::ExitCallback_f eCallback);
	virtual ~Mini2D();

	/*
	 * BeginDrawLoop:
	 * 		Begins the draw loop. Loops endlessly until your DrawCallback_f function returns a value less than 0
	 */
	void BeginDrawLoop();

	/*
	 * Pad:
	 *		Process all connected controllers and pass information to _padCallback
	 */
	void Pad();

	/*
	 * SetAnalogDeadzone:
	 * 		Set the deadzone Pad() uses to detect whether the analog sticks have changed
	 * 
	 * deadzone:
	 * 		The unsigned 8-bit deadzone
	 */
	void SetAnalogDeadzone(unsigned char deadzone);

	/*
	 * SetClearColor:
	 * 		Sets the clear color used to flush the display buffers every frame
	 * 
	 * color:
	 * 		ARGB color
	 */
	void SetClearColor(unsigned int color);

	/*
	 * SetAlphaState:
	 * 		Enable or disable alpha testing
	 * 
	 * enable:
	 * 		True to enable alpha blending
	 */
	void SetAlphaState(bool enable);

	/*
	 * ResetTexturePointer:
	 *		Resets texture pointer. Used to pop the entire texture heap
	 */
	void ResetTexturePointer();

	/*
	 * AddTexture:
	 *		Copy raw ARGB pixel data into RSX
	 * 
	 * pixelData:
	 * 		Pointer to an array of ARGB values
	 * pitch:
	 * 		Number of bytes per row
	 * height:
	 * 		Height of the texture
	 * 
	 * Return:
	 * 		Texture offset in RSX (do not directly access this offset)
	 */
	unsigned int AddTexture(void * pixelData, int pitch, int height);

	/*
	 * DrawTexture:
	 * 		Draws the texture onto the currect frame
	 * 
	 * textureOff:
	 * 		RSX offset to texture
	 * pitch:
	 * 		Number of bytes per row
	 * width
	 * 		Width of image
	 * height:
	 * 		Height of image
	 * x:
	 * 		X coordinate (0 - 1)
	 * y:
	 * 		Y coordinate (0 - 1)
	 * w:
	 * 		New width (0 - 1)
	 * h:
	 * 		New height (0 - 1)
	 * rgba:
	 * 		RGBA color
	 * angle:
	 * 		Angle to rotate image (radians)
	 */
	void DrawTexture(u32 textureOff, int pitch, int width, int height, float x, float y, float w, float h, unsigned int rgba, float angle);


private:
	PadCallback_f _padCallback;
	DrawCallback_f _drawCallback;

	unsigned int _clearColor;				// Value to clear screen to on every draw
	int _alphaEnabled;						// Whether alpha testing is enabled

	//time_t _lastTime;						// Time of last frame
	unsigned int _maxFrameCount;			// Max value of _frameCount before reset. Value is divisible by 10
	unsigned int _frameCount;				// Number of frames drawn, resets on _maxFrameCount

	padData _padData[MAX_PORT_NUM];			// Pad data
	unsigned short _analogDeadzone;			// Deadzone of analog sticks

	void * _textureMem;						// Pointer to vram
	u32 * _texturePointer;					// Active pointer to unused texture vram


	// Draw texture with rotation
	void DrawSpriteRot(float x, float y, float layer, float dx, float dy, u32 rgba, float angle);
};

#endif /* MINI2D_HPP_ */