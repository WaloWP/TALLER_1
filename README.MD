# TALLER 1



1. Crear el código necesario para tener las siguientes características de los generadores vistos

   a. Generador Lineal Congruente.

   ```c++
   // EJEMPLO 1
   /**
        * this function generathe all numbers by  glc or gem 
        * includen inside the period
        *  (lliint) X0, seed
        *  int a, multiplicator
        *  int m, module
        *  int c, increase, default =0 
        *  bool fact, factorizar, default false
        *  bool savef, save data in file, 
        * 
        * */
   
   // X0 = 27, a = 17, c = 43, m = 100
   logicS::printRGLC(27,17,100,43);
   // X0 = 5, a = 5, c = 13, m = 7
   logicS::printRGLC(5,5,7,13);
   
   // EJEMPLOS 2
   // X0 = 5, a = 255, c = 100, m = 1032
   logicS::printRGLC(5,255,1032,100);
   // X0 = 5, a = 255, c = 100, m = 1031
   logicS::printRGLC(5,255,1031,100);
   
   // BUEN GENERADOR
   // X0 = 5, a = 106, c = 1283, m = 6075
   logicS::printRGLC(5,106,1283,6075);
   
   ```

   b. Generador de estándar mínimo. 

   

   ```c++
   // GEM
   // a = 7⁷⁵ = 16807
   // c = 0
   // m = 2³¹ - 1 = 2147483647
   logicS::printRGLC(3,16807,2147483647); // c = 0
   // ejersicio en clase 
   logicS::printRGLC(5,12,21,0,true);
   
   // GENERATE DATA
   
    logicS::printRGLC(5,355,1031,100,false,true);
   // logicS::printRGLC(3,16807,2147483647,0,false,true); // warning
   ```

   

   `

2. Teniendo en cuenta los números generados en el punto anterior, realice pruebas de Uniformidad: 

   ```c++
   // To create data file this have the name of settings, to generate
   ```

   a. Aplicar para los N datos la prueba de chi cuadrado

   ```c++
   logicS::loadDataUNIFORM("X05A106C1283M6075.txt",1);
   ```

   b. Aplicar para los N datos la prueba de Kolmogorov–Smirnov 

   ```c++
   logicS::loadDataUNIFORM("X05A106C1283M6075.txt",2);
   ```

   

3.  Realizar pruebas de Independencia. 

   ```c++
   //corridas
   logicS::loadDataINDEPENDECE("corridas2.txt",1);
   //series
   logicS::loadDataINDEPENDECE("series.txts",2);
   //poker
   logicS::loadDataPOKER("Prueba0.txt");//3
   logicS::loadDataPOKER("Prueba1.txt",2);//5
   ```

4. Utilizando el generador de números aleatorios del lenguaje de programación,, generar N números y realizar la prueba de uniformidad e independencia indicados en los puntos anteriores, ¿Determinar si es un buen generador y porque? 

   ```c++
   // to generate rand numbers random and save
   /**
   * long long int N
   * long long int m, default 100000
   * -> this generate a file randCompile.txt
   *//
    logicS::genCompileRandNumbers(100);
   
   //chi
   logicS::loadDataUNIFORM("randCompile.txt",1);
   //Kolmogorov
   logicS::loadDataUNIFORM("randCompile.txt",2);
   
   //corridas
   logicS::loadDataINDEPENDECE("randCompile.txt",1);
   //series
   logicS::loadDataINDEPENDECE("randCompile.txts",2);
   //poker
   logicS::loadDataPOKER("randCompile.txt");//3
   logicS::loadDataPOKER("randCompile.txt",2);//5
   ```

   

   ```c++
   
   ```

   

