#include <sstream>
#include "../headers/CEvent.h"

using namespace std;

bool checkEvent(const CDateTime & start, const string &name, int duration, const CPlace &place, int repeatingDays, const set<CPerson> &participants){
    if(!start.empty() && !name.empty() && duration > 0 && repeatingDays >= 0 && place.getCapacity() >= static_cast<int>(participants.size())){
        return true;
    }
    else {
        return false;
    }
}

CEvent::CEvent(const std::string &name, const CDateTime &start, int duration, const CPlace &place,
               const std::set<std::string> &tags, int repeatingDays, const std::set<CPerson> &participants,
               const std::string &notes){
    if(checkEvent(start, name, duration, place, repeatingDays, participants)){
        mName = name;
        mStart = start;
        mDuration = duration;
        mPlace = place;
        mTags = tags;
        mRepeatingDays = repeatingDays;
        mParticipants = participants;
        mNotes = notes;
    }
    else throw logic_error(EVENT_ERROR);
}

bool CEvent::operator<(const CEvent &event) const{
    if(mStart == event.mStart){
        return mPlace < event.mPlace;
    }
    return mStart < event.mStart;
}

bool CEvent::operator<(const CDateTime &dateTime) const{
    return mStart < dateTime;
}

bool CEvent::operator==(const CEvent &event) const{
    return !(mStart < event.mStart) && !(event.mStart < mStart);
}

bool CEvent::operator>(const CEvent &event) const{
    return !(mStart < event.mStart) && !(mStart == event.mStart);
}

ostream &operator<<(ostream &os, const CEvent &event) {
    os << event.toString();
    return os;
}

bool CEvent::hasSameDay(const CDateTime & date) const {
    return mStart.sameDay(date);
}

bool CEvent::hasSameMonth(int month, int year) const {
    return mStart.sameMonth(month, year);
}

//returning true if all the filled (not default) attributes are equal
bool CEvent::isLike(const CEvent &event) const {
    if( (event.mName.empty() || mName == event.mName) &&
        (event.mStart.empty() || mStart.sameDay(event.mStart)) &&
        (event.mDuration == -1 || mDuration == event.mDuration) &&
        (event.mPlace.empty() || mPlace == event.mPlace) &&
        (event.mRepeatingDays == -1 || mRepeatingDays == event.mRepeatingDays) &&
        (event.mNotes.empty() || mNotes == event.mNotes)){

        if(!event.mParticipants.empty()){
            for(const CPerson & person : event.mParticipants){
                if(mParticipants.find(person) == mParticipants.end()) return false;
            }
        }

        if(!event.mTags.empty()){
            for(const string & tag : event.mTags){
                if(mTags.find(tag) == mTags.end()) return false;
            }
        }

        return true;
    }
    return false;
}

CEvent::CEvent()
        :mName(),
         mStart(),
         mDuration(-1),
         mPlace(),
         mTags(),
         mRepeatingDays(-1),
         mParticipants(),
         mNotes(){}

CEvent::CEvent(const CDateTime &dateTime)
        :mName(),
         mStart(dateTime),
         mDuration(),
         mPlace(),
         mTags(),
         mRepeatingDays(),
         mParticipants(),
         mNotes(){}

std::string CEvent::toString() const {
    string str;
    str.append(mName + PRINT_TO_CONSOLE_DELIMITER + mStart.toString() + PRINT_TO_CONSOLE_DELIMITER + to_string(mDuration) + PRINT_TO_CONSOLE_DELIMITER + mPlace.toString() + PRINT_TO_CONSOLE_DELIMITER);
    for(const string & tag : mTags){
        str.append(tag + PRINT_TO_CONSOLE_DELIMITER);
    }
    str.append(to_string(mRepeatingDays) + PRINT_TO_CONSOLE_DELIMITER);
    for(const CPerson & participant: mParticipants){
        str.append(participant.toString() + PRINT_TO_CONSOLE_DELIMITER);
    }
    str.append(mNotes);
    return str;
}

string CEvent::toStringExport() const {
    string str;
    str.append(mStart.toString() + EVENTS_DELIMITER + to_string(mDuration) + EVENTS_DELIMITER + mName + EVENTS_DELIMITER + mPlace.toString() + EVENTS_DELIMITER);
    for(const auto & participant : mParticipants){
        str.append(participant.toString() + ITEM_IN_EVENT_DELIMITER);
    }

    if(!mParticipants.empty()) str = str.substr(0, str.size() - 1);
    str += EVENTS_DELIMITER;

    for(const auto & tag : mTags){
        str.append(tag + ITEM_IN_EVENT_DELIMITER);
    }
    str = str.substr(0, str.size() - 1);
    str.append(EVENTS_DELIMITER + to_string(mRepeatingDays) + EVENTS_DELIMITER + mNotes + EVENTS_DELIMITER);
    return str;
}

void CEvent::setDuration(int duration) {
    mDuration = duration;
}

void CEvent::setName(const string &name) {
    mName = name;
}

void CEvent::setPlace(const CPlace &place) {
    mPlace = place;
}

void CEvent::addParticipant(const CPerson &participant) {
    mParticipants.insert(participant);
}

void CEvent::addTag(const string &tag) {
    mTags.insert(tag);
}

void CEvent::addMinutesToStart(int minutes) {
    mStart.addMinutes(minutes);
}

bool CEvent::isInCollision(const CEvent & event) const{
    CDateTime temp1 = mStart;
    CDateTime temp2 = event.mStart;
    temp1.addMinutes(mDuration);
    temp2.addMinutes(event.mDuration);
    if (temp1 >= event.mStart && mStart <= temp2) return true;
    if (temp2 >= mStart && temp1 >= event.mStart) return true;
    return false;
}

CPlace CEvent::getPlace() const {
    return mPlace;
}

bool CEvent::willBeOn(const CDateTime &dateTime) const {
    CDateTime tmp;
    // if start is on same day
    if(hasSameDay(dateTime)) return true;
    // if the event is not repeating or dateTime is before start of repeating
    else if(mRepeatingDays == 0 || dateTime < mStart) {
        tmp = getStart();
        // checks the end of event (midnight issue :/)
        if(dateTime.sameDay(tmp.addMinutes(mDuration))) return true;
        return false;
    }
    // if is repeating
    else{
        // to store the event repetition right before and right after the dateTime
        CDateTime tmpLower(mStart);
        CDateTime tmpHigher(mStart);
        int incrementDays = mRepeatingDays;
        // finding the two bounds
        while(tmp != tmpHigher){
            tmpHigher = tmpLower;
            while(!((dateTime >= tmpLower) && (dateTime <= tmpHigher))){
                tmpLower = tmpHigher;
                tmpHigher.addDays(incrementDays);
                incrementDays *= 2;
            }
            tmp = tmpLower;
            tmp.addDays(mRepeatingDays);
            incrementDays = mRepeatingDays;
        }
        // if one of the bounds is on same day, then the event is also on same day
        return dateTime.sameDay(tmpLower) || dateTime.sameDay(tmpHigher) || dateTime.sameDay(tmpLower.addMinutes(mDuration));
    }
}

bool CEvent::isRepeating() const{
    return mRepeatingDays != 0;
}

void CEvent::setStartDay(int day, int month, int year){
    mStart.setDate(day, month, year);
}

CEvent::CEvent(std::istream &istream) {
    char line[BUFFER_LENGTH];

    int duration, repeatingDays;
    CPlace place;
    CDateTime start;
    set<CPerson> participants;
    string name;

    string str;
    // getting values from istream
    for (int i = 0; i < 8; i++){
        istream.getline(line, BUFFER_LENGTH, EVENTS_DELIMITER);
        if(istream.eof()) return;
        str = line;
        stringstream ss = stringstream (str);

        if(i != 4 && i != 5 && i != 7 && str.empty()) throw invalid_argument(EVENT_ERROR);

        switch (i){
            case 0:
                start = CDateTime(str);
                break;
            case 1:
                try {
                    duration = stoi(str);
                } catch ( ... ){
                    throw invalid_argument(INVALID_ARGUMENT_ERROR);
                }
                break;
            case 2:
                name = str;
                break;
            case 3:
                place = CPlace(str);
                break;
            case 4:
                while(ss.getline(line, BUFFER_LENGTH, ITEM_IN_EVENT_DELIMITER)){
                    participants.insert(CPerson(line));
                }
                break;
            case 5:
                while(ss.getline(line, BUFFER_LENGTH, ITEM_IN_EVENT_DELIMITER)){
                    mTags.insert(string(line));
                }
                break;
            case 6:
                try{
                    repeatingDays = stoi(str);
                } catch( ... ){
                    throw invalid_argument(INVALID_ARGUMENT_ERROR);
                }
                break;
            case 7:
                mNotes = str;
                break;
        }
    }

    // sanitizing before constructing
    if(checkEvent(start, name, duration, place, repeatingDays, participants)){
        mStart = start;
        mName = name;
        mDuration = duration;
        mPlace = place;
        mRepeatingDays = repeatingDays;
        mParticipants = participants;
    }

    else throw invalid_argument(EVENT_ERROR);
}

CDateTime CEvent::getStart() const{
    return mStart;
}

void CEvent::setStartDay(const CDateTime &dateTime) {
    setStartDay(dateTime.getDay(), dateTime.getMonth(), dateTime.getYear());
}

string CEvent::getPlaceName() const {
    return mPlace.getName();
}

CDateTime CEvent::getEnd() const {
    CDateTime end(mStart);
    end.addMinutes(mDuration);
    return end;
}

string CEvent::getName() const{
    return mName;
}
