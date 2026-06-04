#include "utils.h"
#include <locale>
#include <codecvt>
#include <cctype>

std::string isvalytiZodi(const std::string& originalusZodis) {
    try {
        std::locale loc(""); 
        
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::wstring wideZodis = converter.from_bytes(originalusZodis);
        std::wstring wideIsvalytas = L"";
        
        for (wchar_t wc : wideZodis) {
            if (std::isalnum(wc, loc)) {
                wideIsvalytas += std::tolower(wc, loc);
            }
        }
        
        return converter.to_bytes(wideIsvalytas);
    } catch (...) {
        return "";
    }
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