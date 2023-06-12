/**
 * @author Tomas Becza <beczatom@fit.cvut.cz>
 * @date 13.05.2023
 */

#pragma once

#include "CCalendarFormat.h"

/**
 * @class CCalendarFormatMonth
 * @note Printing the events in month format.
 */

class CCalendarFormatMonth : public CCalendarFormat {
public:
    /**
     * Creates an instance of CCalendarFormatMonth
     * @param[in] interface - where the events will be printed out
     * @param[in] events - the events to print out
     */
    explicit CCalendarFormatMonth(const std::shared_ptr<CInterface> & interface, const std::shared_ptr<std::set<CEvent>> & events);

    ~CCalendarFormatMonth() = default;

    /**
     * Prints events in a month format
     * @param [out] toPrint - will contain month format
     */
    void print(std::string & toPrint) const override;
};

