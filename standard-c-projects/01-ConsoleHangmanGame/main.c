/**
 * @file main.c
 * @author Julian Andres Barona Herrera - 201943845
 * @author Jhoan Eduardo Saldarriaga Serna - 2021222107
 * @brief A console-based implementation of the classic Hangman game in C.
 * @version 1.0
 * @date 2024-07-05
 *
 * This program allows a user to play Hangman against the computer. The game
 * runs in a loop, presenting a new word from a predefined list for each round.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h> // For toupper() to standardize input

// --- Constants ---
#define MAX_MISTAKES 6
#define WORD_COUNT 5

// --- Function Prototypes ---

/**
 * @brief Prints the ASCII art for the hangman based on the number of mistakes.
 * @param mistakes The current number of incorrect guesses.
 */
void printHangman(int mistakes);

/**
 * @brief Runs a single round of the Hangman game.
 * @param wordToGuess The word the player needs to guess.
 */
void runGame(const char* wordToGuess);


// --- Main Program Entry ---

int main() {
    // Predefined list of words for the game
    const char words[WORD_COUNT][15] = {"programming", "computer", "algorithm", "developer", "interface"};

    printf("Welcome to Hangman!\n");

    // Main game loop: iterates through the word list
    for (int i = 0; i < WORD_COUNT; i++) {
        printf("\n--- New Round! ---\n");
        runGame(words[i]);
        printf("Press Enter to continue to the next word...\n");
        getchar(); // Consume the newline from the previous scanf
        getchar(); // Wait for user to press Enter
    }
    
    printf("\nThanks for playing! You've completed all the words.\n");

    return 0;
}


// --- Function Definitions ---

void runGame(const char* wordToGuess) {
    int wordLength = strlen(wordToGuess);
    char playerProgress[wordLength + 1]; // +1 for the null terminator
    
    int mistakes = 0;
    int correctGuesses = 0;
    char guessedLetters[26] = {0}; // To track letters already tried (A-Z)

    // Initialize player's progress with underscores
    for (int i = 0; i < wordLength; i++) {
        playerProgress[i] = '_';
    }
    playerProgress[wordLength] = '\0'; // Null-terminate the string

    // Game loop for the current word
    while (mistakes < MAX_MISTAKES && correctGuesses < wordLength) {
        printf("\n-------------------------------------\n");
        printHangman(mistakes);
        printf("\n\nWord: ");
        for (int i = 0; i < wordLength; i++) {
            printf("%c ", playerProgress[i]);
        }
        printf("\nMistakes: %d/%d\n", mistakes, MAX_MISTAKES);
        
        printf("Enter a letter: ");
        char inputChar;
        scanf(" %c", &inputChar); // The space before %c consumes any leftover whitespace
        inputChar = tolower(inputChar); // Standardize input to lowercase

        // Check if the input is a valid letter
        if (inputChar < 'a' || inputChar > 'z') {
            printf("Invalid input. Please enter a letter from A to Z.\n");
            continue;
        }

        // Check if the letter was already guessed
        if (guessedLetters[inputChar - 'a']) {
            printf("You already tried the letter '%c'. Try another one.\n", inputChar);
            continue;
        }

        // Mark the letter as guessed
        guessedLetters[inputChar - 'a'] = 1;

        int foundLetter = 0;
        // Check if the guessed letter is in the word
        for (int i = 0; i < wordLength; i++) {
            if (wordToGuess[i] == inputChar) {
                if (playerProgress[i] == '_') { // Only count as a new correct guess
                    playerProgress[i] = inputChar;
                    correctGuesses++;
                }
                foundLetter = 1;
            }
        }

        if (foundLetter) {
            printf("Good guess!\n");
        } else {
            printf("Sorry, the letter '%c' is not in the word.\n", inputChar);
            mistakes++;
        }
    }

    // End of game check
    printf("\n=====================================\n");
    if (correctGuesses == wordLength) {
        printf("Congratulations! You guessed the word: %s\n", wordToGuess);
    } else {
        printHangman(mistakes);
        printf("\nGame Over! You lost. The word was: %s\n", wordToGuess);
    }
    printf("=====================================\n");
}


void printHangman(int mistakes) {
    printf("     _______\n");
    printf("    |       |\n");
    printf("    |       %s\n", mistakes >= 1 ? "O" : "");
    printf("    |      %s%s%s\n", mistakes >= 3 ? "/" : " ", mistakes >= 2 ? "|" : " ", mistakes >= 4 ? "\\" : "");
    printf("    |      %s %s\n", mistakes >= 5 ? "/" : " ", mistakes >= 6 ? "\\" : "");
    printf("    |\n");
    printf(" ----------\n");
}