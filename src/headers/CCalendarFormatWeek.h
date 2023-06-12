/**
 * @author Tomas Becza <beczatom@fit.cvut.cz>
 * @date 13.05.2023
 */

#pragma once

#include "CCalendarFormat.h"

/**
 * @class CCalendarFormatWeek
 * @note Printing the events in week format.
 */

class CCalendarFormatWeek : public CCalendarFormat {
public:
    /**
     * Creates an instance of CCalendarFormatWeek
     * @param[in] interface - where the events will be printed out
     * @param[in] events - the events to print out
     */
    explicit CCalendarFormatWeek(const std::shared_ptr<CInterface> & interface, const std::shared_ptr<std::set<CEvent>> & events);

    ~CCalendarFormatWeek() = default;

    /**
     * Prints events in a week format
     * @param [out] toPrint - will contain week format
     */
    void print(std::string & toPrint) const override;
};

