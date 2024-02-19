/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2024, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

extern question questions[NUM_QUESTIONS];

// Put macros or constants here using #define
#define BUFFER_LEN 256
#define NUM_PLAYERS 4
//#define MAX_LEN 100

// Put global environment variables here

// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
void tokenize(char *input, char **tokens);

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(player *players, int num_players);

int main(int argc, char *argv[])
{
  (void)argc;
  (void)argv;
    player players[NUM_PLAYERS];
//    char buffer[BUFFER_LEN] = {0};

    initialize_game();

    // Prompt for player names and initialize scores
    for (int i = 0; i < NUM_PLAYERS; i++) {
        printf("Enter name of player %d: ", i + 1);
        fgets(players[i].name, MAX_LEN, stdin);
        players[i].name[strcspn(players[i].name, "\n")] = 0; // Remove newline
        players[i].score = 0;
        while (getchar() != '\n'); // Clear input buffer
    }

    // Main game loop
    bool game_running = true;
    while (game_running) {
        display_categories();

        char selected_player_name[MAX_LEN];
        printf("Enter the name of the player selecting the category and question: ");
        fgets(selected_player_name, MAX_LEN, stdin);
        selected_player_name[strcspn(selected_player_name, "\n")] = 0; // Remove newline

        if (!player_exists(players, NUM_PLAYERS, selected_player_name)) {
            printf("Player name does not exist. Try again.\n");
            continue;
        }

        char category[MAX_LEN];
        int value;
        printf("Enter category: ");
        fgets(category, MAX_LEN, stdin);
        category[strcspn(category, "\n")] = 0; // Remove newline
        printf("Enter value: ");
        scanf("%d", &value);
        while (getchar() != '\n'); // Clear input buffer

        if (already_answered(category, value)) {
            printf("Question already answered. Choose another one.\n");
            continue;
        }

        display_question(category, value);
        printf("Enter your answer: ");
        char answer[BUFFER_LEN];
        fgets(answer, BUFFER_LEN, stdin);
        answer[strcspn(answer, "\n")] = 0; // Remove newline

        if (valid_answer(category, value, answer)) {
            printf("Correct answer!\n");
            update_score(players, NUM_PLAYERS, selected_player_name, value);
        } else {
            printf("Incorrect answer. The correct answer was %s.\n", questions[get_question_index(category, value)].answer);
        }

        game_running = false; // Placeholder for checking if the game should continue
    }

    // Display final results
    show_results(players, NUM_PLAYERS);

    return EXIT_SUCCESS;
}


/*
int main(int argc, char *argv[])
{
  // An array of 4 players, may need to be a pointer if you want it set dynamically
  player players[NUM_PLAYERS];
  
  // Input buffer and and commands
  char buffer[BUFFER_LEN] = { 0 };

  // Display the game introduction and initialize the questions
  initialize_game();

  // Prompt for players names
  for (int i = 0; i < NUM_PLAYERS; i++)
  {
    printf("Enter name of player %d :", i + 1);
    fgets(players[i].name, MAX_LEN, stdin);
    // Remove the newline character that fgets reads at the end of the line
    players[i].name[strcspn(players[i].name, "\n")] = 0;

    // Initialize player's score to be 0
    players[i].score = 0;

    // Clear the input buffer to handle any leftover characters before reading the next string
    while (getchar() != '\n');
  }
  // Optionally, print the entered details to verify

  for(int i = 0; i < NUM_PLAYERS; i++)
  {
      printf("Player %d Name: %s, Score: %d\n", i + 1, players[i].name, players[i].score);
  }
  // initialize each of the players in the array

  // Perform an infinite loop getting command input from users until game ends
  while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
  {
      // Call functions from the questions and players source files

      // Execute the game until all questions are answered

      // Display the final results and exit
  }
  return EXIT_SUCCESS;
}
*/
