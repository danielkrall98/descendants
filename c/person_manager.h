// Daniel Krall

#ifndef PERSON_MANAGER_H
#define PERSON_MANAGER_H

#include <stddef.h>
#include "person.h"

// Define Struct PersonManager
typedef struct
{
    Person *people;
    size_t size;
    size_t capacity;
} PersonManager;

void initialize_person_manager(PersonManager *manager);
int read_persons_from_file(PersonManager *manager, const char *filename);
void calculate_male_descendants(PersonManager *manager);
void sort_people_by_descendants(PersonManager *manager);
int write_persons_to_file(const PersonManager *manager, const char *filename);
void cleanup_person_manager(PersonManager *manager);

#endif
