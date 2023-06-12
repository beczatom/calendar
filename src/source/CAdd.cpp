#include <sstream>
#include "../headers/CAdd.h"

using namespace std;

CAdd::CAdd(shared_ptr<CCalendar> & calendar, const shared_ptr<CInterface> & interface, const string & args) : CCommand(calendar, interface, args){
}

void CAdd::Do() {
    stringstream ss(mArgs);

    if(!ss.good()){
        throw invalid_argument(INVALID_OPERATOR_ERROR);
    }

    CEvent event;
    while (!ss.eof()){
        event = CEvent(ss);
        if(ss.eof()) break;
        mCalendar->addEvent(event);
    }
}