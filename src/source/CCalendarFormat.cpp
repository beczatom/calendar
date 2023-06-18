#include "../headers/CCalendarFormat.h"

using namespace std;

void CCalendarFormat::createHorizontalLine(string & horizontalLine, int maxLineSize) const{
    horizontalLine.append(VIEW_RECTANGLE_CORNER);
    for(int i = 0; i < maxLineSize - 3; i++){
        horizontalLine.append(VIEW_RECTANGLE_HORIZONTAL_SIDE);
    }
    horizontalLine.append(VIEW_RECTANGLE_CORNER);
}

void CCalendarFormat::alignToPrint(string & toPrint, vector<string> & lines, const string & horizontalLine, int maxLineSize) const{
    toPrint.append(horizontalLine + NEWLINE_DELIMITER);
    for (string &line: lines) {
        while (static_cast<int>(line.size()) != maxLineSize - 2) {
            line.append(" ");
        }
        toPrint.append(line + VIEW_RECTANGLE_VERTICAL_SIDE + NEWLINE_DELIMITER);
    }
    toPrint.append(horizontalLine);
}

void CCalendarFormat::toExportPrint(const set<CEvent> & events) const{
    string toExport;
    for(const CEvent & event: events){
        toExport.append(event.toStringExport() + NEWLINE_DELIMITER);
    }
    CExport().Do(toExport);
}