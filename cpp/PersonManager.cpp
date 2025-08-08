// Daniel Krall

#include "PersonManager.h"
#include <fstream>
#include <algorithm>
#include <stdexcept>

void PersonManager::readPersonsFromFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    std::string line;
    while (std::getline(file, line)) {
        people.emplace_back(line);
    }
    file.close();
}

int PersonManager::countMaleDescendants(const Person &person) {
    auto it = maleDescendantCache.find(person.uniqueId());
    if (it != maleDescendantCache.end()) {
        return it->second;
    }

    int count = 0;
    for (const auto &child : people) {
        if (child.getFatherYearOfBirth() == person.getYearOfBirth() &&
            child.getFatherFirstName() == person.getFirstName() &&
            child.getFatherLastName() == person.getLastName()) {
            if (child.getSex() == 'm') count++;
            count += countMaleDescendants(child);
        }
    }

    maleDescendantCache[person.uniqueId()] = count;
    return count;
}

void PersonManager::calculateMaleDescendants() {
    for (auto &person : people) {
        if (person.getSex() == 'm' && person.getMaleDescendants() == 0) {
            person.setMaleDescendants(countMaleDescendants(person));
        }
    }
}

void PersonManager::sortByMaleDescendants() {
    std::sort(people.begin(), people.end(), [](const Person &a, const Person &b) {
        return b.getMaleDescendants() < a.getMaleDescendants();
    });
}

void PersonManager::writePersonsToFile(const std::string &filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    for (const auto &person : people) {
        if (person.getSex() == 'm') {
            file << person.getFirstName() << " " << person.getLastName() << " "
                 << person.getYearOfBirth() << ": " << person.getMaleDescendants()
                 << " male descendent(s)\n";
        }
    }

    file.close();
}