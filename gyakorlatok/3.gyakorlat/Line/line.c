#include "line.h"

void draw_line(SDL_Renderer* renderer, Line line) {
    SDL_SetRenderDrawColor(renderer, line.color.r, line.color.g, line.color.b, 255);
    SDL_RenderDrawLine(renderer, line.x1, line.y1, line.x2, line.y2);
}

void draw_rectangle(SDL_Renderer* renderer, Line line) {
    SDL_SetRenderDrawColor(renderer, line.color.r, line.color.g, line.color.b, 255);
    SDL_Rect rect = {line.x1, line.y1, line.x2 - line.x1, line.y2 - line.y1};
    SDL_RenderFillRect(renderer, &rect);
}
