#ifndef Jatek.h
#define Jatek.h

typedef enum Merre{ /// Az iranyok miatt hoztam letre ezt az enumot
    balra,
    jobbra,
    le,
    fel
} Merre;

typedef struct Iranyom{ /// FIFO, tarolja a beerkezo iranyokat amiket a felhasznalo lenyomott
    Merre megy;
    struct Iranyom* kov;
}Iranyom;

typedef struct Kigyo {      ///kigyo pontja,sugara,sebessege,iranya
        int x, y;
        int r;
        struct Kigyo *kov;
} Kigyo;

typedef struct Narancs{     ///Ezt a bogyot szedi ossze a kigyo pontokert
    int x, y;
    int r;
} Narancs;

Uint32 idozit(Uint32 ms, void *param);  /// ez a fuggveny hivodik meg az idozito altal. betesz a feldolgozando esemenyek koze (push) egy felhasznaloi esemenyt
Narancs narancsgeneral(Narancs narancs,Kigyo *kigyofej,Kigyo *kigyofej2,int palyateteje);    ///narancsnak gener�l egy x �s y-t ami a p�ly�n van �s nem �tk�zik a kigy�val vagy a kigy�kkal
void felszabadit_kigyo(Kigyo *kigyofej);    ///a lefoglalt mem�riater�leteket felszabaditja a program v�g�n
bool jatek(int ABLAK,SDL_Renderer *renderer,bool ketjatekos);   ///Ez maga a j�t�kot teszi �ssze, megkapja, hogy 1 vagy 2 j�t�kos m�dban indul, illetve az ablak m�retet �s a renderert, visszat�r azzal, hogy v�ge van-e a j�t�knak.

#endif // Jatek.h
