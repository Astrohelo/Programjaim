#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <time.h>
#include <string.h>
#include "debugmalloc.h"
#include "Jatek.h"
#include "scorekiir.h"
#include "kigyomozgasa.h"
#include "iranykezeles.h"


/* ez a fuggveny hivodik meg az idozito altal.
 * betesz a feldolgozando esemenyek koze (push) egy felhasznaloi esemenyt */
Uint32 idozit(Uint32 ms, void *param) {
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;   /* ujabb varakozas */
}

Narancs narancsgeneral(Narancs narancs,Kigyo *kigyofej,Kigyo *kigyofej2,int palyateteje){
    narancs.x= (rand()%20+1)*40-20;
    narancs.y= (rand()%20+1)*40-20;
    Kigyo *ideiglenes=kigyofej;
    Kigyo *futo=kigyofej2;
    while(ideiglenes!=NULL){
        while(futo!=NULL){
                if (narancs.x==futo->x&&narancs.y==futo->y){
                narancs.x= (rand()%20+1)*40-20;
                narancs.y= (rand()%20+1)*40-20;
                ideiglenes=kigyofej;
                futo=kigyofej2;

                }
                else if(narancs.y<palyateteje){
                        narancs.y= (rand()%20+1)*40-20;
                        ideiglenes=kigyofej;
                        futo=kigyofej2;
                }
                else{
                    futo=futo->kov;
                }

                }
        if (narancs.x==ideiglenes->x&&narancs.y==ideiglenes->y){
                narancs.x= (rand()%20+1)*40-20;
                narancs.y= (rand()%20+1)*40-20;
                ideiglenes=kigyofej;
                futo=kigyofej2;

        }
        else if(narancs.y<palyateteje){
                narancs.y= (rand()%20+1)*40-20;
                ideiglenes=kigyofej;
                futo=kigyofej2;
        }
        else{
            ideiglenes=ideiglenes->kov;
        }
    }
    return narancs;
}

void felszabadit_kigyo(Kigyo *kigyofej){
    Kigyo *ideiglenes=kigyofej;
    Kigyo *eltuntet=kigyofej;
    while(ideiglenes!=NULL){
        ideiglenes=ideiglenes->kov;
        free(eltuntet);
        eltuntet=ideiglenes;
    }
}


bool jatek(int ABLAK,SDL_Renderer *renderer,bool ketjatekos) {
    srand(time(0));
    int scoretomb[10]={0};
    beolvas(scoretomb,10);
    int palyateteje=79;
    boxRGBA(renderer, 0, 0, ABLAK, ABLAK, 0, 0, 0, 255);
    SDL_RenderPresent(renderer);
    lineRGBA(renderer, 0, 79, 800, 79, 244, 0, 0, 222); ///pálya választó csik
    lineRGBA(renderer, 400, 0, 400, 79, 244, 0, 0, 222); ///a 2 player pontszamat elvalaszto csik
    stringRGBA(renderer, 5, 20, "Player1: ", 0, 0, 255, 255);
    /// idozito
    SDL_TimerID id = SDL_AddTimer(100, idozit, NULL);

    int pont1=0;
    char spont1[5];
    int vx,vy;

    Kigyo *utolso=(Kigyo*)malloc(sizeof(Kigyo));
    utolso->x = 420;
    utolso->y = 180;
    utolso->r= 20;
    utolso->kov=NULL;

    Kigyo *kigyofej=(Kigyo*) malloc(sizeof(Kigyo));
    kigyofej->x = 420;
    kigyofej->y = 220;
    kigyofej->r= 20;
    kigyofej->kov=utolso;

    Iranyom *iranyeleje=(Iranyom*)malloc(sizeof(Iranyom));
    iranyeleje->megy=le;
    iranyeleje->kov=NULL;

    int pont2=0;
    char spont2[5];
    int vx2,vy2;
    Kigyo *utolso2=(Kigyo*)malloc(sizeof(Kigyo));
    utolso2->x = 220;
    utolso2->y = 380;
    utolso2->r= 20;
    utolso2->kov=NULL;

    Kigyo *kigyofej2=(Kigyo*) malloc(sizeof(Kigyo));
    kigyofej2->x = 220;
    kigyofej2->y = 420;
    kigyofej2->r= 20;
    kigyofej2->kov=utolso2;

    Narancs narancs = {.x = 0, .y = 0, .r = 10};
    narancs=narancsgeneral(narancs,kigyofej,kigyofej2,palyateteje);

    Iranyom *iranyeleje2=(Iranyom*)malloc(sizeof(Iranyom));
    iranyeleje2->megy=fel;
    iranyeleje2->kov=NULL;
    bool quit1=false;
    bool quit2=false;
    bool quit = false;
    if (ketjatekos==false){
        quit2=true;
    }
    else
        stringRGBA(renderer, 405, 20, "Player2: ", 255, 0, 0, 255);
    /* szokasos esemenyhurok */
    while (!quit) {

        SDL_Event event;
        SDL_WaitEvent(&event);

        switch (event.type) {

            case SDL_USEREVENT:

                /// kitoroljuk az utolso elem poziciojat
                filledCircleRGBA(renderer, utolso->x, utolso->y, utolso->r, 0, 0, 0, 255);
                filledCircleRGBA(renderer, utolso2->x, utolso2->y, utolso2->r, 0, 0, 0, 255);

                leptet(kigyofej,pont1);
                leptet(kigyofej2,pont2);
                iranyeleje=kiad(iranyeleje);
                iranyeleje2=kiad(iranyeleje2);
                if (iranyeleje->megy==balra){       ///Csekkoljuk mindketto kigyo iranyat
                    vx=-40;
                    vy=0;
                    }
                else if (iranyeleje->megy==jobbra){
                    vx=40;
                    vy=0;
                }
                else if (iranyeleje->megy==fel){
                    vx=0;
                    vy=-40;
                }
                else{
                    vx=0;
                    vy=40;
                }
                if (iranyeleje2->megy==balra){
                    vx2=-40;
                    vy2=0;
                        }
                else if (iranyeleje2->megy==jobbra){
                    vx2=40;
                    vy2=0;
                }
                else if (iranyeleje2->megy==fel){
                    vx2=0;
                    vy2=-40;
                }
                else{
                    vx2=0;
                    vy2=40;
                }
                if (quit1==false){
                    mozog(kigyofej,iranyeleje,ABLAK,vx,vy,palyateteje);    ///kigyo lep
                }
                if (quit2==false){
                    mozog(kigyofej2,iranyeleje2,ABLAK,vx2,vy2,palyateteje);
                }
                quit1=utkozik(kigyofej,kigyofej2);    ///utkozott-e?
                quit2=utkozik(kigyofej2,kigyofej);
                if(quit1==true){
                    torol(renderer,kigyofej);
                }
                if(quit2==true){
                    torol(renderer,kigyofej2);
                }

                if (quit1==true && quit2==true){
                    quit=true;
                }

                if (kigyofej->x==narancs.x && kigyofej->y==narancs.y){      ///kigyo pontot szerez,uj narancs
                    narancs=narancsgeneral(narancs,kigyofej,kigyofej2,palyateteje);
                    pont1++;
                    utolso=kigyono(kigyofej);
                }
                if (kigyofej2->x==narancs.x && kigyofej2->y==narancs.y){      ///kigyo2 pontot szerez,uj narancs
                    narancs=narancsgeneral(narancs,kigyofej,kigyofej2,palyateteje);
                    pont2++;
                    utolso2=kigyono(kigyofej2);
                }
                if (pont1+pont2==10){     ///gyorsitja a kepfrissitest
                    SDL_RemoveTimer(id);
                    id = SDL_AddTimer(80, idozit, NULL);
                }
                if(pont1+pont2==30){
                    SDL_RemoveTimer(id);
                    id = SDL_AddTimer(60, idozit, NULL);
                }

                filledCircleRGBA(renderer, narancs.x, narancs.y, narancs.r, 255,170,0, 255);
                itoa(pont1, spont1, 10);
                itoa(pont2, spont2, 10);
                boxRGBA(renderer, 84, 10, 120, 30, 0, 0, 0, 255);
                stringRGBA(renderer, 100, 20, spont1, 0, 0, 255, 255);
                if (ketjatekos==true){
                    boxRGBA(renderer, 484, 10, 520, 30, 0, 0, 0, 255);
                    stringRGBA(renderer, 500, 20, spont2, 255, 0, 0, 255);
                }
                kirajzol(renderer,kigyofej,0,0,255,255);
                kirajzol(renderer,kigyofej2,255,0,0,255);
                SDL_RenderPresent(renderer);
                break;
            case SDL_KEYDOWN:       ///A gombok lenyomasara az ahhoz hozzarendelt iranyt atadom a FIFO-ba (first in first out)
                switch (event.key.keysym.sym) {
                    case SDLK_a:
                            bevesz(iranyeleje,balra);
                        break;
                    case SDLK_d:
                            bevesz(iranyeleje,jobbra);
                        break;
                    case SDLK_w:
                            bevesz(iranyeleje,fel);
                        break;
                    case SDLK_s:
                            bevesz(iranyeleje,le);
                        break;
                    case SDLK_LEFT:
                            bevesz(iranyeleje2,balra);
                        break;
                    case SDLK_RIGHT:
                            bevesz(iranyeleje2,jobbra);
                        break;
                    case SDLK_UP:
                            bevesz(iranyeleje2,fel);
                        break;
                    case SDLK_DOWN:
                            bevesz(iranyeleje2,le);
                        break;
                }
                break;

            case SDL_QUIT:
                quit = true;
                break;

            default:
                break;
    }
    }
    beleir(scoretomb,10,pont1);
    beleir(scoretomb,10,pont2);
    felszabadit_kigyo(kigyofej);
    felszabadit_irany(iranyeleje);
    felszabadit_kigyo(kigyofej2);
    felszabadit_irany(iranyeleje2);
    /* idozito torlese */
    SDL_RemoveTimer(id);
    return true;
}
