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
Narancs narancsgeneral(Narancs narancs,Kigyo *kigyofej,Kigyo *kigyofej2,int palyateteje);    ///narancsnak generál egy x és y-t ami a pályán van és nem ütközik a kigyóval vagy a kigyókkal
void felszabadit_kigyo(Kigyo *kigyofej);    ///a lefoglalt memóriaterületeket felszabaditja a program végén
bool jatek(int ABLAK,SDL_Renderer *renderer,bool ketjatekos);   ///Ez maga a játékot teszi össze, megkapja, hogy 1 vagy 2 játékos módban indul, illetve az ablak méretet és a renderert, visszatér azzal, hogy vége van-e a játéknak.

#endif // Jatek.h
