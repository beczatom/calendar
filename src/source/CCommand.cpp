#include "../headers/CCommand.h"

using namespace std;

bool CCommand::startsWith(const std::string &word, const std::string &prefix) const {
    if (word.length() < prefix.length()) return false;
    for (size_t i = 0; i < prefix.size(); i++) {
        if (word[i] != prefix[i]) return false;
    }
    return true;
}

CCommand::CCommand(shared_ptr<CCalendar> & calendar, const shared_ptr<CInterface> & interface)
        : mCalendar(calendar),
          mInterface(interface) {
}