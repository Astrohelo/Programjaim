#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "debugmalloc.h"
#include "Jatek.h"
#include "iranykezeles.h"

void bevesz(Iranyom *eleje,Merre ujirany){
    Iranyom *mozgo=eleje;
    while(mozgo->kov!=NULL){
        mozgo=mozgo->kov;
    }
    if (mozgo->megy!=ujirany){
            if(mozgo->megy==balra && ujirany!=jobbra){
                Iranyom *uj=(Iranyom*)malloc(sizeof(Iranyom));
                mozgo->kov=uj;
                uj->megy=ujirany;
                uj->kov=NULL;
            }
            else if(mozgo->megy==jobbra && ujirany!=balra){
                Iranyom *uj=(Iranyom*)malloc(sizeof(Iranyom));
                mozgo->kov=uj;
                uj->megy=ujirany;
                uj->kov=NULL;
            }
            else if(mozgo->megy==fel && ujirany!=le){
                Iranyom *uj=(Iranyom*)malloc(sizeof(Iranyom));
                mozgo->kov=uj;
                uj->megy=ujirany;
                uj->kov=NULL;
            }
            else if(mozgo->megy==le && ujirany!=fel){
                Iranyom *uj=(Iranyom*)malloc(sizeof(Iranyom));
                mozgo->kov=uj;
                uj->megy=ujirany;
                uj->kov=NULL;
            }

    }
}

Iranyom *kiad(Iranyom *eleje){
    Iranyom *mozgo=eleje;
    if (eleje->kov!=NULL){
        eleje=eleje->kov;
        free(mozgo);
    }
    return eleje;
}

void felszabadit_irany(Iranyom *eleje){
    Iranyom *ideiglenes=eleje;
    Iranyom *eltuntet=eleje;
    while(ideiglenes!=NULL){
        ideiglenes=ideiglenes->kov;
        free(eltuntet);
        eltuntet=ideiglenes;
    }
}
