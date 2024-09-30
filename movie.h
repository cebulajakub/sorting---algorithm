#pragma once
#include <string>

struct movie {
    std::string name;  // nazwa filmu
    std::string tytul1;
    float rating;      // ocena filmu (0-10)
    int votes;
    int id1;
    bool operator<(const movie& compared) const { return (rating < compared.rating); }
    bool operator>(const movie& compared) const { return (rating > compared.rating); }
};