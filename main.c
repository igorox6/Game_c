#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include "probabilities.h"

struct timeval t0, t1, startTime;

int day = 1;
int steps_in_row = -1;
int v_corridor = 0;
int is_flash = 0;
int entered = 0;
int stepped = 0;
int num_rem_flash = 3;

static float timedifference_msec(struct timeval t0, struct timeval t1){
    return (t1.tv_sec - t0.tv_sec) * 1000.0f + (t1.tv_usec - t0.tv_usec) / 1000.0f;
}
static void flash(){
    if (num_rem_flash != 0){
        // отображение картинки со светом
        num_rem_flash --;
        if (steps_in_row >= -1 ){
            // отображение картинки со съёбом
            steps_in_row = -1;
            entered = 0;
            stepped = 0;
            v_corridor = 0;
            printf("returnblch\n");
        }

    }
}

int main(void){
    gettimeofday(&startTime, 0);
    gettimeofday(&t0, 0);
    probs_seed((unsigned)time(NULL));
    while (1){
        gettimeofday(&t1, 0);
        float diff = timedifference_msec(t0, t1);
        if (diff >= 500.0f){
            gettimeofday(&t0, 0);
            float elapsed_sec = timedifference_msec(startTime, t1) / 500.0f;
            //printf("[t=%.1fs]\n", elapsed_sec/2);

            if (!v_corridor){ entered = decide_corridor_entry(day, elapsed_sec) ? 1 : 0; } // расчёт прошёл ли

            if (entered){
                if (!v_corridor){
                    printf("[t=%.1fs] entry=1\n", elapsed_sec);
                    v_corridor = 1;
                    steps_in_row = 0; // Первый шаг в коридоре
                }

            }
            if (v_corridor){
                stepped = decide_corridor_step(day, elapsed_sec);
                if (stepped){
                    steps_in_row += 1; // Второй шаг в коридоре
                    flash();

                    printf("[t=%.1fs] step=1 (row=%d)\n", elapsed_sec, steps_in_row);
                    if (steps_in_row >= 2){
                        printf("*** SCREAMER ***\n");
                        v_corridor = 0;
                        steps_in_row = -1;
                    }
                }
            } else {
                steps_in_row = -1;
            }
        }
    }
    return 0;
}
