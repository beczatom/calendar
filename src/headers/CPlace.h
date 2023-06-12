/**
 * @author Tomas Becza <beczatom@fit.cvut.cz>
 * @date 08.05.2023
 */

#pragma once

/**
 * @class CPlace
 * @note Stores information about place.
 */

class CPlace {
private:
    /// name of the place
    std::string mName;
    /// capacity of the place
    int mCapacity;

public:
    /**
     * Creates a default instance of CPlace.
     */
    CPlace();

    /**
     * Creates an instance of CPlace.
     * @param[in] name - name of the place
     * @param[in] capacity - capacity of place
     * @throw invalid_argument - if place is invalid
     */
    CPlace(const std::string &name, int capacity);

    /**
     * Copy constructor.
     * @param[in] place - to copy from
     */
    CPlace(const CPlace &place);

    /**
     * Creates an instance of CPlace from string.
     * @param[in] str - to create place
     * @throw invalid_argument - if place is invalid
     */
    CPlace(const std::string & str);

    /**
     * Similar to copy constructor.
     * @param[in] place - to copy from
     * @return reference to copied this
     */
    CPlace &operator=(const CPlace &place) = default;

    ~CPlace() = default;

    /**
     * Compares this with another place (by name lexicographically).
     * @param[in] place - to compare with
     * @return TRUE if this is less
     * @return FALSE if this is not less
     */
    bool operator<(const CPlace &place) const;

    /**
     * Compares this with another place
     * @param[in] place - to be compared with this
     * @note two places are equal if their names are equal (capacity doesn't matter)
     * @return TRUE if this is equal to place
     * @return FALSE if this is not equal to place
     */
    bool operator==(const CPlace &place) const;

    /**
     * Detects if name is empty
     * @return TRUE if name is empty
     * @return FALSE if this is not empty
     */
    bool empty() const;

    /**
     * Prints out a place.
     * @param[in, out] os - to be appended with place
     * @param[in] place - to be printed out
     * @return ostream appended with place
     */
    friend std::ostream &operator<<(std::ostream &os, const CPlace &place);

    /**
     * Prints out this.
     * @return string with info of this
     */
    std::string toString() const;

    /**
     * Returns the capacity of this.
     * @return capacity of this
     */
    int getCapacity() const;

    /**
     * Returns the name of this.
     * @return name of this
     */
    std::string getName() const;
};
