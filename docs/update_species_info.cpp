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
    for (int i = 0; i < charCount; i += 1)
        fgetc(readPointer);
}
void skipLines(FILE *&readPointer, int lineCount)
{
    for (int i = 0; i < lineCount; i += 1)
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
    FILE *readPointer;
    readPointer = fopen("./../src/data/pokemon/species_info.h", "r");
    if (readPointer == NULL)
    {
        printf("Could not open the input file for reading");
        return;
    }

    skipLines(readPointer, 37); // 37 garbage lines in the beginning
    for (int i = 0; i < MAX_POKEMON; i += 1)
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
    readPointer = fopen("./../src/data/text/species_names.h", "r");
    if (readPointer == NULL)
    {
        printf("Could not open the input file for reading");
        return;
    }

    skipLines(readPointer, 2); // 2 garbage lines in the beginning
    for (int i = 0; i < MAX_POKEMON; i += 1)
    {  
        Pokemon &pkmn = pokedex[i];
        skipChars(readPointer, 20 + pkmn.name.length());
        pkmn.name = readString(readPointer, '"');
        // printf("successfully read %dth pokemon name\n", i + 1);
        skipLines(readPointer, 1);
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

    for (int i = 0; i < pokedex.size(); i += 1)
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
    int typeCount = 18; // including "empty" type
    vector<string> typeName = {"", "NORMAL", "FIRE", "WATER", "ELECTRIC", "GRASS", "ICE", "FIGHTING", "POISON", "GROUND", "FLYING", "PSYCHIC", "BUG", "ROCK", "GHOST", "DRAGON", "DARK", "STEEL"};
    vector<string> typeAbbr = {"???", "NRM", "FIR", "WTR", "ELE", "GRS", "ICE", "FGH", "PSN", "GRN", "FLY", "PSY", "BUG", "RCK", "GHS", "DGN", "DRK", "STL"};
    map<string, int> indexOf;
    for (int i = 0; i < typeCount; i += 1)
    {
        indexOf[typeName[i]] = i;
    }

    vector<int> typeFrequency(typeCount, 0);
    vector<vector<int>> typeCombFrequency2(typeCount, vector<int>(typeCount, 0));

    for (int i = 0; i < pokedex.size(); i += 1)
    {
        Pokemon pkmn = pokedex[i];
        string type1 = pkmn.types[0];
        string type2 = pkmn.types[1];

        typeFrequency[indexOf[type1]] += 1;
        typeFrequency[indexOf[type2]] += 1;
        typeCombFrequency2[indexOf[type1]][indexOf[type2]] += 1;
        typeCombFrequency2[indexOf[type2]][indexOf[type1]] += 1;
    }

    printf("\nType frequency:\n");
    for (int i = 0; i < typeCount; i += 1)
    {
        printf("%s : %3d\n", typeAbbr[i].c_str(), typeFrequency[i]);
    }

    printf("\nType combination frequency:");
    printf("\n###");
    for (int i = typeCount; i > 0; i -= 1)
    {
        printf(" %s ", typeAbbr[i-1].c_str());
    }
    for (int i = 0; i < typeCount; i += 1)
    {
        printf("\n%s", typeAbbr[i].c_str());
        for (int j = typeCount - 1; j > i; j -= 1)
        {
            if (typeCombFrequency2[i][j] > 0)
                printf(" %3d ", typeCombFrequency2[i][j]);
            else
                printf(" %3s ", "---");
        }
    }
}
