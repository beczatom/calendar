#include "../headers/CCalendarFormatDay.h"
#include "../constants.h"
#include <vector>

using namespace std;

CCalendarFormatDay::CCalendarFormatDay(const shared_ptr<CInterface> & interface, const shared_ptr<set<CEvent>> & events) : CCalendarFormat(interface, events){}

void CCalendarFormatDay::print(string & toPrint) const{
    if(mEvents->empty()) {
        toPrint.append(NO_EVENTS_RESPONSE);
        return;
    }

    size_t maxLineSize = 0;
    vector<string> lines;

    //for every event create a line
    for(const CEvent & event : *mEvents){
        lines.emplace_back(VIEW_RECTANGLE_VERTICAL_SIDE + " " + event.getStart().toStringTime() + " " + VIEW_ARROW + " " + event.getEnd().toStringTime() + PRINT_TO_CONSOLE_DELIMITER + event.getName() + "," + event.getPlaceName() + " ");
        if(lines.back().size() + 2 > maxLineSize) maxLineSize = lines.back().size() + 2;
    }

    //create the line up and down side of the border
    string horizontalLine;
    createHorizontalLine(horizontalLine, maxLineSize);

    //align to a nice rectangle
    alignToPrint(toPrint, lines, horizontalLine, maxLineSize);
}