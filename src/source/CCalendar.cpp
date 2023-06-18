#include <fstream>
#include "../headers/CCalendar.h"

using namespace std;

CCalendar::CCalendar(const std::set<CEvent> &events) {
    mEvents = events;
}

void CCalendar::addEvent(const CEvent &event) {
    CEvent newEvent = event;

    CEvent tmp = CEvent();
    tmp.setPlace(event.getPlace());
    set<CEvent> samePlace;
    //events with same place to detect possible collisions
    select(tmp, samePlace);

    bool collision = false;

    //while event is on same day add some minutes and check if still is in collision
    do {
        for (const CEvent &samePlaceEvent: samePlace) {
            if (samePlaceEvent.willBeOn(event.getStart())) {
                CEvent tmp2 = samePlaceEvent;
                tmp2.setStartDay(newEvent.getStart());
                collision = newEvent.isInCollision(tmp2);
                if(collision) break;
            }
        }
        if(collision) newEvent.addMinutesToStart(MINUTES_STEP_COLLISION);
        else break;
    }while(newEvent.hasSameDay(event.getStart()));

    //insert only if no collision is detected
    if(!collision){
        mEvents.insert(newEvent);
    }
}

void CCalendar::select(const CEvent &event, set<CEvent> & events) const {
    for(const CEvent & thisEvent : mEvents){
        if(thisEvent.isLike(event)) events.insert(thisEvent);
    }
}

void CCalendar::selectLessDate(const CDateTime &dateTime, set<CEvent> & events) const {
    for(const CEvent & event : mEvents){
        if(event < dateTime) events.insert(event);
    }
}

void CCalendar::selectGreaterDate(const CDateTime &dateTime, set<CEvent> & events) const {
    CEvent comparedEvent = CEvent(dateTime);

    for(const CEvent & event : mEvents){
        if(event.isRepeating() || event > dateTime) events.insert(event);
    }
}

void CCalendar::selectSameDay(const CDateTime &dateTime, set<CEvent> & events) const {
    for(const CEvent & event : mEvents){
        if(event.willBeOn(dateTime)){
            events.insert(event);
        }
    }
}

void CCalendar::selectSameMonth(int month, int year, set<CEvent> & events) const {
    for(const CEvent & event : mEvents){
        //the easier way
        if(!event.isRepeating()){
            if(event.hasSameMonth(month, year)){
                events.insert(event);
            }
            continue;
        }
        //events with repetition can be possibly on more days in the same month
        else{
            for(int day = 1; day <= DAYS_IN_MONTHS[month - 1]; day++){
                if(event.willBeOn(CDateTime(day, month, year, 0, 0))){
                    CEvent toShowEvent(event);
                    toShowEvent.setStartDay(day, month, year);
                    events.insert(toShowEvent);
                }
            }
        }
    }
}

void CCalendar::selectSameWeek(int weekNum, int year, set<CEvent> & events) const {
    CDateTime monday = CDateTime::getFirstDayInWeek(weekNum, year);
    CDateTime dayInWeek = monday;
    //have to check all the days in week, beginning with monday
    for(int i = 0; i < DAYS_IN_WEEK; i++){
        for(const CEvent & event : mEvents){
            if(event.willBeOn(dayInWeek)){
                CEvent toInsertEvent = event;
                toInsertEvent.setStartDay(dayInWeek.getDay(), dayInWeek.getMonth(), dayInWeek.getYear());
                events.insert(toInsertEvent);
            }
        }
        dayInWeek = monday.addDays(1);
    }
}
