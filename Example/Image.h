#pragma once
#include <SDL.h> // Using SDL

class Image
{
	public:		
		Image();
		Image(const char* path, SDL_Renderer* renderer);		
		Image(const char* path, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b);
		void set(const char* path, SDL_Renderer* renderer);
		void set(const char* path, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b);
		void close();		
		void setSrcRegion(SDL_Rect s);
		void setDstRegion(SDL_Rect d);
		void setAlpha(int a);
		void draw(SDL_Renderer* renderer, SDL_Rect dst, SDL_Rect src);
		int getWidth();
		int getHeight();
		int getAlpha();

	private:
		char path[100];
		SDL_Texture* texture;
		SDL_Rect srcRegion;
		SDL_Rect dstRegion;
		int width;
		int height;
		int alpha;
};

