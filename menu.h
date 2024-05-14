#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <SDL.h>
#include <SDL_ttf.h>

using namespace std;
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

class EngineMenu {
public:
    EngineMenu(SDL_Renderer *windowsplashFontRenderer, SDL_Window *window) {
        TTF_Init();
        splashFontRenderer = windowsplashFontRenderer;
        windowScreen = window;
        splashScreenTextBlink = 0;
        SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    }

    void initSplashScreen(const char *displayName, const char *gameName, const char *fontFamily, const char *backgroundImg = NULL) {
        gameTitle = gameName; // Lưu trữ tên trò chơi
        splashText = displayName;
        prepareSplashScreen(fontFamily, backgroundImg);
    }

    void displaySplashScreen() {
        renderSplashScreen();
    }

    void quitSplashScreen() {
        destroySplashScreen();
    }

private:
    SDL_Window *windowScreen;
    SDL_Renderer *splashFontRenderer, *splashImageRenderer;
    SDL_Texture *splashFontTexture, *splashImageTexture;
    SDL_Surface *splashFontSurface;

    TTF_Font *splashFont;
    const char *splashText;

    int windowHeight, windowWidth, splashScreenTextBlink;

    std::string gameTitle; // Thêm biến gameTitle

    void prepareSplashScreen(const char *fontFamily, const char *backgroundImg) {
        splashFont = TTF_OpenFont(fontFamily, 25);

        if (backgroundImg != NULL) {
            splashImageRenderer = SDL_CreateRenderer(windowScreen, -1, 0);
            SDL_Surface *splashBackgroundSurface = SDL_LoadBMP(backgroundImg);
            splashImageTexture = SDL_CreateTextureFromSurface(splashFontRenderer, splashBackgroundSurface);
        }
    }

    void renderSplashScreenText() {
        int textWidth = 0;
        int textHeight = 0;

        SDL_Color color = {255, 255, 255};

        // Vẽ tên trò chơi trước
        SDL_Surface* gameTitleSurface = TTF_RenderText_Solid(splashFont, gameTitle.c_str(), color);
        SDL_Texture* gameTitleTexture = SDL_CreateTextureFromSurface(splashFontRenderer, gameTitleSurface);
        SDL_QueryTexture(gameTitleTexture, NULL, NULL, &textWidth, &textHeight);
        const int devideScreenWidth = windowWidth / 2;
        const int deviceText = textWidth / 2;
        const int dediceScreenHeight = windowHeight / 2;
        SDL_Rect gameTitleRect = {devideScreenWidth - (textWidth / 2), dediceScreenHeight - textHeight - 10, textWidth, textHeight};
        SDL_RenderCopy(splashFontRenderer, gameTitleTexture, NULL, &gameTitleRect);
        SDL_DestroyTexture(gameTitleTexture);
        SDL_FreeSurface(gameTitleSurface);

        // Vẽ dòng chữ "Press Enter to start"
        splashFontSurface = TTF_RenderText_Solid(splashFont, splashText, color);
        splashFontTexture = SDL_CreateTextureFromSurface(splashFontRenderer, splashFontSurface);

        splashScreenTextBlink++;
        if (splashScreenTextBlink == 100) {
            splashScreenTextBlink = 0;
        }

        if (splashScreenTextBlink < 50) {
            SDL_QueryTexture(splashFontTexture, NULL, NULL, &textWidth, &textHeight);
            const int devideScreenWidth = windowWidth / 2;
            const int deviceText = textWidth / 2;
            const int dediceScreenHeight = windowHeight / 2;
            SDL_Rect fontStruct = {devideScreenWidth - deviceText, dediceScreenHeight, textWidth, textHeight};
            SDL_RenderCopy(splashFontRenderer, splashFontTexture, NULL, &fontStruct);
        } else {
            splashFontTexture = NULL;
            splashFontSurface = NULL;
        }
    }


    void renderSplashScreen() {
        renderSplashScreenText();
    }

    void destroySplashScreen() {
        SDL_DestroyTexture(splashFontTexture);
        SDL_FreeSurface(splashFontSurface);
    }
};



#endif // MENU_H_INCLUDED
