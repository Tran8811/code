#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include <SDL.h>

class EngineWindow {

    public:
        SDL_Window *mainWindow = NULL;
        SDL_Surface *screenSurface = NULL;
        SDL_Renderer *renderer = NULL;

        void createWindow(const char *windowTitle, const int width, const int height){
            mainWindow = SDL_CreateWindow(windowTitle, 10, 10, width, height, SDL_WINDOW_SHOWN);
            renderer = SDL_CreateRenderer(mainWindow, -1, 0);
            screenSurface = SDL_GetWindowSurface(mainWindow);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        }

        void destroyWindow(){
            SDL_UpdateWindowSurface(mainWindow);
            SDL_DestroyWindow(mainWindow);
            SDL_Quit();
        }


};

#endif // WINDOW_H_INCLUDED
