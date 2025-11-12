//
// Created by MSI on 11.11.2025.
//

#ifndef GAME_1_PROBABILITIES_H
#define GAME_1_PROBABILITIES_H
#include <stdbool.h>
void probs_seed(unsigned int seed);
bool decide_corridor_entry(int day, float elapsed_sec);
int decide_corridor_step(int day, float elapsed_sec);

#endif //GAME_1_PROBABILITIES_H
