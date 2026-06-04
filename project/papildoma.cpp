#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <sstream>
#include "utils.h"

int main() {
    int counteris=0;
    std::ifstream ivestis("tekstas.txt");
    if (!ivestis) {
        std::cerr << "Klaida: Nepavyko atidaryti tekstas.txt failo!" << std::endl;
        return 1;
    }

    std::set<std::string, std::greater<std::string>> tanZodziai;
    std::string eilute;

    while (std::getline(ivestis, eilute)) {
        std::stringstream ss(eilute);
        std::string nuskaitytasZodis;
        while (ss >> nuskaitytasZodis) {
            std::string svarusZodis = isvalytiZodi(nuskaitytasZodis);
            if (!svarusZodis.empty() && svarusZodis.find("tan") != std::string::npos) {
                tanZodziai.insert(svarusZodis);
                counteris++;
            }
        } 
    }
    std::cout << counteris << std::endl;
    ivestis.close();

    std::ofstream isvestis("tan_zodziai.txt");
    if (!isvestis) {
        std::cerr << "Klaida: Nepavyko sukurti rezultatu failo!" << std::endl;
        return 1;
    }

    for (const auto& zodis : tanZodziai) {
        isvestis << zodis << "\n";
    }
    isvestis.close();

    std::cout << "Darbas baigtas, unikalus zodziai su 'tan' surasyti i tan_zodziai.txt failas." << std::endl;
    return 0;
}