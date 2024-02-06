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
#include "questions.h"

// Initializes the array of questions for the game
void initialize_game(void)
{
    printf("Welcome to Jeopardy!\n");
    printf("Loading questions...\n");
    // initialize each question struct and assign it to the questions array
    int questions_per_category = NUM_QUESTIONS / NUM_CATEGORIES;
    
    FILE *input_file = fopen("./questions.input", "r");
    if (!input_file) { printf("Could not load questions from questions.input!\n"); return; }

    int q = 0;
    char *buffer = calloc(MAX_LEN, sizeof(char));

    for (int c = 0; c < NUM_CATEGORIES; c++) {
	    for (int i = 0; i < questions_per_category; i++) {
		    strcpy(questions[q].category, categories[c]); //set category
		    questions[q].answered = false; //set answered to false

		    fgets(buffer, MAX_LEN, input_file); //get value
		    questions[q].value = atoi(buffer); //set value
		    
		    fgets(questions[q].question, MAX_LEN, input_file); //get question
		    fgets(questions[q].answer, MAX_LEN, input_file); //get answer
		    fgets(NULL, 0, input_file); //newline
		    q++;
	    }
    }

    printf("%d questions loaded successfully. Ready to play!\n", NUM_QUESTIONS);
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
    // print categories and dollar values for each unanswered question in questions array
}

// Displays the question for the category and dollar value
void display_question(char *category, int value)
{

}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
    // Look into string comparison functions
    return false;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value)
{
    // lookup the question and see if it's already been marked as answered
    return false;
}
