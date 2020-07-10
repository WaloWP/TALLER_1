/**
 * this are the  library where implement the functions 
 * to porceess the main function 
*/

#ifndef _LOGIC_H_
#define _LOGIC_H_

#include <iostream>
#include <iomanip> //setw
#include <fstream> //archiovs
#include <string>

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
        
        /**
         * this function aplly the generator to gen new numbers and classific this 
        */

        /**
         * this function clasifict diferent dates of array 
        */

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
     * 
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
     * with this function allow execute 
     * 
    */ 
    void loadData(std::string url ){
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

            while (getline(loadF,line)){
                //rx saved
                double dato;
                try{
                    dato = std::stod(line);
                }catch(const std::exception& e){
                    std::cerr << e.what() << '\n';
                }

                for(int i =0; i< 10;i++){
                    if(
                        (0.0 + ((double)i/10)) <= dato && (0.1 + ((double)i/10))>dato){
                        FO[i]++;
                    }
                }

                //increase the data count to use FE
                countD++;
            }
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
            // std::cout<<<<std::endl; 
       }else {
           std::cout<<"Dont exist file "<<url<<std::endl;
       }
   }


} // namespace logicS

#endif
