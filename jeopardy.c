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
int questions_answered = 0; // Track the number of questions answered to know when the game ends

while (game_running && questions_answered < NUM_QUESTIONS) {
    display_categories();

    char selected_player_name[MAX_LEN];
    printf("Enter the name of the player selecting the category and question: ");
    fgets(selected_player_name, MAX_LEN, stdin);
    selected_player_name[strcspn(selected_player_name, "\n")] = 0; // Remove newline

    if (!player_exists(players, NUM_PLAYERS, selected_player_name)) {
        printf("Player name does not exist. Try again.\n");
        continue; // Go back to the start of the loop to let the user try again
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
        continue; // Go back to the start of the loop to let the user choose a different question
    }

    // Display question and prompt for answer
display_question(category, value);

printf("Enter your answer (start with 'what is' or 'who is'): ");
char answer_input[BUFFER_LEN];
fgets(answer_input, BUFFER_LEN, stdin);
answer_input[strcspn(answer_input, "\n")] = 0; // Remove newline

// Tokenize input to check if it starts correctly and to extract the answer part
char *token = strtok(answer_input, " ");
char *prefix[3]; // For "what", "is"/"who", "is"
prefix[0] = token;
int prefix_count = 1;

while (token != NULL && prefix_count < 3) {
    token = strtok(NULL, " ");
    prefix[prefix_count++] = token;
}

// Check if the prefix is correct ("what is" or "who is")
if (prefix_count < 3 || (strcmp(prefix[0], "what") != 0 && strcmp(prefix[0], "who") != 0) || strcmp(prefix[1], "is") != 0) {
    printf("Answers must start with 'what is' or 'who is'.\n");
} else {
    char *actual_answer = prefix[2]; // The first word of the actual answer

    // Call a modified version of valid_answer that expects only the actual answer
    if (valid_answer(category, value, actual_answer)) {
        printf("Correct answer!\n");
        update_score(players, NUM_PLAYERS, selected_player_name, value);
        show_scores(players, NUM_PLAYERS);
    } else {
        printf("Incorrect answer. The correct answer was %s.\n", questions[get_question_index(category, value)].answer);
    }
    questions[get_question_index(category, value)].answered = true; // Mark the question as answered
}

    /*
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

    questions[get_question_index(category, value)].answered = true; // Mark the question as answered
    questions_answered++; // Increment the number of questions answered

    if (questions_answered >= NUM_QUESTIONS) {
        game_running = false; // End the game if all questions have been answered
    } else {
        // Optionally, show remaining questions/categories
        display_categories();
    }
    */
}

// Display final results
show_results(players, NUM_PLAYERS);


    return EXIT_SUCCESS;
}
