
#include <iostream>
#include <string>
#include "logic.hpp"
#include <fstream>


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
    // logicS::printRGLC(5,12,21,0,true);

    // generate data 
    // logicS::printRGLC(5,355,1031,100,false,true);
    // logicS::printRGLC(3,16807,2147483647,0,false,true); // warning

    //pruebas 
    // a 106, c = 1283, m = 6075

    // logicS::printRGLC(5,106,6075,1283,false,true,10000);
    // logicS::printRGLC(5,106,6075,1283,false,true,1000);
    // logicS::printRGLC(5,106,6075,1283,false,true,1000);
    
    // logicS::loadData("X05A106C1283M6075.txt",2);
    logicS::loadDataINDEPENDECE("corridas2.txt",1);
    
    
    return 0;
}