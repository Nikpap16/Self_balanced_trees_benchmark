#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "bst.h"
#include "avl.h"
#include "rbt.h"
#include "citizen.h"

#define MAX_CITIZENS 1000
#define NUM_TESTS 100
#define NUM_RUNS 5
#define STRESS_VALUE 10000

 //αποσχολιάζω σε περίπτωση που θέλω να τρέξει το stress
 //#define RUN_STRESS_TEST

int load_citizens(Citizen* citizens, int max) {
    FILE* file = fopen("../database_generator/citizens.txt", "r");
    if (!file) {
        printf("Cannot open citizens.txt\n");
        return 0;
    }
    int count = 0;
    char line[256];
    while (fgets(line, sizeof(line), file) && count < max) {
        line[strcspn(line, "\r\n")] = 0;
        char* token = strtok(line, ",");
        if (!token) continue;
        strncpy(citizens[count].full_name, token, 100);
        token = strtok(NULL, ",");
        citizens[count].age = atoi(token);
        token = strtok(NULL, ",");
        strncpy(citizens[count].state, token, 50);
        token = strtok(NULL, ",");
        citizens[count].income = atoi(token);
        count++;
    }
    fclose(file);
    return count;
}

int main() {
    Citizen citizens[MAX_CITIZENS];
    int total = load_citizens(citizens, MAX_CITIZENS);
    if (total == 0) return 1;

    double bst_insert_avg = 0, avl_insert_avg = 0, rbt_insert_avg = 0;
    double bst_search_avg = 0, avl_search_avg = 0, rbt_search_avg = 0;
    double bst_delete_avg = 0, avl_delete_avg = 0, rbt_delete_avg = 0;

    for (int run = 0; run < NUM_RUNS; run++) {
        BSTNode* bst = NULL;
        AVLNode* avl = NULL;
        RBTNode* rbt = NULL;
        clock_t start, end;

        // ----- Insert -----
        start = clock();
        for (int i = 0; i < total; i++) bst = insert_bst(bst, citizens[i]);
        bst_insert_avg += (double)(clock() - start) / CLOCKS_PER_SEC;

        start = clock();
        for (int i = 0; i < total; i++) avl = insert_avl(avl, citizens[i]);
        avl_insert_avg += (double)(clock() - start) / CLOCKS_PER_SEC;

        start = clock();
        for (int i = 0; i < total; i++) rbt = insert_rbt(rbt, citizens[i]);
        rbt_insert_avg += (double)(clock() - start) / CLOCKS_PER_SEC;

        // ----- Search -----
        #ifdef RUN_STRESS_TEST
            int search_limit = STRESS_VALUE;
        #else
            int search_limit = NUM_TESTS;
        #endif

        start = clock();
        for (int i = 0; i < search_limit; i++) search_bst(bst, citizens[i % total].full_name);
        bst_search_avg += (double)(clock() - start) / CLOCKS_PER_SEC;

        start = clock();
        for (int i = 0; i < search_limit; i++) search_avl(avl, citizens[i % total].full_name);
        avl_search_avg += (double)(clock() - start) / CLOCKS_PER_SEC;

        start = clock();
        for (int i = 0; i < search_limit; i++) search_rbt(rbt, citizens[i % total].full_name);
        rbt_search_avg += (double)(clock() - start) / CLOCKS_PER_SEC;

        // ----- Delete -----
        start = clock();
        for (int i = 0; i < NUM_TESTS; i++) bst = delete_bst(bst, citizens[i].full_name);
        bst_delete_avg += (double)(clock() - start) / CLOCKS_PER_SEC;

        start = clock();
        for (int i = 0; i < NUM_TESTS; i++) avl = delete_avl(avl, citizens[i].full_name);
        avl_delete_avg += (double)(clock() - start) / CLOCKS_PER_SEC;

        start = clock();
        for (int i = 0; i < NUM_TESTS; i++) rbt = delete_rbt(rbt, citizens[i].full_name);
        rbt_delete_avg += (double)(clock() - start) / CLOCKS_PER_SEC;
    }

    // εγγραφή σε αρχείο και εκτύπωση
    FILE *f_res = fopen("results.txt", "w");
    if (!f_res) return 1;

    #ifdef RUN_STRESS_TEST
        int s_count = STRESS_VALUE;
        fprintf(f_res, "MODE: STRESS TEST (%d searches)\n", s_count);
        printf("MODE: STRESS TEST (%d searches)\n", s_count);
    #else
        int s_count = NUM_TESTS;
        fprintf(f_res, "MODE: NORMAL (%d searches)\n", s_count);
        printf("MODE: NORMAL (%d searches)\n", s_count);
    #endif

    fprintf(f_res, "----- AVERAGE TIMES AFTER %d RUNS -----\n", NUM_RUNS);
    fprintf(f_res, "BST insertion: %.6f sec\n", bst_insert_avg / NUM_RUNS);
    fprintf(f_res, "AVL insertion: %.6f sec\n", avl_insert_avg / NUM_RUNS);
    fprintf(f_res, "RBT insertion: %.6f sec\n", rbt_insert_avg / NUM_RUNS);
    fprintf(f_res, "BST search:    %.6f sec\n", bst_search_avg / NUM_RUNS);
    fprintf(f_res, "AVL search:    %.6f sec\n", avl_search_avg / NUM_RUNS);
    fprintf(f_res, "RBT search:    %.6f sec\n", rbt_search_avg / NUM_RUNS);
    fprintf(f_res, "BST deletion:  %.6f sec\n", bst_delete_avg / NUM_RUNS);
    fprintf(f_res, "AVL deletion:  %.6f sec\n", avl_delete_avg / NUM_RUNS);
    fprintf(f_res, "RBT deletion:  %.6f sec\n", rbt_delete_avg / NUM_RUNS);

   
  
    printf("Results saved to results.txt\n");

    fclose(f_res);
    getchar();
    return 0;
}