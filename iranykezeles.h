#ifndef iranykezeles.h
#define iranykezeles.h

void bevesz(Iranyom *eleje,Merre ujirany);      ///A FIFO kap uj iranyt
Iranyom *kiad(Iranyom *eleje);      /// A FIFO kiadja az elso iranyt amit epp tarol
void felszabadit_irany(Iranyom *eleje);     ///a lefoglalt mem�riater�leteket felszabaditja a program v�g�n

#endif // iranykezeles
