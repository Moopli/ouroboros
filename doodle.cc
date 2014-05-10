#include <iostream>
#include "SDL/SDL.h"
#include <cmath>

Uint32 getPixel32( SDL_Surface *surface, int x, int y )
{
    //Convert the pixels to 32 bit
    Uint32 *pixels = (Uint32 *)surface->pixels;

    //Get the requested pixel
    return pixels[ ( y * surface->w ) + x ];
}
Uint32 rgb2Px(int r, int g, int b)
{
    return ((((((255 << 8) + r) << 8) + g) << 8) + b);
}
void putPixel32( SDL_Surface *surface, int x, int y, Uint32 pixel )
{
    if (x < 0 || x >= surface->w || y < 0 || y >= surface->h) return;
    //Convert the pixels to 32 bit
    Uint32 *pixels = (Uint32 *)surface->pixels;

    //Set the pixel
    pixels[ ( y * surface->w ) + x ] = pixel;
}

void drawLine( SDL_Surface *surface, float x1, float y1, float x2, float y2, Uint32 color )
{
    // Bresenham's line algorithm
    const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
    if(steep)
    {
        std::swap(x1, y1);
        std::swap(x2, y2);
    }

    if(x1 > x2)
    {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    const float dx = x2 - x1;
    const float dy = fabs(y2 - y1);

    float error = dx / 2.0f;
    const int ystep = (y1 < y2) ? 1 : -1;
    int y = (int)y1;

    const int maxX = (int)x2;

    for(int x=fmax((int)x1,0); x<maxX; x++)
    {
        if(steep)
        {
            putPixel32(surface, y,x, color);
        }
        else
        {
                putPixel32(surface, x,y, color);
        }

        error -= dy;
        if(error < 0)
        {
            y += ystep;
            error += dx;
        }
    }
}
