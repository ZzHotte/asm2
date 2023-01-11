
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_SIZE 50
#define MAX_NUM_SEED_TYPES 3
#define LAND_SIZE 8
#define NO_SEED ' '
#define TRUE 1
#define FALSE 0
#define INI_SEEDS_NUM 60

struct land {
    int is_watered;
    char seed_name;
};

struct seeds {
    char name;
    int amount;
};

struct farmer {
    int curr_col;
    int curr_row;
    char curr_dir;
};

struct farmer initialise_farmer(struct farmer cse_farmer);
void initialise_seeds(struct seeds seed_collection[MAX_NUM_SEED_TYPES]);
void initialise_land(struct land farm_land[LAND_SIZE][LAND_SIZE]);

void print_top_row(struct land farm_land[LAND_SIZE][LAND_SIZE], int row);
void print_farmer_row(struct land farm_land[LAND_SIZE][LAND_SIZE], struct farmer cse_farmer);
void print_land(struct land farm_land[LAND_SIZE][LAND_SIZE], struct farmer cse_farmer);
static void print_all_seeds(struct seeds seed_collection[MAX_NUM_SEED_TYPES]);

int main(void) {

    struct farmer cse_farmer = {};
    cse_farmer = initialise_farmer(cse_farmer);

    struct land farm_land[LAND_SIZE][LAND_SIZE];
    initialise_land(farm_land);

    struct seeds seed_collection[MAX_NUM_SEED_TYPES];
    initialise_seeds(seed_collection);

    int seeds_num = 0, types_num = 0;

    printf("Welcome to CSE Valley, farmer!\n");
    printf("How many seeds do you need?\n");
    scanf("%d", &seeds_num);
    printf("Congratulations, you have received %d seeds.\n", seeds_num);
    printf("How many different types of seeds do you wish to have? No more than %d.\n", MAX_NUM_SEED_TYPES);
    printf("Enter the name of seeds could be given:\n");

    // Allocate memory for storing the seeds information.
    char seeds_name[MAX_NUM_SEED_TYPES][MAX_NAME_SIZE];
    while (scanf("%s", &seeds_name[types_num]) != EOF) {
        // types_num
        if (types_num + 1 > MAX_NUM_SEED_TYPES) {
            printf("Reach the MAX_NUM_SEED_TYPES, no more input.");
            break;
        }
        types_num = types_num + 1;
    }
    
    // For each seed type, do assign the seed.
    int seeds_spe_num = seeds_num / types_num, seeds_ret_num  = seeds_num % types_num; 

    for (int c1 = 0; c1 < types_num; c1++) {
        struct seeds curr_seed;

        curr_seed.name = seeds_name[c1][0];
        curr_seed.amount = seeds_spe_num;
        if (c1 == types_num - 1) {
            curr_seed.amount = curr_seed.amount + seeds_ret_num;
        }
        seed_collection[c1] = curr_seed;
    }

    // TODO: Scan the number of different seeds here!netsu
    // Note: Please remove all TODO's in your submission (including this comment)

    printf("Game Started!\n");

    /*
        Principle of using scanf:
        The content be scanned into should be a whole sentence, if the sentence be scanned into is not, then issue would take places
        for an infinite loop for returning 0. EOF represents scanning wrong and would never reach.
    */
    char command[1024];
    int ret;

    printf("Enter Command: ");
    while (ret = scanf("%s", &command) != EOF) {
        // Print all seeds
        if (strcmp("a", command) == 0) {
            print_all_seeds(seed_collection);
        // Print the map
        } else if (strcmp("l", command) == 0) {
            print_land(farm_land, cse_farmer);
        }
        printf("Enter Command: ");
    }
    

    return 0;
}


////////////////////////////////
//     Provided Functions     //
////////////////////////////////

// Prints the structs land (including locating where the
// farmer is)
// You will need this function in Stage 2.
void print_land(struct land farm_land[LAND_SIZE][LAND_SIZE],
                struct farmer cse_farmer) {
    printf("|---|---|---|---|---|---|---|---|\n");
    int i = 0;
    while (i < LAND_SIZE) {
        print_top_row(farm_land, i);
        // only prints mid and bottom row when the farmer
        // is in that row
        if (i == cse_farmer.curr_row) {
            print_farmer_row(farm_land, cse_farmer);
        }
        printf("|---|---|---|---|---|---|---|---|\n");
        i++;
    }
}

// NOTE: You do not need to directly call any of the functions
// below this point. You are allowed to modify them, but you
// do not need to.

// Initialises struct farmer to its default state upon starting
// in which the farmer will be on the top left of the farm
// facing to the right (as noted by '>')
struct farmer initialise_farmer(struct farmer cse_farmer) {
    cse_farmer.curr_col = 0;
    cse_farmer.curr_row = 0;
    cse_farmer.curr_dir = '>';
    return cse_farmer;
}

// Initialises a 2d array of struct land to its default state
// upon starting, which is that all land is unwatered and
// contains no seed
void initialise_land(struct land farm_land[LAND_SIZE][LAND_SIZE]) {
    int i = 0;
    while (i < LAND_SIZE) {
        int j = 0;
        while (j < LAND_SIZE) {
            farm_land[i][j].is_watered = FALSE;
            farm_land[i][j].seed_name = NO_SEED;
            j++;
        }
        i++;
    }
}

// Initialises struct farmer to its default state upon starting,
// which that all names are initialised as NO_SEED and its
// amount is 0
void initialise_seeds(struct seeds seed_collection[MAX_NUM_SEED_TYPES]) {
    int i = 0;
    while (i < MAX_NUM_SEED_TYPES) {
        seed_collection[i].amount = 0;
        seed_collection[i].name = NO_SEED;
        i++;
    }
}

////////////////////////////////
//      Helper Functions      //
////////////////////////////////

// prints the top row of a particular struct land
void print_top_row(struct land farm_land[LAND_SIZE][LAND_SIZE], int row) {
    int j = 0;
    while (j < LAND_SIZE) {
        printf("|");
        printf("%c", farm_land[row][j].seed_name);
        printf(" ");
        if (farm_land[row][j].is_watered == TRUE) {
            printf("W");
        } else {
            printf(" ");
        }
        j++;
    }
    printf("|");
    printf("\n");
}

// prints the 2 additional row when a farmer is in
// a particular row
void print_farmer_row(struct land farm_land[LAND_SIZE][LAND_SIZE],
                      struct farmer cse_farmer)  {
    int j = 0;
    while (j < LAND_SIZE) {
        printf("|");
        if (j == cse_farmer.curr_col) {
            if (cse_farmer.curr_dir == '<') {
                printf("<");
            } else {
                printf(" ");
            }
            if (cse_farmer.curr_dir == '^') {
                printf("^");
            } else {
                printf("f");
            }
            if (cse_farmer.curr_dir == '>') {
                printf(">");
            } else {
                printf(" ");
            }
        } else {
            printf("   ");
        }
        j++;
    }
    printf("|");
    printf("\n");
    j = 0;
    while (j < LAND_SIZE) {
        printf("|");
        if (j == cse_farmer.curr_col) {
            printf(" ");
            if (cse_farmer.curr_dir == 'v') {
                printf("v");
            } else if (cse_farmer.curr_dir == '^') {
                printf("f");
            } else {
                printf(" ");
            }
            printf(" ");
        } else {
            printf("   ");
        }
        j++;
    }
    printf("|");
    printf("\n");
}


////////////////////////////////
//      Utility Functions     //
////////////////////////////////

// Command: a, print the seeds recieved.
static void print_all_seeds(struct seeds seed_collection[MAX_NUM_SEED_TYPES]) {
    int counter = 0, length = MAX_NUM_SEED_TYPES;
    printf("Seeds at your disposal:\n");
    while (counter < length) {
        printf("- %d seed(s) with the name '%c'.\n", seed_collection[counter].amount, seed_collection[counter].name);
        counter++;
    }
}