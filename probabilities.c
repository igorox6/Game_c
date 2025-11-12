#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include "probabilities.h"
static inline float clampf(float v, float lo, float hi){ return v<lo?lo:(v>hi?hi:v); }

static float rng01(void){ return (float)rand()/(float)RAND_MAX; }

void probs_seed(unsigned int seed){ srand(seed); }

static float transformator_break_rate_hz(int day, float t){
    if (day<1) day=1;
    float base = 0.1f + 0.5f * clampf(t/360.0f, 0.0f, 1.0f);
    float day_mul = 1.0f + 0.35f * clampf((float)(day-1), 0.0f, 10.0f);
    float surge = 1.0f + 0.5f * clampf((t-240.0f)/180.0f, 0.0f, 1.0f);
    return base * day_mul * surge;
}

static float entry_rate_hz(int day, float t){
    if (day<1) day=1;
    float base = 0.4f + 0.16f * clampf(t/360.0f, 0.0f, 1.0f);
    float day_mul = 1.0f + 0.35f * clampf((float)(day-1), 0.0f, 10.0f);
    float surge = 1.0f + 0.5f * clampf((t-240.0f)/180.0f, 0.0f, 1.0f);
    return base * day_mul * surge;
}
static float step_rate_hz(int day, float t){
    if (day<1) day=1;
    float base = 0.1f + 0.45f * clampf(t/360.0f, 0.0f, 1.0f);
    float day_mul = 1.0f + 0.30f * clampf((float)(day-1), 0.0f, 10.0f);
    float surge = 1.0f + 0.4f * clampf((t-180.0f)/240.0f, 0.0f, 1.0f);
    return base * day_mul * surge;
}
static inline int bernoulli_from_rate(float rate_hz, float dt){
    float p = 1.0f - expf(-rate_hz * dt);
    if (p<0.0f) p=0.0f; else if (p>0.98f) p=0.98f;
    return rng01() < p;
}
bool decide_corridor_entry(int day, float elapsed_sec){
    return bernoulli_from_rate(entry_rate_hz(day, elapsed_sec), 0.4f);
}
int decide_corridor_step(int day, float elapsed_sec){
    return bernoulli_from_rate(step_rate_hz(day, elapsed_sec), 0.3f) ? 1 : 0;
}
int decide_transformator_break(int day, float elapsed_sec){
    return bernoulli_from_rate(step_rate_hz(day, elapsed_sec), 0.2f) ? 1 : 0;
}
