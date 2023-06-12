/**
 * @author Tomas Becza <beczatom@fit.cvut.cz>
 * @date 13.05.2023
 */

#pragma once

#include "CCalendarFormat.h"

/**
 * @class CCalendarFormatDay
 * @note Printing the events in day format.
 */

class CCalendarFormatDay : public CCalendarFormat {
public:
    /**
     * Creates an instance of CCalendarFormatDay
     * @param[in] interface - where the events will be printed out
     * @param[in] events - the events to print out
     */
    explicit CCalendarFormatDay(const std::shared_ptr<CInterface> & interface, const std::shared_ptr<std::set<CEvent>> & events);

    ~CCalendarFormatDay() = default;

    /**
     * Prints events in a day format
     * @param [out] toPrint - will contain day format
     */
    void print(std::string & toPrint) const override;
};
