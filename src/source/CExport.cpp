#include "../headers/CExport.h"

#include <fstream>

using namespace std;

void CExport::Do(string & args) {
    ofstream ofs (EXPORT_FILE_NAME);
    if(!ofs.good()){
        throw invalid_argument(FILE_ERROR);
    }
    ofs << args << endl;
    ofs.close();
}