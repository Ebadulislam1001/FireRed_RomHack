#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define TOTAL_POKEMON 386

struct Evolution
{
    string baseSpecies;
    string method;
    string param;
    string targetSpecies;
};

void read_evolution_data(vector<Evolution> &evolutions);
void write_csv_data(vector<Evolution> &evolutions);

int evolutions_main()
{
    vector<Evolution> evolutions;
    read_evolution_data(evolutions);
    write_csv_data(evolutions);
    return 0;
}

void read_evolution_data(vector<Evolution> &evolutions)
{
    printf("Reading data from evolution.h\n");
    FILE *readPointer;
    readPointer = fopen("./../src/data/pokemon/evolution.h", "r");
    if (readPointer == NULL)
    {
        printf("Could not open evolution.h\n");
        return;
    }

    skipLines(readPointer, 1);
    string base = "NONE";
    while (true)
    {
        Evolution evo;
        skipLines(readPointer, 1);
        if (isNextChar(readPointer, '}'))
        {
            break;
        }
        if (base == "NONE")
        {
            skipChars(readPointer, 13);
            evo.baseSpecies = readString(readPointer, ']');
            skipChars(readPointer, 15 - evo.baseSpecies.size());
        }
        else
        {
            evo.baseSpecies = base;
            skipChars(readPointer, 29);
        }

        evo.method = readString(readPointer, ',');

        skipChars(readPointer, 1);
        evo.param = readString(readPointer, ',');

        skipChars(readPointer, 9);
        evo.targetSpecies = readString(readPointer, '}');

        base = (isNextChar(readPointer, ','))
                   ? evo.baseSpecies
                   : "NONE";

        evolutions.push_back(evo);
    }
    fclose(readPointer);

    printf("Reading new names from species_names.h\n");
    readPointer = fopen("./../src/data/text/species_names.h", "r");
    if (readPointer == NULL)
    {
        printf("Could not open species_names.h\n");
        return;
    }

    skipLines(readPointer, 2);
    for (int i = 0; i < TOTAL_POKEMON; i += 1)
    {
        skipChars(readPointer, 13);
        string oldName = readString(readPointer, ']');
        skipChars(readPointer, 6);
        string newName = readString(readPointer, '"');
        skipLines(readPointer, 1);
        for (int j = 0; j < evolutions.size(); j += 1)
        {
            if (evolutions[j].baseSpecies == oldName)
            {
                evolutions[j].baseSpecies = newName;
            }
            if (evolutions[j].targetSpecies == oldName)
            {
                evolutions[j].targetSpecies = newName;
            }
        }
    }
    fclose(readPointer);
}
void write_csv_data(vector<Evolution> &evolutions)
{
    printf("Writing CSV data\n");
    FILE *writePointer = fopen("./evolutions/evolutions.csv", "w");

    fprintf(writePointer, "baseSpecies,method,param,targetSpecies\n");
    for (int i = 0; i < evolutions.size(); i += 1)
    {
        Evolution evo = evolutions[i];
        fprintf(writePointer, "%s,", evo.baseSpecies.c_str());
        fprintf(writePointer, "%s,", evo.method.c_str());
        fprintf(writePointer, "%s,", evo.param.c_str());
        fprintf(writePointer, "%s\n", evo.targetSpecies.c_str());
    }

    fclose(writePointer);
}