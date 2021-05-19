#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdbool.h>
#include <stdlib.h>
#include "debugmalloc.h"
#include "Jatek.h"
#include "scorekiir.h"
#include "kigyomozgasa.h"


void sdl_init(int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_Window *window = SDL_CreateWindow("SDL peldaprogram", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szeles, magas, 0);
    if (window == NULL) {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(1);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }
    SDL_RenderClear(renderer);

    *pwindow = window;
    *prenderer = renderer;

}



int main(int argc, char *argv[]) {
    SDL_Window *window;
    SDL_Renderer *renderer;
    sdl_init(800, 800, &window, &renderer);

    bool quit = false;
    int egerx=0;
    int egery=0;
    bool vege=true;
    int scoretomb[10]={0};

    while (!quit) {

        SDL_Event event;
        SDL_WaitEvent(&event);
                if (vege==true){    ///Ha kilepett a jatekos valamelyik modbol akkor a menut megrajzolja, illetve amikor elindul
                    boxRGBA(renderer, 0, 0, 800, 800, 0, 0, 0, 255);
                    SDL_RenderPresent(renderer);
                    boxRGBA(renderer,300,100,500,200, 0, 0, 255, 255);
                    stringRGBA(renderer, 340, 150, "Egy szemelyes", 0x00, 0xC0, 0x00, 0xFF);
                    boxRGBA(renderer,300,300,500,400, 0, 0, 255, 255);
                    stringRGBA(renderer, 340, 350, "Ket szemelyes", 0x00, 0xC0, 0x00, 0xFF);
                    boxRGBA(renderer,300,500,500,600, 0, 0, 255, 255);
                    stringRGBA(renderer, 340, 550, "Dicsoseglista", 0x00, 0xC0, 0x00, 0xFF);
                    SDL_RenderPresent(renderer);
                    vege=false;
                }

        switch (event.type) {
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    egerx= event.button.x;
                    egery= event.button.y;
                    if (300<=egerx && egerx<=500 && 100<= egery && egery<=200){ ///egyjatekosba lep ha azt bezarja az felhasznalo vagy meghal a kigyo akkor újra a menü jelenik meg
                        vege=jatek(800,renderer,false);
                    }
                    else if (300<=egerx && egerx<=500 && 300<= egery && egery<=400){ ///ketjatekosba lep ha azt bezarja az felhasznalo vagy meghalnak a kigyok akkor újra a menü jelenik meg
                        vege=jatek(800,renderer,true);
                    }
                    else if (300<=egerx && egerx<=500 && 500<= egery && egery<=600){ ///scoreboardba lep ha azt bezarja az felhasznalo akkor újra a menü jelenik meg
                        vege=pontszamok(800,renderer);
                }
                }
                break;

            case SDL_QUIT:
                quit = true;
                break;
        }
    }

 SDL_Quit();

    return 0;
}
