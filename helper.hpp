#include <vector>
#include <random>
/**
 * @brief Teilt String an bestimmten Chars
 * Teilt einen String an einem gegebenen Zeichen, und gibt
 * die einzelteile als Array zurück
 * @param splitter Charakter nach welchem der String geteilt werden soll
 * @param source String welcher geteilt wird
 * @return std::vector<std::string> geteilter String
 */
std::vector<std::string> SplitStringByChar(char splitter,std::string source){
    int i;
    int from=0;
    std::vector<std::string> result;
    for ( i = 0;i<source.size()-1;i++){
        if (source[i] == splitter||i == source.size()-1){
            result.push_back(source.substr(from,i));
            from = i+1;
       }
    }
    result.push_back(source.substr(from,source.size()-1));
    return result;
}

/**
 * @brief generiert Zufällige Zahl
 * kreeirt zufällige Zahl zwischen zwei gegebenen integern
 * @param start niedrigere Zahl
 * @param end höhre Zahl
 * @returns Zufällige Zahl zwischen start und end
 */
int zufälligeZahlZwischen(int start, int end){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(start,end);
    return dist6(rng);
}