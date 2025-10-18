#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define BUFSIZE 1024

void roll_dice(int num_dice, int die_sides) {
    int total = 0;
    int *results = malloc(num_dice * sizeof(int));
    
    if (results == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    
    // Roll each die
    for (int i = 0; i < num_dice; i++) {
        results[i] = (rand() % die_sides) + 1;
        total += results[i];
    }
    
    // Display results
    printf("You rolled: ");
    for (int i = 0; i < num_dice; i++) {
        printf("%d", results[i]);
        if (i < num_dice - 1) {
            printf(", ");
        }
    }
    printf(" totalling %d\n", total);
    
    free(results);
}

int parse_input(const char *input, int *num_dice, int *die_sides) {
    char *token;
    char *input_copy = malloc(strlen(input) + 1);
    
    if (input_copy == NULL) {
        return 0;
    }
    
    strcpy(input_copy, input);
    
    // Check if input starts with 'd' (e.g., "d6" means 1d6)
    if (input[0] == 'd') {
        *num_dice = 1;
        *die_sides = atoi(input_copy + 1);
    } else {
        // Parse format "NdX"
        token = strtok(input_copy, "d");
        if (token == NULL) {
            free(input_copy);
            return 0;
        }
        *num_dice = atoi(token);
        
        token = strtok(NULL, "d");
        if (token == NULL) {
            free(input_copy);
            return 0;
        }
        *die_sides = atoi(token);
    }
    
    free(input_copy);
    
    // Validate input
    if (*num_dice <= 0 || *die_sides <= 0) {
        return 0;
    }
    
    return 1;
}

int main() {
    srand(time(NULL));
    
    char buffer[BUFSIZE];
    int num_dice, die_sides;
    
    printf("Press ENTER to roll. Input Q to quit.\n");
    
    while (1) {
        printf("> ");
        if (fgets(buffer, BUFSIZE, stdin) == NULL) {
            break;
        }
        
        // Remove newline character
        buffer[strcspn(buffer, "\n")] = 0;
        
        // Check for quit command
        if (strcmp(buffer, "Q") == 0 || strcmp(buffer, "q") == 0) {
            break;
        }
        
        // Parse and validate input
        if (parse_input(buffer, &num_dice, &die_sides)) {
            roll_dice(num_dice, die_sides);
        } else {
            printf("Invalid input format. Use NdX (e.g., 2d6) or dX (e.g., d20)\n");
        }
    }
    
    printf("Good bye! Nice to know you.\n");
    
    return 0;
}
