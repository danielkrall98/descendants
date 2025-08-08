// Daniel Krall

#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person {
private:
    std::string firstName;
    std::string lastName;
    char sex; // 'm' or 'w'
    int yearOfBirth;
    int yearOfDeath;
    std::string fatherFirstName;
    std::string fatherLastName;
    int fatherYearOfBirth;
    std::string motherFirstName;
    std::string motherLastName;
    int motherYearOfBirth;
    int maleDescendants; // Number of male descendants

public:
    Person(); // Default constructor
    Person(const std::string &line); // Parse a line from personen.dat

    // Inline Getter-Methoden
    const std::string &getFirstName() const { return firstName; }
    const std::string &getLastName() const { return lastName; }
    char getSex() const { return sex; }
    int getYearOfBirth() const { return yearOfBirth; }
    const std::string &getFatherFirstName() const { return fatherFirstName; }
    const std::string &getFatherLastName() const { return fatherLastName; }
    int getFatherYearOfBirth() const { return fatherYearOfBirth; }
    int getMaleDescendants() const { return maleDescendants; }
    void setMaleDescendants(int count) { maleDescendants = count; }

    // Helper to uniquely identify this person
    std::string uniqueId() const;
};

#endif