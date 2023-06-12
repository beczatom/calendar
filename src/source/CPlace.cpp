#include <string>
#include <iostream>
#include "../headers/CPlace.h"
#include "../constants.h"

using namespace std;

bool checkPlace(const string &name, int capacity){
    if(name.empty() || capacity <= 0){
        return false;
    }
    return true;
}

CPlace::CPlace(const std::string &name, int capacity){
    if(checkPlace(name, capacity)){
        mName = name;
        mCapacity = capacity;
    }
    else throw invalid_argument(PLACE_ERROR);
}

ostream &operator<<(ostream & os, const CPlace &place) {
    return os << place.mName << PRINT_TO_CONSOLE_DELIMITER << place.mCapacity;
}

CPlace::CPlace(const CPlace &place) {
    mName = place.mName;
    mCapacity = place.mCapacity;
}

CPlace::CPlace()
        :mName(),
         mCapacity(0){}

bool CPlace::operator==(const CPlace &place) const {
    return mName == place.mName;
}

bool CPlace::empty() const {
    return mName.empty();
}

string CPlace::toString() const {
    return string(mName + PRINT_TO_CONSOLE_DELIMITER + to_string(mCapacity));
}

CPlace::CPlace(const std::string &str) {
    char name[BUFFER_LENGTH];
    int capacity;
    char controlChar;

    if(sscanf(str.c_str(), "%s %d%c", name, &capacity, &controlChar) != 2){
        throw invalid_argument(PLACE_ERROR);
    }

    if(checkPlace(name, capacity)){
        mName = name;
        mCapacity = capacity;
    }
    else throw invalid_argument(PLACE_ERROR);
}

int CPlace::getCapacity() const {
    return mCapacity;
}

std::string CPlace::getName() const {
    return mName;
}

bool CPlace::operator<(const CPlace &place) const{
    return mName < place.mName;
}
