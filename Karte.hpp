#ifndef Karte_H
#define Karte_H 1


#include <string>

class Karte{
    public:
        std::string bild;
        int value;
        std::string farbe;
        Karte(){
        }
        /**
         * @brief Construct a new Karte object
         * 
         * @param bildin Input des Bilds
         * @param farbein Input der Farbe
         * @param valuein Input des Punktwerts
         */
        Karte(std::string bildin,std::string farbein,int valuein = 0){
            farbe = farbein;
            bild = bildin;
            value = valuein;
        };
};

#endif