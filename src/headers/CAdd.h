/**
 * @author Tomas Becza <beczatom@fit.cvut.cz>
 * @date 08.06.2023
 */

#pragma once

#include "CCommand.h"

/**
 * @class CAdd
 * @note Adds events from console.
 */

class CAdd : public CCommand{
public:
    /**
     * Constructs an instance of CAdd
     * @param[in] calendar - to append events
     * @param[in] interface - to print
     */
    CAdd(std::shared_ptr<CCalendar> & calendar, const std::shared_ptr<CInterface> & interface);

    ~CAdd() = default;

    /**
     * Adds events to calendar.
     * @param[in] args - input to create events
     * @throw invalid_argument - if args are not in correct format
     */
    void Do(std::string & args) override;
};