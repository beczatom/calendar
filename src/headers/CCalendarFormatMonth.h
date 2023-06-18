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
     */
    CCalendarFormatMonth();

    ~CCalendarFormatMonth() = default;

    /**
      * Prints events in month format.
      * @param[in] calendar - to select from events
      * @param[in] args - which events to select
      * @return string with printed day/week/month
      */
    virtual std::string print(std::shared_ptr<CCalendar> & calendar, std::string & args) const override;

    /**
      * Exports events.
      * @param[in] calendar - to select from events
      * @param[in] args - which events to select
      */
    virtual void exportEvents(std::shared_ptr<CCalendar> & calendar, std::string & args) const override;
};