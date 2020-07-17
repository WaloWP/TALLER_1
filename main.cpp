
#include <iostream>
#include <string>
#include "logic.hpp" // libreria 
#include <fstream>
#include <math.h>

int main(int argc, char const *argv[])
{
    // EJEMPLOS DE LA CLASE

    // GLC
    // logicS::printRGLC(27,17,100,43);
    // logicS::printRGLC(5,5,7,13);

    // graficos 
    // logicS::printRGLC(5,255,1032,100);
    // logicS::printRGLC(5,255,1031,100);

    // GLC bueno
    // logicS::printRGLC(5,106,6075,1283);

    // GEM
    // logicS::printRGLC(3,16807,2147483647); // c = 0
    // ejersicio en clase 
    // logicS::printRGLC(5,12,21,0);

    // generate data 
    // logicS::printRGLC(5,355,1031,100,false,true);
    // logicS::printRGLC(3,16807,2147483647,0,false,true); // warning

    //pruebas 
    // a 106, c = 1283, m = 6075

    // logicS::printRGLC(5,106,6075,1283,false,true,10000);
    // logicS::printRGLC(5,106,6075,1283,false,true,1000);
    // logicS::printRGLC(5,106,6075,1283,false,true,1000);
    
    // logicS::loadDataUNIFORM("X05A106C1283M6075.txt",2);
    // logicS::loadDataINDEPENDECE("corridas2.txt",1);
    // logicS::loadDataINDEPENDECE("series.txts",2);

    //0 0.2, 0.2 0.4 
    // for (double i = 0; i <1; i+=0.001)
    // {
    //     double
    //     fL =0.1;
    //     int douI = ((int) (i*10)/2)% ((int) (fL * 100));
    //     // std::cout<<i<<" -- "<<douI<<" --> "<<((int) (i*10))<<" __"<<((int) (fL * 100))<<std::endl;
    //     std::cout<<i<<" -- "<<douI<<std::endl;
        
    // }

    // logicS::loadDataPOKER("Prueba0.txt");
    // logicS::loadDataPOKER("Prueba1.txt",2);
    // 
    // std::cout << "asd\n";

    logicS::genCompileRandNumbers(100);
    return 0;
}
