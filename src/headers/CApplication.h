/**
 * @author Tomas Becza <beczatom@fit.cvut.cz>
 * @date 08.05.2023
 */

#pragma once

#include <map>

#include "CCalendar.h"
#include "CInterface.h"
#include "CCommand.h"

/**
 * @class CApplication
 * @note Listens to commands and executes them.
 */

class CApplication {
private:
    /// to store the events
    std::shared_ptr<CCalendar> mCalendar;
    /// to communicate with user
    std::shared_ptr<CInterface> mInterface;
    /// holds pointers to commands
    std::map<std::string, CCommand*> mCommands;

public:
    /**
     * Constructs an instance of CApplication.
     */
    CApplication();

    ~CApplication();

    /**
     * Starts listening to commands and executes them.
     */
    void start();
};