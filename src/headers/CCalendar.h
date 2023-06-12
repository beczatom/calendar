/**
 * @author Tomas Becza <beczatom@fit.cvut.cz>
 * @date 08.05.2023
 */

#pragma once

#include <set>
#include <string>
#include "CEvent.h"

/**
 * @class CCalendar
 * @note Stores events.
 */

class CCalendar {
private:
    /// container to store the events
    std::set<CEvent> mEvents;

public:
    CCalendar() = default;

    ~CCalendar() = default;

    /**
     * Creates an instance of CCalendar with given events.
     * @param[in] events - given events
     */
    explicit CCalendar(const std::set<CEvent> &events);

    /**
     * Adds event to beczatom, if is in collision with some event, then tries to reschedule it.
     * @param[in] event - event to be added
     */
    void addEvent(const CEvent &event);

    /**
     * Finds similar events to provided event and places them to the provided set.
     * @param [in] event - event to find
     * @param [out] events - set to store the similar events
     */
    void select(const CEvent &event, std::set<CEvent> & events) const;

    /**
     * Finds events that will be on provided day.
     * @param [in] dateTime - to compare
     * @param [out] events - set to store the wanted events
     */
    void selectSameDay(const CDateTime & dateTime, std::set<CEvent> & events) const;

    /**
     * Finds events that will be on provided month.
     * @param [in] month - to compare
     * @param [in] year - to compare
     * @param [out] events - set to store the wanted events
     */
    void selectSameMonth(int month, int year, std::set<CEvent> & events) const;

    /**
     * Finds events that will be on provided month.
     * @param [in] weekNum - number of week in year
     * @param [in] year - to compare
     * @param [out] events - set to store the wanted events
     */
    void selectSameWeek(int weekNum, int year, std::set<CEvent> & events) const;

    /**
     * Finds events that will be before provided datetime.
     * @param [in] dateTime - to compare
     * @param [out] events - set to store the wanted events
     */
    void selectLessDate(const CDateTime &dateTime, std::set<CEvent> & events) const;

    /**
     * Finds events that will be after provided datetime.
     * @param [in] dateTime - to compare
     * @param [out] events - set to store the wanted events
     */
    void selectGreaterDate(const CDateTime &dateTime, std::set<CEvent> & events) const;
};