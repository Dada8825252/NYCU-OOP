#include "Image2.h"
#include "SDL_image.h" 
#include <stdio.h>
#include <SDL.h> // Using SDL
#include <string.h>
#include "constants.h"


Image2::Image2()
{
	
}

Image2::Image2(const char* path, SDL_Renderer* renderer)
{
	setPath(path);
	setColorKey(NO_TRANSPARENT_BG);
	setRenderer(renderer);
	

	generateTexture();
}

Image2::Image2(const char* path, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b)
{
	setPath(path);
	setColorKey({ r, g, b, 255 });
	setRenderer(renderer);
	

	generateTexture();
}void Image2::generateTexture()
{
	// Load a surface from a PNG file.	
	SDL_Surface* imgSurface = IMG_Load(path);
	if (imgSurface == NULL)
	{
		// Call IMG_GetError to get the error string.
		printf("SDL_LoadBMP failed: %s\n", IMG_GetError());
		exit(0);
	}
	else
	{
		if (colorKey.a == 255)
		{
			// Set the color key (transparent pixel) in a surface.		
			SDL_SetColorKey(imgSurface, true, SDL_MapRGB(imgSurface->format, colorKey.r, colorKey.g, colorKey.b));
		}

		// Create texture from surface pixels	
		texture = SDL_CreateTextureFromSurface(renderer, imgSurface);

		// Also, you can use IMG_LoadTexture() to replace IMG_Load and SDL_CreateTextureFromSurface
		// texture = IMG_LoadTexture(renderer, path);

		if (texture == NULL)
		{
			printf("SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
		}

		width = imgSurface->w;
		height = imgSurface->h;

		// Get rid of old loaded surface
		SDL_FreeSurface(imgSurface);
	}
}



void Image2::close()
{
	// Free loaded image	
	SDL_DestroyTexture(texture);
}

void Image2::draw()
{
	SDL_Rect* d = &dstRegion, * s = &srcRegion;

	if (dstRegion.x == ALLREGION)
	{
		d = NULL;
	}
	if (srcRegion.x == ALLREGION)
	{
		s = NULL;
	}
	
	//加入透明度調整
	if (SDL_SetTextureAlphaMod(texture, alpha) == -1)
	{
		printf("SDL_SetTextureAlphaMod failed: %s\n", SDL_GetError());
		return;
	}

	SDL_RenderCopy(renderer, texture, s, d);
}

void Image2::draw(SDL_Renderer* renderer, SDL_Rect dst, SDL_Rect src)
{
	setSrcRegion(src);
	setDstRegion(dst);

	draw();
}

int Image2::getWidth()
{
	return width;
}

int Image2::getHeight()
{
	return height;
}

void Image2::setPath(const char* p)
{
	path = new char[strlen(p)];
	strcpy_s(path, strlen(p) + 1, p);
}

void Image2::setColorKey(SDL_Color c)
{
	colorKey = c;
}

void Image2::setRenderer(SDL_Renderer* r)
{
	renderer = r;
}

void Image2::setSrcRegion(SDL_Rect s)
{
	srcRegion = s;
}

void Image2::setDstRegion(SDL_Rect d)
{
	dstRegion = d;
}
void Image2::setAlpha(int a)
{
	alpha = a;
}
int Image2::getAlpha()
{
	return alpha;
}
