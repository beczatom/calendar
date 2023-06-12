/**
 * @author Tomas Becza <beczatom@fit.cvut.cz>
 * @date 12.05.2023
 */

#pragma once

#include "CCommand.h"

/**
 * @class CImport
 * @note Imports events from file.
 */

class CImport : public CCommand {
public:
    /**
     * Creates an instance of CImport.
     * @param[in, out] calendar - to import to
     * @param[in] interface - to import from
     * @param[in] args - what to import
     */
    CImport(std::shared_ptr<CCalendar> & calendar, const std::shared_ptr<CInterface> & interface,
            const std::string &args);

    ~CImport() = default;

    /**
     * Imports events from file.
     * @throw invalid_argument - if file is not valid
     */
    void Do() override;
};

