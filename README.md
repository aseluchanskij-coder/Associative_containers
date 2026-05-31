# Teksto analizės programa

## 1. Užduoties tikslas
* Suskaičiuoti, kiek kartų tekste pasikartoja skirtingi žodžiai.
* Nustatyti, kuriose teksto eilutėse tie pasikartojantys žodžiai yra paminėti.
* Surasti ir išrinkti visus tekste esančius pilnus bei sutrumpintus URL adresus.

## 2. Naudotos priemonės
* `std::map`
* `std::unordered_set`
* `std::vector`
* C++17 standartas
* CMake

## 3. Kaip paleisti programą
1. `cmake -S . -B build`
2. `cmake --build build`
3. `./build/programa`