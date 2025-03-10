#ifndef LINE_H
#define LINE_H

#include <SDL2/SDL.h>

#define MAX_LINE_COUNT 100
#define PALETTE_SIZE 5

typedef struct {
    Uint8 r, g, b;
} Color;

typedef struct {
    int x1, y1, x2, y2;
    Color color;
} Line;

void draw_line(SDL_Renderer* renderer, Line line);
void draw_rectangle(SDL_Renderer* renderer, Line line);

#endif
