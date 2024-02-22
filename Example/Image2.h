#pragma once
#include <SDL.h> // Using SDL
//for rotating coin
class Image2
{

public:
	Image2();
	Image2(const char* path, SDL_Renderer* renderer);
	Image2(const char* path, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b);
	void generateTexture();
	void close();
	void draw();
	void draw(SDL_Renderer* renderer, SDL_Rect dst, SDL_Rect src);
	int getWidth();
	int getHeight();
	int getAlpha();

	void setPath(const char* p);
	void setColorKey(SDL_Color c);  // NO_TRANSPARENT_BG | {r,g,b,255}
	void setRenderer(SDL_Renderer* r);
	void setSrcRegion(SDL_Rect s);
	void setDstRegion(SDL_Rect d);
	void setAlpha(int a);

private:
	char* path;
	SDL_Texture* texture;
	int width;
	int height;
	int alpha;
	SDL_Color colorKey;
	SDL_Renderer* renderer;

	SDL_Rect srcRegion;
	SDL_Rect dstRegion;
};

