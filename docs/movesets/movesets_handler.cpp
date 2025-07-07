#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define TOTAL_POKEMON 386
#define TOTAL_MOVES 354

struct LevelUpMove
{
    string species;
    int level;
    string move;
};

string lower_to_upper(string str);
void read_levelup_moveset_data(vector<LevelUpMove> &movesets);
void write_csv_data(vector<LevelUpMove> &movesets);

int movesets_main()
{
    vector<LevelUpMove> movesets;
    read_levelup_moveset_data(movesets);
    write_csv_data(movesets);
    return 0;
}

string lower_to_upper(string lowercase)
{
    if (lowercase == "NidoranF")
    {
        return "NIDORAN_F";
    }
    if (lowercase == "NidoranM")
    {
        return "NIDORAN_M";
    }
    if (lowercase == "Mrmime")
    {
        return "MR_MIME";
    }
    if (lowercase == "HoOh")
    {
        return "HO_OH";
    }
    for (int i = 0; i < lowercase.size(); i += 1)
    {
        if ('a' <= lowercase[i] && lowercase[i] <= 'z')
        {
            lowercase[i] = lowercase[i] - 'a' + 'A';
        }
    }

    return lowercase;
}
void read_levelup_moveset_data(vector<LevelUpMove> &movesets)
{
    printf("Reading data from level_up_learnsets.h\n");
    FILE *readPointer;
    readPointer = fopen("./../src/data/pokemon/level_up_learnsets.h", "r");
    if (readPointer == NULL)
    {
        printf("Could not open level_up_learnsets.h\n");
        return;
    }

    skipLines(readPointer, 3);
    while (true)
    {
        if(isNextChar(readPointer, '/')){
            break;
        }
        skipChars(readPointer, 18);
        string speciesName = lower_to_upper(readString(readPointer, '['));
        for (int c = 0; c < 15; c += 1)
        {
            speciesName.pop_back();
        }

        skipLines(readPointer, 1);
        while (true)
        {
            LevelUpMove newMove;
            newMove.species = speciesName;
            skipChars(readPointer, 13);
            if (isNextChar(readPointer, 'E'))
            {
                skipLines(readPointer, 3);
                break;
            }
            skipChars(readPointer, 5);
            newMove.level = readInt(readPointer);
            skipChars(readPointer, 7);
            newMove.move = readString(readPointer, ')');
            skipLines(readPointer, 1);
            movesets.push_back(newMove);
        }
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
        for (int j = 0; j < movesets.size(); j += 1)
        {
            if (movesets[j].species == oldName)
            {
                movesets[j].species = newName;
            }
        }
    }
    fclose(readPointer);

    printf("Reading new names from move_names.h\n");
    readPointer = fopen("./../src/data/text/move_names.h", "r");
    if (readPointer == NULL)
    {
        printf("Could not open move_names.h\n");
        return;
    }

    skipLines(readPointer, 2);
    for (int i = 0; i < TOTAL_MOVES; i += 1)
    {
        skipChars(readPointer, 10);
        string oldName = readString(readPointer, ']');
        skipChars(readPointer, 19-oldName.size());
        string newName = readString(readPointer, '"');
        skipLines(readPointer, 1);
        for (int j = 0; j < movesets.size(); j += 1)
        {
            if (movesets[j].move == oldName)
            {
                movesets[j].move = newName;
            }
        }
    }
    fclose(readPointer);
}
void write_csv_data(vector<LevelUpMove> &movesets)
{
    printf("Writing CSV data\n");
    FILE *writePointer = fopen("./movesets/movesets.csv", "w");
    if (writePointer == NULL)
    {
        printf("Could not open movesets.csv\n");
        return;
    }

    fprintf(writePointer, "species,level,move\n");

    for (int i = 0; i < movesets.size(); i += 1)
    {
        LevelUpMove newMove = movesets[i];
        fprintf(writePointer, "%s,", newMove.species.c_str());
        fprintf(writePointer, "%d,", newMove.level);
        fprintf(writePointer, "%s\n", newMove.move.c_str());
    }

    fclose(writePointer);
}