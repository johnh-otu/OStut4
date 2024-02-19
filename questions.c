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
#include <ctype.h>
#include "questions.h"

const int questions_per_category = NUM_QUESTIONS / NUM_CATEGORIES;
question questions[NUM_QUESTIONS];

// Initializes the array of questions for the game
void initialize_game(void)
{
    printf("Welcome to Jeopardy!\n");
    printf("Loading questions...\n");

    // initialize each question struct and assign it to the questions array
    FILE *input_file = fopen("./questions.input", "r");
    if (!input_file) { printf("Could not load questions from questions.input!\n"); return; }

    int q = 0;
    char *buffer = calloc(MAX_LEN, sizeof(char));

    for (int c = 0; c < NUM_CATEGORIES; c++) {
	    for (int i = 0; i < questions_per_category; i++) {

		    strcpy(questions[q].category, categories[c]); //set category
		    //questions[q].answered = (i%2 == 0); //set answered to false
        questions[q].answered = false; // set all questions unanswered as it is initialized

		    fgets(buffer, MAX_LEN, input_file); //get value
		    questions[q].value = atoi(buffer);
		    
		    fgets(questions[q].question, MAX_LEN, input_file); //get question
		    fgets(questions[q].answer, MAX_LEN, input_file); //get answer
        questions[q].answer[strcspn(questions[q].answer, "\n")] = '\0';

		    toLower(questions[q].answer); //set to lower
		    fgets(buffer, 5, input_file); //newline
		    
		    //debug
		    //printf("category:%s value:%d q:%s a:%s\n", categories[c], questions[q].value, questions[q].question, questions[q].answer);
		    
		    q++;
	    }
    }

    free(buffer);
    fclose(input_file); // Ensure the file is closed after its use
    printf("%d questions loaded successfully. Ready to play!\n", NUM_QUESTIONS);
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
	// print categories and dollar values for each unanswered question in questions array
	for (int i = 0; i < NUM_CATEGORIES; i++) {
		printf("%s\t", categories[i]);
	}
	printf("\n");
	for (int i = 0; i < questions_per_category; i++)
	{
		for (int j = 0; j < NUM_CATEGORIES; j++) {
			if(questions[j*4 + i].answered) // j*4 hardcode?
				printf("[ - ]\t\t");
			else
				printf("$%d\t\t", questions[j*4 + i].value);
		}
		printf("\n");
	}
}

// Displays the question for the category and dollar value
void display_question(char *category, int value)
{
	int i = get_question_index(category, value);
	if (i > -1) {
		system("clear");
		printf("----------------------------------------\n\n");
		printf("%s\n\n", questions[i].question);	
		printf("----------------------------------------\n\n");
	}
	else {
		printf("Error: Couldn't retrieve question (%s, %d)\n", category, value);
	}
}

/*
bool valid_answer(char *category, int value, char *actual_answer) {
    // Convert actual_answer to lowercase, trim whitespace, etc.
    // Assuming actual_answer now holds the entire answer phrase correctly processed
    toLower(actual_answer); // Assuming toLower modifies the string in place

    int i = get_question_index(category, value);
    if(i > -1) {
      toLower(questions[i].answer); // Ensure the stored answer is in lowercase for comparison
        // Assuming toLower modifies the string in place and you've handled multi-word answers correctly
        if (strcmp(questions[i].answer, actual_answer) == 0) {
            questions[i].answered = true;
            return true;
        }
    }
    return false;
}
*/
/*
bool valid_answer(char *category, int value, char *actual_answer) {
    int i = get_question_index(category, value);
    if(i > -1) {
        toLower(actual_answer); // Assuming toLower modifies the string in place
        //toLower(questions[i].answer); // Ensure the stored answer is in lowercase for comparison

printf("User's answer: '%s'\n", actual_answer);
printf("Expected answer: '%s'\n", questions[i].answer);
        // Since we're now working with one-word answers, directly compare
        if (strcmp(questions[i].answer, actual_answer) == 0) {
            questions[i].answered = true;
            return true;
        }
    }
    return false;
} */
bool valid_answer(char *category, int value, char *actual_answer) {
    toLower(actual_answer); // Convert user's answer to lowercase
    int i = get_question_index(category, value);
    if(i > -1) {
        char stored_answer[MAX_LEN];
        strcpy(stored_answer, questions[i].answer);
        toLower(stored_answer); // Convert stored answer to lowercase
 printf("User's answer: '%s'\n", actual_answer);
printf("Expected answer: '%s'\n", questions[i].answer);
printf("Expected answer: '%s'\n", stored_answer);
        if (strcmp(stored_answer, actual_answer) == 0) {
            questions[i].answered = true;
            return true;
        }
    }
    return false;
}

/*
// Correct the string comparison logic
bool valid_answer(char *category, int value, char *answer)
{
    int i = get_question_index(category, value);
    if(i > -1) {
        char temp_answer[MAX_LEN]; // Temporary buffer for comparison
        toLower(answer); // Ensure the provided answer is in lowercase

        // Formulate the correct answer in various formats and compare
        sprintf(temp_answer, "what is %s", questions[i].answer);
        if (strcmp(temp_answer, answer) == 0) {
            questions[i].answered = true;
            return true;
        }

        sprintf(temp_answer, "what is %s?", questions[i].answer);
        if (strcmp(temp_answer, answer) == 0) {
            questions[i].answered = true;
            return true;
        }

        sprintf(temp_answer, "who is %s", questions[i].answer);
        if (strcmp(temp_answer, answer) == 0) {
            questions[i].answered = true;
            return true;
        }

        sprintf(temp_answer, "who is %s?", questions[i].answer);
        if (strcmp(temp_answer, answer) == 0) {
            questions[i].answered = true;
            return true;
        }

        sprintf(temp_answer, "what are %s", questions[i].answer);
        if (strcmp(temp_answer, answer) == 0) {
            questions[i].answered = true;
            return true;
        }

        sprintf(temp_answer, "what are %s?", questions[i].answer);
        if (strcmp(temp_answer, answer) == 0) {
            questions[i].answered = true;
            return true;
        }

        // If none of the formats match, the answer is considered incorrect
        return false;
    }
    printf("Error: Couldn't retrieve question (%s, %d)\n", category, value);
    return false;
}
*/
/*
// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
	int i = get_question_index(category, value);
	if(i > -1) {
		toLower(answer);
		if ( strcmp("what is " + questions[i].answer, answer)) {
			strcpy(answer, questions[i].answer);
			questions[i].answered = true;
			return true;
		}
		else if ( strcmp("what is " + questions[i].answer + "?", answer)) {
			strcpy(answer, questions[i].answer);
			questions[i].answered = true;
			return true;
		}
		else if ( strcmp("who is " + questions[i].answer, answer)) {
			strcpy(answer, questions[i].answer);
			questions[i].answered = true;
			return true;
		}
		else if ( strcmp("who is " + questions[i].answer + "?", answer)) {
			strcpy(answer, questions[i].answer);
			questions[i].answered = true;
			return true;
		}
		else if ( strcmp("what are " + questions[i].answer, answer)) {
			strcpy(answer, questions[i].answer);
			questions[i].answered = true;
			return true;
		}
		else if ( strcmp("what are " + questions[i].answer + "?", answer)) {
			strcpy(answer, questions[i].answer);
			questions[i].answered = true;
			return true;
		}
		else {
			strcpy(answer, questions[i].answer);
			questions[i].answered = true;
			return false;
		}
	}
	printf("Error: Couldn't retrieve question (%s, %d)\n", category, value);
	return false;
}
*/

// Returns true if the question has already been answered
bool already_answered(char *category, int value)
{
	// lookup the question and see if it's already been marked as answered
	int i = get_question_index(category, value);
 	if (i > -1) {
		return questions[i].answered;
	}
	return false;
}

// Converts char array to char array with all lowercase characters
void toLower(char *string)
{
	for (int i = 0; i < MAX_LEN; i++) {
		if (string[i] != '\0')
			string[i] = tolower(string[i]);
		else
			return;
	}
}

// Returns index of first question from given category with given value based on location in questions array
// Returns -1 on failed attempt
int get_question_index(char *category, int value)
{
	for (int c = 0; c < NUM_CATEGORIES; c++) {
		if (strcmp(category, categories[c]) == 0) {
			for (int q = 0; q < questions_per_category; q++) {
				if (questions[c*4 + q].value == value) {
					return c*4 + q;
				}
			}
		}
	}
	return -1;
}

