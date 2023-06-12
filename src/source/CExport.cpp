#include "../headers/CExport.h"

#include <fstream>

using namespace std;

void CExport::Do() {
    ofstream ofs (EXPORT_FILE_NAME);
    if(!ofs.good()){
        throw invalid_argument(FILE_ERROR);
    }
    ofs << mArgs << endl;
    ofs.close();
}

CExport::CExport(shared_ptr<CCalendar> & calendar, const shared_ptr<CInterface> & interface,
                 const string &args) : CCommand(calendar, interface, args) {

}

