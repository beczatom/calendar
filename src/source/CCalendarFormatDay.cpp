#include "../headers/CCalendarFormatDay.h"

using namespace std;

CCalendarFormatDay::CCalendarFormatDay() : CCalendarFormat(){}

string CCalendarFormatDay::print(std::shared_ptr<CCalendar> & calendar, std::string & args) const{
    set<CEvent> events;
    calendar->selectSameDay(CDateTime(args.substr(DAY_COMMAND.length())), events);
    string toPrint;
    if(events.empty()) {
        toPrint.append(NO_EVENTS_RESPONSE);
        return toPrint;
    }

    size_t maxLineSize = 0;
    vector<string> lines;

    //for every event create a line
    for(const CEvent & event : events){
        lines.emplace_back(VIEW_RECTANGLE_VERTICAL_SIDE + " " + event.getStart().toStringTime() + " " + VIEW_ARROW + " " + event.getEnd().toStringTime() + PRINT_TO_CONSOLE_DELIMITER + event.getName() + "," + event.getPlaceName() + " ");
        if(lines.back().size() + 2 > maxLineSize) maxLineSize = lines.back().size() + 2;
    }

    //create the line up and down side of the border
    string horizontalLine;
    createHorizontalLine(horizontalLine, maxLineSize);

    //align to a nice rectangle
    alignToPrint(toPrint, lines, horizontalLine, maxLineSize);

    return toPrint;
}

void CCalendarFormatDay::exportEvents(std::shared_ptr<CCalendar> & calendar, std::string & args) const{
    set<CEvent> events;
    size_t exportIndex = args.find(EXPORT_OPERATOR);
    if (exportIndex != string::npos) exportIndex += EXPORT_OPERATOR.length();
    calendar->selectSameDay(CDateTime(args.substr(exportIndex)), events);
    toExportPrint(events);
}