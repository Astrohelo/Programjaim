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

void mozog(Kigyo *kigyofej,Iranyom *iranyeleje,int ABLAK,int vx, int vy,int palyateteje){
    if ((kigyofej->x <= kigyofej->r && iranyeleje->megy==balra)|| (kigyofej->x >= ABLAK-kigyofej->r && iranyeleje->megy==jobbra)){
        kigyofej->x=ABLAK-kigyofej->x;
    }
    else if(kigyofej->y <= 2*kigyofej->r+palyateteje && iranyeleje->megy==fel){
        kigyofej->y=ABLAK-20;
    }
    else if(kigyofej->y >= ABLAK-kigyofej->r && iranyeleje->megy==le){
        kigyofej->y=100;
    }
    else{
        kigyofej->x += vx;
        kigyofej->y += vy;
    }
}

void leptet(Kigyo *kigyofej,int pont){
    for (int i=0; i<=pont; i++){
        Kigyo *uj=kigyofej;
        for (int j=i+1; j<=pont; j++){
            uj=uj->kov;
        }
        uj->kov->x=uj->x;
        uj->kov->y=uj->y;
        uj->r=20;
    }
}

Kigyo *kigyono(Kigyo *kigyofej){
    Kigyo *uj=(Kigyo*)malloc(sizeof(Kigyo));
    uj->x=-20;
    uj->y=-20;
    uj->r=20;
    Kigyo *mozgo=kigyofej;
    while (mozgo->kov != NULL){
        mozgo = mozgo->kov;
    }
    mozgo->kov = uj;
    uj->kov = NULL;
    return uj;
}

void kirajzol(SDL_Renderer *renderer,Kigyo *kigyofej,int szinr,int szing,int szinb,int szina){
    Kigyo *ideiglenes=kigyofej;
    while(ideiglenes->kov!=NULL){
        filledCircleRGBA(renderer, ideiglenes->x, ideiglenes->y, ideiglenes->r, szinr, szing,szinb,szina);
        ideiglenes=ideiglenes->kov;
    }
    filledCircleRGBA(renderer, ideiglenes->x, ideiglenes->y, ideiglenes->r, szinr,szing,szinb,szina);
}

void torol(SDL_Renderer *renderer,Kigyo *kigyofej){
    Kigyo *mozgo=kigyofej;
    while(mozgo!=NULL){
        filledCircleRGBA(renderer, mozgo->x, mozgo->y, mozgo->r, 0, 0, 0, 255);
        mozgo->x=-20;
        mozgo->y=-20;
        mozgo=mozgo->kov;
    }

}

bool utkozik(Kigyo *kigyofej1,Kigyo *kigyofej2){
    Kigyo *futo=kigyofej2;
    Kigyo *mozgo=kigyofej1->kov;
    while (mozgo!= NULL){
        if (mozgo->x==kigyofej1->x && mozgo->y==kigyofej1->y){
            return true;
        }
        mozgo=mozgo->kov;
    }
    while(futo!= NULL){
        if (kigyofej1->x==futo->x && kigyofej1->y==futo->y){
            return true;
        }
        futo=futo->kov;

        }
    return false;
}
