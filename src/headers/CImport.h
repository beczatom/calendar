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
     */
    CImport(std::shared_ptr<CCalendar> & calendar, const std::shared_ptr<CInterface> & interface);

    ~CImport() override = default;

    /**
     * Imports events from file.
     * @param[in] args - import file name
     * @throw invalid_argument - if file is not valid
     */
    void Do(std::string & args) override;
};