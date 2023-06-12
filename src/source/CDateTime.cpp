#include <iomanip>
#include "../headers/CDateTime.h"
#include "../constants.h"

using namespace std;

//well-known algorithm
bool isLeap(int year){
    if(year % 4 == 0){
        if(year % 100 == 0){
            if(year % 400 == 0) return true;
            return false;
        }
        return true;
    }
    return false;
}

bool checkDateTime(int day, int month, int year, int hour, int minute){
    if(month >= 1 && month <= 12  && hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59 && day > 0){
        if(!isLeap(year)){
            return day <= DAYS_IN_MONTHS[month - 1];
        }
        else{
            return day <= DAYS_IN_MONTHS_LEAP[month - 1];
        }
    }
    return false;
}

CDateTime::CDateTime(int day, int month, int year, int hour, int minute){
    if(checkDateTime(day, month, year, hour, minute)){
        mDay = day;
        mMonth = month;
        mYear = year;
        mHour = hour;
        mMinute = minute;
    }
    else{
        throw logic_error(DATETIME_ERROR);
    }
}

CDateTime::CDateTime()
        :mDay(0),
         mMonth(0),
         mYear(0),
         mHour(0),
         mMinute(0){}

bool CDateTime::operator<(const CDateTime & dateTime) const{
    if(mYear == dateTime.mYear) {
        if (mMonth == dateTime.mMonth){
            if(mDay == dateTime.mDay){
                if(mHour == dateTime.mHour){
                    return mMinute < dateTime.mMinute;
                }
                return mHour < dateTime.mHour;
            }
            return mDay < dateTime.mDay;
        }
        return mMonth < dateTime.mMonth;
    }
    return mYear < dateTime.mYear;
}

bool CDateTime::operator>(const CDateTime & dateTime) const{
    return !(*this < dateTime) && !(*this == dateTime);
}

bool CDateTime::operator>=(const CDateTime & dateTime) const{
    return (*this > dateTime) || (*this == dateTime);
}

bool CDateTime::operator<=(const CDateTime & dateTime) const{
    return (*this < dateTime) || (*this == dateTime);
}

bool CDateTime::operator==(const CDateTime & dateTime) const{
    return !(*this < dateTime) && !(dateTime < *this);
}

bool CDateTime::operator!=(const CDateTime & dateTime) const{
    return !(*this == dateTime);
}

CDateTime::CDateTime(const std::string &str) {
    int date[5];
    for(int & x : date){
        x = 0;
    }
    char controlChar = '\n';
    if(sscanf(str.c_str(), "%d.%d.%d%c%d:%d", &date[0], &date[1], &date[2], &controlChar, &date[3], &date[4]) < 3) throw logic_error(DATETIME_ERROR);

    if(checkDateTime(date[0], date[1], date[2], date[3], date[4]) && (controlChar == '\n' || controlChar == ' ')){
        mDay = date[0];
        mMonth = date[1];
        mYear = date[2];
        mHour = date[3];
        mMinute = date[4];
    }
    else{
        throw logic_error(DATETIME_ERROR);
    }
}

//default constructed, else month can't be 0
bool CDateTime::empty() const {
    return mMonth == 0;
}

bool CDateTime::sameDay(const CDateTime & date) const {
   return date.mDay == mDay && date.mMonth == mMonth && date.mYear == mYear;
}

bool CDateTime::sameMonth(int month, int year) const {
    return month == mMonth && year == mYear;
}

string CDateTime::toStringDate() const {
    stringstream ss;
    ss << setw(2) << setfill('0') << mDay << DATE_DELIMITER << setw(2) << setfill('0') << mMonth << DATE_DELIMITER << setw(2) << setfill('0') << mYear;
    return ss.str();
}

string CDateTime::toStringTime() const {
    stringstream ss;
    ss << setw(2) << setfill('0') << mHour << TIME_DELIMITER << setw(2) << setfill('0') << mMinute;
    return ss.str();
}

string CDateTime::toString() const {
    return string(toStringDate() + PRINT_TO_CONSOLE_DELIMITER + toStringTime());
}

CDateTime CDateTime::addMinutes(int minutes) {
    int toAddDays = 0;
    mMinute += minutes;
    if(mMinute >= 60){
        mHour += (mMinute / 60);
        mMinute %= 60;
        if(mHour >= 24){
            toAddDays = (mHour / 24);
            mHour %= 24;
        }
    }
    addDays(toAddDays);
    return *this;
}

CDateTime CDateTime::addDays(int days) {
    mDay += days;
    if(!isLeap(mYear)){
        while(mDay > DAYS_IN_MONTHS[mMonth - 1]){
            mDay -= DAYS_IN_MONTHS[mMonth - 1];
            mMonth++;
            if(mMonth > 12){
                mMonth = 1;
                mYear++;
            }
        }
    }
    else{
        //the leap years :/
        while(mDay > DAYS_IN_MONTHS_LEAP[mMonth - 1]){
            mDay -= DAYS_IN_MONTHS_LEAP[mMonth - 1];
            mMonth++;
            if(mMonth > 12){
                mMonth = 1;
                mYear++;
            }
        }
    }
    return *this;
}

int CDateTime::getDayInYearNum() const{
    int dayNum = 0;
    //count all the days to the first day of this' month
    if(!isLeap(mYear)){
        for(int i = 0; i < mMonth - 1; i++){
            dayNum += DAYS_IN_MONTHS[i];
        }
    }
    else{
        //the leap years :/
        for(int i = 0; i < mMonth - 1; i++){
            dayNum += DAYS_IN_MONTHS_LEAP[i];
        }
    }
    //finally just add the day of month
    dayNum += mDay;
    return dayNum;
}

//algorithm -> Zeller's congruence
int CDateTime::getDayInWeekNum() const {
    int tmp = mYear;
    if(mMonth < 3){
        tmp -= mMonth;
    }
    return ((tmp + tmp / 4 - tmp / 100 + tmp / 400 + KEY_VALUE_MONTHS[mMonth - 1] + mDay) - 1) % 7;
}

//application of Zeller's congruence
int CDateTime::getWeekNum() const {
    return (getDayInYearNum() + DAYS_IN_WEEK - getDayInWeekNum() + 1) / DAYS_IN_WEEK;
}

bool CDateTime::sameYear(int year) const {
    return mYear == year;
}

int CDateTime::getMonth() const {
    return mMonth;
}

int CDateTime::getYear() const {
    return mYear;
}

void CDateTime::setDate(int day, int month, int year) {
    mDay = day;
    mMonth = month;
    mYear = year;
}

CDateTime CDateTime::getFirstDayInWeek(int weekNum, int year) {
    //invalid weekNum
    if(weekNum <= 0 || weekNum > CDateTime(31,12,year,0,0).getWeekNum()){
        throw logic_error(DATETIME_ERROR);
    }

    CDateTime date;
    date.setDate(1, 1, year);
    int dayInWeekNum = date.getDayInWeekNum();
    date.addDays(DAYS_IN_WEEK - dayInWeekNum);
    date.addDays((weekNum - 1) * DAYS_IN_WEEK);
    return date;
}

int CDateTime::getDay() const {
    return mDay;
}

std::ostream &operator<<(ostream &os, const CDateTime &dateTime) {
    return os << dateTime.mDay << DATE_DELIMITER << dateTime.mMonth << DATE_DELIMITER << dateTime.mYear << " "
              << dateTime.mHour << TIME_DELIMITER
              << dateTime.mMinute;
}
