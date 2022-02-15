#include <iostream>
#include <string>
#include <vector>
#include "Karte.hpp"

/**
 * @brief Klasse der Spieler
 * Klasse für die Teilnehmer des Spieles
 * 
 * Speichert Name, Karten, Stiche Punkte  
 */
class Spieler{
    public:
        std::string name;

        /**
         * @brief Get the Karten object
         * 
         * @return std::vector<Karte> 
         */
        std::vector<Karte> getKarten(){
            return this->karten;
        }
        
        Spieler(){
        }

        /**
         * @brief Construct a new Spieler object
         * 
         * @param namein Name den Der Spieler Haben soll
         */
        Spieler(std::string namein){
            name = namein;
        };

        /**
         * @brief löscht Karte aus Hand
         * löscht die gelegte Karte aus der Kartenhand des  Spielers 
         * @param karteindex Index der Karte in der Liste von Karten die der Spieler hat
         */
        void removeKarte(int karteindex){
            this->karten.erase(this->karten.begin()+karteindex);
        }

        /**
         * @brief Get the Punkte object
         * Gibt Punkte aus
         * @return int 
         */
        int GetPunkte(){
            return punkte;
        }

        /**
         * @brief Speichert Stich zu Spieler
         * Speichert einen Stich, den der Spieler gewonnen hat
         * und berechnet die Punkte darin und schreibt sie dem eigenen Punkte-Konto gut
         * 
         * @param stich
         */
        void AddStich(std::vector<Karte> stich){
            stiche.push_back(stich);
            for (int i= 0; i<stich.size(); i++){
                punkte += stich[i].value;
            }
        }

        /**
         * @brief fügt Karte zum Stapel hinzu
         * 
         * @param kartein 
         */
        void addKarte(Karte kartein){
            this->karten.push_back(kartein);
        }
        void setKarten(std::vector<Karte> kartenin){
            this->karten = kartenin;
        }

        /**
         * @brief gibt alle Karten des Spielers auf dem Bildschirm aus
         * gibt jede Karte die Spieler X auf der Hand hand in neuer Zeile
         * in der Form, "Bild","Farbe" aus.
         * @pre Karten müssen ausgeteilt worden sein sonst sinnfrei.
         *      -> karten.size() != 0
         * @param 
         * @returns 
         * 
         */
        void showKarten(){
            for (int i = 0;i<this->karten.size();i++){
                std::cout<<i<<" "<<this->karten[i].bild<<","<<this->karten[i].farbe<<std::endl;
            }
            std::cout<<std::endl<<std::endl;
        }
    private:
        int punkte=0;
        std::vector<std::vector<Karte>> stiche;
        std::vector<Karte> karten;
};

/**
 * 1
 * 2
 * 3
 * 4
 * 5
 * 6
 * 
 * 8
 * 9
 * 10
 * 11
 * 12
 * 13
 * 14
 * 15
 * 16
 * 17
 * 18
 * 19
 * 20
 * 21
 * 
 * 23
 * 24
 * 25
 * 26
 * 27
 * 28
 * 29
 * 30
 * 31
 */