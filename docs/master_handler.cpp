#include "./fileHelper.cpp"
#include "./species/species_info_handler.cpp"
#include "./evolutions/evolutions_handler.cpp"
#include "./moves/moves_info_handler.cpp"
#include "./movesets/movesets_handler.cpp"

int main() {
    // call the main functions or trigger points from each file manually
    printf("\nRunning species_info_main()\n");
    species_info_main();
    printf("\nRunning evolutions_main()\n");
    evolutions_main();
    printf("\nRunning moves_info_main()\n");
    moves_info_main();
    printf("\nRunning movesets_main()\n");
    movesets_main();
    return 0;
}