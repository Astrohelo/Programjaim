#ifndef iranykezeles.h
#define iranykezeles.h

void bevesz(Iranyom *eleje,Merre ujirany);      ///A FIFO kap uj iranyt
Iranyom *kiad(Iranyom *eleje);      /// A FIFO kiadja az elso iranyt amit epp tarol
void felszabadit_irany(Iranyom *eleje);     ///a lefoglalt memóriaterületeket felszabaditja a program végén

#endif // iranykezeles
