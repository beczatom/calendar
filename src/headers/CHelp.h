/**
 * @author Tomas Becza <beczatom@fit.cvut.cz>
 * @date 12.05.2023
 */

#pragma once

#include "CCommand.h"

/**
 * @class CHelp
 * @note Prints help.
 */

class CHelp : public CCommand {
public:
    /**
     * Creates an instance of CHelp.
     * @param[in] calendar - parent constructor
     * @param[in] interface - to print out help.
     */
    explicit CHelp(std::shared_ptr<CCalendar> & calendar, const std::shared_ptr<CInterface> & interface);

    ~CHelp() override = default;

    /**
     * Prints help.
     * @param[in] args
     */
    void Do(std::string & args) override;
};