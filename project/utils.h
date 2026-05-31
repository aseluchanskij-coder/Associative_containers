#pragma once
#include <string>
#include <unordered_set>

std::string isvalytiZodi(const std::string& originalusZodis);
std::string apvalytiZodiDelURL(std::string zodis);
bool arTaiURL(const std::string& zodis, const std::unordered_set<std::string>& tldSarasas);