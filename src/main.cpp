#include <stdio.h>
#include "parsing.h"

int main(int argc, char **argv) {
    printf("[MAIN] Solutions for day ...\n");

    int val = Parse::tests();
    printf("[MAIN] Here's a value = %i\n", val);

    return 0;
}
