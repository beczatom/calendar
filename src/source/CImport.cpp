#include <fstream>
#include <sstream>
#include "../headers/CImport.h"

using namespace std;

CImport::CImport(shared_ptr<CCalendar> & calendar, const shared_ptr<CInterface> & interface) : CCommand(calendar, interface){
}

void CImport::Do(string & args) {
    string fileName = args.substr(IMPORT_COMMAND.length() + 1, args.length());
    ifstream ifs(fileName);

    if(!ifs.good()){
        throw invalid_argument(FILE_ERROR);
    }

    CEvent event;
    while (!ifs.eof()){
        event = CEvent(ifs);
        if(ifs.eof()) break;
        mCalendar->addEvent(event);
    }

    ifs.close();
}