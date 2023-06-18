/**
 * @author Tomas Becza <beczatom@fit.cvut.cz>
 * @date 08.05.2023
 */

#pragma once

#include <set>
#include <ctime>
#include <string>
#include "CPerson.h"
#include "CPlace.h"
#include "CDateTime.h"

/**
 * @class CEvent
 * @note Stores information about event.
 */

class CEvent {
private:
    /// name of event
    std::string mName;
    /// start of event
    CDateTime mStart;
    /// duration in minutes of event
    int mDuration;
    /// place of event
    CPlace mPlace;
    /// tags of event
    std::set<std::string> mTags;
    /// frequency of repeating in days (0, if is not repeating)
    int mRepeatingDays;
    /// participants of event
    std::set<CPerson> mParticipants;
    /// notes of event
    std::string mNotes;
public:
    /**
     * Constructs an default instance of CEvent.
     * @note duration and repeatingDays are set to -1, to ensure this is default constructed
     */
    CEvent();

    /**
     * Constructs an instance of CEvent
     * @param[in] name - desired name
     * @param[in] start - desired start
     * @param[in] duration - desired duration in minutes
     * @param[in] place - desired place
     * @param[in] tags - desired tags
     * @param[in] repeatingDays - desired frequency of repeating in days (0 if is not repeating)
     * @param[in] participants - desired participants
     * @param[in] notes - desired notes
     * @throw logic_error - if event is not valid
     */
    CEvent(const std::string &name,
           const CDateTime &start,
           int duration,
           const CPlace &place,
           const std::set<std::string> &tags,
           int repeatingDays,
           const std::set<CPerson> &participants,
           const std::string &notes);

    /**
     * Creates default event with dateTime start.
     * @param[in] dateTime - start
     */
    explicit CEvent(const CDateTime & dateTime);

    /**
     * Constructs an instance of CEvent from istream.
     * @param[in] is - to construct CEvent from
     * @throw invalid_argument - if event is not valid
     */
    explicit CEvent(std::istream & is);

    ~CEvent() = default;

    /**
     * Compares if this is less than given event (first by date, then by its place)
     * @param[in] event - compared to event
     * @return TRUE if this is less than given event.
     * @return FALSE if this is not less than given event.
     */
    bool operator<(const CEvent &event) const;

    /**
     * Compares if this starts before some dateTime.
     * @param[in] dateTime - compared to dateTime
     * @return TRUE if this starts before the given dateTime.
     * @return FALSE if this do not start before the given dateTime.
     */
    bool operator<(const CDateTime & dateTime) const;

    /**
     * Compares if this starts after some dateTime.
     * @param[in] dateTime - compared to dateTime
     * @return TRUE if this starts after the given dateTime.
     * @return FALSE if this do not start after the given dateTime.
     */
    bool operator>(const CDateTime & dateTime) const;

    /**
     * Compares if this is greater than given event (first by date, then by its place)
     * @param[in] event - compared to event
     * @return TRUE if this is greater than given event.
     * @return FALSE if this is not greater than given event.
     */
    bool operator>(const CEvent &event) const;

    /**
     * Compares if this is equal to given event (first by date, then by its place)
     * @param[in] event - compared to event
     * @return TRUE if this is equal to the given event.
     * @return FALSE if this is not equal to the given event.
     */
    bool operator==(const CEvent &event) const;

    /**
     * Prints out the event.
     * @param[in, out] os - ostream to append event
     * @param[in] event - to be printed
     * @return ostream appended by event
     */
    friend std::ostream &operator<<(std::ostream &os, const CEvent &event);

    /**
     * Sets the duration of the event.
     * @param[in] duration - desired duration
     */
    void setDuration(int duration);

    /**
     * Sets the name of the event.
     * @param[in] name - desired name
     */
    void setName(const std::string & name);

    /**
     * Sets the place of the event.
     * @param[in] place - desired place
     */
    void setPlace(const CPlace & place);

    /**
    * Appends the given participant to this.
    * @param[in] participant - will be appended to this
    */
    void addParticipant(const CPerson & participant);

    /**
    * Appends the given tag to this.
    * @param[in] tag - will be appended to this
    */
    void addTag(const std::string & tag);

    /**
     * Sets the start day of this.
     * @note the start time remains untouched
     * @param[in] day - desired day
     * @param[in] month - desired month
     * @param[in] year - desired year
     */
    void setStartDay(int day, int month, int year);

    /**
     * Sets the start day of this.
     * @note the start time remains untouched
     * @see CEvent::setStartDay(int day, int month, int year)
     * @param[in] dateTime - desired dateTime
     */
    void setStartDay(const CDateTime & dateTime);

    /**
     * Returns place where will be the event.
     * @return place where will be the event
     */
    CPlace getPlace() const;

    /**
     * Returns the start of event.
     * @return start of event
     */
    CDateTime getStart() const;

    /**
     * Returns name of the event.
     * @return name of the event
     */
    std::string getName() const;

    /**
     * Returns place name where will be the event.
     * @return place name where will be the event
     */
    std::string getPlaceName() const;

    /**
     * Returns the end of the event.
     * @return the end of the event
     */
    CDateTime getEnd() const;

    /**
     * Returns the number of participants.
     * @return the number of participants
     */
     int getParticipantsNum() const;

    /**
    * Returns the participants.
    * @return the participants
    */
    std::set<CPerson> getParticipants() const;

    /**
     * Detects if event is repeating.
     * @return TRUE if is repeating
     * @return FALSE if is not repeating
     */
    bool isRepeating() const;

    /**
     * Compares this and other event.
     * @param[in] event - to compare with
     * @return TRUE if all the filled (not default) attributes of event are equal to the attributes of this
     * @return FALSE if at least one of the filled (not default) attributes of event are not equal to the attributes of this
     */
    bool isLike(const CEvent &event) const;

    /**
     * Compares the starting days of this and given event.
     * @param[in] date - to compare with
     * @return TRUE if the starting days are equal
     * @return FALSE if the starting days are not equal
     */
    bool hasSameDay(const CDateTime & date) const;

    /**
     * Compares the starting months of this and given event.
     * @param[in] month - to compare with month
     * @param[in] year - to compare with year
     * @return TRUE if the starting months and years are equal
     * @return FALSE if the starting months and years are not equal
     */
    bool hasSameMonth(int month, int year) const;

    /**
     * Prints the event.
     * @return string with printed event.
     */
    std::string toString() const;

    /**
     * Prints the event for export.
     * @attention different format from CEvent::toString() const;
     * @see CEvent::toString() const;
     * @return string with printed event to export.
     */
    std::string toStringExport() const;

    /**
     * Increments the starting dateTime by given minutes.
     * @param[in] minutes - will be incremented to this starting datetime
     */
    void addMinutesToStart(int minutes);

    /**
     * Detects if this is in collision with given event.
     * @param[in] event - possibly colliding event
     * @return TRUE if is in collision with given event
     * @return FALSE if is not in collision with given event
     */
    bool isInCollision(const CEvent & event) const;

    /**
     * Detects if the event will be on given date.
     * @note can not just compare dates, because the events can be repeating
     * @param[in] dateTime - given date
     * @return TRUE if will be on given date
     * @return FALSE if will not be on given date
     */
    bool willBeOn(const CDateTime & dateTime) const;
};