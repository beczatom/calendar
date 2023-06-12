#include "../headers/CCalendarFormatWeek.h"

using namespace std;

CCalendarFormatWeek::CCalendarFormatWeek(const std::shared_ptr<CInterface> & interface,
                                           const std::shared_ptr<std::set<CEvent>> & events) : CCalendarFormat(interface, events){}

void CCalendarFormatWeek::print(string & toPrint) const{
    if(mEvents->empty()) {
        toPrint.append(NO_EVENTS_RESPONSE);
        return;
    }

    int beforeDay = -1;
    size_t maxLineSize = 0;
    vector<string> lines;
    size_t i = 0;

    for(const CEvent & event : *mEvents){
        if(event.getStart().getDayInWeekNum() != beforeDay){
            beforeDay = event.getStart().getDayInWeekNum();
            lines.emplace_back(VIEW_RECTANGLE_VERTICAL_SIDE + " " + DAY_NAMES[beforeDay]);
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