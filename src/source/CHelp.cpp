#include "../headers/CHelp.h"

using namespace std;

void CHelp::Do(string & args) {
    args.clear();
    mInterface->print<string>(HELP);
}

CHelp::CHelp(shared_ptr<CCalendar> & calendar, const shared_ptr<CInterface> & interface) : CCommand(calendar, interface){

}