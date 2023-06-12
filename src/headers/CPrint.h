/**
 * @author Tomas Becza <beczatom@fit.cvut.cz>
 * @date 12.05.2023
 */

#pragma once

#include "CCalendarFormat.h"
#include "CCalendarFormatDay.h"
#include "CCalendarFormatWeek.h"
#include "CCalendarFormatMonth.h"
#include "CExport.h"

/**
 * @class CPrint
 * @note Prints out events.
 */

class CPrint : public CCommand {
private:
    /**
     * Exporting - printing to file.
     * @param[out] toPrint - out printed events
     * @param[in] events - events to print
     */
    void toExportPrint(std::string & toPrint, const std::set<CEvent> & events);
public:
    /**
     * Creates an instance of CPrint.
     * @param[in] calendar - to print from
     * @param[in] interface - to print to
     * @param[in] args - what to print
     */
    CPrint(std::shared_ptr<CCalendar> & calendar, const std::shared_ptr<CInterface> & interface,
           const std::string &args);

    ~CPrint() = default;

    /**
     * Finds the format to use and calls it.
     * @throw invalid_argument - if args is not in correct format
     */
    void Do() override;
};