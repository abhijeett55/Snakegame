#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width, const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }

    sdl_window = SDL_CreateWindow("Snake Game",
                                  screen_width,
                                  screen_height,
                                  SDL_WINDOW_RESIZABLE);
    if (sdl_window == nullptr) {
        std::cerr << "Window could not be created.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }

    sdl_renderer = SDL_CreateRenderer(sdl_window, nullptr);
    if (sdl_renderer == nullptr) {
        std::cerr << "Renderer could not be created.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(sdl_renderer);
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
}

void Renderer::Render(Snake const &snake, SDL_Point const &food) {
    SDL_FRect block;
    block.w = static_cast<float>(screen_width) / grid_width;
    block.h = static_cast<float>(screen_height) / grid_height;

    // Clear screen (dark gray)
    SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
    SDL_RenderClear(sdl_renderer);

    // Draw food (yellow)
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
    block.x = static_cast<float>(food.x) * block.w;
    block.y = static_cast<float>(food.y) * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);

    // Draw snake body (white)
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    for (SDL_Point const &point : snake.body) {
        block.x = static_cast<float>(point.x) * block.w;
        block.y = static_cast<float>(point.y) * block.h;
        SDL_RenderFillRect(sdl_renderer, &block);
    }

    // Draw snake head (bigger, blue if alive, red if dead)
    block.x = snake.head_x * block.w;
    block.y = snake.head_y * block.h;
    block.w *= 1.2f;  // make head 20% bigger
    block.h *= 1.2f;

    if (snake.alive) {
        SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
    } else {
        SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
    }
    SDL_RenderFillRect(sdl_renderer, &block);

    // Present everything
    SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
    std::string title = "Snake Score: " + std::to_string(score) + " | FPS: " + std::to_string(fps);
    SDL_SetWindowTitle(sdl_window, title.c_str());
}
