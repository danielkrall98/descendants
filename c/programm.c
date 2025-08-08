// Daniel Krall

#include "person_manager.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Print correct usage if less/more than 3 arguments are provided
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s personen.dat stand.dat\n", argv[0]);
        return 1;
    }

    const char *input_file = argv[1]; // only personen.dat is necessary
    const char *output_file = "maennlichenachkommen.dat"; // name of the output file

    PersonManager manager;
    initialize_person_manager(&manager);

    // returns -1 is file not found
    if (read_persons_from_file(&manager, input_file) != 0)
    {
        fprintf(stderr, "Error reading input file.\n");
        cleanup_person_manager(&manager);
        return 1;
    }

    // calculate and sort
    calculate_male_descendants(&manager);
    sort_people_by_descendants(&manager);

    if (write_persons_to_file(&manager, output_file) != 0)
    {
        fprintf(stderr, "Error writing output file.\n");
    }

    cleanup_person_manager(&manager);
    return 0;
}
