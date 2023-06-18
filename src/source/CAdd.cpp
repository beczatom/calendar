#include <sstream>
#include "../headers/CAdd.h"

using namespace std;

CAdd::CAdd(shared_ptr<CCalendar> & calendar, const shared_ptr<CInterface> & interface) : CCommand(calendar, interface){
}

void CAdd::Do(string & args) {
    args = args.substr(ADD_COMMAND.length());
    stringstream ss(args);

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