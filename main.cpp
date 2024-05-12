#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "graphics.h"
#include "defs.h"
#include "game.h"
#include "score.h"
#include<fstream>
using namespace std;

int main(int argc, char *argv[]) {
    // Khởi tạo SDL và SDL_ttf
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    Graphics graphics;
    if (!graphics.init()) {
        cerr << "Failed to initialize graphics." << endl;
        return 1;
    }

    // Load font
    TTF_Font* font = TTF_OpenFont("C:\\Users\\Admin\\Downloads\\PixelGosub-ZaRz.ttf", 28);
    if (font == nullptr) {
        cerr << "Failed to load font. SDL_ttf Error: " << TTF_GetError() << endl;
        graphics.quit();
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Load textures for cheese images
    SDL_Texture* cheeseTexture = graphics.loadTexture("C:\\Users\\Admin\\Desktop\\img\\cheese.png");
    if (cheeseTexture == nullptr) {
        cerr << "Failed to load textures." << endl;
        graphics.quit();
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    int currentDirection = 0; // 0: phải, 1: trái, 2: lên, 3: xuống

    Mouse mouse(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    Cheese cheese(100, 100);
    SDL_Texture* backgroundTexture = graphics.loadTexture("C:\\Users\\Admin\\Desktop\\img\\background.png");
    if (backgroundTexture == nullptr) {
        cerr << "Failed to load background texture." << endl;
        graphics.quit();
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    int score = 0; // Biến để lưu điểm
    int highestScore = 0; // Biến để lưu điểm cao nhất
    ifstream inFile("highestscore.txt");
    if (inFile.is_open()) {
        inFile >> highestScore;
        inFile.close();
    }

    bool quit = false;
    SDL_Event event;
    while (!quit && !gameOver(mouse)) {
        graphics.prepareScene();
        graphics.renderTexture(backgroundTexture, 0, 0);
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = true;
        }

        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

        if (currentKeyStates[SDL_SCANCODE_UP]) {
            mouse.turnNorth();
            currentDirection = 2; // Thay đổi hướng lên
        }
        if (currentKeyStates[SDL_SCANCODE_DOWN]) {
            mouse.turnSouth();
            currentDirection = 3; // Thay đổi hướng xuống
        }
        if (currentKeyStates[SDL_SCANCODE_LEFT]) {
            mouse.turnWest();
            currentDirection = 1; // Thay đổi hướng trái
        }
        if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
            mouse.turnEast();
            currentDirection = 0; // Thay đổi hướng phải
        }

        // Load texture cho con chuột tương ứng với hướng mới
        std::string mouseTexturePath;
        switch (currentDirection) {
            case 0:
                mouseTexturePath = "C:\\Users\\Admin\\Desktop\\img\\mouserightframe1.png";
                break;
            case 1:
                mouseTexturePath = "C:\\Users\\Admin\\Desktop\\img\\mouseleftframe1.png";
                break;
            case 2:
                mouseTexturePath = "C:\\Users\\Admin\\Desktop\\img\\mouseupframe1.png";
                break;
            case 3:
                mouseTexturePath = "C:\\Users\\Admin\\Desktop\\img\\mousedownframe1.png";
                break;
        }
        SDL_Texture* mouseTexture = graphics.loadTexture(mouseTexturePath.c_str());

        mouse.move();
        if (mouse.canEat(cheese)){
            mouse.grow();
            cheese.respawn();
            //cheese.updatePosition();
            score++; // Tăng điểm khi ăn phô mai
            if (score > highestScore) {
                highestScore = score; // Cập nhật điểm cao nhất nếu điểm hiện tại vượt qua điểm cao nhất
                // Lưu điểm cao nhất vào tập tin
                ofstream outFile("highestscore.txt");
                if (outFile.is_open()) {
                    outFile << highestScore;
                    outFile.close();
                }
            }
        }

        // Render mouse and cheese textures on screen
        graphics.renderTexture(mouseTexture, mouse.rect.x, mouse.rect.y);
        graphics.renderTexture(cheeseTexture, cheese.rect.x, cheese.rect.y);

        // Hiển thị điểm và điểm cao nhất
        renderScore(graphics, font, score, highestScore);

        // Free texture của con chuột
        SDL_DestroyTexture(mouseTexture);

        graphics.presentScene();
        SDL_Delay(10);
    }

    // Giải phóng bộ nhớ và thoát
    SDL_DestroyTexture(cheeseTexture);
    SDL_DestroyTexture(backgroundTexture);
    TTF_CloseFont(font);
    TTF_Quit();
    graphics.quit();
    SDL_Quit();
    return 0;
}


