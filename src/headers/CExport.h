/**
 * @author Tomas Becza <beczatom@fit.cvut.cz>
 * @date 12.05.2023
 */

#pragma once

#include "CCommand.h"

/**
 * @class CExport
 * @note Exports events.
 */

class CExport : public CCommand {
public:
    /**
     * Creates an instance of CExport.
     * @param[in] calendar - to export from
     * @param[in] interface - to export to
     * @param[in] args - what to export
     */
    CExport(std::shared_ptr<CCalendar> & calendar, const std::shared_ptr<CInterface> & interface,
            const std::string &args);

    ~CExport() = default;

    /**
     * Exports events in args.
     * @throw invalid_argument - if file is not valid
     */
    void Do() override;
};
