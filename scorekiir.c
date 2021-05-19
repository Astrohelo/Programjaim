#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "debugmalloc.h"
#include "scorekiir.h"

void beolvas(int *tomb,int meret){
    FILE *fp=fopen("scoreboard.txt","r");
    for (int i=0; i<meret; i++){
        fscanf(fp, "%d", &tomb[i]);
        }
    fclose(fp);
}

void beleir(int *tomb,int meret,int pont){
    FILE *fp=fopen("scoreboard.txt","w");
    for (int i=0; i<meret; i++){
        if (tomb[i]<pont){
            for(int j=meret-1; j>i; j--){
                tomb[j]=tomb[j-1];
            }
            tomb[i]=pont;
            break;
        }
    }
    for (int i=0; i<meret; i++){
        fprintf(fp, "%d\n",tomb[i]);
    }
    fclose(fp);
}

bool pontszamok(int ABLAK,SDL_Renderer *renderer) {
    boxRGBA(renderer, 0, 0, ABLAK, ABLAK, 0, 0, 0, 255);
    SDL_RenderPresent(renderer);
    stringRGBA(renderer, ABLAK/2-80, 40, "A legjobb pontszamok:", 255, 255, 255, 255);
    bool quit=false;
    int scoretomb[10]={0};
    beolvas(scoretomb,10);
    for (int i=0; i<10; i++){
        char szoveg[10];
        itoa(scoretomb[i],szoveg,10);
        stringRGBA(renderer, ABLAK/2-20, 80+i*20, szoveg, 255, 255, 255, 255);
    }
    while (!quit) {
    SDL_RenderPresent(renderer);
    SDL_Event event;
    SDL_WaitEvent(&event);
    switch (event.type){
        case SDL_QUIT:
                quit=true;
                break;
    }
    }

    return true;
}
