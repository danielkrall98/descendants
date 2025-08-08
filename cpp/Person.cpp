// Daniel Krall

#include "Person.h"
#include <sstream>
#include <stdexcept>

// Kurze Funktionen sollten durchaus im Header-File in der Klassendeklaration implementiert werden, damit Inlining möglich wird.  Sonst ist C++ sehr langsam.  Rade
// Ich hoffe Sie haben das so gemeint, die kurzen Funktionen sind jetzt im Headerfile.
Person::Person() : sex(' '), yearOfBirth(0), yearOfDeath(0),
                   fatherYearOfBirth(0), motherYearOfBirth(0), maleDescendants(0) {}

Person::Person(const std::string &line) : maleDescendants(0) {
    std::istringstream iss(line);
    if (!(iss >> firstName >> lastName >> sex >> yearOfBirth >> yearOfDeath >>
          fatherFirstName >> fatherLastName >> fatherYearOfBirth >>
          motherFirstName >> motherLastName >> motherYearOfBirth)) {
        throw std::invalid_argument("Invalid line format: " + line);
    }
}

std::string Person::uniqueId() const {
    return firstName + " " + lastName + " " + std::to_string(yearOfBirth);
}
