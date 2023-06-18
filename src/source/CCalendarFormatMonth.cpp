#include "../headers/CCalendarFormatMonth.h"

using namespace std;

CCalendarFormatMonth::CCalendarFormatMonth() : CCalendarFormat(){}

string CCalendarFormatMonth::print(std::shared_ptr<CCalendar> & calendar, std::string & args) const{
    set<CEvent> events;

    size_t firstNum = args.find_first_of("0123456789");
    if (firstNum > args.length()) throw invalid_argument(INVALID_ARGUMENT_ERROR);
    args.insert(firstNum, "1.");


    CDateTime dateTime(args.substr(MONTH_COMMAND.length()));

    calendar->selectSameMonth(dateTime.getMonth(), dateTime.getYear(), events);

    string toPrint;
    if(events.empty()) {
        toPrint.append(NO_EVENTS_RESPONSE);
        return toPrint;
    }

    CDateTime beforeDay;
    size_t maxLineSize = 0;
    vector<string> lines;
    size_t i = 0;

    for(const CEvent & event : events){
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

    return toPrint;
}

void CCalendarFormatMonth::exportEvents(std::shared_ptr<CCalendar> & calendar, std::string & args) const{
    set<CEvent> events;
    size_t exportIndex = args.find(EXPORT_OPERATOR);
    if (exportIndex != string::npos) exportIndex += EXPORT_OPERATOR.length();

    size_t firstNum = args.find_first_of("0123456789");
    if (firstNum > args.length()) throw invalid_argument(INVALID_ARGUMENT_ERROR);
    args.insert(firstNum, "1.");

    CDateTime dateTime(args.substr(exportIndex));
    calendar->selectSameMonth(dateTime.getMonth(), dateTime.getYear(), events);
    toExportPrint(events);
}