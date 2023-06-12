/**
 * @author Tomas Becza <beczatom@fit.cvut.cz>
 * @date 08.06.2023
 */

#pragma once

#include <stdlib.h>
#include <string>

/// Command for displaying help
const std::string HELP_COMMAND = "help";
/// Command for import
const std::string IMPORT_COMMAND = "import";
/// Command for displaying day
const std::string DAY_COMMAND = "day";
/// Command for displaying week
const std::string WEEK_COMMAND = "week";
/// Command for displaying month
const std::string MONTH_COMMAND = "month";
/// Command for selecting events
const std::string SELECT_COMMAND = "select";
/// Command for quitting from app
const std::string QUIT_COMMAND = "quit";
/// Command for adding events
const std::string ADD_COMMAND = "add";

/// Response to eof
const std::string EOF_RESPONSE = "EOF.";
/// Response to empty set of events
const std::string NO_EVENTS_RESPONSE = "No events.";
/// Problem with dateTime
const std::string DATETIME_ERROR = "Datetime doesn't exist.";
/// Problem with event
const std::string EVENT_ERROR = "Error in event.";
/// Problem with file
const std::string FILE_ERROR = "Can't open file.";
/// Problem with place
const std::string PLACE_ERROR = "Place can't be created.";
/// Problem with person
const std::string PERSON_ERROR = "Person can't be created.";
/// Problem with command
const std::string INVALID_COMMAND_ERROR = "Invalid command.";
/// Problem with operator
const std::string INVALID_OPERATOR_ERROR = "Invalid operator.";
/// Problem with name
const std::string NAME_ERROR = "Invalid name.";
/// Problem with argument
const std::string INVALID_ARGUMENT_ERROR = "Invalid argument.";
/// Problem with overflow
const std::string OVERFLOW_ERROR = "Overflow error.";

/// Export file name
const std::string EXPORT_FILE_NAME = "export.txt";

/// Response to the end of program
const std::string END_OF_PROGRAM = "Goodbye.";

/// Before every command
const std::string ASKING_FOR_QUERY = "Enter query or type \'help\':";

/// Number of days in each month
const int DAYS_IN_MONTHS[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
/// Number of days in each month in a leap year
const int DAYS_IN_MONTHS_LEAP[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
/// Used for calculating the day in week
const int KEY_VALUE_MONTHS[12] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
/// Number of days in a week
const int DAYS_IN_WEEK = 7;

/// Name of each day in a week
const std::string DAY_NAMES[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

/// Default buffer length
const size_t BUFFER_LENGTH = 1024;

/// Event argument name (used for select)
const std::string NAME_ARGUMENT = "name";
/// Event argument tag (used for select)
const std::string TAG_ARGUMENT = "tag";
/// Event argument duration (used for select)
const std::string DURATION_ARGUMENT = "duration";
/// Event argument participant (used for select)
const std::string PARTICIPANT_ARGUMENT = "participant";
/// Event argument place (used for select)
const std::string PLACE_ARGUMENT = "place";
/// Event argument start (used for select)
const std::string START_ARGUMENT = "start";
/// Logic AND operator (used ins select)
const std::string AND_OPERATOR = "and";
/// Logic OR operator (used ins select)
const std::string OR_OPERATOR = "or";
/// Operator for exporting
const std::string EXPORT_OPERATOR = "-e";


const char LESS_THAN_OPERATOR = '<';
const char GREATER_THAN_OPERATOR = '>';
const char EQUAL_OPERATOR = '=';
const char ITEM_IN_EVENT_DELIMITER = ',';
const char PRINT_TO_CONSOLE_DELIMITER = ' ';
const char EVENTS_DELIMITER = ';';
const char NEWLINE_DELIMITER = '\n';
const char DATE_DELIMITER = '.';
const char TIME_DELIMITER = ':';
const std::string VIEW_RECTANGLE_HORIZONTAL_SIDE = "-";
const std::string VIEW_RECTANGLE_VERTICAL_SIDE = "|";
const std::string VIEW_RECTANGLE_CORNER = "+";
const std::string VIEW_ARROW = "->";

/// help for user (used in help)
const std::string HELP = "select [arguments/and/or]\t- selects events\n"
                         "day [date]\t\t\t- day report (date format DD.MM.YYYY)\n"
                         "week [weekNum] \t\t\t- week report (weekNum format [numberOfWeekInYear].YYYY)\n"
                         "month [monthNum] \t\t- month report (monthNum format [numberOfMonthInYear].YYYY)\n"
                         "-e [fileName] \t\t\t- can be used in previous commands, exports events to file\n"
                         "add [event] \t\t\t- adds event (event format dateTime;duration;name;place;participants;tags;repetition;notes;)\n"
                         "import [fileName] \t\t- imports events from file\n"
                         "help \t\t\t\t- displays this :)\n"
                         "quit \t\t\t\t- ends the program :(\n";

/// used to avoid collisions
const int MINUTES_STEP_COLLISION = 10;