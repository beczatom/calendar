#include "../headers/CCalendarFormatMonth.h"
#include "../constants.h"
#include <vector>

using namespace std;

CCalendarFormatMonth::CCalendarFormatMonth(const std::shared_ptr<CInterface> & interface,
                                           const std::shared_ptr<std::set<CEvent>> & events) : CCalendarFormat(interface, events){}

void CCalendarFormatMonth::print(string & toPrint) const{
    if(mEvents->empty()) {
        toPrint.append(NO_EVENTS_RESPONSE);
        return;
    }

    CDateTime beforeDay;
    size_t maxLineSize = 0;
    vector<string> lines;
    size_t i = 0;

    for(const CEvent & event : *mEvents){
        if(event.getStart().toStringDate() != beforeDay.toStringDate()){
            beforeDay = event.getStart();
            lines.emplace_back(VIEW_RECTANGLE_VERTICAL_SIDE + " " + beforeDay.toStringDate());
        }
        lines.emplace_back(VIEW_RECTANGLE_VERTICAL_SIDE + " " + event.getStart().toStringTime() + " " + VIEW_ARROW + " " + event.getEnd().toStringTime() + PRINT_TO_CONSOLE_DELIMITER + event.getName() + "," + event.getPlaceName() + " ");
        if(lines.back().size() + 2 > maxLineSize) maxLineSize = lines.back().size() + 2;
        i++;
    }

    //create the line up and down side of the border
    string horizontalLine;
    createHorizontalLine(horizontalLine, maxLineSize);

    //align to a nice rectangle
    alignToPrint(toPrint, lines, horizontalLine, maxLineSize);
}