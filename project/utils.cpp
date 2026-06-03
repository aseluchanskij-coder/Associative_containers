#include "utils.h"

std::string isvalytiZodi(const std::string& originalusZodis) {
    std::string isvalytas = "";
    
    for (size_t i = 0; i < originalusZodis.length(); ++i) {
        unsigned char c = originalusZodis[i];

        if (c >= 'A' && c <= 'Z') {
            isvalytas += static_cast<char>(c + 32); 
        } else if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
            isvalytas += static_cast<char>(c);
        }
        
        else if (c > 127) {
            if (i + 1 < originalusZodis.length()) {
                unsigned char next = originalusZodis[i + 1];

                if (c == 0xD0) {
                    if (next >= 0x90 && next <= 0x9F) { 
                        isvalytas += static_cast<char>(0xD0);
                        isvalytas += static_cast<char>(next + 0x20);
                        i++; continue;
                    } else if (next >= 0xA0 && next <= 0xAF) { 
                        isvalytas += static_cast<char>(0xD1);
                        isvalytas += static_cast<char>(next - 0x20);
                        i++; continue;
                    } else if (next == 0x81) { 
                        isvalytas += static_cast<char>(0xD1);
                        isvalytas += static_cast<char>(0x91);
                        i++; continue;
                    }
                }

                if (c == 0xC4) {
                    if (next == 0x84 || next == 0x8C || next == 0x96 || next == 0x98 || next == 0xAE) { // Ą, Č, Ė, Ę, Į
                        isvalytas += static_cast<char>(0xC4);
                        isvalytas += static_cast<char>(next + 1);
                        i++; continue;
                    }
                }
                if (c == 0xC5) {
                    if (next == 0xA0 || next == 0xAA || next == 0xB2 || next == 0xBD) { // Š, Ū, Ų, Ž
                        isvalytas += static_cast<char>(0xC5);
                        isvalytas += static_cast<char>(next + 1);
                        i++; continue;
                    }
                }
            }

            isvalytas += static_cast<char>(c);
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