#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "fileHelper.cpp"
using namespace std;

#define TOTAL_MOVES 354

struct Move
{
    int index;
    string name;
    string effect;
    int basePower;
    string type;
    int accuracy;
    int pp;
    int effectChance;
    string target;
    int priority;
};

void readMoveList(vector<Move> &moveList);
void updateNames(vector<Move> &moveList);
void printMoveList(vector<Move> &moveList);
// void printCSV(vector<Move> &moveList);

int main()
{
    vector<Move> moveList;
    readMoveList(moveList);
    updateNames(moveList);
    printMoveList(moveList); // use new names
    // printCSV(moveList); // use new names
}

void readMoveList(vector<Move> &moveList)
{
    printf("READING ...\n");
    FILE *readPointer = fopen("./../src/data/battle_moves.h", "r");
    if (readPointer == NULL)
    {
        printf("Could not open battle_moves.h\n");
        return;
    }

    skipLines(readPointer, 15); // 15 garbage lines in the beginning
    for (int i = 0; i < TOTAL_MOVES; i++)
    {
        Move thisMove;
        thisMove.index = i + 1;
        // printf("Move.index        = %d\n", thisMove.index);

        skipChars(readPointer, 10);
        thisMove.name = readString(readPointer, ']');
        // printf("Move.name         = %s\n", thisMove.name.c_str());

        skipLines(readPointer, 2);
        skipChars(readPointer, 25);
        thisMove.effect = readString(readPointer, ',');
        // printf("Move.effect       = %s\n", thisMove.effect.c_str());

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
    printf("READING COMPLETE !!!\n");
}
void updateNames(vector<Move> &moveList)
{
    printf("UPDATING ...\n");
    FILE *readPointer = fopen("./../src/data/text/move_names.h", "r"); // this needs a fix
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
    printf("UPDATING COMPLETE !!!\n");
}
void printMoveList(vector<Move> &moveList)
{
    printf("PRINTING ...\n");
    FILE *writePointer = fopen("moves_info.txt", "w");
    if (writePointer == NULL)
    {
        printf("Could not open moves_info.txt\n");
        return;
    }

    // Apply custom sorting on the moveList
    stable_sort(moveList.begin(), moveList.end(), [](Move a, Move b)
                { return a.priority > b.priority; });
    stable_sort(moveList.begin(), moveList.end(), [](Move a, Move b)
                { return a.pp > b.pp; });
    stable_sort(moveList.begin(), moveList.end(), [](Move a, Move b)
                { return a.accuracy > b.accuracy; });
    stable_sort(moveList.begin(), moveList.end(), [](Move a, Move b)
                { return a.effectChance > b.effectChance; });
    stable_sort(moveList.begin(), moveList.end(), [](Move a, Move b)
                { return a.target > b.target; });
    stable_sort(moveList.begin(), moveList.end(), [](Move a, Move b)
                { return a.effect < b.effect; });
    stable_sort(moveList.begin(), moveList.end(), [](Move a, Move b)
                { return a.basePower > b.basePower; });
    stable_sort(moveList.begin(), moveList.end(), [](Move a, Move b)
                { return a.type < b.type; });

    // Print the sorted moveList
    string lineSeparator = "+-------+----------------+----------+------------+----------+--------------------------+----------+-----------------+----------+----------+";
    fprintf(writePointer, "%s\n", lineSeparator.c_str());
    fprintf(writePointer, "| INDEX |  NAME          | TYPE     | BASE POWER | ACCURACY | ADDITIONAL EFFECT NAME   | EFFECT % |     TARGET      |    PP    | PRIORITY |\n");
    fprintf(writePointer, "%s\n", lineSeparator.c_str());

    for (int i = 0, j = 0; i < moveList.size(); i++)
    {
        Move thisMove = moveList[i];
        // bool condition = true;
        // bool condition = thisMove.type == "BUG";
        // bool condition = thisMove.basePower >= 100;
        // bool condition = thisMove.accuracy < 100;
        // bool condition = thisMove.target == "USER";
        // bool condition = thisMove.effectChance >= 50;
        bool condition = thisMove.effect == "MULTI_HIT";
        // bool condition = thisMove.priority < 0;
        // bool condition = true;
        if (condition)
        {
            // fprintf(writePointer, "| %4d  ", thisMove.index);
            fprintf(writePointer, "| %4d  ", ++j);
            fprintf(writePointer, "| %-14s ", thisMove.name.c_str());
            fprintf(writePointer, "| %-8s ", thisMove.type.c_str());
            fprintf(writePointer, "| %10d ", thisMove.basePower);
            fprintf(writePointer, "| %8d ", thisMove.accuracy);
            fprintf(writePointer, "| %-24s ", thisMove.effect.c_str());
            fprintf(writePointer, "| %8d ", thisMove.effectChance);
            fprintf(writePointer, "| %-15s ", thisMove.target.c_str());
            fprintf(writePointer, "| %8d ", thisMove.pp);
            fprintf(writePointer, "| %+8d ", thisMove.priority);
            fprintf(writePointer, "|\n%s\n", lineSeparator.c_str());
            // printf("successfully wrote %dth Move info\n", i + 1);}
        }
    }

    fclose(writePointer);
    printf("PRINTING COMPLETE !!!\n");
}
// void printCSV(vector<Move> &moveList)
// {
//     printf("GENERATING CSV...\n");
//     FILE *writePointer = fopen("moves_info.csv", "w");
//     if (writePointer == NULL)
//     {
//         printf("Could not open moves_info.csv\n");
//         return;
//     }
// 
//     fprintf(writePointer, "Serial,Name,Type,BP,Accuracy,PP,Sec_Effect,Effect%,Target,Priority\n");
// 
//     for (int i = 0; i < moveList.size(); i += 1)
//     {
//         Move thisMove = moveList[i];
//         fprintf(writePointer, "%d,", thisMove.index);
//         fprintf(writePointer, "\"%s\",", thisMove.name.c_str());
//         fprintf(writePointer, "\"%s\",", thisMove.type.c_str());
//         fprintf(writePointer, "%d,", thisMove.basePower);
//         fprintf(writePointer, "%d,", thisMove.accuracy);
//         fprintf(writePointer, "%d,", thisMove.pp);
//         fprintf(writePointer, "\"%s\",", thisMove.effect.c_str());
//         fprintf(writePointer, "%d,", thisMove.effectChance);
//         fprintf(writePointer, "\"%s\",", thisMove.target.c_str());
//         fprintf(writePointer, "%d\n", thisMove.priority);
//     }
// 
//     fclose(writePointer);
//     printf("GENERATING COMPLETE !!!\n");
// }