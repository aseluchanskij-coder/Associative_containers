#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <cctype>

std::string apvalytiZodi(std::string zodis) {
    while (!zodis.empty() && (zodis.back() == ',' || zodis.back() == '.' || zodis.back() == ';' || zodis.back() == ')' || zodis.back() == ']' || zodis.back() == '"')) {
        zodis.pop_back();
    }
    while (!zodis.empty() && (zodis.front() == '(' || zodis.front() == '[' || zodis.front() == '"')) {
        zodis.erase(0, 1);
    }
    return zodis;
}

bool arTaiURL(const std::string& zodis, const std::unordered_set<std::string>& tldSarasas) {
    size_t pradziosIndeksas = 0;
    size_t protokolas = zodis.find("://");
    if (protokolas != std::string::npos) {
        pradziosIndeksas = protokolas + 3;
    }

    size_t pirmoSlesoIndeksas = zodis.find('/', pradziosIndeksas);
    std::string domenas = zodis.substr(0, pirmoSlesoIndeksas);

    size_t paskutinisTaskas = domenas.find_last_of('.');
    if (paskutinisTaskas != std::string::npos && paskutinisTaskas > pradziosIndeksas) {
        std::string tld = domenas.substr(paskutinisTaskas + 1);
        for (char& c : tld) {
            c = std::toupper(c);
        }
        if (tldSarasas.count(tld) > 0) {
            return true;
        }
    }
    return false;
}

int main() {
    std::ifstream tldFailas("galunes.txt");
    if (!tldFailas) {
        std::cerr << "Klaida: nerastas tld.txt failas!" << std::endl;
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

    std::ofstream isvestis("url_adresai.txt");
    if (!isvestis) {
        std::cerr << "Klaida: nepavyko sukurti url_adresai.txt!" << std::endl;
        return 1;
    }

    std::string nuskaitytasZodis;
    while (ivestis >> nuskaitytasZodis) {
        std::string isvalytas = apvalytiZodi(nuskaitytasZodis);
        if (arTaiURL(isvalytas, tldSarasas)) {
            isvestis << isvalytas << "\n";
        }
    }

    ivestis.close();
    isvestis.close();

    std::cout << "Darbas baigtas! Rasti URL adresai issaugoti i 'url_adresai.txt'" << std::endl;
    return 0;
}