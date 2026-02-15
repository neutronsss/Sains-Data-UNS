#include <stdio.h>
#include <string.h>
#include <time.h>
#include "kasir.h"

// Fungsi untuk mencari barang berdasarkan kode
Item* find_item(Item items[], int size, const char* code) {
    for (int i = 0; i < size; i++) {
        if (strcmp(items[i].code, code) == 0) {
            return &items[i];
        }
    }
    return NULL;  // Barang tidak ditemukan
}

// Fungsi untuk menghitung total belanja dan kembalian
void calculate_total_and_change(float total, float paid_amount) {
    while (paid_amount < total) {
        printf("Uang tidak cukup. Masukkan jumlah yang valid: ");
        scanf("%f", &paid_amount);
    }

    float change = paid_amount - total;
    printf("Total Belanja: %.2f\n", total);
    printf("Uang Dibayar: %.2f\n", paid_amount);
    printf("Uang Kembalian: %.2f\n", change);
}

// Fungsi untuk mencetak nota transaksi
void print_receipt(Item items[], int size, float total, float paid_amount) {
    FILE *file = fopen("nota.txt", "w");
    if (file == NULL) {
        perror("Gagal membuka file");
        return;
    }

    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);

    fprintf(file, "---NOTA BELANJA---\n");
    fprintf(file, "Tanggal: %s", asctime(tm_info));
    for (int i = 0; i < size; i++) {
        if (items[i].stock < 0) continue;
        fprintf(file, "Nama Barang: %s | Harga: %.2f | Stok Sisa: %d\n", items[i].name, items[i].price, items[i].stock);
    }
    fprintf(file, "Total Belanja: %.2f\n", total);
    fprintf(file, "Uang Dibayar: %.2f\n", paid_amount);
    fprintf(file, "Uang Kembalian: %.2f\n", paid_amount - total);
    fclose(file);

    printf("Nota telah disimpan dalam file 'nota.txt'.\n");
}
