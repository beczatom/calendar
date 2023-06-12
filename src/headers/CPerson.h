/**
 * @author Tomas Becza <beczatom@fit.cvut.cz>
 * @date 08.05.2023
 */

#pragma once

#include <string>
#include <iostream>

/**
 * @class CPerson
 * @note Stores information about person.
 */

class CPerson {
private:
    /// name of person
    std::string mName;
    /// surname of person
    std::string mSurname;
    /// email of person, email can be an empty string
    std::string mEmail;

public:
    /**
     * default constructor
     */
    CPerson();

    /**
     * Constructs an instance of CPerson.
     * @param[in] name - name of person
     * @param[in] surname - surname of person.
     * @param[in] email - email of person.
     * @note email can be an empty string
     * @throw invalid_argument - if person is invalid
     */
    CPerson(const std::string &name, const std::string &surname, const std::string &email = std::string());

    /**
     * Creates an instance of CPerson from const char *.
     * @param[in] str - to construct instance from
     * @throw invalid_argument - if str format is invalid
     */
    explicit CPerson(const char * str);

    ~CPerson() = default;

    /**
     * Compares by surname and name lexicographically.
     * @param[in] person - will be compared with this
     * @return TRUE if this is less than person lexicographically
     * @return FALSE if this is not less than person lexicographically
     */
    bool operator<(const CPerson &person) const;

    /**
     * Compares by surname and name lexicographically.
     * @param[in] person - will be compared with this
     * @return TRUE if this is equal to person lexicographically
     * @return FALSE if this is not equal to person lexicographically
     */
    bool operator==(const CPerson &person) const;

    /**
     * Prints out a person.
     * @param[in, out] os - to be appended with person
     * @param[in] person - to be printed out
     * @return ostream appended with person
     */
    friend std::ostream &operator<<(std::ostream &os, const CPerson &person);

    /**
     * Prints out this.
     * @return string with info of this
     */
    std::string toString() const;
};
