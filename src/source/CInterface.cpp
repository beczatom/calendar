#include <string>
#include "../headers/CInterface.h"
#include "../headers/CEvent.h"

using namespace std;

string CInterface::getInput() const {
    char input[BUFFER_LENGTH];

    mIn.getline(input, BUFFER_LENGTH);

    if(mIn.eof()){
        throw runtime_error(EOF_RESPONSE);
    }

    if(mIn.fail()){
        mIn.clear();
        mIn.ignore();
        getInput();
        throw overflow_error(OVERFLOW_ERROR);
    }

    return string(input);
}

CInterface::CInterface()
    :mIn(cin),
    mOut(cout){
}

template void CInterface::print<string>(const string & obj) const;
template void CInterface::print<CEvent>(const CEvent & obj) const;

template<class T>
void CInterface::print(const T & obj) const {
    mOut << obj << endl;
}
