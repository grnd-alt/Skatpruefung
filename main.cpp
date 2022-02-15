#include <iostream>
#include <string>
#include <vector>
#include "Spieler.hpp"
#include "Karte.hpp"
#include "helper.hpp"







/**
 * @brief HauptKlasse für gesamtes Spiel
 * Diese Klasse managed den Rest aller Klassen,
 * und ruft alle anderen nötigen Funktionen und Klassen auf
 * speichert, spieler, den Kartenstapel,  
 *
 */
class Spiel{
    public:
        std::vector<Karte> stapel;
        std::vector<std::string> bilder =   {"Ass", "Zehn", "Koenig",   "Ober", "Unter","Neun", "Acht", "Sieben"};
        std::vector<int> values =           {11,    10,     4,          3,      2,      0,      0,      0};
        std::vector<std::string> farben = {"Schellen","Gruen","Rot","Eichel"};
        std::vector<Karte> skat;
        std::vector<Spieler> allespieler;

        /**
         * @brief Construct a new Spiel object
         * Initialisiert ein neues Spiel, teilt Karten aus
         * fragt Spieler nach Namen, tut restliche Karten ins Skat
         * 
         */
        Spiel(){
            std::vector<Karte> allekarten = kartenErstellen();
            std::vector<int> indizes;
            std::cout<<"testdaten Laden? (y/n)";
            std::string test;
            std::cin>>test;
            if(test != "y"){
                int i;
                for (i = 0;i<32;i++){
                    indizes.push_back(i);
                }
                int index;
                std::string nameholder;
                for (i = 0; i<3;i++){
                    std::cout<<"Namen fuer Spieler "<< i <<" eingeben:";
                    std::getline(std::cin,nameholder);
                    allespieler.push_back(Spieler(nameholder));
                    for (int j = 0;j<10;j++){
                        index = zufälligeZahlZwischen(0,indizes.size()-1);
                        allespieler[i].addKarte(allekarten[indizes[index]]);
                        indizes.erase(indizes.begin() + index);
                    }
                }
                for (i = 0; i<indizes.size();i++){
                    skat.push_back(allekarten[indizes[i]]);
                }
            }
            else{
                allespieler.push_back(Spieler("Spieler 1"));
                allespieler.push_back(Spieler("Spieler 2"));
                allespieler.push_back(Spieler("Spieler 3"));
                std::vector<Karte> karten1 = {allekarten[16],allekarten[19],allekarten[0],allekarten[4],allekarten[23],allekarten[13],allekarten[9],allekarten[14],allekarten[31],allekarten[25]};
                allespieler[0].setKarten(karten1);
                karten1 = {allekarten[17],allekarten[18],allekarten[1],allekarten[5],allekarten[10],allekarten[11],allekarten[26],allekarten[15],allekarten[30],allekarten[27]};
                allespieler[1].setKarten(karten1);
                karten1 = {allekarten[8],allekarten[12],allekarten[2],allekarten[20],allekarten[24],allekarten[28],allekarten[3],allekarten[21],allekarten[6],allekarten[29]};
                allespieler[2].setKarten(karten1);
                skat = {allekarten[7],allekarten[22]};
            }
        }

        /**
         * @brief interpretiert Befehle
         * handelt nache Befehlen
         * meinekarten
         * punkte
         * stapel
         * @param cmd eingegebener Befehl
         * @param spieler spieler der den Befehl eingab
         * @returns -1 quit program
         * @returns 0  no command
         * @returns 1  command handled
         */
        int CommandHandler(std::string cmd,Spieler spieler){
            if(cmd.size() == 0){
                return 1;
            }
            if(cmd[0]!='/'){
                return 0; 
            }
            cmd = cmd.substr(1,cmd.size());
            if(cmd == "stop"){
                return -1;
            }
            if(cmd == "meinekarten"){
                spieler.showKarten();
            }
            if(cmd == "punkte"){
                std::cout<<spieler.GetPunkte()<<std::endl;
            }
            if(cmd == "stapel"){
                ShowStapel();
            }
            return 1;
        }
        /**
         * @brief gibt liegenden Kartenstapel aus
         * 
         */
        void ShowStapel(){
            if(stapel.size()>0){
                std::cout<<"Diese Karten liegen auf dem Stapel: (letzte liegt ganz Oben)"<<std::endl;
                for(int j = 0; j<stapel.size();j++){
                    std::cout<<stapel[j].bild<<","<<stapel[j].farbe<<std::endl<<std::endl;
                }
            }
        }
        /**
         * @brief Hauptfunktion managed Spiel
         * Läuft in einer Schleife über alle 11 Spielrunden,
         * beachtet dabei wer an der Reihe ist, welche Karten liegen,
         * verteilt den Stich an den Spieler der in Gewonnen hat,
         * Ruft Unterfunktionen auf die gelegte Karten validieren
         * und prüfen wer einen Stich gewinnt,
         * Macht Ausgaben an die Spieler in der Konsole
         * 
         * @param
         * @returns
         */
        void GameLoop(){
            int round = 1;
            std::string cmd;
            int amzugindex = 0;
            while (round < 11){                                                                                             // 10 runden lang legen die Spieler Karten
                for (int i = 0;i<3;i++){
                    Spieler& amzug = allespieler[amzugindex];                                                               // Pointer zu Object des Spielers der am Zug ist um Veränderungen der Daten machen zu können
                    std::cout<<amzug.name<<" ist an der Reihe"<<std::endl<<std::endl;
                    std::cout<<"diese Karten hast du auf der Hand:"<<std::endl;
                    amzug.showKarten();
                    std::cout<<std::endl;
                    ShowStapel();
                    std::cout<<std::endl;
                    bool valid = false;
                    while (!valid){                                                                                             //solange die Karte die der Spieler legen möchte nicht validiert ist muss er es erneut versuchen     
                        std::cout<<"welche Karte m"<<static_cast<unsigned char>(148)<<"chtest du Spielen: ";
                        std::cin>>cmd;
                        std::vector<std::string> legen;
                        switch(CommandHandler(cmd,amzug)){
                            case 0:
                                try{
                                    int cmdind = std::stoi(cmd);                                                                // string und int verarbeitung möglich
                                    Karte legen = amzug.getKarten()[cmdind];
                                    if(this->validiereBedienen(legen,amzug)){
                                        stapel.push_back(amzug.getKarten()[cmdind]);                                             //Karte auf den Stapel legen
                                        amzug.removeKarte(cmdind);                                                                   //Karte von der Hand des Spielers entfernen
                                        valid = true;                                                                           //Überprüfung abgeschlossen                                        
                                    }
                                }
                                catch(...){
                                    legen = SplitStringByChar(',',cmd);                                        //UserInput in einzelteile zerlegen BSP.: "Ass,Schellen" -> {"Ass","Schellen"}
                                    for (int j = 0; j<amzug.getKarten().size();j++){
                                        if(amzug.getKarten()[j].bild == legen[0] && amzug.getKarten()[j].farbe == legen[1]){            //Überprüfen ob der Spieler die Karte auf der Hand hat
                                            if(this->validiereBedienen(Karte(legen[0],legen[1]),amzug)){
                                                stapel.push_back(amzug.getKarten()[j]);                                             //Karte auf den Stapel legen
                                                amzug.removeKarte(j);                                                                   //Karte von der Hand des Spielers entfernen
                                                valid = true;                                                                           //Überprüfung abgeschlossen
                                                break;                                                                                  //for-schleife wird vorzeitig beendet um "Zeit zu sparen"    
                                            }
                                        }
                                    }
                                }
                                if(!valid){
                                    std::cout<<"FEHLER, Karte kann nicht gespielt werden!!!"<<std::endl;
                                    std::cout<<"Bitte versuche es noch einmal"<<std::endl<<std::endl;
                                }
                                break;
                            case 1:
                                break;
                            case -1:
                                return;
                        }
                    }
                    std::cout<<std::endl<<std::endl;
                    if(i == 2) continue;
                    if(amzugindex != 2){
                        amzugindex++;
                        continue;
                    }
                    amzugindex = 0;                                                         // wenn der Spieler mit dem letzten Index an dere Reihe ist, ist der Spieler mit Index 0 der nächste
                }

                amzugindex = GewinnerStich(amzugindex);                
                Spieler& gewinner = allespieler[amzugindex];                              
                gewinner.AddStich(stapel);                                                  // Stich wird dem Gewinner der Runde zu geschrieben
                stapel.clear();
                round++;

                std::cout<<"Runde ist vorbei"<<std::endl;
                for(int i = 0; i<25;i++){
                    std::cout<<"*";
                };
                std::cout<<gewinner.name<<" Hat den Stich gewonnen"<<std::endl;
    	        std::cout<<std::endl;
                std::cout<<std::endl;
                std::cout<<std::endl;
                std::cout<<std::endl;

            };
            allespieler[amzugindex].AddStich(skat);
            std::vector<Spieler> gewinner = GewinnerSpiel(allespieler);
            for (int i = 0;i<3;i++){
                std::cout<<gewinner[i].name<<": "<<gewinner[i].GetPunkte()<<std::endl;
            }
            std::cout<<gewinner[2].name<<" Hat das Spiel mit nur: "<<gewinner[2].GetPunkte()<<" Punkten gewonnen!"<<std::endl<<"Herzlichen Glückwunsch"<<std::endl;
        }

        /**
         * @brief erkennt die Rangliste des Spiels
         * sortiert alle Spieler nach ihren Punkten, wobei spieler[0] die meisten 
         * Punkte hat und somit verliert
         * @param spieler alle Spieler des Spiels
         * @return std::vector<Spieler> alle Spieler des Spiels sortiert nach ihren Punkten
         */
        std::vector<Spieler> GewinnerSpiel(std::vector<Spieler> spieler){
            bool sortiert = false;
            while (!sortiert){
                sortiert = true;
                for (int i = 0; i<spieler.size()-1;i++){
                    if(spieler[i].GetPunkte()<spieler[i+1].GetPunkte()){
                        Spieler temp = spieler[i];
                        spieler[i] = spieler[i+1];
                        spieler[i+1] = temp;
                        sortiert = false;
                    }
                }
            }
            return spieler;
        };

        /**
         * @brief berechnet Gewinner eines Stichs
         * prüft welche Karte, die richtig bedient ist, das höchste Bild zeigt,
         * prüft ob jemand gestochen hat,
         * prüft höchste Farbe wenn Trumpf gefordert ist,
         * @param letzteramzugindex Index des Spielers der zuletzt am Zug war in Variable: allespieler
         * @return int Index des Spielers in variable: allespieler
         */
        int GewinnerStich(int letzteramzugindex){
            int höchstekarteindex = 0;
            for(int i = 1;i<stapel.size();i++){
                if(stapel[i].bild!="Unter"){                                                                    
                    if(stapel[i].farbe!=stapel[höchstekarteindex].farbe){                                       // wenn Farbe nicht bedient wurde
                        continue;                                                                               // kann die momentane Karte nicht höher sein als die höchste bis dahin
                    }
                    if(stapel[höchstekarteindex].bild != "Unter"){                                              // wenn Höchste Karte kein Trumpf ist
                        if(GetIndex(stapel[i].bild,bilder)<GetIndex(stapel[höchstekarteindex].bild,bilder)){    // und momentane Karte kleineren Index als die höchste hat
                            höchstekarteindex=i;                                                                // dann hat die momentane Karte ein höherwertiges Bild
                        }
                    }
                }
                else{                                                                                           // momentane Karte ist ein Trumpf
                    if(stapel[höchstekarteindex].bild != "Unter"){                                              // höchste Karte auf Stapel ist Kein Trumpf
                        höchstekarteindex = i;                                                                  // momentane Karte Sticht höchste Karte auf Stapel automatisch
                        continue;
                    }
                    if(GetIndex(stapel[höchstekarteindex].farbe,farben)<GetIndex(stapel[i].farbe,farben)){      // wenn höchste Karte Trumpf ist und die höchste Karte einen niedrigeren Index hat als die Momentane Karte
                        höchstekarteindex = i;                                                                  // dann hat die Momentane Karte eine höherwertige Farbe
                        continue;
                    }
                }
            }
            return (letzteramzugindex+1+höchstekarteindex)%3;                                                   // Berechnung, des Gewinners mit Grundlage des letzten spielers und des Index der Höchsten Karte, Rechenweg auf Nachfrage.
        };
    private:

        /**
         * @brief validiert gelegte Karte
         * prüft ob eine Karte, richtig Bedient (Trumpf Farbe)
         * prüft ob, wenn Karte nicht bedient, eine passende Karte
         * auf der Hand wäre
         * @param kartezumlegen Karte die der Spieler legen möchte
         * @param amzug Spieler der die Karte legen möchte
         * @return true Karte richtig gelegt 
         * @return false Karte falsch gelegt
         */
        bool validiereBedienen(Karte kartezumlegen,Spieler amzug){
            if(this->stapel.size()>0){                                                                                          // erste Karte immer valide
                if (this->stapel[0].bild != "Unter"){                                                                           // wenn Trumpf gefordert ist besondere Regeln
                    if(this->stapel[0].farbe == kartezumlegen.farbe && kartezumlegen.bild != "Unter"){                          // wenn farbe bedient wird, und Bild kein Trumpf ist
                        return true;                                                                                            // darf die Karte gelegt werden
                    }
                    for(int i = 0;i<amzug.getKarten().size();i++){                                                              // falls Farbe nicht bedient
                        if (amzug.getKarten()[i].farbe == this->stapel[0].farbe && amzug.getKarten()[i].bild != "Unter"){       // wird für jede Karte geprüft ob sie die zu bedienende Farbe ist
                            return false;                                                                                       // ist das der Fall hätte diese Karte gelegt werden müssen
                        }
                    }
                    return true;                                                                                                // wurde keine Farbe gefunden die zur geforderten Farbe passt, ist die Karte valide
                }
                else{
                    if(kartezumlegen.bild != "Unter"){                                                                          // wenn gelegte Karte kein Trumpf ist   
                        for(int i = 0;i<amzug.getKarten().size();i++){                                                          
                            if (amzug.getKarten()[i].bild == "Unter"){                                                          // wird die Hand des Spielers auf Trumpf kontrolliert
                                return false;                                                                                   // Trumpf vorhanden -> falsch bedient
                            }
                        }
                        return true;                                                                                            // kein Trumpf gefunden -> richtig bedient
                    }
                    return true;                                                                                                // Trumpf auf Trumpf -> richtig bedient
                }
            }
            return true;
        };
        /**
         * @brief Get the Index object
         * sucht nach einem String in einem Array von Strings
         * @param searching string der gesucht ist
         * @param input Array in dem gesucht wird 
         * @return int index des gesuchten Elements in Array, falls nicht vorhanden -1
         */
        int GetIndex(std::string searching, std::vector<std::string> input){
            for (int i = 0;i<input.size();i++){
                if (input[i] == searching){
                    return i;
                }
            }
            return -1;
        }

        /**
         * @brief erstellt jede mögliche karte
         * erstellt jede mögliche Karte aus den vectoren bilder,farben und values,
         * somit gibt es ein Objekt für jedes Bild mit jeder Farbe,
         * 
         * @return std::vector<Karte> gibt Liste von Karten zurück
         */
        std::vector<Karte> kartenErstellen(){
            std::vector<Karte> allekarten;
            int i;
            for (int i = 0; i<8;i++){
                for (int j = 0; j<4;j++){
                    Karte karte = Karte(bilder[i],farben[j],values[i]);
                    allekarten.push_back(karte);
                    std::cout<<allekarten.size()-1<<" "<<karte.bild<<","<<karte.farbe<<std::endl;
                }
            }
            return allekarten;
        }
};




/**
 * @brief main
 * 
 * @return int 
 */
int main(){
    Spiel spiel = Spiel();
    spiel.GameLoop();
}