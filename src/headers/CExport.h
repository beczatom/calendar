/**
 * @author Tomas Becza <beczatom@fit.cvut.cz>
 * @date 12.05.2023
 */

#pragma once

#include <string>

#include "../constants.h"

/**
 * @class CExport
 * @note Exports events.
 */

class CExport{
public:
    /**
     * Creates an instance of CExport.
     */
    CExport() = default;

    ~CExport() = default;

    /**
     * Exports events in args.
     * @param args - events to export
     * @throw invalid_argument - if file is not valid
     */
    void Do(std::string & args);
};