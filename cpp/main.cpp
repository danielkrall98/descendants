// Daniel Krall

#include "PersonManager.h"
#include <iostream>

// Passt sonst.  Rade
int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " personen.dat stand.dat\n";
        return 1;
    }

    const std::string input_file = argv[1];
    const std::string output_file = "maennlichenachkommen.dat";

    try {
        PersonManager manager;
        manager.readPersonsFromFile(input_file);
        manager.calculateMaleDescendants();
        manager.sortByMaleDescendants();
        manager.writePersonsToFile(output_file);
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
