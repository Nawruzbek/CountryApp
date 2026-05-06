#include <stdio.h>
#include "utils.h"

void clear_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
