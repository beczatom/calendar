#include <sstream>
#include <cstring>
#include <algorithm>
#include "../headers/CSelect.h"
#include "../headers/CExport.h"

using namespace std;

// deletes double whitespace from str
void deleteWS(string & str){
    if(str.empty()) return;

    for(size_t i = 0; i < str.size() && isblank(str.at(i)); i++){
        try{
            str.erase(i, 1);
        }catch ( ... ){
            return;
        }
        i--;
    }

    size_t length = str.length();

    if(length == 0) return;

    for(size_t i = 0; i < length - 2; i++){
        if(isblank(str.at(i)) && isblank(str.at(i+1))){
            str.erase(i, 1);
            i--;
            length--;
        }
    }
}

//returns true if the string starts with given prefix
bool startsWithPrefix(const string &word, const string &prefix) {
    if (word.length() < prefix.length()) return false;
    size_t prefixStart = 0;
    for (size_t i = 0; i < prefix.size(); i++) {
        if(isblank(word[i])) continue;
        if (word[i] != prefix[prefixStart]) {
            return false;
        }
        prefixStart++;
    }
    return true;
}

CSelect::CSelect(shared_ptr<CCalendar> & calendar, const shared_ptr<CInterface> & interface,
                 const string &args) : CCommand(calendar, interface, args) {}

void doAnd(set<CEvent> & events, const set<CEvent> & newEvents){
    set<CEvent> tmp = events;
    events.clear();
    set_intersection(tmp.begin(), tmp.end(), newEvents.begin(), newEvents.end(), inserter(events, events.begin()));
}

void doOr(set<CEvent> & events, const set<CEvent> & newEvents){
    for(const CEvent & newEvent : newEvents){
        events.insert(newEvent);
    }
}

void CSelect::Do() {
    set<CEvent> events;
    CEvent event = CEvent();
    deleteWS(mArgs);

    // find if contains export symbol
    size_t exportIndex = mArgs.find(EXPORT_OPERATOR);
    if(exportIndex != string::npos) {
        mArgs = mArgs.substr(exportIndex + EXPORT_OPERATOR.length());
        deleteWS(mArgs);
    }

    char arg[BUFFER_LENGTH];
    stringstream ss(mArgs);
    bool start = true;
    bool isAnd = false;
    bool lastLogicOperator = false;

    // if empty print everything
    if(ss.str().empty()){
        mCalendar->select(event, events);
    }

    // for every argument in select
    while(ss.getline(arg, BUFFER_LENGTH, ' ')){
        string strArg(arg);

        // and input
        if(strArg == AND_OPERATOR){
            if(start) throw invalid_argument(INVALID_OPERATOR_ERROR);
            start = true;
            isAnd = true;
            lastLogicOperator = true;
        }
        // or input
        else if(strArg == OR_OPERATOR){
            if(start) throw invalid_argument(INVALID_OPERATOR_ERROR);
            start = true;
            isAnd = false;
            lastLogicOperator = true;
        }
        // name selection
        else if(startsWithPrefix(strArg, string(NAME_ARGUMENT + EQUAL_OPERATOR))){
            lastLogicOperator = false;
            start = false;
            strArg = strArg.substr(NAME_ARGUMENT.length() + 1, string::npos);
            if(strArg.empty()) throw invalid_argument(INVALID_ARGUMENT_ERROR);
            event.setName(strArg);
        }
        // tag selection
        else if(startsWithPrefix(strArg, string(TAG_ARGUMENT + EQUAL_OPERATOR))){
            start = false;
            lastLogicOperator = false;
            strArg = strArg.substr(TAG_ARGUMENT.length() + 1, string::npos);
            if(strArg.empty()) throw invalid_argument(INVALID_ARGUMENT_ERROR);
            event.addTag(strArg);
        }
        // duration selection
        else if(startsWithPrefix(strArg, string(DURATION_ARGUMENT + EQUAL_OPERATOR))){
            start = false;
            lastLogicOperator = false;
            strArg = strArg.substr(DURATION_ARGUMENT.length() + 1, string::npos);
            if(strArg.empty()) throw invalid_argument(INVALID_ARGUMENT_ERROR);
            event.setDuration(stoi(strArg));
        }
        // participant selection (if contains provided person)
        else if(startsWithPrefix(strArg, string(PARTICIPANT_ARGUMENT + EQUAL_OPERATOR))){
            start = false;
            lastLogicOperator = false;
            strArg = strArg.substr(PARTICIPANT_ARGUMENT.length() + 1, string::npos);
            ss.getline(arg, BUFFER_LENGTH, ' ');
            if(strlen(arg) == 0){
                throw invalid_argument(NAME_ERROR);
            }
            event.addParticipant(CPerson(strArg, string(arg)));
        }
        // place selection with provided capacity
        else if(startsWithPrefix(strArg, string(PLACE_ARGUMENT + EQUAL_OPERATOR))){
            start = false;
            lastLogicOperator = false;
            strArg = strArg.substr(PLACE_ARGUMENT.length() + 1, string::npos);
            ss.getline(arg, BUFFER_LENGTH, ' ');
            if(strlen(arg) == 0){
                throw invalid_argument(PLACE_ERROR);
            }
            try{
                stoi(arg);
            } catch ( ... ){
                throw invalid_argument(PLACE_ERROR);
            }
            event.setPlace(CPlace(strArg, stoi(arg)));
        }
        // by start selection with extended less or greater than operators
        else if(startsWithPrefix(strArg, START_ARGUMENT)){
            start = false;
            lastLogicOperator = false;
            CDateTime eventStart = CDateTime(strArg.substr(START_ARGUMENT.length() + 1, string::npos));
            set<CEvent> newEvents;
            switch(strArg.at(START_ARGUMENT.length())){
                case LESS_THAN_OPERATOR:
                    mCalendar->selectLessDate(eventStart, newEvents);
                    break;
                case GREATER_THAN_OPERATOR:
                    mCalendar->selectGreaterDate(eventStart, newEvents);
                    break;
                case EQUAL_OPERATOR:
                    mCalendar->selectSameDay(eventStart, newEvents);
                    break;
                default:
                    throw invalid_argument(INVALID_OPERATOR_ERROR);
            }
            if(isAnd){
                doAnd(events, newEvents);
            }
            else{
                doOr(events, newEvents);
            }
            continue;
        }
        else{
            throw invalid_argument(INVALID_ARGUMENT_ERROR);
        }
        if(isAnd){
            set<CEvent> newEvents;
            mCalendar->select(event, newEvents);
            doAnd(events, newEvents);
        }
        else if(strArg != OR_OPERATOR){
            set<CEvent> newEvents;
            mCalendar->select(event, newEvents);
            doOr(events, newEvents);
        }
        event = CEvent();
    }
    if(lastLogicOperator) throw invalid_argument(INVALID_OPERATOR_ERROR);
    string toPrint;

    // printing out events
    if(!events.empty()){
        for(const CEvent & it : events){
            toPrint.append(it.toStringExport() + NEWLINE_DELIMITER);
        }
        toPrint.erase(toPrint.length() - 1);
    }

    // deciding if print to interface or file
    if(exportIndex != string::npos){
        CExport(mCalendar, mInterface, toPrint).Do();
    }

    else{
        if(toPrint.empty()) toPrint.append(NO_EVENTS_RESPONSE);
        mInterface->print<string>(toPrint);
    }
}
