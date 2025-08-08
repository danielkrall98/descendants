// Daniel Krall

#ifndef PERSON_MANAGER_H
#define PERSON_MANAGER_H

#include "Person.h"
#include <vector>
#include <string>
#include <unordered_map>

class PersonManager {
private:
    std::vector<Person> people;
    std::unordered_map<std::string, int> maleDescendantCache;

    // Recursive helper for counting male descendants with caching
    int countMaleDescendants(const Person &person);

public:
    void readPersonsFromFile(const std::string &filename);
    void calculateMaleDescendants();
    void sortByMaleDescendants();
    void writePersonsToFile(const std::string &filename) const;
};

#endif