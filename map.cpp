#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <cctype>

std::string isvalytiZodi(const std::string& originalusZodis) {
    std::string isvalytas = "";
    for (char c : originalusZodis) {
        if (std::isalnum(c)) {
            isvalytas += std::tolower(c);
        }
    }
    return isvalytas;
}

int main() {
    std::ifstream ivestis("tekstas.txt");
    if (!ivestis) {
        std::cerr << "Klaida: Nepavyko atidaryti tekstas.txt failo!" << std::endl;
        return 1;
    }

    std::map<std::string, std::vector<int>> zodziuZodynas;
    std::string eilute;
    int eilutesNumeris = 0;

    while (std::getline(ivestis, eilute)) {
        eilutesNumeris++;
        std::stringstream ss(eilute);
        std::string nuskaitytasZodis;
        
        while (ss >> nuskaitytasZodis) {
            std::string svarusZodis = isvalytiZodi(nuskaitytasZodis);
            if (!svarusZodis.empty()) {
                zodziuZodynas[svarusZodis].push_back(eilutesNumeris);
            }
        }
    }
    ivestis.close();

    std::ofstream isvestis1("pasikartojimai.txt");
    std::ofstream isvestis2("cross_reference.txt");

    if (!isvestis1 || !isvestis2) {
        std::cerr << "Klaida: Nepavyko sukurti rezultatu failu!" << std::endl;
        return 1;
    }

    for (const auto& pora : zodziuZodynas) {
        if (pora.second.size() > 1) {
            isvestis1 << pora.first << " : " << pora.second.size() << "\n";

            isvestis2 << pora.first << " : ";
            for (size_t i = 0; i < pora.second.size(); ++i) {
                isvestis2 << pora.second[i];
                if (i < pora.second.size() - 1) {
                    isvestis2 << ", ";
                }
            }
            isvestis2 << "\n";
        }
    }

    isvestis1.close();
    isvestis2.close();

    std::cout << "Darbas baigtas!" << std::endl;
    return 0;
}