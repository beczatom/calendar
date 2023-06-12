/**
 * @author Tomas Becza <beczatom@fit.cvut.cz>
 * @date 13.05.2023
 */

#pragma once

#include "CCommand.h"

/**
 * @class CSelect
 * @note Manages selecting events from beczatom.
 */

class CSelect : public CCommand {
public:
    /**
     * Creates an instance of CSelect.
     * @param[in] calendar - to select from
     * @param[in] interface - to print to
     * @param[in] args - what to print
     */
    CSelect(std::shared_ptr<CCalendar> & calendar, const std::shared_ptr<CInterface> & interface,
            const std::string &args);

    ~CSelect() = default;

    /**
     * Gets the arguments entered in interface, processes them and selects the correct events from beczatom
     * @throw invalid_argument - if args is not in correct format
     */
    void Do() override;
};

