#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "graphics.h"
#include "defs.h"
#include <string>
// Hàm này sẽ hiển thị điểm lên màn hình
void renderScore(const Graphics& graphics, TTF_Font* font, int score) {
    SDL_Color textColor = {255, 255, 255}; // Màu của văn bản

    // Tạo một chuỗi string từ điểm
    std::string scoreText = "Score: " + std::__cxx11::to_string(score);

    // Render văn bản vào một SDL_Surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);
    if (textSurface == nullptr) {
        std::cerr << "Failed to render text surface. SDL_ttf Error: " << TTF_GetError() << std::endl;
        return;
    }

    // Tạo texture từ SDL_Surface
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(graphics.renderer, textSurface);
    if (textTexture == nullptr) {
        std::cerr << "Failed to create texture from text surface. SDL Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(textSurface);
        return;
    }

    // Hiển thị texture lên màn hình
    SDL_Rect textRect = {10, 10, textSurface->w, textSurface->h}; // Vị trí và kích thước của văn bản
    SDL_RenderCopy(graphics.renderer, textTexture, NULL, &textRect);

    // Giải phóng bộ nhớ
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

#endif // SCORE_H_INCLUDED
