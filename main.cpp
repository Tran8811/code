#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
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

    // Load textures for mouse and cheese images
    SDL_Texture* mouseTexture = graphics.loadTexture("C:\\Users\\Admin\\Desktop\\img\\mouseleftframe1.png");
    SDL_Texture* cheeseTexture = graphics.loadTexture("C:\\Users\\Admin\\Desktop\\img\\cheese.png");
    if (mouseTexture == nullptr || cheeseTexture == nullptr) {
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
    bool quit = false;
    SDL_Event event;
    while (!quit && !gameOver(mouse)) {
        graphics.prepareScene();
        graphics.renderTexture(backgroundTexture, 0, 0);
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = true;
        }

        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

        if (currentKeyStates[SDL_SCANCODE_UP]) mouse.turnNorth();
        if (currentKeyStates[SDL_SCANCODE_DOWN]) mouse.turnSouth();
        if (currentKeyStates[SDL_SCANCODE_LEFT]) mouse.turnWest();
        if (currentKeyStates[SDL_SCANCODE_RIGHT]) mouse.turnEast();

        mouse.move();
        if (mouse.canEat(cheese)) mouse.grow();

        // Render mouse and cheese textures on screen
        graphics.renderTexture(mouseTexture, mouse.rect.x, mouse.rect.y);
        graphics.renderTexture(cheeseTexture, cheese.rect.x, cheese.rect.y);

        graphics.presentScene();
        SDL_Delay(10);
    }

    // Free textures
    SDL_DestroyTexture(mouseTexture);
    SDL_DestroyTexture(cheeseTexture);
    SDL_DestroyTexture(backgroundTexture);
    graphics.quit();
    return 0;
}
