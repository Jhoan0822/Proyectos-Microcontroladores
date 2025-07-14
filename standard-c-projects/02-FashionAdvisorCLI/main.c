/**
 * @file main.c
 * @author Julian Andres Barona Herrera - 201943845
 * @author Jhoan Eduardo Saldarriaga Serna - 2021222107
 * @brief A command-line "Fashion Advisor" expert system.
 * @version 2.0 (Refactored)
 * @date 2024-07-05
 *
 * This program recommends an outfit characteristic (shirt color, pants color, etc.)
 * based on two other characteristics provided by the user.
 *
 * The original version used deeply nested switch-case statements. This refactored
 * version uses a data-driven approach, where all combination rules are stored in an
 * array of structs. This makes the code cleaner, more readable, and easily extensible.
 */

#include <stdio.h>

// --- ENUMS for Readability (No more magic numbers!) ---

// The three main characteristics
typedef enum {
    TYPE_NONE = 0,
    TYPE_EYES = 1,
    TYPE_PANTS = 2,
    TYPE_SHIRT = 3
} CharacteristicType;

// Enums for the specific colors/options for each characteristic
typedef enum { EYE_GREEN = 1, EYE_BROWN, EYE_BLUE, EYE_GRAY } EyeColor;
typedef enum { PANTS_BLUE = 1, PANTS_BLACK } PantsColor;
typedef enum { SHIRT_BLACK = 1, SHIRT_WHITE, SHIRT_PINK, SHIRT_GREEN, SHIRT_BLUE, SHIRT_GRAY, SHIRT_YELLOW, SHIRT_RED } ShirtColor;


// --- DATA STRUCTURES ---

// Represents one of the user's choices
typedef struct {
    CharacteristicType type;
    int color; // Generic int to hold any of the color enums
} Selection;

// Represents a single "fashion rule"
typedef struct {
    Selection input1;
    Selection input2;
    Selection recommendation;
} FashionRule;


// --- DATA-DRIVEN LOGIC: The Rule Table ---
// This is the entire logic of the program, stored as data.
// To add a new rule, just add a new line to this array.
const FashionRule rules[] = {
    // Rules to recommend a SHIRT
    { {TYPE_EYES, EYE_GREEN}, {TYPE_PANTS, PANTS_BLUE},  {TYPE_SHIRT, SHIRT_BLACK} },
    { {TYPE_EYES, EYE_GREEN}, {TYPE_PANTS, PANTS_BLACK}, {TYPE_SHIRT, SHIRT_WHITE} },
    { {TYPE_EYES, EYE_BROWN}, {TYPE_PANTS, PANTS_BLUE},  {TYPE_SHIRT, SHIRT_PINK} },
    { {TYPE_EYES, EYE_BROWN}, {TYPE_PANTS, PANTS_BLACK}, {TYPE_SHIRT, SHIRT_GREEN} },
    { {TYPE_EYES, EYE_BLUE},  {TYPE_PANTS, PANTS_BLUE},  {TYPE_SHIRT, SHIRT_BLUE} },
    { {TYPE_EYES, EYE_BLUE},  {TYPE_PANTS, PANTS_BLACK}, {TYPE_SHIRT, SHIRT_GRAY} },
    { {TYPE_EYES, EYE_GRAY},  {TYPE_PANTS, PANTS_BLUE},  {TYPE_SHIRT, SHIRT_YELLOW} },
    { {TYPE_EYES, EYE_GRAY},  {TYPE_PANTS, PANTS_BLACK}, {TYPE_SHIRT, SHIRT_RED} },

    // Rules to recommend PANTS
    { {TYPE_EYES, EYE_GREEN}, {TYPE_SHIRT, SHIRT_BLACK}, {TYPE_PANTS, PANTS_BLUE} },
    { {TYPE_EYES, EYE_GREEN}, {TYPE_SHIRT, SHIRT_WHITE}, {TYPE_PANTS, PANTS_BLACK} },
    { {TYPE_EYES, EYE_BROWN}, {TYPE_SHIRT, SHIRT_PINK},  {TYPE_PANTS, PANTS_BLUE} },
    { {TYPE_EYES, EYE_BROWN}, {TYPE_SHIRT, SHIRT_GREEN}, {TYPE_PANTS, PANTS_BLACK} },

    // Rules to recommend EYE COLOR (Hypothetical, but shows extensibility)
    { {TYPE_PANTS, PANTS_BLUE}, {TYPE_SHIRT, SHIRT_BLACK}, {TYPE_EYES, EYE_GREEN} }
    // Add more rules here...
};

// Helper arrays to convert enums to strings for printing
const char* characteristic_names[] = {"", "Eye Color", "Pants Color", "Shirt Color"};
const char* eye_color_names[] = {"", "Green", "Brown", "Blue", "Gray"};
const char* pants_color_names[] = {"", "Blue", "Black"};
const char* shirt_color_names[] = {"", "Black", "White", "Pink", "Green", "Blue", "Gray", "Yellow", "Red"};

// --- Function Prototypes ---
void print_welcome_message();
void get_user_selections(Selection* s1, Selection* s2);
const FashionRule* find_recommendation(Selection s1, Selection s2);
void print_result(const FashionRule* rule);


// --- MAIN PROGRAM ---
int main() {
    while (1) {
        print_welcome_message();

        Selection selection1 = {TYPE_NONE, 0};
        Selection selection2 = {TYPE_NONE, 0};
        
        get_user_selections(&selection1, &selection2);

        const FashionRule* recommendation = find_recommendation(selection1, selection2);
        
        print_result(recommendation);

        printf("\n\nPress Enter to start over...");
        getchar(); // Consume newline from last scanf
        getchar(); // Wait for Enter key
    }
    return 0;
}


// --- Function Definitions ---

void print_welcome_message() {
    printf("--- Fashion Advisor ---\n");
    printf("Provide two characteristics, and I will recommend the third.\n");
}

// Handles the logic for getting user input for one characteristic
void get_single_selection(Selection* s, CharacteristicType avoid_type) {
    int choice = 0;
    // Get characteristic type
    do {
        printf("\nChoose a characteristic to define:\n");
        printf(" (1) Eye Color\n (2) Pants Color\n (3) Shirt Color\n");
        printf("Your choice (must be different from the first one): ");
        scanf("%d", &choice);
    } while (choice < 1 || choice > 3 || choice == avoid_type);
    s->type = (CharacteristicType)choice;

    // Get color based on characteristic type
    do {
        choice = 0;
        switch (s->type) {
            case TYPE_EYES:
                printf("\nEnter Eye Color: (1) Green, (2) Brown, (3) Blue, (4) Gray: ");
                scanf("%d", &choice);
                if (choice < 1 || choice > 4) choice = 0;
                break;
            case TYPE_PANTS:
                printf("\nEnter Pants Color: (1) Blue, (2) Black: ");
                scanf("%d", &choice);
                if (choice < 1 || choice > 2) choice = 0;
                break;
            case TYPE_SHIRT:
                printf("\nEnter Shirt Color: (1) Black, (2) White, ... (8) Red: ");
                scanf("%d", &choice);
                if (choice < 1 || choice > 8) choice = 0;
                break;
            default: break;
        }
    } while (choice == 0);
    s->color = choice;
}

void get_user_selections(Selection* s1, Selection* s2) {
    printf("\n--- First Characteristic ---\n");
    get_single_selection(s1, TYPE_NONE);
    
    printf("\n--- Second Characteristic ---\n");
    get_single_selection(s2, s1->type);
}

// The new logic core: just a simple loop!
const FashionRule* find_recommendation(Selection s1, Selection s2) {
    int num_rules = sizeof(rules) / sizeof(FashionRule);
    for (int i = 0; i < num_rules; i++) {
        // Check both A-B and B-A combinations
        if ((rules[i].input1.type == s1.type && rules[i].input1.color == s1.color &&
             rules[i].input2.type == s2.type && rules[i].input2.color == s2.color) ||
            (rules[i].input1.type == s2.type && rules[i].input1.color == s2.color &&
             rules[i].input2.type == s1.type && rules[i].input2.color == s1.color))
        {
            return &rules[i]; // Return a pointer to the matching rule
        }
    }
    return NULL; // No rule found
}

// Prints the final output to the user
void print_result(const FashionRule* rule) {
    printf("\n----------------------------------------\n");
    printf("RESULT:\n");
    if (rule == NULL) {
        printf("Sorry, I don't have a recommendation for that combination.\n");
    } else {
        printf("Based on your selections, my recommendation is:\n");
        Selection r = rule->recommendation;
        const char* rec_color_name = "";
        switch (r.type) {
            case TYPE_EYES: rec_color_name = eye_color_names[r.color]; break;
            case TYPE_PANTS: rec_color_name = pants_color_names[r.color]; break;
            case TYPE_SHIRT: rec_color_name = shirt_color_names[r.color]; break;
            default: break;
        }
        printf(">> %s: %s\n", characteristic_names[r.type], rec_color_name);
    }
    printf("----------------------------------------\n");
}