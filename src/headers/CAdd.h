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
     * @param[in] args - input to create events
     */
    CAdd(std::shared_ptr<CCalendar> & calendar, const std::shared_ptr<CInterface> & interface,
    const std::string &args);

    ~CAdd() = default;

    /**
     * Adds events to beczatom.
     * @throw invalid_argument - if args are not in correct format
     */
    void Do() override;
};
