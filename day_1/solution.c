#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {

    if(argc != 2) {
        fprintf(stderr, "Provide input file as second argument");
        return 0;
    }

    char* filepath = argv[1];
    FILE* file = fopen(filepath, "r");

    char direction;
    int rotation;
    
    int num_zeros = 0;
    int dial = 50;

    char* line = calloc(256, sizeof(char));
    size_t size;
    
  while(getline(&line, &size, file) > 0) {
        direction = line[0];
        rotation = atoi(line+1);
        int start_dial = dial;

        if(direction == 'L') {
            dial -= (rotation % 100);
            if(dial < 0)
                dial += 100;
        }
        if(direction == 'R') {
            dial = (dial + rotation) % 100;
        }

        num_zeros += rotation / 100;

        int rem = rotation % 100;
        if (rem > 0 && start_dial != 0) {
            if(direction == 'L' && start_dial < rem)
                    num_zeros++;
            if(direction == 'R' && start_dial + rem > 100)
                    num_zeros++;

        }

        if(dial == 0) num_zeros++;
    }

    printf("SOLUTION: %d\n", num_zeros);

    free(line);
    return 0;
}