/**
 * @author Tomas Becza <beczatom@fit.cvut.cz>
 * @date 12.05.2023
 */

#pragma once

#include <map>

#include "CCommand.h"
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
    std::map<std::string, CCalendarFormat*> mFormats;
public:
    /**
     * Creates an instance of CPrint.
     * @param[in] calendar - to print from
     * @param[in] interface - to print to
     */
    CPrint(std::shared_ptr<CCalendar> & calendar, const std::shared_ptr<CInterface> & interface);

    ~CPrint() override;

    /**
     * Finds the format to use and calls it.
     * @param[in] args - contains the format type and arguments
     * @throw invalid_argument - if args is not in correct format
     */
    void Do(std::string & args) override;
};