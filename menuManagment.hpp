/**
 * this library generathe a mangmentoo to Dinamic Menu
*/

#include <iostream> //flujo 
#include <stdlib.h> //atoi
#include <iomanip> //setw

#include <unistd.h>//necesario
#include <termios.h>//necesaria

#include "logic.hpp"

namespace menuS
{
    

    //iterators
    long long int x0=27,a=17,c=43,m=100;
    //url file
    std::string url ="";
    //this a internall worck space
    namespace internal
    {
         
        /**
         * this function clean the screem to better print 
        */
        void clear_screen(){
            #ifdef WINDOWS
                std::system("cls");
            #else
                // linux
                std::system ("clear");
            #endif
        }
        /**
         * saber si es un numero
        */
       bool isNumber(std::string str){
           for(int i =0; i < str.size();i++){
               if(str[i] <= 47 || str[i] >= 58 ){
                    return false;
               }
           }
           return true;
       }
        /**
         * This function load the string and proces strign loaded
         * to generate a number 
        */
       long long int scanP(std::string var,long long int prevar){
           long long int num;
           std::string str="";
           std::cout<<"\nUse la palabra 'BACK' para regresar"<<"\n--->"<<var<<"\nIngrese un valor para "<<var;
           while (true)
           {    
               std::cout<<"\n$_ ";
               std::cin>>str;
               if(str == "back" || str == "BACK"){
                   num = prevar;
                   break;
               }else if(isNumber(str)){
                   num = std::atoll(str.c_str());
                   break;
               }else {
                    std::cout<<"\nIngrese un valor valido....\n";
               }
           }
           return num;
           
       }

        /**
         * process de election
        */
       bool  processElection(int election){
           int Nr =0;
           

           switch (election){
               //parametros
            case 0:
                x0 = scanP("X0",x0);
               return true;
               break;
            case 1:
                a = scanP("A",a);
               return true;
               break;
            case 2:
                c = scanP("C",c);
               return true;
               break;
            case 3:
                m = scanP("M",m);
               return true;
               break;
            //opciones
            //gen 
            case 4:
                clear_screen();
                logicS::printRGLC(x0,a,m,c,false,false);
                logicS::printRGLC(x0,a,m,c,false,true);
                url= 
                "X0" + std::to_string(x0)+
                "A" + std::to_string(a) +
                "C" + std::to_string(c) +
                "M" + std::to_string(m) +
                ".txt";
               return true;
               break;
            case 5:
                clear_screen();
                logicS::printRGLC(x0,a,m,0,true,false);
                logicS::printRGLC(x0,a,m,0,true,true);
                url= 
                "X0" + std::to_string(x0)+
                "A" + std::to_string(a) +
                "C" + std::to_string(c) +
                "M" + std::to_string(m) +
                ".txt";
                return true;
               break;
            case 6:
                clear_screen();
                std::cout<<"\n Este generador posee un periodo completo de 2147483647, por lo cual podría demorar bastante...\n";
                logicS::printRGLC(x0,16807,2147483647,0,false,true);
                url= 
                "X0" + std::to_string(x0)+
                "A" + std::to_string(a) +
                "C" + std::to_string(c) +
                "M" + std::to_string(m) +
                ".txt";
               return true;
               break;
            //pruebas
            case 7: //chi
                clear_screen();
                logicS::loadDataUNIFORM( url);
                
               return true;
               break;
            case 8: //kol
                clear_screen();
                logicS::loadDataUNIFORM( url,1);
                
               return true;
               break;
            case 9: //corridas
                clear_screen();
                logicS::loadDataINDEPENDECE(url);
                
               return true;
               break;
            case 10: //series
                clear_screen();
                logicS::loadDataINDEPENDECE(url,2);
               return true;
               break;
            case 11: //poker
                clear_screen();
                logicS::loadDataPOKER(url);
               return true;
               break;
            case 12: //poker
                clear_screen();
                logicS::loadDataPOKER(url,2);
               return true;
               break;
            case 13: //poker
                clear_screen();
                std::cout<<"\nGenerando numeros aleatorios en el archivo\n se hará la prueba con 1000 datos";
                url="randCompile.txt";

                // Nr =scanP("N (el numero de iteracciones con el compilador)",-1);

                logicS::genCompileRandNumbers(1000);
               return true;
               break;
          //exit
           case 14:
               std::cout<<"\n\n---Thanks For Using ---\n\n";
               return false;
               break;
           default:
                return true;
               break;
           }
           
        
       }

       /**
        * arrays
       */
       int getch_echo(bool echo=true){
            struct termios oldt, newt;
            int ch;
            tcgetattr( STDIN_FILENO, &oldt );
            newt = oldt;
            newt.c_lflag &= ~ICANON;
            if(echo)
                newt.c_lflag &=  ECHO;
            else
                newt.c_lflag &= ~ECHO;
            tcsetattr( STDIN_FILENO, TCSANOW, &newt );
            ch = getchar();
            tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
            return ch;
        }

        int getch(){
            getch_echo(false);
        }

        int getche(){
            getch_echo(true);
        }
      

    } // namespace internal

    //includ internal space
    // using namespace internal;s

    void mainMenu(){
        //selector 
        int selector=0;
        //continuar
        bool contin=true;
        //sizes
        int 
        widthCTR = 30,
        widthSep=widthCTR*3/2,
        widthDates=17;

        do
        {
            // del to spacement
            internal::clear_screen();
            //tittle 
            std::cout
            <<std::right
            <<" "<<std::setw(widthSep)<<std::setfill('=')<<""<<std::endl
            <<"|"<<std::setw(widthCTR )<<std::setfill(' ')<<"TALLER GENERADORES"<<std::endl
            <<"|"<<std::setw(widthSep)<<std::setfill('=')<<""<<std::endl
            // <<"|"<<std::setw(widthSep)<<std::setfill('=')<<""<<std::endl
            //menu Parametro
            <<"|"<<std::setw(widthSep)<<std::setfill('-')<<""<<std::endl
            <<"|"<<std::setw(widthDates)<<std::setfill(' ')<<std::left<<"      PARAMETROS"<<std::endl
            <<std::right
            <<"|"<<std::setw(widthSep)<<std::setfill('-')<<""<<std::endl<<"|Generar:"<<std::endl
            <<"|URL actual:= "<<url<<std::endl
            //selector print
            <<std::right<<std::setfill('.')

            << ((selector==0)? "|\t >>":"|\t   ") << " X0"<<std::setw(widthDates)<<x0<<std::endl
            << ((selector==1)? "|\t >>":"|\t   ") << " A "<<std::setw(widthDates)<<a<<std::endl
            << ((selector==2)? "|\t >>":"|\t   ") << " C "<<std::setw(widthDates)<<c<<std::endl
            << ((selector==3)? "|\t >>":"|\t   ") << " M "<<std::setw(widthDates)<<m<<std::endl
            
            //Menu opciones
            <<"|"<<std::setw(widthSep)<<std::setfill('-')<<""<<std::endl
            <<"|"<<std::setw(widthDates)<<std::setfill(' ')<<std::left<<"      OPCIONES"<<std::endl
            
            <<"|"<<std::setw(widthSep)<<std::setfill('-')<<""<<std::endl<<std::left<<std::setfill(' ')<<"|Generar:"<<std::endl

            << ((selector==4)? "|\t >>":"|\t   ") <<std::setw(widthDates)<<" Iterar con GLC"<<std::endl
            << ((selector==5)? "|\t >>":"|\t   ") <<std::setw(widthDates)<<" Iterar con GLC Fact(C=0)"<<std::endl
            << ((selector==6)? "|\t >>":"|\t   ") <<std::setw(widthDates)<<" Mostrar GEM (WARNING)"<<std::endl
            <<"|"<<std::setw(widthSep)<<std::setfill('-')<<""<<std::endl<<std::left<<std::setfill(' ')<<"|P.B.U.:"<<std::endl
            << ((selector==7)? "|\t >>":"|\t   ") <<std::setw(widthDates)<<" Chi cuadrado x²"<<std::endl
            << ((selector==8)? "|\t >>":"|\t   ") <<std::setw(widthDates)<<" Kolmogorov–Smirnov "<<std::endl
            <<"|"<<std::setw(widthSep)<<std::setfill('-')<<""<<std::endl<<std::left<<std::setfill(' ')<<"|P.B.I.:"<<std::endl
            << ((selector==9)? "|\t >>":"|\t   ") <<std::setw(widthDates)<<" Corridas"<<std::endl
            << ((selector==10)? "|\t >>":"|\t   ") <<std::setw(widthDates)<<" Series"<<std::endl
            << ((selector==11)? "|\t >>":"|\t   ") <<std::setw(widthDates)<<" Poker 3"<<std::endl
            << ((selector==12)? "|\t >>":"|\t   ") <<std::setw(widthDates)<<" Poker 5"<<std::endl
            <<"|"<<std::setw(widthSep)<<std::setfill('-')<<""<<std::endl<<std::left<<std::setfill(' ')<<"|Rand():"<<std::endl
            << ((selector==13)? "|\t >>":"|\t   ") <<std::setw(widthDates)<<" Usar generador del compilador"<<std::endl
            <<"|"<<std::setw(widthSep)<<std::setfill('-')<<""<<std::endl<<std::left<<std::setfill(' ')<<"|Exit :"<<std::endl
            << ((selector==14)? "|\t >>":"|\t   ") <<std::setw(widthDates)<<" Exit"<<std::endl

            <<std::setw(widthSep)<<std::setfill('-')<<""<<std::endl<<std::right;

            //load options 27 91 
            int key;
            while (true)
            {
                key =internal::getch();
                if(key==27){
                    key =internal::getch();
                    if(key==91){
                        key =internal::getch();
                    }
                }
                if(key==65||key== 66||key ==10){
                    break;
                }
            }
            
            
            // load option
            switch (key)
            {
            case 65:
                selector--;
                if(selector <0)
                    selector=14;
                break;
            case 66:
                selector++;
                selector %=15;
                break;
            case 10:
                contin= internal::processElection(selector);
                internal::getch();
                // selector=-1;
                break;
            default:
                break;
            }
        } while (contin);
        

        
        //optoin
        //process
    }
} // namespace menuS


