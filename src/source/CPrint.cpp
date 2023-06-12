#include <sstream>
#include "../headers/CPrint.h"
#include "../headers/CCalendarFormat.h"
#include "../headers/CCalendarFormatDay.h"
#include "../headers/CCalendarFormatWeek.h"
#include "../headers/CCalendarFormatMonth.h"
#include "../headers/CExport.h"
#include "../constants.h"

using namespace std;

//returns true if the string starts with given prefix
bool startsWithString(const string &word, const string &prefix) {
    if (word.length() < prefix.length()) return false;
    for (size_t i = 0; i < prefix.size(); i++) {
        if (word[i] != prefix[i]) return false;
    }
    return true;
}

void CPrint::toExportPrint(string & toPrint, const set<CEvent> & events){
    for(const CEvent & event: events){
        toPrint.append(event.toStringExport() + NEWLINE_DELIMITER);
    }
    CExport(mCalendar, mInterface, toPrint).Do();
}

void CPrint::Do() {
    set<CEvent> events;
    string toPrint;
    size_t exportIndex = mArgs.find(EXPORT_OPERATOR);
    if(exportIndex != string::npos) exportIndex += EXPORT_OPERATOR.length();

    // day
    if(startsWithString(mArgs, DAY_COMMAND)) {
        if(exportIndex < mArgs.length()){
            mCalendar->selectSameDay(CDateTime(mArgs.substr(exportIndex)), events);
            toExportPrint(toPrint, events);
            return;
        }
        mCalendar->selectSameDay(CDateTime(mArgs.substr(DAY_COMMAND.length())), events);
        CCalendarFormatDay(mInterface, make_shared<set<CEvent>>(events)).print(toPrint);
    }

    // week
    else if(startsWithString(mArgs, WEEK_COMMAND)) {
        int weekNum, year;

        if(exportIndex < mArgs.length()) {
            mArgs = mArgs.substr(exportIndex);
            if(sscanf(mArgs.c_str(), "%d.%d", &weekNum, &year) != 2) throw invalid_argument(INVALID_ARGUMENT_ERROR);
            mCalendar->selectSameWeek(weekNum, year, events);
            toExportPrint(toPrint, events);
            return;
        }

        else mArgs = mArgs.substr(WEEK_COMMAND.length());
        if(sscanf(mArgs.c_str(), "%d.%d", &weekNum, &year) != 2) throw invalid_argument(INVALID_ARGUMENT_ERROR);
        mCalendar->selectSameWeek(weekNum, year, events);
        CCalendarFormatWeek(mInterface, make_shared<set<CEvent>>(events)).print(toPrint);
    }
    // month
    else if(startsWithString(mArgs, MONTH_COMMAND)) {
        size_t firstNum = mArgs.find_first_of("0123456789");
        if(firstNum > mArgs.length()) throw invalid_argument(INVALID_ARGUMENT_ERROR);
        mArgs.insert(firstNum, "1.");

        if(exportIndex < mArgs.length()){
            CDateTime dateTime(mArgs.substr(exportIndex));
            mCalendar->selectSameMonth(dateTime.getMonth(), dateTime.getYear(), events);
            toExportPrint(toPrint, events);
            return;
        }

        CDateTime dateTime(mArgs.substr(MONTH_COMMAND.length()));

        mCalendar->selectSameMonth(dateTime.getMonth(), dateTime.getYear(), events);
        CCalendarFormatMonth(mInterface, make_shared<set<CEvent>>(events)).print(toPrint);
    }

    mInterface->print<string>(toPrint);
}

CPrint::CPrint(shared_ptr<CCalendar> & calendar, const shared_ptr<CInterface> & interface,
               const string &args) : CCommand(calendar, interface, args) {

}
