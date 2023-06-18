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

    /**
     * Finds out if the given word starts with given prefix.
     * @param[in] word - given word
     * @param[in] prefix - given prefix
     * @return TRUE - if word starts with given prefix
     * @return FALSE - if word does not start with given prefix
     */
    bool startsWith(const std::string &word, const std::string &prefix) const;
public:
    /**
     * Creates an instance of CCommand
     * @param[in] calendar - for searching and appending events
     * @param[in] interface - for output
     */
    CCommand(std::shared_ptr<CCalendar> & calendar, const std::shared_ptr<CInterface> & interface);

    virtual ~CCommand() = default;

    /**
     * Executes the correct command.
     * @param[in] args - arguments of command
     * @throw invalid_argument - if args are not in correct format
     */
    virtual void Do(std::string & args) = 0;
};