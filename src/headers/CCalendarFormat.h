/**
 * @author Tomas Becza <beczatom@fit.cvut.cz>
 * @date 12.05.2023
 */

#pragma once

#include <memory>
#include <vector>
#include <map>

#include "CCalendar.h"
#include "CEvent.h"
#include "CInterface.h"
#include "CExport.h"

/**
 * @class CCalendarFormat
 * @note Printing the events in correct format.
 */
class CCalendarFormat {
protected:
    /**
     * Creates horizontal lines for rectangle in printing.
     * @param[out] horizontalLine - the wanted line
     * @param[in] maxLineSize - line size
     */
    void createHorizontalLine(std::string & horizontalLine, int maxLineSize) const;

    /**
     * Aligns the right border of the rectangle to printing.
     * @param[out] toPrint - the wanted string
     * @param[in] lines - unaligned lines
     * @param[in] horizontalLine - horizontal borders of printing
     * @param[in] maxLineSize - needed for right alignment
     */
    void alignToPrint(std::string & toPrint, std::vector<std::string> & lines, const std::string & horizontalLine, int maxLineSize) const;

    /**
     * Exporting - printing to file.
     * @param[in] events - events to export
     */
    void toExportPrint(const std::set<CEvent> & events) const;

public:
    /**
     * Creates an instance of CCalendarFormat
     */
    CCalendarFormat() = default;

    virtual ~CCalendarFormat() = default;

    /**
     * Prints events in a correct format (day/week/month).
     * @param[in] calendar - to select from events
     * @param[in] args - which events to select
     * @return string with printed day/week/month
     */
    virtual std::string print(std::shared_ptr<CCalendar> & calendar, std::string & args) const = 0;

    /**
      * Exports events.
      * @param[in] calendar - to select from events
      * @param[in] args - which events to select
      */
    virtual void exportEvents(std::shared_ptr<CCalendar> & calendar, std::string & args) const = 0;
};