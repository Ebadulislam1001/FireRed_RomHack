#include <iostream>
#include <string>
#include <vector>
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
    int phAtk;
    int phDef;
    int spAtk;
    int spDef;
    int speed;
    int totalStats;
    vector<string> types;
    vector<string> abils;
    vector<string> eggGroups;
    vector<int> evYields;
    int expYield;
    int catchRate;
    int eggCycles;
    int baseHappiness;
    string growthRate;
    string bodyColor;
};

void read_data_from_species_info(vector<Pokemon> &pokedex);
void write_data_in_pokedex_text(vector<Pokemon> &pokedex);
void read_newnames_from_species_names(vector<Pokemon> &pokedex);
void read_order_from_pokedex_order(vector<Pokemon> &pokedex);
void write_csv_data(vector<Pokemon> &pokedex);

int main()
{
    vector<Pokemon> pokedex;
    read_data_from_species_info(pokedex);
    write_data_in_pokedex_text(pokedex);
    read_newnames_from_species_names(pokedex);
    read_order_from_pokedex_order(pokedex);
    write_csv_data(pokedex);
    return 0;
}

void read_data_from_species_info(vector<Pokemon> &pokedex)
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
        pkmn.phAtk = readInt(readPointer);

        skipLines(readPointer, 1);
        skipChars(readPointer, 23);
        pkmn.phDef = readInt(readPointer);

        skipLines(readPointer, 1);
        skipChars(readPointer, 21);
        pkmn.speed = readInt(readPointer);

        skipLines(readPointer, 1);
        skipChars(readPointer, 24);
        pkmn.spAtk = readInt(readPointer);

        skipLines(readPointer, 1);
        skipChars(readPointer, 25);
        pkmn.spDef = readInt(readPointer);

        // BST is not given in the file. It has to be calculated
        pkmn.totalStats = pkmn.HP + pkmn.phAtk + pkmn.phDef + pkmn.spAtk + pkmn.spDef + pkmn.speed;

        skipLines(readPointer, 1);
        skipChars(readPointer, 23);
        pkmn.types.push_back(readString(readPointer, ','));
        skipChars(readPointer, 6);
        pkmn.types.push_back(readString(readPointer, '}'));
        if (pkmn.types[1] == pkmn.types[0])
            pkmn.types[1] = "---";

        skipLines(readPointer, 1);
        skipChars(readPointer, 21);
        pkmn.catchRate = readInt(readPointer);

        skipLines(readPointer, 1);
        skipChars(readPointer, 20);
        pkmn.expYield = readInt(readPointer);

        int evYieldsOffsets[6] = {22, 26, 27, 25, 28, 29};
        for (int i = 0; i < 6; i += 1)
        {
            skipLines(readPointer, 1);
            skipChars(readPointer, evYieldsOffsets[i]);
            pkmn.evYields.push_back(readInt(readPointer));
        }
        // speed, spAtk, spDef -> spAtk, spDef, speed
        int temp = pkmn.evYields[3];
        pkmn.evYields[3] = pkmn.evYields[4];
        pkmn.evYields[4] = pkmn.evYields[5];
        pkmn.evYields[5] = temp;

        skipLines(readPointer, 4);
        skipChars(readPointer, 21);
        pkmn.eggCycles = readInt(readPointer);

        skipLines(readPointer, 1);
        skipChars(readPointer, 22);
        pkmn.baseHappiness = readInt(readPointer);

        skipLines(readPointer, 1);
        skipChars(readPointer, 29);
        pkmn.growthRate = readString(readPointer, ',');

        skipLines(readPointer, 1);
        skipChars(readPointer, 32);
        pkmn.eggGroups.push_back(readString(readPointer, ','));
        skipChars(readPointer, 11);
        pkmn.eggGroups.push_back(readString(readPointer, '}'));
        if (pkmn.eggGroups[1] == pkmn.eggGroups[0])
            pkmn.eggGroups[1] = "---";

        skipLines(readPointer, 1);
        skipChars(readPointer, 30);
        pkmn.abils.push_back(readString(readPointer, ','));
        skipChars(readPointer, 9);
        pkmn.abils.push_back(readString(readPointer, '}'));
        if (pkmn.abils[1] == "NONE")
            pkmn.abils[1] = "---";

        skipLines(readPointer, 2);
        skipChars(readPointer, 32);
        pkmn.bodyColor = readString(readPointer, ',');

        pokedex.push_back(pkmn);
        skipLines(readPointer, 3);
        if (i == 250)
        {
            skipLines(readPointer, 25); // 22 garbage lines for unown data
        }
    }

    fclose(readPointer);
}
void write_data_in_pokedex_text(vector<Pokemon> &pokedex)
{
    FILE *writePointer;
    writePointer = fopen("./../../src/data/pokemon/pokedex_text_fr.h", "w");
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
            for (int i = 1; i < upperCase.length(); i += 1)
            {
                camelCase.push_back(upperCase[i] + 32);
            }
        }

        fprintf(writePointer, "\nconst u8 g%sPokedexText[] = _(\n", camelCase.c_str());
        fprintf(writePointer, "    \"HP     - %3d    Ph.Atk - %3d\\n\"\n", pokedex[i].HP, pokedex[i].phAtk);
        fprintf(writePointer, "    \"Ph.Def - %3d    Sp.Atk - %3d\\n\"\n", pokedex[i].phDef, pokedex[i].spAtk);
        fprintf(writePointer, "    \"Sp.Def - %3d    Speed  - %3d\");\n", pokedex[i].spDef, pokedex[i].speed);
        fprintf(writePointer, "\nconst u8 g%sPokedexTextUnused[] = _(\"\");\n", camelCase.c_str());
    }

    fclose(writePointer);
}
void read_newnames_from_species_names(vector<Pokemon> &pokedex)
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
        skipLines(readPointer, 1);
    }

    fclose(readPointer);
}
void read_order_from_pokedex_order(vector<Pokemon> &pokedex)
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
void write_csv_data(vector<Pokemon> &pokedex)
{
    FILE *writePointer = fopen("./species_info.csv", "w");
    if (writePointer == NULL)
    {
        printf("Could not open species_info.csv\n");
        return;
    }

    fprintf(writePointer, "oldIndex,newIndex,oldName,newName,");
    fprintf(writePointer, "HP,phAtk,phDef,spAtk,spDef,speed,totalStats,");
    fprintf(writePointer, "type1,type2,abil1,abil2,eggGroup1,eggGroup2,");
    fprintf(writePointer, "HPYield,phAtkYield,phDefYield,spAtkYield,spDefYield,speedYield,");
    fprintf(writePointer, "expYield,catchRate,eggCycles,baseHappiness,growthRate,bodyColor\n");

    for (int i = 0; i < pokedex.size(); i += 1)
    {
        Pokemon pkmn = pokedex[i];
        fprintf(writePointer, "%03d,", pkmn.oldIndex);
        fprintf(writePointer, "%03d,", pkmn.newIndex);
        fprintf(writePointer, "%s,", pkmn.oldName.c_str());
        fprintf(writePointer, "%s,", pkmn.newName.c_str());
        fprintf(writePointer, "%d,%d,%d,", pkmn.HP, pkmn.phAtk, pkmn.phDef);
        fprintf(writePointer, "%d,%d,%d,", pkmn.spAtk, pkmn.spDef, pkmn.speed);
        fprintf(writePointer, "%d,", pkmn.totalStats);
        fprintf(writePointer, "%s,%s,", pkmn.types[0].c_str(), pkmn.types[1].c_str());
        fprintf(writePointer, "%s,%s,", pkmn.abils[0].c_str(), pkmn.abils[1].c_str());
        fprintf(writePointer, "%s,%s,", pkmn.eggGroups[0].c_str(), pkmn.eggGroups[1].c_str());
        for (int EV = 0; EV < 6; EV += 1)
        {
            fprintf(writePointer, "%d,", pkmn.evYields[EV]);
        }
        fprintf(writePointer, "%d,", pkmn.expYield);
        fprintf(writePointer, "%d,", pkmn.catchRate);
        fprintf(writePointer, "%d,", pkmn.eggCycles);
        fprintf(writePointer, "%d,", pkmn.baseHappiness);
        fprintf(writePointer, "%s,", pkmn.growthRate.c_str());
        fprintf(writePointer, "%s\n", pkmn.bodyColor.c_str());
    }

    fclose(writePointer);
}