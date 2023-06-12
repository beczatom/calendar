/**
 * @author Tomas Becza <beczatom@fit.cvut.cz>
 * @date 08.05.2023
 */

#pragma once

#include <iostream>
#include "../constants.h"

/**
 * @class CDateTime
 * @note Stores information about date and time.
 */

class CDateTime {
private:
    /// number of day in month
    int mDay;
    /// number of month in year
    int mMonth;
    /// year number
    int mYear;
    /// number of hour in day
    int mHour;
    /// number of minute in hour
    int mMinute;

    /**
     * Returns the number of days since 1. Jan.
     * @return number of days since 1. Jan
     */
    int getDayInYearNum() const;

public:
    /**
     * Creates an instance of CDatetime (default value with zeros)
     */
    CDateTime();

    /**
     * Creates an instance of CDateTime
     * @param[in] day - desired day
     * @param[in] month - desired month
     * @param[in] year - desired year
     * @param[in] hour - desired hour
     * @param[in] minute - desired minute
     * @throw logic_error - if dateTime is not valid
     */
    CDateTime(int day, int month, int year, int hour, int minute);

    /**
     * Creates an instance of CDateTime from string.
     * @param[in] str - string to create dateTime from
     * @throw logic_error - if str is not in correct format
     */
    explicit CDateTime (const std::string & str);

    ~CDateTime() = default;

    /**
     * Finds out if this is before compared dateTime.
     * @param[in] dateTime - compared with dateTime
     * @return TRUE if is before
     * @return FALSE if is not before
     */
    bool operator<(const CDateTime &dateTime) const;

    /**
     * Finds out if this after compared dateTime.
     * @param[in] dateTime - compared with dateTime
     * @return TRUE if is after
     * @return FALSE if is not after
     */
    bool operator>(const CDateTime &dateTime) const;

    /**
     * Finds out if this is equal to compared dateTime.
     * @param[in] dateTime - compared with dateTime
     * @return TRUE if is equal
     * @return FALSE if is not equal
     */
    bool operator==(const CDateTime &dateTime) const;

    /**
     * Finds out if this is after or on compared dateTime.
     * @param[in] dateTime - compared with dateTime
     * @return TRUE if is after or on same dateTime
     * @return FALSE if is not after or on same dateTime
     */
    bool operator>=(const CDateTime &dateTime) const;

    /**
     * Finds out if this is before or on compared dateTime.
     * @param[in] dateTime - compared with dateTime
     * @return TRUE if is before or on same dateTime
     * @return FALSE if is not before or on same dateTime
     */
    bool operator<=(const CDateTime &dateTime) const;

    /**
     * Finds out if this is not equal to dateTime.
     * @param[in] dateTime - compared with dateTime
     * @return TRUE if is not equal
     * @return FALSE if is equal
     */
    bool operator!=(const CDateTime &dateTime) const;

    /**
     * Prints out dateTime.
     * @param[in, out] os - object to print dateTime to
     * @param[in] dateTime - to print out
     * @return ostream with appended dateTime
     */
    friend std::ostream &operator<<(std::ostream &os, const CDateTime &dateTime);

    /**
     * Sets the date.
     * @note the time remains untouched
     * @param[in] day - desired day
     * @param[in] month - desired month
     * @param[in] year - desired year
     */
    void setDate(int day, int month, int year);

    /**
     * Returns if this is on same day as compared dateTime.
     * @param[in] date - compared with
     * @return TRUE if is on same day
     * @return FALSE if is not on same day
     */
    bool sameDay(const CDateTime & date) const;

    /**
     * Returns if this is in same month as compared month and year.
     * @param[in] month - compared with month
     * @param[in] year - compared with year
     * @return TRUE if is in same month
     * @return FALSE if is not in same month
     */
    bool sameMonth(int month, int year) const;

    /**
     * Returns if this is in same year as compared year.
     * @param[in] year - compared with
     * @return TRUE if is in same year
     * @return FALSE if is not in same year
     */
    bool sameYear(int year) const;

    /**
     * Finds out if this is default constructed (month is 0)
     * @return TRUE if is default constructed
     * @return FALSE if not default constructed
     */
    bool empty() const;

    /**
     * Prints out dateTime.
     * @return string with dateTime
     */
    std::string toString() const;

    /**
     * Prints out time.
     * @return string with time
     */
    std::string toStringTime() const;

    /**
     * Prints out date.
     * @return string with date
     */
    std::string toStringDate() const;

    /**
     * Increments this with provided amount of minutes.
     * @param[in] minutes - increment
     * @return this incremented
     */
    CDateTime addMinutes(int minutes);

    /**
     * Increments this with provided amount of days.
     * @param[in] days - increment
     * @return this incremented
     */
    CDateTime addDays(int days);

    /**
     * Returns the number of days since Monday.
     * @return number of days since Monday
     */
    int getDayInWeekNum() const;

    /**
     * Returns the number of week of this in a year.
     * @return number of week of this in a year
     */
    int getWeekNum() const;

    /**
     * Returns the day number in a month.
     * @return number of day in a month
     */
    int getDay() const;

    /**
     * Returns the month number in a year.
     * @return number of month in a year
     */
    int getMonth() const;

    /**
     * Returns the year.
     * @return year
     */
    int getYear() const;

    /**
     * Returns first day in a specific week in a year.
     * @param[in] weekNum - number of week in year
     * @param[in] year - the desired year
     * @return first day in a specific week in a year.
     * @throw logic_error - if weekNum is not valid
     */
    static CDateTime getFirstDayInWeek(int weekNum, int year);
};