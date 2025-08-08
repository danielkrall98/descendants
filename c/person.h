// Daniel Krall

#ifndef PERSON_H
#define PERSON_H

// Define Struct Person
// A single Person with their input Information and number of male descendants
typedef struct
{
    char first_name[101];
    char last_name[101];
    char sex;  // 'm' for man and 'w' for woman
    int year_of_birth;
    int year_of_death;
    char father_first_name[101];
    char father_last_name[101];
    int father_year_of_birth;
    char mother_first_name[101];
    char mother_last_name[101];
    int mother_year_of_birth;
    int male_descendants;  // Number of male descendnets
} Person;

#endif
