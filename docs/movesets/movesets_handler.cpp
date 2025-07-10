#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define TOTAL_POKEMON 386
#define TOTAL_MOVES 354

struct Moveset
{
    string species;
    /*
        always -1 for a tutor move
        always 0 for an egg move
        ranges from 1 to 100 for a level-up move
        ranges from 101 to 150 for a TM move
        ranges from 151 onwards for an HM move
    */
    int level;
    string move;
};

string lower_to_upper(string str);
void read_levelup_moves_data(vector<Moveset> &movesets);
void read_tmhm_moves_data(vector<Moveset> &movesets);
void read_egg_moves_data(vector<Moveset> &movesets);
void read_tutor_moves_data(vector<Moveset> &movesets);
void write_csv_data(vector<Moveset> &movesets);

int movesets_main()
{
    vector<Moveset> movesets;
    read_levelup_moves_data(movesets);
    read_tmhm_moves_data(movesets);
    read_egg_moves_data(movesets);
    read_tutor_moves_data(movesets);
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
void read_levelup_moves_data(vector<Moveset> &movesets)
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
        if (isNextChar(readPointer, '/'))
        {
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
            Moveset newMove;
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
}
void read_tmhm_moves_data(vector<Moveset> &movesets)
{
    printf("Reading data from tmhm_learnsets.h\n");
    FILE *readPointer;
    readPointer = fopen("./../src/data/pokemon/tmhm_learnsets.h", "r");
    if (readPointer == NULL)
    {
        printf("Could not open tmhm_learnsets.h\n");
        return;
    }

    skipLines(readPointer, 10);
    for (int i = 0; i < TOTAL_POKEMON + 25; i += 1)
    {
        skipChars(readPointer, 13);
        string speciesName = readString(readPointer, ']');
        skipChars(readPointer, 28 - speciesName.size());
        if (isNextChar(readPointer, '0'))
        {
            skipLines(readPointer, 2);
            continue;
        }
        skipChars(readPointer, 5);
        while (true)
        {
            Moveset newMove;
            newMove.species = speciesName;

            int offSet = 200;
            if (isNextChar(readPointer, 'T'))
            {
                offSet = 100;
            }
            else if (isNextChar(readPointer, 'H'))
            {
                offSet = 150;
            }
            skipChars(readPointer, 2);
            newMove.level = offSet + readInt(readPointer);

            skipChars(readPointer, 1);
            newMove.move = readString(readPointer, ')');

            movesets.push_back(newMove);
            if (isNextChar(readPointer, ')'))
            {
                skipLines(readPointer, 2);
                break;
            }
            else
            {
                skipLines(readPointer, 1);
                skipChars(readPointer, 47);
            }
        }
    }
    fclose(readPointer);
}
void read_egg_moves_data(vector<Moveset> &movesets)
{
    printf("Reading data from egg_moves.h\n");
    FILE *readPointer;
    readPointer = fopen("./../src/data/pokemon/egg_moves.h", "r");
    if (readPointer == NULL)
    {
        printf("Could not open egg_moves.h\n");
        return;
    }

    skipLines(readPointer, 5);
    while (true)
    {
        skipChars(readPointer, 13);
        if (isNextChar(readPointer, '_'))
        {
            break;
        }
        skipChars(readPointer, 1);
        string speciesName = readString(readPointer, ',');
        skipLines(readPointer, 1);
        while (true)
        {
            Moveset newMove;
            skipChars(readPointer, 19);
            newMove.species = speciesName;
            newMove.level = 0;
            newMove.move = readString(readPointer, ',');
            skipLines(readPointer, 1);
            if (newMove.move.back() == ')')
            {
                newMove.move.pop_back();
                movesets.push_back(newMove);
                skipLines(readPointer, 1);
                break;
            }
            else
            {
                movesets.push_back(newMove);
            }
        }
    }
    fclose(readPointer);
}
void read_tutor_moves_data(vector<Moveset> &movesets)
{
    printf("Reading data from tutor_learnsets.h\n");
    FILE *readPointer;
    readPointer = fopen("./../src/data/pokemon/tutor_learnsets.h", "r");
    if (readPointer == NULL)
    {
        printf("Could not open tutor_learnsets.h\n");
        return;
    }

    skipLines(readPointer, 25);
    for (int i = 0; i < TOTAL_POKEMON; i += 1)
    {
        skipChars(readPointer, 13);
        string speciesName = readString(readPointer, ']');
        skipChars(readPointer, 3);
        if(isNextChar(readPointer, '0'))
        {
            skipLines(readPointer, 2);
            continue;
        }
        skipChars(readPointer, 11);
        while (true)
        {
            Moveset newMove;
            newMove.species = speciesName;
            newMove.level = -1;
            newMove.move = readString(readPointer, ')');
            movesets.push_back(newMove);
            if (isNextChar(readPointer, ','))
            {
                skipLines(readPointer, 2);
                break;
            }
            else
            {
                skipLines(readPointer, 1);
                skipChars(readPointer, 28 + speciesName.size());
            }
        }
    }
    fclose(readPointer);
}
void write_csv_data(vector<Moveset> &movesets)
{
    FILE *readPointer;

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
        skipChars(readPointer, 19 - oldName.size());
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
        Moveset newMove = movesets[i];
        fprintf(writePointer, "%s,", newMove.species.c_str());
        fprintf(writePointer, "%d,", newMove.level);
        fprintf(writePointer, "%s\n", newMove.move.c_str());
    }

    fclose(writePointer);
}