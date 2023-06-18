/**
 * @author Tomas Becza <beczatom@fit.cvut.cz>
 * @date 13.05.2023
 */

#pragma once

#include "CCommand.h"

/**
 * @class CSelect
 * @note Manages selecting events from calendar.
 */

class CSelect : public CCommand {
public:
    /**
     * Creates an instance of CSelect.
     * @param[in] calendar - to select from
     * @param[in] interface - to print to
     */
    CSelect(std::shared_ptr<CCalendar> & calendar, const std::shared_ptr<CInterface> & interface);

    ~CSelect() override = default;

    /**
     * Gets the arguments entered in interface, processes them and selects the correct events from calendar
     * @param args - select pattern
     * @throw invalid_argument - if args is not in correct format
     */
    void Do(std::string & args) override;
};