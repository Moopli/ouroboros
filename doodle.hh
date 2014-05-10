#ifndef DOODLE_HH_INCLUDED
#define DOODLE_HH_INCLUDED

Uint32 get_pixel32( SDL_Surface *surface, int x, int y );
void put_pixel32( SDL_Surface *surface, int x, int y, Uint32 pixel );
void drawLine(SDL_Surface *surface, float x1, float y1, float x2, float y2, Uint32 color );
Uint32 rgb2Px(int r, int g, int b);

#endif // DOODLE_HH_INCLUDED
