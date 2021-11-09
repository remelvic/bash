#include <stdio.h>
#include <stdlib.h>
#include <string.h>


 //sdsd
/* You can use these functions and data structures to transform strings to
 * numbers and use them in arrays
 */
enum place {
    NUZKY, VRTACKA, OHYBACKA, SVARECKA, LAKOVNA, SROUBOVAK, FREZA,
    _PLACE_COUNT
};

const char *place_str[_PLACE_COUNT] = {
    [NUZKY] = "nuzky",
    [VRTACKA] = "vrtacka",
    [OHYBACKA] = "ohybacka",
    [SVARECKA] = "svarecka",
    [LAKOVNA] = "lakovna",
    [SROUBOVAK] = "sroubovak",
    [FREZA] = "freza",
};

enum product {
    A, B, C,
    _PRODUCT_COUNT
};

const char *product_str[_PRODUCT_COUNT] = {
    [A] = "A",
    [B] = "B",
    [C] = "C",
};

int find_string_in_array(const char **array, int length, char *what)
{
    for (int i = 0; i < length; i++)
        if (strcmp(array[i], what) == 0)
            return i;
    return -1;
}

/* It is not necessary to represent each working place with a dynamically
 * allocated object.  You can store only number of ready places
 *
 * int ready_places[_PLACE_COUNT];
 */

/* It is not necessary to represent each part as a dynamically allocated
 * object.  you can have only number of parts for each working phase
 *
 * #define _PHASE_COUNT 6
 * int parts[_PRODUCT_COUNT][_PHASE_COUNT]
 */

int main(int argc, char **argv)
{
    /* Initialize your internal structures, mutexes and conddition variables.
     */
    while (1) {
        char *line, *cmd, *arg1, *arg2, *arg3, *saveptr;
        int s = scanf(" %m[^\n]", &line);
        if (s == EOF)
            break;
        if (s == 0)
            continue;

        cmd  = strtok_r(line, " ", &saveptr);
        arg1 = strtok_r(NULL, " ", &saveptr);
        arg2 = strtok_r(NULL, " ", &saveptr);
        arg3 = strtok_r(NULL, " ", &saveptr);

        if (strcmp(cmd, "start") == 0 && arg1 && arg2 && !arg3) {
            /* - start new thread for new worker
             * - copy (e.g. strdup()) worker name from arg1, the
             *   arg1 will be removed at the end of scanf cycle
             * - workers should have dynamic objects, you don't know
             *   total number of workers
             */
        } else if (strcmp(cmd, "make") == 0 && arg1 && !arg2) {
            /* int product = find_string_in_array(
             *     product_str,
             *     _PRODUCT_COUNT,
             *     arg1
             * );
             *
             * if (product >= 0) {.....
             *     add the part to factory cycle
             *     you need to wakeup worker to start working if possible
             *     ...
             *     }
             */
        } else if (strcmp(cmd, "end") == 0 && arg1 && !arg2) {
            /* tell the worker to finish
             * the worker has to finish their work first
             * you should not wait here for the worker to finish
             *
             * if the worker is waiting for work
             * you need to wakeup the worker
             */
        } else if (strcmp(cmd, "add") == 0 && arg1 && !arg2) {
            /* add new place
             *
             * if worker and part is ready, start working - wakeup worker
             */
        } else if (strcmp(cmd, "remove") == 0 && arg1 && !arg2) {
            /* if you cannot remove empty place you cannot wait for finish
             * work
             */
        } else {
            fprintf(stderr, "Invalid command: %s\n", line);
        }
        free(line);
    }

    /* Wait for every worker to finish their work. Nobody should be able to
     * continue.
     */
}
