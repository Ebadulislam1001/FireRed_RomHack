#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_POKEMON 386

struct Pokemon
{
    int index;
    string name;
    int HP;
    int PA;
    int PD;
    int SA;
    int SD;
    int SP;
    int BST;
    vector<string> types;
    vector<string> abils;
};

void skipChars(FILE *&readPointer, int charCount);
void skipLines(FILE *&readPointer, int lineCount);
int readInt(FILE *&readPointer);
string readString(FILE *&readPointer, char delim);
void readPokedex(vector<Pokemon> &pokedex);
void printPokedex(vector<Pokemon> &pokedex);
void printDataAnalysis(vector<Pokemon> &pokedex);

int main()
{
    vector<Pokemon> pokedex;
    readPokedex(pokedex);

    int prevChoice = 1;
    while (true)
    {
        printPokedex(pokedex);

        printf("Sort the pokedex in the order of\n");
        printf("1. Index\t2. Name \t3. BST\n");
        printf("4. HP   \t5. PA   \t6. PD \n");
        printf("7. SA   \t8. SD   \t9. SP \n");
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
            reverse(pokedex.begin(), pokedex.end());
        }
        else if (currChoice == 1)
        {
            stable_sort(pokedex.begin(), pokedex.end(), [](Pokemon a, Pokemon b)
                        { return a.index < b.index; });
        }
        else if (currChoice == 2)
        {
            stable_sort(pokedex.begin(), pokedex.end(), [](Pokemon a, Pokemon b)
                        { return a.name < b.name; });
        }
        else if (currChoice == 3)
        {
            stable_sort(pokedex.begin(), pokedex.end(), [](Pokemon a, Pokemon b)
                        { return a.BST < b.BST; });
        }
        else if (currChoice == 4)
        {
            stable_sort(pokedex.begin(), pokedex.end(), [](Pokemon a, Pokemon b)
                        { return a.HP < b.HP; });
        }
        else if (currChoice == 5)
        {
            stable_sort(pokedex.begin(), pokedex.end(), [](Pokemon a, Pokemon b)
                        { return a.PA < b.PA; });
        }
        else if (currChoice == 6)
        {
            stable_sort(pokedex.begin(), pokedex.end(), [](Pokemon a, Pokemon b)
                        { return a.PD < b.PD; });
        }
        else if (currChoice == 7)
        {
            stable_sort(pokedex.begin(), pokedex.end(), [](Pokemon a, Pokemon b)
                        { return a.SA < b.SA; });
        }
        else if (currChoice == 8)
        {
            stable_sort(pokedex.begin(), pokedex.end(), [](Pokemon a, Pokemon b)
                        { return a.SD < b.SD; });
        }
        else if (currChoice == 9)
        {
            stable_sort(pokedex.begin(), pokedex.end(), [](Pokemon a, Pokemon b)
                        { return a.SP < b.SP; });
        }
        prevChoice = currChoice;
    }

    printDataAnalysis(pokedex);
    return 0;
}

void skipChars(FILE *&readPointer, int charCount)
{
    for (int i = 0; i < charCount; i++)
        fgetc(readPointer);
}
void skipLines(FILE *&readPointer, int lineCount)
{
    for (int i = 0; i < lineCount; i++)
    {
        char line[100];
        fscanf(readPointer, "%[^\n]", line);
        fgetc(readPointer);
    }
}
int readInt(FILE *&readPointer)
{
    int ans = 0;
    fscanf(readPointer, "%d", &ans);
    return ans;
}
string readString(FILE *&readPointer, char delim)
{
    string ans = "";
    char ch;
    while (true)
    {
        fscanf(readPointer, "%c", &ch);
        if (ch == delim)
            break;
        ans.push_back(ch);
    }
    return ans;
}

void readPokedex(vector<Pokemon> &pokedex)
{
    FILE *readPointer = fopen("./../src/data/pokemon/species_info.h", "r");
    if (readPointer == NULL)
    {
        printf("Could not open the input file for reading");
        return;
    }

    skipLines(readPointer, 37); // 37 garbage lines in the beginning
    for (int i = 0; i < MAX_POKEMON; i++)
    {
        Pokemon pkmn;
        pkmn.index = (i + 1);
        skipChars(readPointer, 13);
        pkmn.name = readString(readPointer, ']');
        skipLines(readPointer, 2);
        skipChars(readPointer, 18);
        pkmn.HP = readInt(readPointer);
        skipLines(readPointer, 1);
        skipChars(readPointer, 22);
        pkmn.PA = readInt(readPointer);
        skipLines(readPointer, 1);
        skipChars(readPointer, 23);
        pkmn.PD = readInt(readPointer);
        skipLines(readPointer, 1);
        skipChars(readPointer, 21);
        pkmn.SP = readInt(readPointer);
        skipLines(readPointer, 1);
        skipChars(readPointer, 24);
        pkmn.SA = readInt(readPointer);
        skipLines(readPointer, 1);
        skipChars(readPointer, 25);
        pkmn.SD = readInt(readPointer);
        // BST is not given in the file. It has to be calculated
        pkmn.BST = pkmn.HP + pkmn.PA + pkmn.PD + pkmn.SA + pkmn.SD + pkmn.SP;
        skipLines(readPointer, 1);
        skipChars(readPointer, 23);
        pkmn.types.push_back(readString(readPointer, ','));
        skipChars(readPointer, 6);
        pkmn.types.push_back(readString(readPointer, '}'));
        if (pkmn.types[1] == pkmn.types[0])
            pkmn.types[1] = "";
        skipLines(readPointer, 16);
        skipChars(readPointer, 30);
        pkmn.abils.push_back(readString(readPointer, ','));
        skipChars(readPointer, 9);
        pkmn.abils.push_back(readString(readPointer, '}'));
        if (pkmn.abils[1] == "NONE")
            pkmn.abils[1] = "";
        pokedex.push_back(pkmn);
        // printf("successfully read %dth pokemon data\n", i + 1);
        skipLines(readPointer, 5);
        if (i == 250)
        {
            skipLines(readPointer, 25); // 25 garbage lines for unown data
        }
    }

    fclose(readPointer);
}
void printPokedex(vector<Pokemon> &pokedex)
{
    FILE *writePointer = fopen("species_info.txt", "w");
    if (writePointer == NULL)
    {
        cout << "Could not open the output file for writing" << endl;
        return;
    }

    string lineSeparator = "+-------+---------------+-----------+-----------+---------------+---------------+-----+-----+-----+-----+-----+-----+-----+";
    fprintf(writePointer, "%s\n", lineSeparator.c_str());
    fprintf(writePointer, "| INDEX |  NAME         | TYPE 1    | TYPE 2    | ABILITY 1     | ABILITY 2     | HP  | PA  | PD  | SA  | SD  | SP  | BST |\n");
    fprintf(writePointer, "%s\n", lineSeparator.c_str());

    for (int i = 0; i < pokedex.size(); i++)
    {
        Pokemon pkmn = pokedex[i];
        fprintf(writePointer, "|  %03d  | %-12s  ", pokedex[i].index, pkmn.name.c_str());
        fprintf(writePointer, "| %-8s  ", pkmn.types[0].c_str());
        fprintf(writePointer, "| %-8s  ", pkmn.types[1].c_str());
        fprintf(writePointer, "| %-13s ", pkmn.abils[0].c_str());
        fprintf(writePointer, "| %-13s ", pkmn.abils[1].c_str());
        fprintf(writePointer, "| %3d | %3d | %3d ", pkmn.HP, pkmn.PA, pkmn.PD);
        fprintf(writePointer, "| %3d | %3d | %3d ", pkmn.SA, pkmn.SD, pkmn.SP);
        fprintf(writePointer, "| %3d |\n", pkmn.BST);
        fprintf(writePointer, "%s\n", lineSeparator.c_str());
        // printf("successfully wrote %dth pokemon data\n", i + 1);
    }

    fclose(writePointer);
}
void printDataAnalysis(vector<Pokemon> &pokedex)
{
    // This printing takes place on terminal and not on the file
    map<string, int> typeMap;
    for (int i = 0; i < pokedex.size(); i++)
    {
        Pokemon pkmn = pokedex[i];
        for (int j = 0; j < 2; j++)
        {
            typeMap[pkmn.types[j]] += 1;
        }
    }
    printf("\nTYPES    : COUNT");
    printf("\n-----------------\n");
    for (auto it = typeMap.begin(); it != typeMap.end(); it++)
    {
        printf("%-9s:  %3d\n", it->first.c_str(), it->second);
    }
}