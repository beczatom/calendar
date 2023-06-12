/**
 * @author Tomas Becza <beczatom@fit.cvut.cz>
 * @date 12.05.2023
 */

#pragma once

#include <memory>
#include <vector>
#include "CEvent.h"
#include "CInterface.h"

/**
 * @class CCalendarFormat
 * @note Printing the events in correct format.
 */
class CCalendarFormat {
protected:
    /// events to print out
    std::shared_ptr<std::set<CEvent>> mEvents;
    /// interface to where the events will be printed
    std::shared_ptr<CInterface> mInterface;

    /**
     * Creates horizontal lines for rectangle in printing.
     * @param[out] horizontalLine - the wanted line
     * @param[in] maxLineSize - line size
     */
    void createHorizontalLine(std::string & horizontalLine, int maxLineSize) const;

    /**
     * Aligns the right border of the rectangle to printing.
     * @param[out] toPrint - the wanted string
     * @param[in] lines - unaligned lines
     * @param[in] horizontalLine - horizontal borders of printing
     * @param[in] maxLineSize - needed for right alignment
     */
    void alignToPrint(std::string & toPrint, std::vector<std::string> & lines, const std::string & horizontalLine, int maxLineSize) const;

public:
    /**
     * Creates an instance of CCalendarFormat
     * @param[in] interface - where the events will be printed out
     * @param[in] events - events to print out
     */
    CCalendarFormat(const std::shared_ptr<CInterface> & interface, const std::shared_ptr<std::set<CEvent>> & events);

    ~CCalendarFormat() = default;

    /**
     * Prints events in a correct format (day/week/month)
     * @param [out] toPrint - will contain the correct format
     */
    virtual void print(std::string & toPrint) const = 0;
};