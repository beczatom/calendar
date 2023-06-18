#include "../headers/CApplication.h"

#include "../headers/CHelp.h"
#include "../headers/CImport.h"
#include "../headers/CAdd.h"
#include "../headers/CSelect.h"
#include "../headers/CPrint.h"

using namespace std;

string getStartingString(const std::string &word) {
    if (word.empty()) return string();

    string startingString;
    for (size_t i = 0; !isblank(word[i]) && i < word.length(); i++) {
        startingString += word[i];
    }
    return startingString;
}

CApplication::CApplication(){
    mCalendar = make_shared<CCalendar>();
    mInterface = make_shared<CInterface>();
    mCommands = {
            {HELP_COMMAND, new CHelp(mCalendar, mInterface)},
            {IMPORT_COMMAND, new CImport(mCalendar, mInterface)},
            {ADD_COMMAND, new CAdd(mCalendar, mInterface)},
            {SELECT_COMMAND, new CSelect(mCalendar, mInterface)},
            {DAY_COMMAND, new CPrint(mCalendar, mInterface)},
            {WEEK_COMMAND, new CPrint(mCalendar, mInterface)},
            {MONTH_COMMAND, new CPrint(mCalendar, mInterface)}};
}

bool startsWithQuit(const std::string &word) {
    if (word.length() < QUIT_COMMAND.length()) return false;
    for (size_t i = 0; i < QUIT_COMMAND.length(); i++) {
        if (word[i] != QUIT_COMMAND[i]) return false;
    }
    return true;
}

CApplication::~CApplication() {
    for(auto command : mCommands){
        delete command.second;
    }
}

void CApplication::start() {
    string input;
    for(;;){
        mInterface->print<string>(ASKING_FOR_QUERY);

        //handling problems in interface
        try{
            input = mInterface->getInput();
        } catch ( const exception & e ){
            mInterface->print<string>(e.what());
            if(e.what() == EOF_RESPONSE) return;
            continue;
        }

        //program end
        if(startsWithQuit(input)){
            mInterface->print<string>(END_OF_PROGRAM);
            return;
        }

        //command execution
        try{
            string startingString = getStartingString(input);
            auto it = mCommands.find(startingString);
            if(it != mCommands.end()) it->second->Do(input);
            else throw invalid_argument(INVALID_COMMAND_ERROR);
        } catch (const exception & e) {
            mInterface->print<string>(e.what());
        }
    }
}
