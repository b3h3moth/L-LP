#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

/* Lo scopo del programma e' di creare una finestra - window - con una
superficie rettangolare */

int main(int argc, char *argv[]) {
    const int scr_width = 320;
    const int scr_height = 400;
    // La finestra
    SDL_Window *window = NULL;
    // Superficie 2D
    SDL_Surface *surface = NULL;
    
    // Inizializzazione della libreria SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Err. Cannot initialize SDL: %s\n", SDL_GetError());
    } else {
        window = SDL_CreateWindow("Take a Walk on The Wild Side",   \
                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,     \
                scr_width, scr_height, SDL_WINDOW_SHOWN);

        if (window == NULL)
            fprintf(stderr, "Err. Could not create window: %s\n", SDL_GetError());
        else {
            // Creazione della superficie della finestra
            surface = SDL_GetWindowSurface(window);

            /* Riempie la superficie, un rettangolo, con specifici parametri:
            - SDL surface;
            - la superficie, il rettangolo, da riempire;
            - il colore con cui riempiere il rettangolo, in questo caso rosso.
            */
            SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 0, 0));

            // Update della superficie
            SDL_UpdateWindowSurface(window);
        }
    }

    // Pausa di 5000 millisecondi (5 secondi)
    SDL_Delay(5000);

    // Distrugge la finestra
    SDL_DestroyWindow(window);

    // Chiusura della libreria
    SDL_Quit();
    
    return(EXIT_SUCCESS);
}
