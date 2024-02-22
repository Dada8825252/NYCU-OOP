#include "Text.h"
#include <stdio.h>
#include <SDL.h> // Using SDL
#include <string.h>
#include "constants.h"
#include<iostream>
using namespace std;

// The extension library SDL_ttf allows you to create images from 
// TrueType fonts which we'll use here to create textures from font text.
// https://github.com/libsdl-org/SDL_ttf  
// https://github.com/libsdl-org/SDL_ttf/releases/
// https://www.libsdl.org/projects/docs/SDL_ttf/SDL_ttf_toc.html#SEC_Contents
// Using truetype font
#include "SDL_ttf.h"


Text::Text()
{
}

// A structure that represents a color.
// https://wiki.libsdl.org/SDL_Color

Text::Text(const char* str, const char* fontPath, int fontSize, int style, SDL_Color fgColor, int textType, SDL_Color bgColor, SDL_Renderer* renderer, SDL_Point pos, SDL_Point center, double angle, SDL_RendererFlip flip, int alpha)
{
	setString(str);
	setFontPath(fontPath);
	setFontSize(fontSize);
	setStyle(style);
	setFgColor(fgColor);
	setTextType(textType);
	setBgColor(bgColor);
	setRenderer(renderer);

	generateTexture();

	setPos(pos);
	setCenterAngle(center, angle);
	setFlip(flip);
	setAlpha(alpha);
}

void Text::generateTexture()
{
	// TTF Font sturct	
	// https://www.libsdl.org/projects/docs/SDL_ttf/SDL_ttf_49.html#SEC49
	TTF_Font* ttfFont = NULL;

	// Open the font	
	// https://www.libsdl.org/projects/docs/SDL_ttf/SDL_ttf_14.html#SEC14
	ttfFont = TTF_OpenFont(fontPath, fontSize); //("../fonts/lazy.ttf", 28);	
	if (ttfFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		exit(0);
	}


	// Set style of font including TTF_STYLE_BOLD | TTF_STYLE_ITALIC | TTF_STYLE_UNDERLINE | TTF_STYLE_NORMAL
	// https://www.libsdl.org/projects/docs/SDL_ttf/SDL_ttf_22.html#SEC22	
	TTF_SetFontStyle(ttfFont, style);

	// Render text surface
	// The way SDL_ttf works is that you create a new image from a font and color. 
	// We're going to be loading our image from text rendered by SDL_ttf instead of a file.

	SDL_Surface* surface = NULL;

	// Creates a solid/shaded/blended color surface from the font, text, and color given.
	// https://www.libsdl.org/projects/docs/SDL_ttf/SDL_ttf_35.html
	if (textType == SOLID)
	{
		// Quick and Dirty
		surface = TTF_RenderText_Solid(ttfFont, str, fgColor);
	}
	else if (textType == SHADED)
	{
		// Slow and Nice, but with a Solid Box
		surface = TTF_RenderText_Shaded(ttfFont, str, fgColor, bgColor);
	}

	else if (textType == BLENDED)
	{
		// Slow Slow Slow, but Ultra Nice over another image
		surface = TTF_RenderUTF8_Blended(ttfFont, str, fgColor);


	}

	// Free font
	// https://www.libsdl.org/projects/docs/SDL_ttf/SDL_ttf_18.html#SEC18
	TTF_CloseFont(ttfFont);

	if (surface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		exit(0);
	}
	else
	{
		// Create texture from surface pixels
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (texture == NULL)
		{
			printf("SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
			exit(0);
		}

		//Get text dimensions and information
		width = surface->w;
		height = surface->h;

		// Get rid of old loaded surface
		SDL_FreeSurface(surface);
	}
}

void Text::close()
{
	// Free loaded image	
	SDL_DestroyTexture(texture);
}

void Text::draw()
{
	SDL_Rect d;
	d.x = pos.x;
	d.y = pos.y;
	d.w = width;
	d.h = height;


	// Set and enable standard alpha blending mode for a texture	
	if (SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND) == -1)
	{
		printf("SDL_SetTextureBlendMode failed: %s\n", SDL_GetError());
		return;
	}

	// Modulate texture alpha	
	if (SDL_SetTextureAlphaMod(texture, alpha) == -1)
	{
		printf("SDL_SetTextureAlphaMod failed: %s\n", SDL_GetError());
		return;
	}

	// Copy a portion of the texture to the current rendering target, 
	// optionally rotating it by angle around the given center and also flipping it top-bottom and/or left-right.
	// if center is NULL, rotation will be done around dstrect.w / 2, dstrect.h / 2	
	SDL_RenderCopyEx(renderer, texture, NULL, &d, angle, &center, flip);
}
void Text::draw2(SDL_Renderer* renderer, SDL_Point pos, SDL_Point center, double angle, SDL_RendererFlip flip, int alpha) { //for money only
	setPos(pos);
	setCenterAngle(center, angle);
	setFlip(flip);
	setAlpha(alpha);
	setWidth(28);
	setHeight(35);
	draw();
}

void Text::draw(SDL_Renderer* renderer, SDL_Point pos, SDL_Point center, double angle, SDL_RendererFlip flip, int alpha)
{
	setPos(pos);
	setCenterAngle(center, angle);
	setFlip(flip);
	setAlpha(alpha);

	draw();
}

int Text::getWidth()
{
	return width;
}

int Text::getHeight()
{
	return height;
}

char* Text::getString()
{
	return str;
}

int Text::getAlpha() {
	return alpha;
}

void Text::addpoints() {
	if (strlen(str) == 1) {
		if (str[0] < '9') {
			str[0] += 1;
			cout << str << endl;
		}
		else {
			strcpy_s(str, 3, "10");
		}
	}
	else if (strlen(str) == 2) {
		if (str[1] < '9') {
			str[1] += 1;
		}
		else {
			str[0] += 1;
			str[1] = '0';
		}
	}
	printf("%ld\n",strlen(str));
}
void Text::setString(const char* s)
{
	SDL_DestroyTexture(texture);
	str = new char[strlen(s)];
	strcpy_s(str, strlen(s) + 1, s);
}

void Text::setFontPath(const char* f)
{
	fontPath = new char[strlen(f)];
	strcpy_s(fontPath, strlen(f) + 1, f);
}

void Text::setFontSize(int s)
{
	fontSize = s;
}

void Text::setStyle(int s)
{
	style = s;
}

void Text::setFgColor(SDL_Color fc)
{
	fgColor = fc;
}

void Text::setTextType(int t)
{
	textType = t;
}

void Text::setBgColor(SDL_Color bc)
{
	bgColor = bc;
}

void Text::setRenderer(SDL_Renderer* r)
{
	renderer = r;
}

void Text::setPos(SDL_Point p)
{
	pos = p;
}


void Text::setCenterAngle(SDL_Point c, double a)
{
	center = c;
	angle = a;
}

void Text::setFlip(SDL_RendererFlip f)
{
	flip = f;
}

void Text::setAlpha(int a)
{
	alpha = a;
}
Uint32 Text::changeData(Uint32 interval, void* param)
{
	Text* t = (Text*)param;
	if (t != 0)
	{
		if (t->alpha-10 >= 0) {
			t->alpha -= 10;
		}
		else {
			t->alpha = 0;
		}
		return interval;
	}
	else
		return 0;
	
}
void Text::startTimer(Uint32 t)
{
	time = t;
	/*if (flyormove) //move
		timerID = SDL_AddTimer(time, changeData, this);
	else //fly*/
	timerID = SDL_AddTimer(time, changeData, this);

}
void Text::stopTimer() {
	time = 0;
}
int Text::getX() {
	return pos.x;
}
int Text::getY() {
	return pos.y;
}
void Text::setWidth(int w) {
	width = w;
}
void Text::setHeight(int h) {
	height = h;
}
void Text::buysth() {
	if (strlen(str) == 1) {
		if (str[0] < '9' && str[0] >= '3') {
			str[0] -= 3;
			//	cout << str << endl;
		}
	}
	else if (strlen(str) == 2) {
		if (str[0] < '3') {
			char* s = new char[2];
			s[0] = str[0];
			s[1] = '\0';
			if (str[1] == '1') {
				strcpy_s(str, 2, s);
			}
			else {
				str[1] -= 1;
			}
			str[0] += 7;
		}
		else {
			str[0] -= 3;
		}
	}
}

int Text::getmoney() {
	int money = 0;
	if (strlen(str) == 1) {
		money = str[0] - '0';
	}
	else if (strlen(str) == 2) {
		money = (str[1] - '0') * 10 + (str[0] - '0');
	}
	return money;
}