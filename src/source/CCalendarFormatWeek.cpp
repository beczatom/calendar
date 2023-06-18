#include "../headers/CCalendarFormatWeek.h"

using namespace std;

CCalendarFormatWeek::CCalendarFormatWeek() : CCalendarFormat(){}

string CCalendarFormatWeek::print(std::shared_ptr<CCalendar> & calendar, std::string & args) const{
    int weekNum, year;
    args = args.substr(WEEK_COMMAND.length());
    if (sscanf(args.c_str(), "%d.%d", &weekNum, &year) != 2) throw invalid_argument(INVALID_ARGUMENT_ERROR);
    set<CEvent> events;
    calendar->selectSameWeek(weekNum, year, events);

    string toPrint;
    if(events.empty()) {
        toPrint.append(NO_EVENTS_RESPONSE);
        return toPrint;
    }

    int beforeDay = -1;
    size_t maxLineSize = 0;
    vector<string> lines;
    size_t i = 0;

    for(const CEvent & event : events){
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

    return toPrint;
}

void CCalendarFormatWeek::exportEvents(std::shared_ptr<CCalendar> & calendar, std::string & args) const{
    int weekNum, year;
    set<CEvent> events;
    size_t exportIndex = args.find(EXPORT_OPERATOR);
    if (exportIndex != string::npos) exportIndex += EXPORT_OPERATOR.length();
    args = args.substr(exportIndex);
    if (sscanf(args.c_str(), "%d.%d", &weekNum, &year) != 2) throw invalid_argument(INVALID_ARGUMENT_ERROR);
    calendar->selectSameWeek(weekNum, year, events);
    toExportPrint(events);
}