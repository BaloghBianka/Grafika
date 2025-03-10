#include <SDL2/SDL.h>
#include <stdio.h>
#include "line.h"

#define WIDTH 800
#define HEIGHT 600
#define PALETTE_X 10
#define PALETTE_Y 10
#define PALETTE_SPACING 50

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Line Drawer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Line lines[MAX_LINE_COUNT];
    int line_count = 0;
    int is_drawing = 0;
    Line temp_line = {0, 0, 0, 0, {255, 255, 255}};

    Color palette[PALETTE_SIZE] = {
        {255, 0, 0},   
        {0, 255, 0},   
        {0, 0, 255},   
        {255, 255, 0}, 
        {255, 255, 255} 
    };
    int selected_color = 0;
    int draw_mode = 0; 

    SDL_Event event;
    int running = 1;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_t) {
                    draw_mode = !draw_mode; 
                }
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouse_x = event.button.x;
                int mouse_y = event.button.y;

                
                for (int i = 0; i < PALETTE_SIZE; i++) {
                    if (mouse_x >= PALETTE_X + i * PALETTE_SPACING &&
                        mouse_x <= PALETTE_X + i * PALETTE_SPACING + 40 &&
                        mouse_y >= PALETTE_Y &&
                        mouse_y <= PALETTE_Y + 40) {
                        selected_color = i;
                    }
                }

                if (is_drawing == 0) {
                    temp_line.x1 = mouse_x;
                    temp_line.y1 = mouse_y;
                    temp_line.color = palette[selected_color];
                    is_drawing = 1;
                } else {
                    temp_line.x2 = mouse_x;
                    temp_line.y2 = mouse_y;
                    if (line_count < MAX_LINE_COUNT) {
                        lines[line_count++] = temp_line;
                    }
                    is_drawing = 0;
                }
            } else if (event.type == SDL_MOUSEMOTION) {
                printf("Mouse position: (%d, %d)\n", event.motion.x, event.motion.y);
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

       
        for (int i = 0; i < PALETTE_SIZE; i++) {
            SDL_Rect rect = {PALETTE_X + i * PALETTE_SPACING, PALETTE_Y, 40, 40};
            SDL_SetRenderDrawColor(renderer, palette[i].r, palette[i].g, palette[i].b, 255);
            SDL_RenderFillRect(renderer, &rect);
        }

       
        for (int i = 0; i < line_count; i++) {
            if (draw_mode == 0) {
                draw_line(renderer, lines[i]);
            } else {
                draw_rectangle(renderer, lines[i]);
            }
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
