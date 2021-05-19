#ifndef kigyomozgasa.h
#define kigyomozgasa.h

void mozog(Kigyo *kigyofej,Iranyom *iranyeleje,int ABLAK,int vx, int vy,int palyateteje);   ///kigyo kovetkezo pozicioja a helyetol es iranyatol fuggoen esetekre bontva.
void leptet(Kigyo *kigyofej,int pont);  ///a kigyó részeit lépteti, követi az elsõ elemet
Kigyo *kigyono(Kigyo *kigyofej);    ///A kigyonak letrehoz egy uj bogyot amit a palyan kivul ad meg helyzetet mert a leptet fv-el ugyis sorba rakja
void kirajzol(SDL_Renderer *renderer,Kigyo *kigyofej,int szinr,int szing,int szinb,int szina);  ///kirajzolja a kigyot, megkapja a kigyofejet es a szinet
void torol(SDL_Renderer *renderer,Kigyo *kigyofej);     ///A palyan kivulre rakja a kigyot
bool utkozik(Kigyo *kigyofej1,Kigyo *kigyofej2);   ///Megkapja a 2 kigyofejet es ellenorzi, hogy az elso atadott kigyofeje utkozik e a masodik kigyoval

#endif // kigyomozgasa
