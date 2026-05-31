#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <unordered_set>
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

std::string apvalytiZodiDelURL(std::string zodis) {
    while (!zodis.empty() && (zodis.back() == ',' || zodis.back() == '.' || zodis.back() == ';' || zodis.back() == ')' || zodis.back() == ']' || zodis.back() == '"' || zodis.back() == '/' || zodis.back() == '!')) {
        zodis.pop_back();
    }
    while (!zodis.empty() && (zodis.front() == '(' || zodis.front() == '[' || zodis.front() == '"')) {
        zodis.erase(0, 1);
    }
    return zodis;
}

bool arTaiURL(const std::string& zodis, const std::unordered_set<std::string>& tldSarasas) {
    if (zodis.find("://") != std::string::npos) {
        return true;
    }
    if (zodis.rfind("www.", 0) == 0) {
        return true;
    }

    size_t paskutinisTaskas = zodis.find_last_of('.');
    if (paskutinisTaskas != std::string::npos && paskutinisTaskas > 0 && paskutinisTaskas < zodis.length() - 1) {
        std::string tld = zodis.substr(paskutinisTaskas + 1);
        for (char& c : tld) {
            c = std::toupper(c);
        }
        
        if (tldSarasas.count(tld) > 0) {
            for (size_t i = 0; i < paskutinisTaskas; ++i) {
                if (zodis[i] < 0) {
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}

int main() {
    std::ifstream tldFailas("galunes.txt");
    if (!tldFailas) {
        std::cerr << "Klaida: nerastas galunes.txt failas!" << std::endl;
        return 1;
    }

    std::unordered_set<std::string> tldSarasas;
    std::string tld;
    while (tldFailas >> tld) {
        tldSarasas.insert(tld);
    }
    tldFailas.close();

    std::ifstream ivestis("tekstas.txt");
    if (!ivestis) {
        std::cerr << "Klaida: nerastas tekstas.txt failas!" << std::endl;
        return 1;
    }

    std::map<std::string, std::vector<int>> zodziuZodynas;
    std::vector<std::string> rastiUrlai;
    std::string eilute;
    int eilutesNumeris = 0;

    while (std::getline(ivestis, eilute)) {
        eilutesNumeris++;
        std::stringstream ss(eilute);
        std::string nuskaitytasZodis;
        
        while (ss >> nuskaitytasZodis) {
            std::string urlIsvalytas = apvalytiZodiDelURL(nuskaitytasZodis);
            if (arTaiURL(urlIsvalytas, tldSarasas)) {
                rastiUrlai.push_back(urlIsvalytas);
            }

            std::string svarusZodis = isvalytiZodi(nuskaitytasZodis);
            if (!svarusZodis.empty()) {
                zodziuZodynas[svarusZodis].push_back(eilutesNumeris);
            }
        }
    }
    ivestis.close();

    std::ofstream isvestis1("pasikartojimai.txt");
    std::ofstream isvestis2("cross_reference.txt");
    std::ofstream isvestis3("url_adresai.txt");

    if (!isvestis1 || !isvestis2 || !isvestis3) {
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

    for (const auto& url : rastiUrlai) {
        isvestis3 << url << "\n";
    }

    isvestis1.close();
    isvestis2.close();
    isvestis3.close();

    std::cout << "Darbas baigtas." << std::endl;
    return 0;
}