#include "../headers/CCommand.h"

#include <utility>
#include "../headers/CHelp.h"
#include "../headers/CImport.h"
#include "../headers/CPrint.h"
#include "../headers/CSelect.h"
#include "../headers/CAdd.h"
#include "../constants.h"

using namespace std;

bool startsWith(const std::string &word, const std::string &prefix) {
    if (word.length() < prefix.length()) return false;
    for (size_t i = 0; i < prefix.size(); i++) {
        if (word[i] != prefix[i]) return false;
    }
    return true;
}

CCommand::CCommand(shared_ptr<CCalendar> & calendar, const shared_ptr<CInterface> & interface, const std::string & args)
        : mCalendar(calendar),
          mInterface(interface),
          mArgs(std::move(args)) {
}

void CCommand::Do() {
    //deciding which command to execute
    if (startsWith(mArgs, HELP_COMMAND)) {
        CHelp(mCalendar, mInterface).Do();
    }
    else if (startsWith(mArgs, IMPORT_COMMAND)) {
        CImport(mCalendar, mInterface, mArgs).Do();
    } else if (startsWith(mArgs, ADD_COMMAND)) {
       CAdd(mCalendar, mInterface, mArgs.substr(ADD_COMMAND.length())).Do();
    }
    else if (startsWith(mArgs, SELECT_COMMAND)) {
        CSelect(mCalendar, mInterface, mArgs.substr(SELECT_COMMAND.length())).Do();
    }
    else if (startsWith(mArgs, DAY_COMMAND) || startsWith(mArgs, WEEK_COMMAND) ||
               startsWith(mArgs, MONTH_COMMAND)) {
        CPrint(mCalendar, mInterface, mArgs).Do();
    }
    else {
        throw invalid_argument(INVALID_COMMAND_ERROR);
    }
}



