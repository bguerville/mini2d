#include <stdio.h>
#include <io/pad.h>

#include <Mini2D/Mini2D.hpp>
#include <Mini2D/Font.hpp>

#include "comfortaa_regular_ttf.h"

int drawUpdate(float deltaTime, unsigned int frame);
void padUpdate(int changed, int port, padData pData);
void exit();

Mini2D mini((Mini2D::PadCallback_f)&padUpdate, (Mini2D::DrawCallback_f)&drawUpdate, (Mini2D::ExitCallback_f)&exit);

int doExit = 0;
Font *font1;

const Vector2 FONT_SMALL(0.03*mini.MAXW, 0.03*mini.MAXH);

const Vector2 PRINT_TOPLEFT(0,0);
const Vector2 PRINT_CENTER(0.5*mini.MAXW, 0.5*mini.MAXH);
const Vector2 PRINT_BOTTOMRIGHT(mini.MAXW, mini.MAXH);

int main(s32 argc, const char* argv[]) {
	font1 = new Font(&mini);
	if (font1->Load((void*)comfortaa_regular_ttf, comfortaa_regular_ttf_size))
		printf("error loading font\n");

	mini.SetAnalogDeadzone(15);
	mini.SetClearColor(0xFFFFFFFF);
	mini.SetAlphaState(1);
	mini.BeginDrawLoop();

	return 0;
}

int drawUpdate(float deltaTime, unsigned int frame) {
	font1->Print((char*)"Left align.", PRINT_TOPLEFT, FONT_SMALL);	
	font1->Print((char*)"Right align.", PRINT_BOTTOMRIGHT, FONT_SMALL, 0x000000FF, Font::PRINT_ALIGN_BOTTOMRIGHT);	
	font1->Print((char*)"Center.", PRINT_CENTER, FONT_SMALL, 0x000000FF, Font::PRINT_ALIGN_CENTER);
	
	return doExit;
}

void padUpdate(int changed, int port, padData pData) {
	if (pData.BTN_START && changed & Mini2D::BTN_CHANGED_START)
		doExit = -1;
}

void exit() {
	printf("exiting\n");
}
