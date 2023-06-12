#include "../headers/CPerson.h"
#include "../constants.h"

using namespace std;

bool checkPerson(const string &name, const string & surname){
    return !name.empty() && !surname.empty();
}

CPerson::CPerson(const std::string &name, const std::string &surname, const std::string &email){
    if(checkPerson(name, surname)){
        mName = name;
        mSurname = surname;
        mEmail = email;
    }
    else throw invalid_argument(PERSON_ERROR);
}

bool CPerson::operator<(const CPerson &person) const {
    if(mSurname == person.mSurname){
        return mName < person.mName;
    }
    return mSurname < person.mSurname;
}

ostream &operator<<(ostream &os, const CPerson &person) {
    os << person.mSurname << PRINT_TO_CONSOLE_DELIMITER << person.mName;

    if(person.mEmail.size() == 0)
        return os;

    os << PRINT_TO_CONSOLE_DELIMITER << person.mEmail;
    return os;
}

CPerson::CPerson()
        :mName(),
         mSurname(),
         mEmail(){}


bool CPerson::operator==(const CPerson &person) const {
    return !(*this < person) && !(person < *this);
}

string CPerson::toString() const {
    if(mEmail.empty()){
        return string(mName + PRINT_TO_CONSOLE_DELIMITER + mSurname);
    }
    return string(mName + PRINT_TO_CONSOLE_DELIMITER + mSurname + PRINT_TO_CONSOLE_DELIMITER + mEmail);
}

CPerson::CPerson(const char * str) {
    if(!str) throw invalid_argument(PERSON_ERROR);

    char name[BUFFER_LENGTH];
    char surname[BUFFER_LENGTH];
    char email[BUFFER_LENGTH];

    int read = sscanf(str, "%s %s %s", name, surname, email);
    // case : no email
    if(read == 2){
        if(checkPerson(name, surname)){
            mName = string(name);
            mSurname = string(surname);
        }
        else throw invalid_argument(PERSON_ERROR);
    }
    // case : is email
    else if(read == 3){
        if(checkPerson(name, surname)){
            mName = string(name);
            mSurname = string(surname);
            mEmail = string(email);
        }
        else throw invalid_argument(PERSON_ERROR);
    }
    else throw invalid_argument(PERSON_ERROR);
}
