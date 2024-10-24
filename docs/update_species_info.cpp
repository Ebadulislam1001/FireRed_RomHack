#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "fileHelper.cpp"
using namespace std;

#define TOTAL_POKEMON 386

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

void readPokedex(vector<Pokemon> &pokedex);
void writeStatsInDex(vector<Pokemon> &pokedex);
void updateNames(vector<Pokemon> &pokedex);
void printPokedex(vector<Pokemon> &pokedex);
void printCSV(vector<Pokemon> &pokedex);
void printDataAnalysis(vector<Pokemon> &pokedex);

int main()
{
    vector<Pokemon> pokedex;
    readPokedex(pokedex);
    writeStatsInDex(pokedex); // use old names
    updateNames(pokedex);
    printPokedex(pokedex); // use new names
    printCSV(pokedex);
    // printDataAnalysis(pokedex);
    return 0;
}

void readPokedex(vector<Pokemon> &pokedex)
{
    FILE *readPointer;
    readPointer = fopen("./../src/data/pokemon/species_info.h", "r");
    if (readPointer == NULL)
    {
        printf("Could not open species_info.h\n");
        return;
    }

    skipLines(readPointer, 37); // 37 garbage lines in the beginning
    for (int i = 0; i < TOTAL_POKEMON; i += 1)
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
void writeStatsInDex(vector<Pokemon> &pokedex)
{
    FILE *writePointer;
    writePointer = fopen("./../src/data/pokemon/pokedex_text_fr.h", "w");
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
        string upperCase = pokedex[i].name;
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
    readPointer = fopen("./../src/data/text/species_names.h", "r");
    if (readPointer == NULL)
    {
        printf("Could not open species_names.h\n");
        return;
    }

    skipLines(readPointer, 2); // 2 garbage lines in the beginning
    for (int i = 0; i < TOTAL_POKEMON; i += 1)
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
        printf("Could not open species_info.txt\n");
        return;
    }

    // string lineSeparator = "+-------+---------------+-----------+-----------+---------------+---------------+-----+-----+-----+-----+-----+-----+-----+";
    string lineSeparator = "+-------+---------------+-----+-----+-----+-----+-----+-----+-----+-----------+-----------+---------------+---------------+";
    fprintf(writePointer, "%s\n", lineSeparator.c_str());
    // fprintf(writePointer, "| INDEX |  NAME         | TYPE 1    | TYPE 2    | ABILITY 1     | ABILITY 2     | HP  | PA  | PD  | SA  | SD  | SP  | BST |\n");
    fprintf(writePointer, "| INDEX |  NAME         | HP  | PA  | PD  | SA  | SD  | SP  | BST | TYPE 1    | TYPE 2    | ABILITY 1     | ABILITY 2     |\n");
    fprintf(writePointer, "%s\n", lineSeparator.c_str());

    for (int i = 0; i < pokedex.size(); i += 1)
    {
        Pokemon pkmn = pokedex[i];
        fprintf(writePointer, "|  %03d  | %-12s  ", pokedex[i].index, pkmn.name.c_str());
        fprintf(writePointer, "| %3d | %3d | %3d ", pkmn.HP, pkmn.PA, pkmn.PD);
        fprintf(writePointer, "| %3d | %3d | %3d ", pkmn.SA, pkmn.SD, pkmn.SP);
        fprintf(writePointer, "| %3d ", pkmn.BST);
        fprintf(writePointer, "| %-8s  ", pkmn.types[0].c_str());
        fprintf(writePointer, "| %-8s  ", pkmn.types[1].c_str());
        fprintf(writePointer, "| %-13s ", pkmn.abils[0].c_str());
        fprintf(writePointer, "| %-13s ", pkmn.abils[1].c_str());
        fprintf(writePointer, "|\n%s\n", lineSeparator.c_str());
        // printf("successfully wrote %dth pokemon data\n", i + 1);
    }

    fclose(writePointer);
}
void printCSV(vector<Pokemon> &pokedex)
{
    FILE *writePointer = fopen("./../../../Data_Analysis/Ebad/species_info.csv", "w");
    if (writePointer == NULL)
    {
        printf("Could not open species_info.csv\n");
        return;
    }

    fprintf(writePointer, "DexNum,Name,HP,PA,PD,SA,SD,SP,BST,Type1,Type2,Abil1,Abil2\n");

    for (int i = 0; i < pokedex.size(); i += 1)
    {
        Pokemon pkmn = pokedex[i];
        fprintf(writePointer, "%03d,", pokedex[i].index);
        fprintf(writePointer, "\"%s\",", pkmn.name.c_str());
        fprintf(writePointer, "%d,%d,%d,%d,%d,%d,", pkmn.HP, pkmn.PA, pkmn.PD, pkmn.SA, pkmn.SD, pkmn.SP);
        fprintf(writePointer, "%d,", pkmn.BST);

        if (pkmn.types[1] == "")
            fprintf(writePointer, "%s,...,", pkmn.types[0].c_str());
        else
            fprintf(writePointer, "%s,%s,", pkmn.types[0].c_str(), pkmn.types[1].c_str());

        if (pkmn.abils[1] == "")
            fprintf(writePointer, "%s,...\n", pkmn.abils[0].c_str());
        else
            fprintf(writePointer, "%s,%s\n", pkmn.abils[0].c_str(), pkmn.abils[1].c_str());
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
        printf(" %s ", typeAbbr[i - 1].c_str());
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
