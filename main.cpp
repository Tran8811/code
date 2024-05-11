
#include "graphics.h"
#include "defs.h"
#include "game.h"

using namespace std;

int main(int argc, char *argv[]) {
    Graphics graphics;
    if (!graphics.init()) {
        cerr << "Failed to initialize graphics." << endl;
        return 1;
    }

    // Load textures for cheese images
    SDL_Texture* cheeseTexture = graphics.loadTexture("C:\\Users\\Admin\\Desktop\\img\\cheese.png");
    if (cheeseTexture == nullptr) {
        cerr << "Failed to load textures." << endl;
        graphics.quit();
        return 1;
    }

    Mouse mouse(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    Cheese cheese(100, 100);
    SDL_Texture* backgroundTexture = graphics.loadTexture("C:\\Users\\Admin\\Desktop\\img\\background.png");
    if (backgroundTexture == nullptr) {
        cerr << "Failed to load background texture." << endl;
        graphics.quit();
        return 1;
    }

    int currentDirection = 0; // 0: phải, 1: trái, 2: lên, 3: xuống

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
                mouseTexturePath = "C:\\Users\\Admin\\Desktop\\img\\mouseleftframe2.png";
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
        }

        // Render mouse and cheese textures on screen
        graphics.renderTexture(mouseTexture, mouse.rect.x, mouse.rect.y);
        graphics.renderTexture(cheeseTexture, cheese.rect.x, cheese.rect.y);

        // Free texture của con chuột
        SDL_DestroyTexture(mouseTexture);

        graphics.presentScene();
        SDL_Delay(10);
    }

    // Free textures
    SDL_DestroyTexture(cheeseTexture);
    SDL_DestroyTexture(backgroundTexture);
    graphics.quit();
    return 0;
}

