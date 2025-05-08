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
    string name;
    string effect;
    string description;
    int basePower;
    string type;
    int accuracy;
    int pp;
    int effectChance;
    string target;
    int priority;
};

void readMoveList(vector<Move> &moveList);
void readMoveDesc(vector<Move> &moveList);
void updateNames(vector<Move> &moveList);
void printMoveList(vector<Move> &moveList);
void printCSV(vector<Move> &moveList);

int main()
{
    vector<Move> moveList;
    readMoveList(moveList);
    readMoveDesc(moveList);
    updateNames(moveList);
    printMoveList(moveList); // use new names
    printCSV(moveList);      // use new names
}

void readMoveList(vector<Move> &moveList)
{
    FILE *readPointer = fopen("./../../src/data/battle_moves.h", "r");
    if (readPointer == NULL)
    {
        printf("Could not open battle_moves.h\n");
        return;
    }

    skipLines(readPointer, 15); // 15 garbage lines in the beginning
    for (int i = 0; i < TOTAL_MOVES; i++)
    {
        Move thisMove;
        thisMove.index = i;
        // printf("Move.index        = %d\n", thisMove.index);

        skipChars(readPointer, 10);
        thisMove.name = readString(readPointer, ']');
        // printf("Move.name         = %s\n", thisMove.name.c_str());

        skipLines(readPointer, 2);
        skipChars(readPointer, 25);
        thisMove.effect = readString(readPointer, ',');
        // printf("Move.basePower    = %d\n", thisMove.basePower);

        skipLines(readPointer, 1);
        skipChars(readPointer, 17);
        thisMove.basePower = readInt(readPointer);
        // printf("Move.basePower    = %d\n", thisMove.basePower);

        skipLines(readPointer, 1);
        skipChars(readPointer, 21);
        thisMove.type = readString(readPointer, ',');
        // printf("Move.type         = %s\n", thisMove.type.c_str());

        skipLines(readPointer, 1);
        skipChars(readPointer, 20);
        thisMove.accuracy = readInt(readPointer);
        // printf("Move.accuracy     = %d\n", thisMove.accuracy);

        skipLines(readPointer, 1);
        skipChars(readPointer, 14);
        thisMove.pp = readInt(readPointer);
        // printf("Move.pp           = %d\n", thisMove.pp);

        skipLines(readPointer, 1);
        skipChars(readPointer, 33);
        thisMove.effectChance = readInt(readPointer);
        // printf("Move.effectChance = %d\n", thisMove.effectChance);

        skipLines(readPointer, 1);
        skipChars(readPointer, 30);
        thisMove.target = readString(readPointer, ',');
        // printf("Move.target     = %s\n", thisMove.target.c_str());

        skipLines(readPointer, 1);
        skipChars(readPointer, 20);
        thisMove.priority = readInt(readPointer);
        // printf("Move.priority     = %d\n", thisMove.priority);

        skipLines(readPointer, 4);
        moveList.push_back(thisMove);
        // printf("successfully read %dth Move info\n", i + 1);
    }

    fclose(readPointer);
}
void readMoveDesc(vector<Move> &moveList)
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
        int underscoreCount = count(thismove.name.begin(), thismove.name.end(), '_');
        skipChars(readPointer, 34 + thismove.name.size() - underscoreCount);
        string text = readString(readPointer, '"');
        for (int i = 0; i < text.size(); i++)
        {
            if (text[i] == '\\')
            {
                i += 2;
                thismove.description.push_back(' ');
            }
            thismove.description.push_back(text[i]);
        }
        // printf("New name : %s\n", thismove.name.c_str());
        skipLines(readPointer, 1);
    }

    fclose(readPointer);
}
void updateNames(vector<Move> &moveList)
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
        thismove.name = readString(readPointer, '"');
        // printf("New name : %s\n", thismove.name.c_str());
        skipLines(readPointer, 1);
    }

    fclose(readPointer);
}
void printMoveList(vector<Move> &moveList)
{
    FILE *writePointer = fopen("./moves_info.txt", "w");
    if (writePointer == NULL)
    {
        printf("Could not open moves_info.txt\n");
        return;
    }

    // Select columns to print
    bool printName = true;
    bool printType = true;
    bool printEffect = true;
    bool printDescription = true;
    bool printBasePower = true;
    bool printAccuracy = true;
    bool printEffectChance = true;
    bool printPP = true;
    bool printTarget = true;
    bool printPriority = true;

    // Apply custom sorting on the moveList
    // stable_sort(moveList.begin(), moveList.end(), [](Move a, Move b)
    //             { return a.basePower < b.basePower; });
    // stable_sort(moveList.begin(), moveList.end(), [](Move a, Move b)
    //             { return a.type < b.type; });
    // stable_sort(moveList.begin(), moveList.end(), [](Move a, Move b)
    //             { return a.effect < b.effect; });
    // stable_sort(moveList.begin(), moveList.end(), [](Move a, Move b)
    //             { return a.index < b.index; });

    // Print the sorted moveList
    string lineSeparator = "+-------+";
    string tableHeader__ = "| INDEX |";
    if (printName)
    {
        lineSeparator += "----------------+";
        tableHeader__ += "  NAME          |";
    }
    if (printType)
    {
        lineSeparator += "----------+";
        tableHeader__ += " TYPE     |";
    }
    if (printEffect)
    {
        lineSeparator += "--------------------------+";
        tableHeader__ += "          EFFECT          |";
    }
    if (printDescription)
    {
        lineSeparator += "----------------------------------------------------------------------------------+";
        tableHeader__ += "                                MOVE DESCRIPTION                                  |";
    }
    if (printBasePower)
    {
        lineSeparator += "------------+";
        tableHeader__ += " BASE POWER |";
    }
    if (printAccuracy)
    {
        lineSeparator += "----------+";
        tableHeader__ += " ACCURACY |";
    }
    if (printEffectChance)
    {
        lineSeparator += "----------+";
        tableHeader__ += " EFFECT % |";
    }
    if (printPP)
    {
        lineSeparator += "----------+";
        tableHeader__ += "    PP    |";
    }
    if (printTarget)
    {
        lineSeparator += "------------------+";
        tableHeader__ += "     TARGET       |";
    }
    if (printPriority)
    {
        lineSeparator += "----------+";
        tableHeader__ += " PRIORITY |";
    }

    fprintf(writePointer, "%s\n", lineSeparator.c_str());
    fprintf(writePointer, "%s\n", tableHeader__.c_str());
    fprintf(writePointer, "%s\n", lineSeparator.c_str());

    for (int i = 0, j = 0; i < moveList.size(); i++)
    {
        Move thisMove = moveList[i];

        // Apply custom filtering on the moveList
        bool condition = (true
                          // && thisMove.type == "WATER"
                          // && thisMove.effect == "MULTI_HIT"
                          // && thisMove.basePower >= 100
                          // && thisMove.accuracy < 100
                          // && thisMove.pp == 40
                          // && thisMove.target == "USER"
                          // && thisMove.effectChance >= 50
                          // && thisMove.priority < 0
        );

        if (condition)
        {
            // fprintf(writePointer, "| %4d  ", thisMove.index);
            fprintf(writePointer, "| %4d  ", ++j);
            if (printName)
                fprintf(writePointer, "| %-14s ", thisMove.name.c_str());
            if (printType)
                fprintf(writePointer, "| %-8s ", thisMove.type.c_str());
            if (printEffect)
                fprintf(writePointer, "| %-24s ", thisMove.effect.c_str());
            if (printDescription)
                fprintf(writePointer, "| %-80s ", thisMove.description.c_str());
            if (printBasePower)
                fprintf(writePointer, "| %10d ", thisMove.basePower);
            if (printAccuracy)
                fprintf(writePointer, "| %8d ", thisMove.accuracy);
            if (printEffectChance)
                fprintf(writePointer, "| %8d ", thisMove.effectChance);
            if (printPP)
                fprintf(writePointer, "| %8d ", thisMove.pp);
            if (printTarget)
                fprintf(writePointer, "| %-16s ", thisMove.target.c_str());
            if (printPriority)
                fprintf(writePointer, "| %+8d ", thisMove.priority);
            fprintf(writePointer, "|\n%s\n", lineSeparator.c_str());
            // printf("successfully wrote %dth Move info\n", i + 1);}
        }
    }

    fclose(writePointer);
}
void printCSV(vector<Move> &moveList)
{
    FILE *writePointer = fopen("./moves_info.csv", "w");
    if (writePointer == NULL)
    {
        printf("Could not open moves_info.csv\n");
        return;
    }

    fprintf(writePointer, "Serial,Name,Type,BP,Accuracy,PP,Sec_Effect,Effect%,Target,Priority\n");

    for (int i = 0; i < moveList.size(); i += 1)
    {
        Move thisMove = moveList[i];
        fprintf(writePointer, "%d,", thisMove.index);
        fprintf(writePointer, "\"%s\",", thisMove.name.c_str());
        fprintf(writePointer, "\"%s\",", thisMove.type.c_str());
        fprintf(writePointer, "%d,", thisMove.basePower);
        fprintf(writePointer, "%d,", thisMove.accuracy);
        fprintf(writePointer, "%d,", thisMove.pp);
        fprintf(writePointer, "\"%s\",", thisMove.effect.c_str());
        fprintf(writePointer, "%d,", thisMove.effectChance);
        fprintf(writePointer, "\"%s\",", thisMove.target.c_str());
        fprintf(writePointer, "%d\n", thisMove.priority);
    }

    fclose(writePointer);
}