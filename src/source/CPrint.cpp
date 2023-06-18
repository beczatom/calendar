#include <sstream>
#include "../headers/CPrint.h"

using namespace std;

string getStartingWord(const std::string &word) {
    if (word.empty()) return string();

    string startingString;
    for (size_t i = 0; !isblank(word[i]) && i < word.length(); i++) {
        startingString += word[i];
    }
    return startingString;
}

CPrint::CPrint(shared_ptr<CCalendar> & calendar, const shared_ptr<CInterface> & interface) : CCommand(calendar, interface) {
    mFormats = {
            {DAY_COMMAND, new CCalendarFormatDay()},
            {WEEK_COMMAND, new CCalendarFormatWeek()},
            {MONTH_COMMAND, new CCalendarFormatMonth()}
    };
}

CPrint::~CPrint(){
    for(auto it : mFormats){
        delete it.second;
    }
}

//returns true if the string starts with given prefix
bool startsWithString(const string &word, const string &prefix) {
    if (word.length() < prefix.length()) return false;
    for (size_t i = 0; i < prefix.size(); i++) {
        if (word[i] != prefix[i]) return false;
    }
    return true;
}

void CPrint::Do(string & args) {

    string startingString = getStartingWord(args);
    string toPrint;

    auto it = mFormats.find(startingString);
    size_t exportIndex = args.find(EXPORT_OPERATOR);

    if(it != mFormats.end()){
        if(exportIndex != string::npos){
            it->second->exportEvents(mCalendar, args);
            return;
        }
        toPrint = it->second->print(mCalendar, args);
    }
    else throw invalid_argument(INVALID_COMMAND_ERROR);
    mInterface->print<string>(toPrint);
}