#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "./../fileHelper.cpp"
using namespace std;

#define TOTAL_MOVES 354

struct Move
{
    int index;
    string oldName;
    string newName;
    string type;
    string effect;
    string description;
    string target;
    int basePower;
    int accuracy;
    int pp;
    int effectChance;
    int priority;
    vector<int> flags;
};

void read_move_data_from_battle_moves(vector<Move> &moveList);
void read_move_desc_from_move_descriptions(vector<Move> &moveList);
void read_new_names_from_move_names(vector<Move> &moveList);
void write_csv_data(vector<Move> &moveList);

int main()
{
    vector<Move> moveList;
    read_move_data_from_battle_moves(moveList);
    read_move_desc_from_move_descriptions(moveList);
    read_new_names_from_move_names(moveList);
    write_csv_data(moveList); // use new names
}

void read_move_data_from_battle_moves(vector<Move> &moveList)
{
    FILE *readPointer = fopen("./../../src/data/battle_moves.h", "r");
    if (readPointer == NULL)
    {
        printf("Could not open battle_moves.h\n");
        return;
    }

    skipLines(readPointer, 15); // 15 garbage lines in the beginning
    for (int i = 0; i < TOTAL_MOVES; i += 1)
    {
        Move thisMove;
        thisMove.index = i;

        skipChars(readPointer, 10);
        thisMove.oldName = readString(readPointer, ']');

        skipLines(readPointer, 2);
        skipChars(readPointer, 25);
        thisMove.effect = readString(readPointer, ',');

        skipLines(readPointer, 1);
        skipChars(readPointer, 17);
        thisMove.basePower = readInt(readPointer);

        skipLines(readPointer, 1);
        skipChars(readPointer, 21);
        thisMove.type = readString(readPointer, ',');

        skipLines(readPointer, 1);
        skipChars(readPointer, 20);
        thisMove.accuracy = readInt(readPointer);

        skipLines(readPointer, 1);
        skipChars(readPointer, 14);
        thisMove.pp = readInt(readPointer);

        skipLines(readPointer, 1);
        skipChars(readPointer, 33);
        thisMove.effectChance = readInt(readPointer);

        skipLines(readPointer, 1);
        skipChars(readPointer, 30);
        thisMove.target = readString(readPointer, ',');

        skipLines(readPointer, 1);
        skipChars(readPointer, 20);
        thisMove.priority = readInt(readPointer);
        
        skipLines(readPointer, 1);
        skipChars(readPointer, 17);
        string flags = readString(readPointer, ',');
        thisMove.flags.push_back(flags.find("FLAG_MAKES_CONTACT") != string::npos ? 1 : 0);
        thisMove.flags.push_back(flags.find("FLAG_PROTECT_AFFECTED") != string::npos ? 1 : 0);
        thisMove.flags.push_back(flags.find("FLAG_MAGIC_COAT_AFFECTED") != string::npos ? 1 : 0);
        thisMove.flags.push_back(flags.find("FLAG_SNATCH_AFFECTED") != string::npos ? 1 : 0);
        thisMove.flags.push_back(flags.find("FLAG_MIRROR_MOVE_AFFECTED") != string::npos ? 1 : 0);
        thisMove.flags.push_back(flags.find("FLAG_KINGS_ROCK_AFFECTED") != string::npos ? 1 : 0);

        skipLines(readPointer, 3);
        moveList.push_back(thisMove);
    }

    fclose(readPointer);
}
void read_move_desc_from_move_descriptions(vector<Move> &moveList)
{
    FILE *readPointer = fopen("./../../src/move_descriptions.c", "r");
    if (readPointer == NULL)
    {
        printf("Could not open move_names.h\n");
        return;
    }

    skipLines(readPointer, 2); // 3 garbage lines in the beginning
    for (int i = 0; i < TOTAL_MOVES; i += 1)
    {
        Move &thismove = moveList[i];
        int underscoreCount = count(thismove.oldName.begin(), thismove.oldName.end(), '_');
        skipChars(readPointer, 34 + thismove.oldName.size() - underscoreCount);
        string text = readString(readPointer, '"');
        for (int i = 0; i < text.size(); i += 1)
        {
            if (text[i] == '\\')
            {
                i += 2;
                thismove.description.push_back(' ');
            }
            thismove.description.push_back(text[i]);
        }
        skipLines(readPointer, 1);
    }

    fclose(readPointer);
}
void read_new_names_from_move_names(vector<Move> &moveList)
{
    FILE *readPointer = fopen("./../../src/data/text/move_names.h", "r");
    if (readPointer == NULL)
    {
        printf("Could not open move_names.h\n");
        return;
    }

    skipLines(readPointer, 2); // 2 garbage lines in the beginning
    for (int i = 0; i < TOTAL_MOVES; i += 1)
    {
        Move &thismove = moveList[i];
        skipChars(readPointer, 30);
        thismove.newName = readString(readPointer, '"');
        skipLines(readPointer, 1);
    }

    fclose(readPointer);
}
void write_csv_data(vector<Move> &moveList)
{
    FILE *writePointer = fopen("./moves_info.csv", "w");
    if (writePointer == NULL)
    {
        printf("Could not open moves_info.csv\n");
        return;
    }
    // int index;
    // string oldName;
    // string newName;
    // string type;
    // string effect;
    // string description;
    // string target;
    // int basePower;
    // int accuracy;
    // int pp;
    // int effectChance;
    // int priority;
    // vector<int> flags;
    fprintf(writePointer, "serial,oldName,newName,type,basePower,accuracy,secondaryEffect,effectChance,");
    fprintf(writePointer, "PP,priority,target,description,");
    fprintf(writePointer, "makesContact,protectAffected,magicCoatAffected,snatchAffected,mirrorMoveAffected,kingsRockAffected\n");

    for (int i = 0; i < moveList.size(); i += 1)
    {
        Move thisMove = moveList[i];
        fprintf(writePointer, "%d,", thisMove.index);
        fprintf(writePointer, "%s,", thisMove.oldName.c_str());
        fprintf(writePointer, "%s,", thisMove.newName.c_str());
        fprintf(writePointer, "%s,", thisMove.type.c_str());
        fprintf(writePointer, "%d,", thisMove.basePower);
        fprintf(writePointer, "%d,", thisMove.accuracy);
        fprintf(writePointer, "%s,", thisMove.effect.c_str());
        fprintf(writePointer, "%d,", thisMove.effectChance);
        fprintf(writePointer, "%d,", thisMove.pp);
        fprintf(writePointer, "%d,", thisMove.priority);
        fprintf(writePointer, "%s,", thisMove.target.c_str());
        replace(thisMove.description.begin(), thisMove.description.end(), ',', ';');
        fprintf(writePointer, "%s", thisMove.description.c_str());
        for(int j = 0; j < thisMove.flags.size(); j += 1)
        {
            fprintf(writePointer, ",%d", thisMove.flags[j]);
        }
        fprintf(writePointer, "\n");
    }

    fclose(writePointer);
}