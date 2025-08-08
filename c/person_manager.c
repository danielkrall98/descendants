// Daniel Krall

#include "person_manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Inizialize a Person Manager
void initialize_person_manager(PersonManager *manager)
{
    manager->people = NULL;
    manager->size = 0;
    manager->capacity = 0;
}

// Read People from File
// Es wäre besser, das read_persons_from_file zu nennen, damit es keinen Namenskonflikt gibt, falls das Programm erweitert wird und weitere Dateien gelesen werden.  Rade
// erledigt
int read_persons_from_file(PersonManager *manager, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file) return -1; // file not found

    char buffer[512];
    while (fgets(buffer, sizeof(buffer), file))     // until end of the file
    { 
        if (manager->size == manager->capacity)
        {
            manager->capacity = manager->capacity == 0 ? 10 : manager->capacity * 2; // manage capacity
            manager->people = realloc(manager->people, manager->capacity * sizeof(Person));
            if (!manager->people)
            {
                fclose(file);
                return -1;
            }
        }

        Person *p = &manager->people[manager->size++];
        sscanf(buffer, "%100s %100s %c %d %d %100s %100s %d %100s %100s %d",
               p->first_name, p->last_name, &p->sex, &p->year_of_birth, &p->year_of_death,
               p->father_first_name, p->father_last_name, &p->father_year_of_birth,
               p->mother_first_name, p->mother_last_name, &p->mother_year_of_birth);
        p->male_descendants = -1; // Anpassung fuer count_male_descendants

    }

    fclose(file);
    return 0;
}

// Count male descendants of a Person in PersonManager
static int count_male_descendants(PersonManager *manager, Person *person)
{
    // Es wäre geschickt, wenn man hier "if (person->male_descendants) return person->male_descendants;"
    // machen würde und unten vor dem return person->male_descendants=count;  Das würde viel redundante Berechnung verhindern. 
    // Oder besser noch am Anfang alle Einträge auf -1 setzen, damit die berechneten 0-Einträg auch nicht noch einmal berechnet werden müssen.
    // Rade
    // erledigt (+ read_persons_from_file angepasst)

    if (person->male_descendants != -1)
        return person->male_descendants;

    int count = 0;

    for (size_t i = 0; i < manager->size; ++i)
    {
        Person *child = &manager->people[i]; // pointer to current person in loop
        if (child->father_year_of_birth == person->year_of_birth &&
            strcmp(child->father_first_name, person->first_name) == 0 &&
            strcmp(child->father_last_name, person->last_name) == 0)
        {
            if (child->sex == 'm') count++;
            count += count_male_descendants(manager, child); // recursive call
        }
    }

    // Cache the calculated result
    person->male_descendants = count;
    return count;
}


// Calculate number of male descendants for each male Person in PersonManager
void calculate_male_descendants(PersonManager *manager)
{
    for (size_t i = 0; i < manager->size; ++i)
    {
        Person *p = &manager->people[i];
        if (p->sex == 'm')
        {
            p->male_descendants = count_male_descendants(manager, p); // store result in Person's male_descendants
        }
    }
}

// Static function to compare people for Sort
static int compare_descendants(const void *a, const void *b)
{
    const Person *pa = a, *pb = b;
    return pb->male_descendants - pa->male_descendants;
}

// Sort using Quicksort
void sort_people_by_descendants(PersonManager *manager)
{
    qsort(manager->people, manager->size, sizeof(Person), compare_descendants);
}

// Print Results into File
// Auch hier besser write_persons_to_file oder so.  Rade
// erledigt
int write_persons_to_file(const PersonManager *manager, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (!file) return -1;

    for (size_t i = 0; i < manager->size; ++i)
    {
        const Person *p = &manager->people[i];
        if (p->sex == 'm')
        {
            fprintf(file, "%s %s %d: %d male descendant(s)\n",
                    p->first_name, p->last_name, p->year_of_birth, p->male_descendants);
        }
    }

    fclose(file);
    return 0;
}

// Release allocated Memory
void cleanup_person_manager(PersonManager *manager)
{
    free(manager->people);
}
