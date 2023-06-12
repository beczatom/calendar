/**
 * @author Tomas Becza <beczatom@fit.cvut.cz>
 * @date 12.05.2023
 */

#pragma once

#include <memory>
#include "CInterface.h"
#include "CCalendar.h"

/**
 * @class CCommand
 * @note Finds the correct command and executes it.
 */

class CCommand {
protected:
    /// to find the correct events or a place to append them
    std::shared_ptr<CCalendar> mCalendar;
    /// for possible output
    std::shared_ptr<CInterface> mInterface;
    /// input from user
    std::string mArgs;
public:
    /**
     * Creates an instance of CCommand
     * @param[in] calendar - for searching and appending events
     * @param[in] interface - for output
     * @param[in] args - input text
     */
    CCommand(std::shared_ptr<CCalendar> & calendar, const std::shared_ptr<CInterface> & interface,
             const std::string & args);

    ~CCommand() = default;

    /**
     * Finds the correct command and then executes it.
     * @throw invalid_argument - if args are not in correct format
     */
    virtual void Do();
};

