#include "../headers/CApplication.h"

using namespace std;

CApplication::CApplication(){
    mCalendar = make_shared<CCalendar>();
    mInterface = make_shared<CInterface>();
}

bool startsWithQuit(const std::string &word) {
    if (word.length() < QUIT_COMMAND.length()) return false;
    for (size_t i = 0; i < QUIT_COMMAND.length(); i++) {
        if (word[i] != QUIT_COMMAND[i]) return false;
    }
    return true;
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
            break;
        }

        //command execution
        try{
            CCommand(mCalendar, mInterface, input).Do();
        } catch (const exception & e) {
            mInterface->print<string>(e.what());
        }
    }
}
