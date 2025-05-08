#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "./../fileHelper.cpp"
using namespace std;

#define TOTAL_POKEMON 386

struct Pokemon
{
    int oldIndex;
    int newIndex;
    string oldName;
    string newName;
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

void readPokedex(vector<Pokemon> &pokedex);
void writeStatsInDex(vector<Pokemon> &pokedex);
void updateNames(vector<Pokemon> &pokedex);
void reOrderPokedex(vector<Pokemon> &pokedex);
void printPokedex(vector<Pokemon> &pokedex);
void printCSV(vector<Pokemon> &pokedex);

int main()
{
    vector<Pokemon> pokedex;
    readPokedex(pokedex);
    writeStatsInDex(pokedex); // use old names
    updateNames(pokedex);
    reOrderPokedex(pokedex); // use new names
    printPokedex(pokedex);   // use new names
    printCSV(pokedex);       // use new names
    return 0;
}

void readPokedex(vector<Pokemon> &pokedex)
{
    FILE *readPointer;
    readPointer = fopen("./../../src/data/pokemon/species_info.h", "r");
    if (readPointer == NULL)
    {
        printf("Could not open species_info.h\n");
        return;
    }

    skipLines(readPointer, 37); // 37 garbage lines in the beginning
    for (int i = 0; i < TOTAL_POKEMON; i += 1)
    {
        Pokemon pkmn;
        pkmn.oldIndex = (i + 1);
        skipChars(readPointer, 13);
        pkmn.oldName = readString(readPointer, ']');
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
void writeStatsInDex(vector<Pokemon> &pokedex)
{
    FILE *writePointer;
    writePointer = fopen("./../../src/data/pokemon/pokedex_text_fr.h", "w");
    // writePointer = fopen("./output.txt", "w");
    if (writePointer == NULL)
    {
        printf("Could not open pokedex_text_fr.h\n");
        return;
    }
    fprintf(writePointer, "const u8 gDummyPokedexText[] = _(\n");
    fprintf(writePointer, "    \"This is a newly discovered POKéMON. It is\\n\"\n");
    fprintf(writePointer, "    \"currently under investigation. No detailed\\n\"\n");
    fprintf(writePointer, "    \"information is available at this time.\");\n");
    fprintf(writePointer, "\nconst u8 gDummyPokedexTextUnused[] = _(\"\");\n");

    for (int i = 0; i < pokedex.size(); i += 1)
    {
        string upperCase = pokedex[i].oldName;
        string camelCase;
        if (upperCase == "NIDORAN_F")
        {
            camelCase = "NidoranF";
        }
        else if (upperCase == "NIDORAN_M")
        {
            camelCase = "NidoranM";
        }
        else if (upperCase == "MR_MIME")
        {
            camelCase = "Mrmime";
        }
        else if (upperCase == "PORYGON2")
        {
            camelCase = "Porygon2";
        }
        else if (upperCase == "HO_OH")
        {
            camelCase = "HoOh";
        }
        else
        {
            camelCase.push_back(upperCase[0]);
            for (int i = 1; i < upperCase.length(); i++)
            {
                camelCase.push_back(upperCase[i] + 32);
            }
        }

        fprintf(writePointer, "\nconst u8 g%sPokedexText[] = _(\n", camelCase.c_str());
        fprintf(writePointer, "    \"HP     - %3d    Ph.Atk - %3d\\n\"\n", pokedex[i].HP, pokedex[i].PA);
        fprintf(writePointer, "    \"Ph.Def - %3d    Sp.Atk - %3d\\n\"\n", pokedex[i].PD, pokedex[i].SA);
        fprintf(writePointer, "    \"Sp.Def - %3d    Speed  - %3d\");\n", pokedex[i].SD, pokedex[i].SP);
        fprintf(writePointer, "\nconst u8 g%sPokedexTextUnused[] = _(\"\");\n", camelCase.c_str());
        // printf("successfully wrote %dth pokemon name\n", i + 1);
    }

    fclose(writePointer);
}
void updateNames(vector<Pokemon> &pokedex)
{
    FILE *readPointer;
    readPointer = fopen("./../../src/data/text/species_names.h", "r");
    if (readPointer == NULL)
    {
        printf("Could not open species_names.h\n");
        return;
    }

    skipLines(readPointer, 2); // 2 garbage lines in the beginning
    for (int i = 0; i < TOTAL_POKEMON; i += 1)
    {
        Pokemon &pkmn = pokedex[i];
        skipChars(readPointer, 20 + pkmn.oldName.length());
        pkmn.newName = readString(readPointer, '"');
        // printf("successfully read %dth pokemon name\n", i + 1);
        skipLines(readPointer, 1);
    }

    fclose(readPointer);
}
void reOrderPokedex(vector<Pokemon> &pokedex)
{
    FILE *readPointer;
    readPointer = fopen("./../../include/constants/pokedex.h", "r");
    if (readPointer == NULL)
    {
        printf("Could not open pokedex.h\n");
        return;
    }

    skipLines(readPointer, 7);
    vector<Pokemon> tempPokedex;
    for (int i = 0; i < TOTAL_POKEMON; i += 1)
    {
        skipChars(readPointer, 17);
        string name = readString(readPointer, ',');
        skipLines(readPointer, 1);
        // printf("%s\n", name.c_str());

        for (int j = 0; j < pokedex.size(); j += 1)
        {
            if (pokedex[j].oldName == name)
            {
                pokedex[j].newIndex = i + 1;
                tempPokedex.push_back(pokedex[j]);
                break;
            }
        }
    }
    pokedex = tempPokedex;
    fclose(readPointer);

    FILE *writePointer;
    writePointer = fopen("./new_pokedex.js", "w");
    if (writePointer == NULL)
    {
        printf("Could not open new_pokdex.txt\n");
        return;
    }

    fprintf(writePointer, "const pokemon_names = [\n");
    for (int i = 0; i < pokedex.size(); i += 1)
    {
        if (pokedex[i].oldName == "UNOWN")
        {
            fprintf(writePointer, "\t\"UNOWN/A\",\n");
        }
        else if (pokedex[i].oldName == "CASTFORM")
        {
            fprintf(writePointer, "\t\"CASTFORM/NORMAL\",\n");
        }
        else
        {

            fprintf(writePointer, "\t\"%s\",\n", pokedex[i].oldName.c_str());
        }
    }
    fprintf(writePointer, "];\n");
    fclose(writePointer);
}
void printPokedex(vector<Pokemon> &pokedex)
{
    FILE *writePointer = fopen("./species_info.txt", "w");
    if (writePointer == NULL)
    {
        printf("Could not open species_info.txt\n");
        return;
    }

    // Select columns to print
    bool printName = true;
    bool printTypes = true;
    bool printAbilities = true;
    bool printStats = true;
    bool printBST = true;

    // Apply custom sorting on the moveList
    // stable_sort(pokedex.begin(), pokedex.end(), [](const Pokemon &a, const Pokemon &b)
    //             { return a.name < b.name; });
    // stable_sort(pokedex.begin(), pokedex.end(), [](const Pokemon &a, const Pokemon &b)
    //             { return a.BST < b.BST; });
    // stable_sort(pokedex.begin(), pokedex.end(), [](const Pokemon &a, const Pokemon &b)
    //             { return a.index < b.index; });

    // Print the sorted pokedex
    string lineSeparator = "+-------+-------+";
    string tableHeader = "| INDEX | INDEX |";
    if (printName)
    {
        lineSeparator += "------------+";
        tableHeader += "  NAME      |";
    }
    if (printTypes)
    {
        lineSeparator += "----------+----------+";
        tableHeader += "  TYPE 1  |  TYPE 2  |";
    }
    if (printAbilities)
    {
        lineSeparator += "---------------+---------------+";
        tableHeader += "   ABILITY 1   |   ABILITY 2   |";
    }
    if (printStats)
    {
        lineSeparator += "-----+-----+-----+-----+-----+-----+";
        tableHeader += " HP  | PA  | PD  | SA  | SD  | SP  |";
    }
    if (printBST)
    {
        lineSeparator += "-----+";
        tableHeader += " BST |";
    }
    fprintf(writePointer, "%s\n", lineSeparator.c_str());
    fprintf(writePointer, "%s\n", tableHeader.c_str());
    fprintf(writePointer, "%s\n", lineSeparator.c_str());

    for (int i = 0; i < pokedex.size(); i += 1)
    {
        Pokemon pkmn = pokedex[i];
        fprintf(writePointer, "|  %03d  |  %03d  |", pokedex[i].oldIndex, pokedex[i].newIndex);
        if (printName)
        {
            fprintf(writePointer, " %-10s |", pkmn.newName.c_str());
        }
        if (printTypes)
        {
            fprintf(writePointer, " %-8s | %-8s |", pkmn.types[0].c_str(), pkmn.types[1].c_str());
        }
        if (printAbilities)
        {
            fprintf(writePointer, " %-13s | %-13s |", pkmn.abils[0].c_str(), pkmn.abils[1].c_str());
        }
        if (printStats)
        {
            fprintf(writePointer, " %3d | %3d | %3d | %3d | %3d | %3d |", pkmn.HP, pkmn.PA, pkmn.PD, pkmn.SA, pkmn.SD, pkmn.SP);
        }
        if (printBST)
        {
            fprintf(writePointer, " %3d |", pkmn.BST);
        }
        fprintf(writePointer, "\n");
        fprintf(writePointer, "%s\n", lineSeparator.c_str());
    }
}
void printCSV(vector<Pokemon> &pokedex)
{
    FILE *writePointer = fopen("./species_info.csv", "w");
    if (writePointer == NULL)
    {
        printf("Could not open species_info.csv\n");
        return;
    }

    fprintf(writePointer, "OldIndex,NewIndex,Name,Sprite,Type1,Type2,Abil1,Abil2,HP,PA,PD,SA,SD,SP,BST\n");

    for (int i = 0; i < pokedex.size(); i += 1)
    {
        Pokemon pkmn = pokedex[i];
        fprintf(writePointer, "%03d,", pkmn.oldIndex);
        fprintf(writePointer, "%03d,", pkmn.newIndex);
        fprintf(writePointer, "\"%s\",", pkmn.newName.c_str());
        string name = pkmn.oldName;
        transform(name.begin(), name.end(), name.begin(), ::tolower);
        fprintf(writePointer, "https://raw.githubusercontent.com/Ebadulislam1001/FireRed_RomHack/refs/heads/main/graphics/pokemon/%s/front.png,", name.c_str());
        // printing types
        if (pkmn.types[1] == "")
            fprintf(writePointer, "%s,...,", pkmn.types[0].c_str());
        else
            fprintf(writePointer, "%s,%s,", pkmn.types[0].c_str(), pkmn.types[1].c_str());
        // printing abilities
        if (pkmn.abils[1] == "")
            fprintf(writePointer, "%s,...,", pkmn.abils[0].c_str());
        else
            fprintf(writePointer, "%s,%s,", pkmn.abils[0].c_str(), pkmn.abils[1].c_str());
        // printing stats
        fprintf(writePointer, "%d,%d,%d,%d,%d,%d,", pkmn.HP, pkmn.PA, pkmn.PD, pkmn.SA, pkmn.SD, pkmn.SP);
        fprintf(writePointer, "%d\n", pkmn.BST);
    }

    fclose(writePointer);
}