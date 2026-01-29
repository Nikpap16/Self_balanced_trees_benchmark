#ifndef CITIZEN_H
#define CITIZEN_H

#define MAX_NAME_LEN 100
#define MAX_STATE_LEN 50

typedef struct {
    char full_name[MAX_NAME_LEN];
    int age;
    char state[MAX_STATE_LEN];
    int income; 
} Citizen;

#endif // CITIZEN_H
