/**
 * @author Tomas Becza <beczatom@fit.cvut.cz>
 * @date 08.05.2023
 */

#pragma once

#include <iostream>
#include <utility>
#include <memory>

/**
 * @class CInterface
 * @note communicates with the user.
 */

class CInterface {
private:
    /// input
    std::istream & mIn;
    /// output
    std::ostream & mOut;
public:
    /// default constructor (input = cin, output = cout)
    CInterface();

    ~CInterface() = default;

    /**
     * Gets input from istream
     * @return the input
     * @throw runtime_error - if read null
     * @throw overflow_error - if input is longer than buffer length
     */
    std::string getInput() const;

    /**
     * Prints to ostream.
     * @tparam T - class of object to print out
     * @param obj - to print out
     */
    template<class T>
    void print(const T &obj) const;
};
