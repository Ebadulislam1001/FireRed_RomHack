#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "fileHelper.cpp"
using namespace std;

#define TOTAL_MOVES 354

struct Move
{
    string name;
    string type;
    string effect;
    int basePower;
    int accuracy;
    int pp;
    int priority;
    int effectChance;
};

void readMoveList(vector<Move> &moveList);
void printMoveList(vector<Move> &moveList);

int main()
{
    vector<Move> moveList;
    readMoveList(moveList);
    
    int prevChoice = -1;
    while (true)
    {
        printMoveList(moveList);
        printf("Sort the move list in the order of\n");
        printf("1. Name         \t2. Type     \t3. Effect \n");
        printf("4. Base Power   \t5. Accuracy \t6. PP     \n");
        printf("7. Priority     \t8. Effect % \t0. Reverse\n");
        printf("0. Exit \n");
        printf("Enter your choice: ");
        int currChoice;
        scanf("%d", &currChoice);
        if (currChoice == 0)
        {
           break;
        }
        else if (currChoice == prevChoice)
        {
            reverse(moveList.begin(), moveList.end());
        }
        else if(currChoice == 1)
        {
            stable_sort(moveList.begin(), moveList.end(), [](Move a, Move b)
                        { return a.name < b.name; });
        }
        else if(currChoice == 2)
        {
            stable_sort(moveList.begin(), moveList.end(), [](Move a, Move b)
                        { return a.type < b.type; });
        }
        else if(currChoice == 3)
        {
            stable_sort(moveList.begin(), moveList.end(), [](Move a, Move b)
                        { return a.effect < b.effect; });
        }
        else if(currChoice == 4)
        {
            stable_sort(moveList.begin(), moveList.end(), [](Move a, Move b)
                        { return a.basePower < b.basePower; });
        }
        else if(currChoice == 5)
        {
            stable_sort(moveList.begin(), moveList.end(), [](Move a, Move b)
                        { return a.accuracy < b.accuracy; });
        }
        else if(currChoice == 6)
        {
            stable_sort(moveList.begin(), moveList.end(), [](Move a, Move b)
                        { return a.pp < b.pp; });
        }
        else if(currChoice == 7)
        {
            stable_sort(moveList.begin(), moveList.end(), [](Move a, Move b)
                        { return a.priority < b.priority; });
        }
        else if(currChoice == 8)
        {
            stable_sort(moveList.begin(), moveList.end(), [](Move a, Move b)
                        { return a.effectChance < b.effectChance; });
        }
        prevChoice = currChoice;
    }
    return 0;
}

void readMoveList(vector<Move> &moveList)
{
    FILE *readPointer = fopen("./../src/data/battle_moves.h", "r");
    if (readPointer == NULL)
    {
        printf("Could not open the input file for reading");
        return;
    }

    skipLines(readPointer, 15); // 15 garbage lines in the beginning
    for (int i = 0; i < TOTAL_MOVES; i++)
    {
        Move thisMove;
        skipChars(readPointer, 10);
        thisMove.name = readString(readPointer, ']');
        skipLines(readPointer, 2);
        skipChars(readPointer, 25);
        thisMove.effect = readString(readPointer, ',');
        if (thisMove.effect == "HIT")
            thisMove.effect = "NONE";
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
        skipLines(readPointer, 2);
        skipChars(readPointer, 20);
        thisMove.priority = readInt(readPointer);
        moveList.push_back(thisMove);
        skipLines(readPointer, 4);
    }

    fclose(readPointer);
}
void printMoveList(vector<Move> &moveList)
{
    FILE *writePointer = fopen("moves_info.txt", "w");
    if (writePointer == NULL)
    {
        cout << "Could not open the output file for writing" << endl;
        return;
    }

    string lineSeparator = "+----------------+----------+-----------------------+----------+--------------------------+----------+----------+";
    fprintf(writePointer, "%s\n", lineSeparator.c_str());
    fprintf(writePointer, "|  NAME          | TYPE     | BASE POWER | ACCURACY |    PP    | ADDITIONAL EFFECT NAME   | EFFECT % | PRIORITY |\n");
    fprintf(writePointer, "%s\n", lineSeparator.c_str());

    for (int i = 0; i < moveList.size(); i++)
    {
        Move thisMove = moveList[i];
        fprintf(writePointer, "| %-14s ", thisMove.name.c_str());
        fprintf(writePointer, "| %-8s ", thisMove.type.c_str());
        fprintf(writePointer, "| %10d ", thisMove.basePower);
        fprintf(writePointer, "| %8d ", thisMove.accuracy);
        fprintf(writePointer, "| %8d ", thisMove.pp);
        fprintf(writePointer, "| %-24s ", thisMove.effect.c_str());
        fprintf(writePointer, "| %8d ", thisMove.effectChance);
        fprintf(writePointer, "| %+8d ", thisMove.priority);
        fprintf(writePointer, "|\n%s\n", lineSeparator.c_str());
        // printf("successfully wrote %dth Move data\n", i + 1);
    }

    fclose(writePointer);
}