#ifndef KASIR_H
#define KASIR_H

#include <time.h>

typedef struct {
    char code[20];
    char name[50];
    float price;
    int stock;
} Item;

Item* find_item(Item items[], int size, const char* code);
void calculate_total_and_change(float total, float paid_amount);
void print_receipt(Item items[], int size, float total, float paid_amount);

#endif
