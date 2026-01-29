#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NAME_LEN 100 // όριο χαρακτήρων για τα ονόματα των πολιτών 
#define MAX_STATE_LEN 50 // όριο χαρακτήρων για τις πολιτείες 
#define NUM_CITIZENS 1000  // αριθμός πολιτών που θα δημιουργηθούν

int main() {
    FILE *namesFile = fopen("names.txt", "r");
    FILE *statesFile = fopen("states.txt", "r");
    FILE *outFile = fopen("citizens.txt", "w");

    if (!namesFile || !statesFile || !outFile) {
        printf("Error opening files.\n");
        return 1;
    }

    // φόρτωση πολιτειών σε πίνακα
    char states[50][MAX_STATE_LEN];
    int numStates = 0;
    while (fgets(states[numStates], MAX_STATE_LEN, statesFile)) {
        
        states[numStates][strcspn(states[numStates], "\r\n")] = 0;
        numStates++;
    }

    srand(time(NULL));

    char name[MAX_NAME_LEN];
    for (int i = 0; i < NUM_CITIZENS && fgets(name, MAX_NAME_LEN, namesFile); i++) {
        name[strcspn(name, "\r\n")] = 0; // αδφαίρεση newline
        int age = rand() % 80 + 21; // ηλικία 21-100
        int income = rand() % 1000001;    // εισόδημα 0-1Μ
        char *state = states[rand() % numStates];

        fprintf(outFile, "%s,%d,%s,%d\n", name, age, state, income);
    }

    fclose(namesFile);
    fclose(statesFile);
    fclose(outFile);
    printf("Citizens file created succesfully");
    getchar();

    return 0;
}
