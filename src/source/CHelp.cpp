#include "../headers/CHelp.h"

using namespace std;

void CHelp::Do() {
    mInterface->print<string>(HELP);
}

CHelp::CHelp(shared_ptr<CCalendar> & calendar, const shared_ptr<CInterface> & interface) : CCommand(calendar, interface, string()){

}

