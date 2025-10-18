#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define BUFSIZE 1024

void roll_dice(int num_die, int die_size) {
    int sum = 0;
    int *results = malloc(num_die * sizeof(int));
    
    if (results == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    
    // Roll each die
    for (int i = 0; i < num_die; i++) {
        results[i] = rand() % die_size + 1;
        sum += results[i];
    }
    
    // Print individual results
    printf("You rolled: ");
    for (int i = 0; i < num_die; i++) {
        printf("%d", results[i]);
        if (i < num_die - 1) {
            printf(", ");
        }
    }
    printf(" totalling %d\n", sum);
    
    free(results);
}

int main() {
    srand(time(NULL));
    
    char buffer[BUFSIZE] = { 0 };
    int num_die = 0;
    int die_size = 0;
    
    printf("Press ENTER to roll. Input Q to quit.\n");
    
    while (fgets(buffer, BUFSIZE, stdin)) {
        buffer[strcspn(buffer, "\n")] = 0;
        
        if (buffer[0] == 'Q' || buffer[0] == 'q') {
            break;
        }
        
        // Parse input in NdX format
        char *d_pos = strchr(buffer, 'd');
        if (d_pos == NULL) {
            printf("Invalid format. Use NdX (e.g., 3d6)\n");
            continue;
        }
        
        // Extract number of dice
        if (d_pos == buffer) {
            // Handle case where no number before 'd' (e.g., "d6")
            num_die = 1;
        } else {
            num_die = atoi(buffer);
            if (num_die <= 0) {
                printf("Invalid number of dice. Must be positive.\n");
                continue;
            }
        }
        
        // Extract die size
        die_size = atoi(d_pos + 1);
        if (die_size <= 0) {
            printf("Invalid die size. Must be positive.\n");
            continue;
        }
        
        // Roll the dice
        roll_dice(num_die, die_size);
        printf("> ");
    }
    
    printf("Good bye! Nice to know you.\n");
    
    return 0;
}
