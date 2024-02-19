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
#include "players.h"

// Returns true if the player name matches one of the existing players
bool player_exists(player *players, int num_players, char *name)
{
    for (int i = 0; i < num_players; i++) {
        if (strcmp(players[i].name, name) == 0) {
            return true;
        }
    }
    return false;
}

// Go through the list of players and update the score for the
// player given their name
void update_score(player *players, int num_players, char *name, int score)
{
    for (int i = 0; i < num_players; i++) {
        if (strcmp(players[i].name, name) == 0) {
            players[i].score += score;
            break;
        }
    }
}

// Displays the current score for each player
void show_scores(const player *players, int num_players) {
    printf("\nCurrent scores:\n");
    for (int i = 0; i < num_players; i++) {
        printf("Player %s: %d\n", players[i].name, players[i].score);
    }
    printf("\n"); // Add an extra newline for better readability
}

// Initialize each player in the array with name and initial score
void initialize_players(player *players, int num_players)
{
    for (int i = 0; i < num_players; i++) {
        printf("Enter the name of Player %d: ", i + 1);
        scanf("%s", players[i].name);
        players[i].score = 0;
    }
}

