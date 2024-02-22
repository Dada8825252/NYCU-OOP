#include "Image.h"
#include "SDL_image.h"
#include "constants.h"
#include <stdio.h>
#include<string.h>
#include <SDL.h> // Using SDL

Image::Image()
{
}

Image::Image(const char* path, SDL_Renderer* renderer)
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

Image::Image(const char* path, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b)
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
		// Set the color key (transparent pixel) in a surface.		
		SDL_SetColorKey(imgSurface, true, SDL_MapRGB(imgSurface->format, r, g, b));

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
		//setRenderer(renderer);

		// Get rid of old loaded surface
		SDL_FreeSurface(imgSurface);
	}
}

void Image::set(const char* path, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b)
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
		// Set the color key (transparent pixel) in a surface.		
		SDL_SetColorKey(imgSurface, true, SDL_MapRGB(imgSurface->format, r, g, b));
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

void Image::set(const char* path, SDL_Renderer* renderer)
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
		// Set the color key (transparent pixel) in a surface.		
		//SDL_SetColorKey(imgSurface, true, SDL_MapRGB(imgSurface->format, r, g, b));

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

void Image::close()
{
	// Free loaded image	
	SDL_DestroyTexture(texture);
}

void Image::draw(SDL_Renderer* renderer, SDL_Rect dst, SDL_Rect src)
{
	setSrcRegion(src);
	setDstRegion(dst);
	SDL_Rect* d = &dstRegion, * s = &srcRegion;

	if (dst.x == ALLREGION)
	{
		d = NULL;
	}
	if (src.x == ALLREGION)
	{
		s = NULL;
	}
	if (SDL_SetTextureAlphaMod(texture, alpha) == -1)
	{
		printf("SDL_SetTextureAlphaMod failed: %s\n", SDL_GetError());
		return;
	}
	SDL_RenderCopy(renderer, texture, s, d);
}
/*void Image::draw()
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


	// Set and enable standard alpha blending mode for a texture
	// https://wiki.libsdl.org/SDL_SetTextureBlendMode
	// https://wiki.libsdl.org/SDL_BlendMode
	if (SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND) == -1)
	{
		printf("SDL_SetTextureBlendMode failed: %s\n", SDL_GetError());
		return;
	}

	// Modulate texture alpha
	// https://wiki.libsdl.org/SDL_SetTextureAlphaMod
	/*if (SDL_SetTextureAlphaMod(texture, alpha) == -1)
	{
		printf("SDL_SetTextureAlphaMod failed: %s\n", SDL_GetError());
		return;
	}*/

	// Copy a portion of the texture to the current rendering target, 
	// optionally rotating it by angle around the given center and also flipping it top-bottom and/or left-right.
	// if center is NULL, rotation will be done around dstrect.w / 2, dstrect.h / 2
	// https://wiki.libsdl.org/SDL_RenderCopyEx
	// https://wiki.libsdl.org/SDL_RendererFlip
//	SDL_RenderCopyEx(renderer, texture, s, d, angle, &center, flip);
	//SDL_RenderCopy(renderer, texture, s, d);
//}
/*void Image::draw(SDL_Renderer* renderer, SDL_Rect dst, SDL_Rect src, SDL_Point center, double angle, SDL_RendererFlip flip)
{
	setSrcRegion(src);
	setDstRegion(dst);
	setCenterAngle(center, angle);
	setFlip(flip);
	draw();
}*/
void Image::setSrcRegion(SDL_Rect s)
{
	srcRegion = s;
}

void Image::setDstRegion(SDL_Rect d)
{
	dstRegion = d;
}
/*void Image::setRenderer(SDL_Renderer* r)
{
	renderer = r;
}
void Image::setCenterAngle(SDL_Point c, double a)
{
	center = c;
	angle = a;
}
void Image::setFlip(SDL_RendererFlip f)
{
	flip = f;
}*/
int Image::getWidth()
{
	return width;
}

int Image::getHeight()
{
	return height;
}
void Image::setAlpha(int a)
{
	alpha = a;
}
int Image::getAlpha()
{
	return alpha;
}