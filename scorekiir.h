#ifndef scorekiir.h
#define scorekiir.h

void beolvas(int *tomb,int meret);  /// beolvasom egy 10 elemu tombbe a fajlban tarolt dicsoseglistat
void beleir(int *tomb,int meret,int pont);  /// kiirom fajlba a modositott tombot ami a dicsoseglista (abban az esetben valtozik ha a jelenlegi jatek pontszama belekerul)
bool pontszamok(int ABLAK,SDL_Renderer *render); ///Kiirja a 10 legjobb pontszamot

#endif // scorekiir
