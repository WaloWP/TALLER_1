/**
 * this are the  library where implement the functions 
 * to porceess the main function 
*/

#ifndef _LOGIC_H_
#define _LOGIC_H_

#include <iostream>
#include <iomanip> //setw
#include <fstream> //archiovs
#include <math.h>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


namespace logicS
{

    namespace _internal
    {
        /**
         * this functiona generate the next pseudo-random number 
         * using the comgruent lineal generator 
         * parametros:
         *  (lliint) X0, seed
         *  int a, multiplicator
         *  int m, module
         *  int c, increase
         * */

        long long int glc(long long int X0, int a, int m, int c=0){
            return ((a*X0) + c) % m;
        }

        /**
         * this functiona generate the next pseudo-random number 
         * using the comgruent lineal generator 
         * parametros:
         *  (lliint) X0, seed
         *  int a, multiplicator
         *  int m, module
         *  int c, increase
         * */

        long long int gemF(long long int X0, int a, int m, int c=0){
            // fact a M
            long long int q = (int) ((double )m/a);
            long long int r = m % a;
            // calculate Xn+1
            long long int Xn = (a * (X0 % q)) - (r* ((int) ((double) X0/q)));
            if (Xn < 0)
                Xn +=m;
            return Xn;
        }

        /**
         * this function search in the array a number
         * parametros
         * int number 
         * int array
         * int arraySize
         * 
         * -> bool (existence the number un the array)
        */
        bool exist(long long int number, long long int* arr,int arrSize){
            for (int i =0; i<arrSize;i++){
                if(arr[i] == number)
                    return true;
            }
            return false;
        }

    } // namespace _internal
    
    
    /**
     * this function generathe all numbers by  glc or gem 
     * includen inside the period
     *  (lliint) X0, seed
     *  int a, multiplicator
     *  int m, module
     *  int c, increase, default =0 
     *  bool fact, factorizar, default false
     *  bool savef, save data in file, 
     *  int tope, is the topw to stop, -1
     * */

    void printRGLC(long long int X0, int a, int m, int c=0, bool fact=false , bool saveF =false, int tope = -1){
        //loaded TOPE
        if(tope == -1 || tope <0){
            tope = m;
        }
        //limit to storage
        int limitStorage = 5;

        // this array storage the new arrayasd
        long long int firstResults[limitStorage];

        // contador de la seleccion 
        long long int countP =0;

        // this the RX expresion
        double rx =0;

        //initial 
        std::cout<<std::setfill('.');
        std::cout<<"X0:"<<std::setw(10)<<X0<<std::endl;
        std::cout<<"a :"<<std::setw(10)<<a<<std::endl;
        std::cout<<"c :"<<std::setw(10)<<c<<std::endl;
        std::cout<<"m :"<<std::setw(10)<<m<<std::endl;

        // storage seed 
        firstResults[0]=X0;
        

        //first RN
        rx = (double)X0/m;

        ////////////////// GENERATE OUPUT
        std::ofstream loadedF;
        if (saveF){//if select save this file
            //shoow dialog
            std::cout<< "\n generating file....\n";
            //url to arcive
            std::string url = 
            "X0" + std::to_string(X0)+
            "A" + std::to_string(a) +
            "C" + std::to_string(c) +
            "M" + std::to_string(m) +
            ".txt";

            loadedF.open(url);
        }
        ///////////// SHOW TABLE TITLE 
        // table spaces 
        int separatorSize = 57, space1=10,space2=20,space3=18;
        
        if (saveF){
            // loadedF << rx; 
            // loadedF<<"\n";
        }else {
            std::cout<<std::setw(separatorSize)<<std::setfill('-')<<"\n"<<std::setfill(' ');
            std::cout<<"| "<<std::setw(space1)<<"i"<<"| "<<std::setw(space2)<<"Xi"<<"| "<<std::setw(space3)<<"Rxi"<<" |"<<std::endl;
            std::cout<<std::setw(separatorSize)<<std::setfill('-')<<"\n"<<std::setfill(' ');
            
            //print the seed
            std::cout<<"| "<<std::setw(space1)<<countP<<"| "<<std::setw(space2)<<X0;
            std::cout<<"| "<<std::setw(space3)<<(double) X0/m<<" |"<<std::endl;
            std::cout<<std::setw(separatorSize)<<std::setfill('-')<<""<<std::setfill(' ')<<"\n";
        }
        

        while (true)
        {
            //define who procedure execute
            if(fact && c == 0)// si se pide hacer por factorización
                X0 = _internal::gemF(X0,a,m);
            else
                X0 = _internal::glc(X0,a,m,c);
            
            // RN
            rx = (double) X0/m;

            /////////// verifi if dont overflowit
            if(X0>=m){
                std::cerr<<"\n--ERROR: this generator overflow or reach to m\nXN: "<<X0<<"\n M: "<<m<<std::endl;
                break;
            }else if (X0 < 0){
                std::cerr<<"\n--ERROR: some go bad\nXN: "<<X0<<std::endl;
                break;
            }

            //increase the period
            countP++;
            
            //print the XN
            if(saveF){
                loadedF << rx;
                loadedF<<"\n";
            }else {
                std::cout<<"| "<<std::setw(space1)<<countP<<"| "<<std::setw(space2)<<X0;
                std::cout<<"| "<<std::setw(space3)<<(double) X0/m<<" |"<<std::endl;
                std::cout<<std::setw(separatorSize)<<std::setfill('-')<<""<<std::setfill(' ')<<"\n";    
            }

                // verify cicle (period)
            if (_internal::exist(X0,firstResults,limitStorage) ){
                // SHOW THE RESULT AND REPEAT PSEUDO-RANDOM
                if (!saveF)
                    for (int i =0; i<limitStorage;i++){
                        if(firstResults[i] == X0)
                            std::cout << firstResults[i]<<" ___ "<< X0<<std::endl;
                            // std:cout<<firstResults[i] << " ___ "<<X0;
                    }
                break;
            }else if ( countP>= tope){
                std::cout <<"\n--TOPE--\n";
                break;
            }
            
            //save Xn
            if (countP < limitStorage){//storage the Xn
                //Storage
                firstResults[countP] = X0;
            }
        }
        
        // show the period
        // if(saveF){
        //     loadedF<< "PERIODO: " + std::to_string(countP);
        //     loadedF.close();
        //     std::cout<<"\nFILE GENERATE\n";
        // }
        std::cout<<"PERIODO: "<<countP<<std::endl<<std::endl;
        
    }

    /**
     * this function load data of file and proces the data to create the distribution
     * with this function allow execute the CHI x^2 
     * String url, direcion or name to txt
     * int option ,option to select chi cuadrado o konmogorob, default 1 <- chhi2
     * 1 -> chi cuadrado
     * 2 -> kogmogorob
     * 
     * 
     * 
    */ 
    void loadDataUNIFORM(std::string url ,int option = 1){
       //load file 
       std::ifstream loadF(url);
       //LOAD DATA
       if(loadF){//exist?
            //load line
            std::string line ="";
            //LOAD DATA
            //cont data
            long long int countD=0;
            // clasificacion
            long long int FO[10]={};
            //remember than onli use 10 class

            /// RECOPILATED DATA
            while (getline(loadF,line)){
                //rx saved
                double dato;
                try{
                    dato = std::stod(line);
                }catch(const std::exception& e){
                    std::cerr << e.what() << '\n';
                }

                // for(int i =0; i< 10;i++){
                //     if(
                //         (0.0 + ((double)i/10)) <= dato && (0.1 + ((double)i/10))>dato){
                //         FO[i]++;
                //         break;
                //     }
                // }
                //clasificate data
                // (data*10) /(increase-factor)*10 MOD 10
                // en este caso es 100 porque el factos es 0.1
                int pos = ((int)( dato*10 )) % 10;
                // int pos = ((int)( dato*100 )) % 10;
                // std::cout<<"POS:"<<pos<<" - "<<(int)(dato*100 )<<std::endl;
                FO[pos]++;

                //increase the data count to use FE
                countD++;
            }

            
            if(option== 1){
                ///////CHI CUADRADO

                //WAINTED FRECUENCE
                int FE = countD/10;
                // CHI CALCULADO
                double chiCal =0;
                 /////////////////SHOW TABLE ///////////////////
                int separatorSize = 70,space1=12,space2=16;
                std::cout<<std::setw(separatorSize)<<std::setfill('-')<<"\n"<<std::setfill(' ');
                std::cout
                <<"| "<<std::setw(space1)<<"rango"
                <<"| "<<std::setw(space2)<<"FO"
                <<"| "<<std::setw(space2)<<"FE"
                <<"| "<<std::setw(space2)<<"(FE-FO)²/FE"
                <<" |"<<std::endl;
                std::cout<<std::setw(separatorSize)<<std::setfill('-')<<"\n"<<std::setfill(' ');
                
                // 
                for (int i=0; i<10;i++){
                    // calculate CHI
                    double chiTemp=(double)((FE - FO[i])*(FE - FO[i]))/FE;
                    //PLUS  CHI
                    chiCal += chiTemp;

                    std::cout<<std::setw(separatorSize)<<std::setfill('-')<<"\n"<<std::setfill(' ');
                    std::cout
                    <<"| "<<"["<<std::setw((space1/2)-3)<<  (double) (0.0 + ((double)i/10)) << " - "<<std::setw((space1/2)-3)<<(double) (0.1+ ((double)i/10))<<") "
                    <<"| "<<std::setw(space2)<<FO[i]
                    <<"| "<<std::setw(space2)<<FE
                    <<"| "<<std::setw(space2)<<chiTemp
                    <<" |"<<std::endl;
                    std::cout<<std::setw(separatorSize)<<std::setfill('-')<<"\n"<<std::setfill(' ');
                }

                //SHOW CHI CAL 
                std::cout<<"|  "<<std::setw(separatorSize*2/3)<<"CHICALCULADO: "<<std::setw(separatorSize/3 - 4)<<chiCal<<" |"<<std::endl;
                std::cout<<std::setw(separatorSize)<<std::setfill('-')<<"\n"<<std::setfill(' ');

                // COMPARATE CHI
                std::cout<<"DADO:\n α  = "<< 0.005<<std::endl;
                std::cout<<" gl = "<< 9<<std::endl;
                std::cout<<"---> X² crit: "<<16.92<<std::endl;
                if(16.92 < chiCal)
                    std::cout<<"---------------- NO HA SUPERADO LA PRUEBA DE x²"<<std::endl;
                else 
                    std::cout<<"\n----------------!!  HA SUPERADO LA PRUEBA DE x² !!!--------------------------------"<<std::endl;

            }else if (option == 2){
                 //////KOLLMOGOROV
                //View Frecuence 
                long long int FOA[10]={};
                FOA[0]= FO[0];

                //POA
                double POA[10]={};
                POA[0]=((double)FO[0]/countD);

                // double PE = ((double)countD/10)/countD; == siempre a 1/10 = 0.1
                double PEA[10]={};
                PEA[0]= 0.1;
                
                //DECAL
                double DCAL[10]={};
                // DCAL[0] = std::abs(PEA[0] - POA[0]);

                double DCALMAX =0;

                ////// SHOW TABLE
                int separatorSize = 106,space1=12,space2=16;
                std::cout<<std::setw(separatorSize)<<std::setfill('-')<<"\n"<<std::setfill(' ');
                std::cout
                <<"| "<<std::setw(space1)<<"rango"
                <<"| "<<std::setw(space2)<<"FO"
                <<"| "<<std::setw(space2)<<"FOA"
                <<"| "<<std::setw(space2)<<"POA"
                <<"| "<<std::setw(space2)<<"PEA"
                <<"| "<<std::setw(space2)<<"|PEA - POA|"
                <<" |"<<std::endl;
                std::cout<<std::setw(separatorSize)<<std::setfill('-')<<"\n"<<std::setfill(' ');
                
                //ACOMULACIONES
                for (int i = 0; i < 10; i++)
                {
                    if(i!=0){
                        FOA[i] = FO[i]+ FOA[i-1];
                        POA[i] = ((double)FOA[i]/countD);
                        PEA[i] = PEA[i-1] + 0.1;
                        DCAL[i] = std::abs(PEA[i] - POA[i]);
                        if(DCALMAX< DCAL[i])
                            DCALMAX=DCAL[i];
                        
                    }
                    
                    ////SEGMENT
                    std::cout<<std::setw(separatorSize)<<std::setfill('-')<<"\n"<<std::setfill(' ');
                    std::cout
                    <<"| "<<"["<<std::setw((space1/2)-3)<<  (double) (0.0 + ((double)i/10)) << " - "<<std::setw((space1/2)-3)<<(double) (0.1+ ((double)i/10))<<") "
                    <<"| "<<std::setw(space2)<<FO[i]
                    <<"| "<<std::setw(space2)<<FOA[i]
                    <<"| "<<std::setw(space2)<<POA[i]
                    <<"| "<<std::setw(space2)<<PEA[i]
                    <<"| "<<std::setw(space2)<<DCAL[i]
                    <<" |"<<std::endl;
                    std::cout<<std::setw(separatorSize)<<std::setfill('-')<<"\n"<<std::setfill(' ');
                    
                    // std::cout<<"->->"<<DCALMAX<<std::endl;
                }

                std::cout<<"|  "<<std::setw(separatorSize*2/3)<<"DM CALCULADO: "<<std::setw(separatorSize/3 - 4)<<DCALMAX<<" |"<<std::endl;
                std::cout<<std::setw(separatorSize)<<std::setfill('-')<<"\n"<<std::setfill(' ');

                //// compare DM

                double DMcrit = (1.36/ sqrt(countD));
                std::cout<<"DADO:\n α  = "<< 0.005<<std::endl;
                std::cout<<" gl = "<< 9<<std::endl;
                std::cout<<"---> DM crit: "<<DMcrit<<std::endl;
                if(DMcrit < DCALMAX)
                    std::cout<<"---------------- NO HA SUPERADO LA PRUEBA DE KOGMOGOROB"<<std::endl;
                else 
                    std::cout<<"\n----------------!!  HA SUPERADO LA PRUEBA DE KOGMOGOROB!!!--------------------------------"<<std::endl;
            }else {
                std::cout<<"The option don't is congruent"<<std::endl;
            }            
            
           
            // std::cout<<<<std::endl; 
       }else {
           std::cout<<"Dont exist file "<<url<<std::endl;
       }
   }

    /**
     * this function load the data file and process this data to geneerate
     * probes of independece
     * string url, url to load file 
     * int option, select option to select the probe, default = 1
     *  1-> corridas
     *  2-> series en 2
    */
    void loadDataINDEPENDECE(std::string url ,int option = 1){
        //load file 
       std::ifstream loadF(url);

       if(loadF){//exist?
            //load line
            std::string line ="";
            
            //cont data
            long long int countD=0;

            if(option == 1){ //corridas
                //number of corridas
                // This init in 1, cause 
                // the minim of corridas is 1
                long long int corridas=1;

                //FLAG TO COUNT CORRIDAS
                //-1  Not init
                // 1 increase
                // 0 decrease
                int flagC = -1;// not init
                // previou data
                double previousD =-1;

                /// RECOPILATED DATA
                while (getline(loadF,line)){
                    //rx saved
                    double dato;
                    // casting 
                    try{
                        dato = std::stod(line);
                    }catch(const std::exception& e){
                        std::cerr << e.what() << '\n';
                    }

                    //comparate corridas
                    
                    if(previousD != -1){//init data
                        if(previousD >dato ){
                            //decremento
                            if(flagC != 0){//init flg
                                if(flagC == 1)//change flag
                                    corridas++;
                                flagC =0;//decrease
                            }
                            
                        }else {
                            //increase
                            if(flagC != 1){//init flg
                                if(flagC == 0)//change flag
                                    corridas++;
                                flagC =1;//decrease
                            }
                        }
                    }
                    //save data
                    previousD = dato;

                    // SEGUIMIENTO DE LAS CORRIDAS
                    std::cout
                    <<std::setw(4)<<countD
                    <<" DATA: "<<std::setw(5)<<dato
                    <<" PREVIOUS "<<std::setw(5)<<previousD
                    <<" CORRIDAS: "<<std::setw(5)<<corridas
                    <<" FLAG: "<<std::setw(5)<<flagC
                    <<std::endl;

                    //count datas
                    countD++;
                    
                }

                std::cout <<" CORRIDAS TOTALES: "<<corridas<<std::endl;
                // NUMBER OF DATA enougth
                if(countD > 20){
                    double 
                    meduaU = (double)(2 * countD -1)/3,
                    varianzaO = (double)(16 * countD -29)/90,
                    zObs = (double)(corridas-meduaU)/std::sqrt(varianzaO),
                    //con un nivel de confianza con a = 0.05 -> 1.69
                    zCrit = 1.69,
                    zaMin = -zCrit,
                    zaMax =zCrit;

                    //show results 
                    std::cout
                    <<"\nMEDIA 𝝻   : "<<std::setw(5)<<meduaU<<std::endl
                    <<"VARIANZA σ: "<<std::setw(5)<<varianzaO<<std::endl
                    <<"Zobs      : "<<std::setw(5)<<zObs<<std::endl
                    <<"INTERVALO con 0.05 :"
                    <<"["<<std::setw(5)<<zaMin<<" : "
                    <<std::setw(5)<<zaMax<<"]"<<
                    std::endl
                    ;
                    
                    //COMPARATE
                    if(zObs >= zaMin && zObs<= zaMax){
                        std::cout <<"\n La prueba de independencia a sido superada ";
                    }else {
                        std::cout <<"\n La prueba de independencia NO!!! a sido superada ";
                    }
                }else {
                    std::cout<<"EL NUMERO DE DATOS A LEER ES INFERIOR A 20\n\n";
                }
            }else if (option == 2){
                ///////// series
                // in this case is used 5 class
                double FO[5][5]={};

                //position to clasification
                int posA=0,posB=0;
                // acomulate posible counts
                long long int countP=0;
                 /// RECOPILATED DATA
                while (getline(loadF,line)){
                    //rx saved
                    double dato;
                    // casting 
                    try{
                        dato = std::stod(line);
                    }catch(const std::exception& e){
                        std::cerr << e.what() << '\n';
                    }

                    //increase count data
                    countD++;

                    // CLASIFICATE DATA
                    //(A,B)
                    if(countD%2 != 0){ //(A, ...)
                        posA = ((int) (dato*10)/2)% 10; 
                    }else {//(...,B)
                        posB = ((int) (dato*10)/2)% 10; 
                        // save the data in the matrix
                        FO[posA][posB] ++;
                        //cuenta de parejas 
                        countP++;
                        
                    }
                    
                }

                //show matrix 
                std::cout<<std::setw(12)<<" "<<
                "[0.0 - 0.2)[0.2 - 0.4)[0.4 - 0.8)[0.8 - 0.9)[0.9 - 1.0)\n";
                for (int i = 0; i < 5; i++)
                {
                    std::cout<<"[ "<<std::setw(3)<<0.0 + i*0.2<<" - "<<std::setw(3)<<0.2 + i*0.2<<")";
                    for (int j = 0; j < 5; j++)
                    {
                        std::cout<<std::setw(9)<<FO[i][j]<<"  ";
                    }
                    std::cout<<std::endl;
                    std::cout<<std::endl;
                    
                }

                // probabilidad teorica 1/25
                double FE = (double)countP/25;
                
                //show matrix CHI
                
                std::cout<<"\n"<<std::setw(12)<<" "<<
                "[0.0 - 0.2)[0.2 - 0.4)[0.4 - 0.8)[0.8 - 0.9)[0.9 - 1.0)\n";
                for (int i = 0; i < 5; i++)
                {
                    std::cout<<"[ "<<std::setw(3)<<0.0 + i*0.2<<" - "<<std::setw(3)<<0.2 + i*0.2<<")";
                    for (int j = 0; j < 5; j++)
                    {
                        //calculate the 
                        FO[i][j]= (double) std::pow( (FO[i][j] - FE),2)/FE;
                        std::cout<<std::setw(9)<<FO[i][j]<<"  ";
                    }
                    std::cout<<std::endl;
                    std::cout<<std::endl;
                    
                }

                //acomulated 
                double chiCal =0;
                for (int i = 0; i < 5; i++)
                    for (int j = 0; j < 5; j++)
                        chiCal += FO[i][j];//acomulated mounth
                std::cout
                <<" GL: 24\n"
                <<" a : 0.05\n"
                <<" Chi-Critico     : 36.42\n"
                <<" Chic-Calculado  : "<<chiCal<<std::endl;

                if(chiCal > 36.42){
                    std::cout <<"La prueba de serie NO!! ha sido superada"<<std::endl;
                }else{
                    std::cout <<"La prueba de serie ha sido superada"<<std::endl;
                }
            }
            


       }else {
           std::cout<<"\n El fuchero "<<url<<" no se encuentra disponible o no ha podido ser leido\n";
       }
    }

    /***
     * this function apply poker 
     * 1 <- poker 3
     * 2 <- poker 5
    */

   void loadDataPOKER(std::string url, int option =1){
       //load file
       std::ifstream loadF(url);

       if(loadF){//exist?
            //load line
            std::string line ="";
            
            //cont data
            long long int countD=0;

            if(option == 1){ 
                // POKER 3
                /**
                 * GL = 2
                 * CLASES = 3
                 * xCRITICO = 10.5965
                 * 
                 * 3 clases de almacemnamiento 
                 * 
                 * 0 -> 3 cartas iguales  = 0.01
                 * 1 -> 2 cartas iguales  = 0.27
                 * 2 -> todas diferentes  = 0.72
                */

                long long int FO[3]={};
                /// RECOPILATED DATA
                while (getline(loadF,line)){
                    //rx saved
                    double dato;
                    // casting 
                    try{
                        dato = std::stod(line);
                    }catch(const std::exception& e){
                        std::cerr << e.what() << '\n';
                    }

                    //extracción de decimales
                    //partes enteras, digitos
                    int dig1,dig2,dig3;
                    //partes de rrecorrido
                    // double mov1,mov2,mov3;
                    dig1 = ((int)(dato*10))%10;
                    dig2 = ((int)(dato*100))%10;
                    dig3 = ((int)(dato*1000))%10;
                    int pos = -1;
                    // clasificación
                    if(dig1==dig2 && dig2==dig3){//todos son iguales
                        std::cout<<dato<<" -> 0 TI  "<<dig1<<dig2<<dig3<<"\n";
                        pos =0;
                    }else if((dig1 == dig2 || dig1 == dig3) || dig2 == dig3){ //dos iguales
                        std::cout<<dato<<" -> 0 DI  "<<dig1<<dig2<<dig3<<"\n";
                        pos =1;
                    }else {
                        std::cout<<dato<<" -> 0 TD  "<<dig1<<dig2<<dig3<<"\n";
                        pos =2;
                    }
                    //conteo
                    FO[pos]++;

                    //count data
                    countD++;
                }
                //waint frecuence
                double FE[3]={0.01*countD, 0.27*countD, 0.72*countD};

                //SHOW TABLES
                int separatorSize = 106,space1=12,space2=16;
                std::cout<<std::setw(separatorSize)<<std::setfill('-')<<"\n"<<std::setfill(' ');
                std::cout
                <<"| "<<std::setw(space1)<<"rango"
                <<"| "<<std::setw(space2)<<"FO"
                <<"| "<<std::setw(space2)<<"FE"
                <<"| "<<std::setw(space2)<<"(FE-FO)²/FE"
                <<" |"<<std::endl;
                std::cout<<std::setw(separatorSize)<<std::setfill('-')<<"\n"<<std::setfill(' ');
                

                //chi cal
                double chiC, chiCA=0;
                for (int i = 0; i < 3; i++){
                    chiC = ((double) std::pow((FE[i]-FO[i]),2)/FE[i]);
                    chiCA += chiC;

                    std::cout<<std::setw(separatorSize)<<std::setfill('-')<<"\n"<<std::setfill(' ');
                    std::cout
                    <<"| "<<std::setw(space1)<<((i == 0)? "3 IG":((i == 1)? "2 IG 1 DIF":"TD"))
                    <<"| "<<std::setw(space2)<<FO[i]
                    <<"| "<<std::setw(space2)<<FE[i]
                    <<"| "<<std::setw(space2)<<chiC
                    <<" |"<<std::endl;
                    std::cout<<std::setw(separatorSize)<<std::setfill('-')<<"\n"<<std::setfill(' ');

                }

                //result
                std::cout<<"|  "<<std::setw(separatorSize*2/3)<<"CHI CALCULADO: "<<std::setw(separatorSize/3 - 4)<<chiCA<<" |"<<std::endl;
                std::cout<<std::setw(separatorSize)<<std::setfill('-')<<"\n"<<std::setfill(' ');

                // COMPARATION
                double chiCrit = 10.5965;
                std::cout<<"DADO:\n α  = "<< 0.005<<std::endl;
                std::cout<<" gl = "<< 2<<std::endl;
                std::cout<<"---> CHIcrit: "<<chiCrit<<std::endl;
                if(chiCrit < chiCA)
                    std::cout<<"---------------- NO HA SUPERADO LA PRUEBA DE POKER"<<std::endl;
                else 
                    std::cout<<"\n----------------!!  HA SUPERADO LA PRUEBA DE POKER!!!--------------------------------"<<std::endl;
                

            }else if(option == 2){
                 // POKER 5
                /**
                 * GL = 6
                 * CLASES = 7
                 * xCRITICO = 18.5475
                 * 
                 * 7 clases de almacemnamiento 
                 * 
                 * 0 -> TD todas diferentes  = 0.3024
                 * 1 -> P un par  = 0.504
                 * 2 -> 2P dos pares  = 0.108
                 * 3 -> TP 1 tercia 1 par = 0.009
                 * 4 -> T 1 tercia = 0.072
                 * 5 -> poker 4 iguales = 0.0045
                 * 6 -> Q quintilla = 0.0001
                 * 
                */

                long long int FO[7]={};
                /// RECOPILATED DATA
                while (getline(loadF,line)){
                    //rx saved
                    double dato;
                    // casting 
                    try{
                        dato = std::stod(line);
                    }catch(const std::exception& e){
                        std::cerr << e.what() << '\n';
                    }

                    //extracción de decimales
                    //partes enteras, digitos
                    int dig1=0,dig2=0,dig3=0,dig4=0,dig5=0;
                    //partes de rrecorrido
                    // double mov1,mov2,mov3;
                    // dig1 = ((int)(dato*10))%10;
                    // dig2 = ((int)(dato*100))%10;
                    // dig3 = ((int)(dato*1000))%10;
                    // dig4 = ((int)(dato*10000))%10;
                    // dig5 = ((int)(dato*100000))%10;

                    int classi[10]={};
                    int acomu[6]={};
                    // std::cout<<dato<<"--> ";
                    for (int i = 0; i < 5; i++)
                    {
                        // std::cout<<((int)(dato*(std::pow (10,i+1))))%10 <<" ";
                        classi[((int)(dato*(std::pow (10,i+1))))%10]++ ;
                    }
                    // std::cout<<"----"<<std::endl;
                    for(int i = 0; i < 10; i++){
                        acomu[classi[i]]++;
                    }
                    // for(int i = 1; i < 6; i++){
                    //     std::cout<<acomu[i]<<" ";
                    // }
                    // std::cout<<std::endl;
                    //95412
                    //[0,1,1,0,1,1,0,0,0,1] -- calssi
                    //[5,5,0,0,0,0]
                    /*


                    * 0 -> TD todas diferentes  = 0.3024
                 * 1 -> P un par  = 0.504
                 * 2 -> 2P dos pares  = 0.108
                 * 3 -> TP 1 tercia 1 par = 0.009
                 * 4 -> T 1 tercia = 0.072
                 * 5 -> poker 4 iguales = 0.0045
                 * 6 -> Q quintilla = 0.0001*/
                    // clasificación
                    //[ 1, ,2 , ,2 , , , , , ] un for con un int i =0 : 5  n = 10^i
                    int pos = -1;

                    if(acomu[5]==1){//todos son iguales 
                        pos = 6;
                    }else if(acomu[4]==1 && acomu[1]==1){ //poker
                        pos = 5;
                    }else if(acomu[3]==1 && acomu[1]==2){ //tercia
                        pos = 4;
                    }else if(acomu[3]==1 && acomu[2]==1){//1 Tercia y un par
                        pos = 3;
                    }else if(acomu[2]==2 && acomu[1]==1){// 2 pares
                        pos = 2;
                    }else if(acomu[2]==1 && acomu[1]==3){//1 par
                        pos = 1;
                    }else if(acomu[1]==5){//TD
                        pos = 0;
                    }
                    //FO
                    FO[pos]++;
                    //count data
                    countD++;
                }

                
                //waint frecuence
                double FE[7]={
                    0.3024*countD, 
                    0.504*countD, 
                    0.108*countD,
                    0.009*countD,
                    0.072*countD,
                    0.0045*countD,
                    0.0001*countD
                    };

                //SHOW TABLES
                int separatorSize = 106,space1=12,space2=16;
                std::cout<<std::setw(separatorSize)<<std::setfill('-')<<"\n"<<std::setfill(' ');
                std::cout
                <<"| "<<std::setw(space1)<<"rango"
                <<"| "<<std::setw(space2)<<"FO"
                <<"| "<<std::setw(space2)<<"FE"
                <<"| "<<std::setw(space2)<<"(FE-FO)²/FE"
                <<" |"<<std::endl;
                std::cout<<std::setw(separatorSize)<<std::setfill('-')<<"\n"<<std::setfill(' ');
                

                //chi cal
                double chiC, chiCA=0;
                for (int i = 0; i < 7; i++){
                    chiC = ((double) std::pow((FE[i]-FO[i]),2)/FE[i]);
                    chiCA += chiC;

                    std::cout<<std::setw(separatorSize)<<std::setfill('-')<<"\n"<<std::setfill(' ');
                    std::cout
                    <<"| "<<std::setw(space1)<<
                    ((i == 0)? "TD ":((i == 1)? "1P ":((i == 2)? "2P ":((i == 3)? "1T 1P TP":((i == 4)? "T ":((i == 5)? "PKER ":"QUINT"))))))
                    <<"| "<<std::setw(space2)<<FO[i]
                    <<"| "<<std::setw(space2)<<FE[i]
                    <<"| "<<std::setw(space2)<<chiC
                    <<" |"<<std::endl;
                    std::cout<<std::setw(separatorSize)<<std::setfill('-')<<"\n"<<std::setfill(' ');

                }

                //result
                std::cout<<"|  "<<std::setw(separatorSize*2/3)<<"CHI CALCULADO: "<<std::setw(separatorSize/3 - 4)<<chiCA<<" |"<<std::endl;
                std::cout<<std::setw(separatorSize)<<std::setfill('-')<<"\n"<<std::setfill(' ');

                // COMPARATION
                double chiCrit = 18.5475;
                std::cout<<"DADO:\n α  = "<< 0.005<<std::endl;
                std::cout<<" gl = "<< 2<<std::endl;
                std::cout<<"---> CHIcrit: "<<chiCrit<<std::endl;
                if(chiCrit < chiCA)
                    std::cout<<"---------------- NO HA SUPERADO LA PRUEBA DE POKER"<<std::endl;
                else 
                    std::cout<<"\n----------------!!  HA SUPERADO LA PRUEBA DE POKER!!!--------------------------------"<<std::endl;
                
            }
       }else {
           std::cout<<"No se ah podico cargar el archivo" <<url<<"\n\n";
       }
   }


    /**
     * This function are the generate a random number to load latter
     */

    void genCompileRandNumbers( int N, int m = 100000){
        std::string url = "randCompile.txt";
        //open file
        std::ofstream fileOUT(url);
        /* initialize random seed: */
        srand (time(NULL));

        while (N!=0)
        {
            // Save number 
            // fileOUT<<rand()<<"\n";
            fileOUT<<((double)(rand()%m)/m)<<"\n";
            //decrease N
            N--; 
        }
        
        fileOUT.close();

    }

} // namespace logicS

#endif
