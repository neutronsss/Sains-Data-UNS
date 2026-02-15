#include <stdio.h>
#include <string.h>
#include "kasir.h"
#include "barang.h"

#define MAX_ITEMS 100

int main() {
    Item items[MAX_ITEMS];
    int item_count = 0;
    int choice;

    while (1) {
        printf("\n==== Menu Kasir ====\n");
        printf("1. Tambah Barang\n");
        printf("2. Update Barang\n");
        printf("3. Transaksi Kasir\n");
        printf("4. Keluar\n");
        printf("Pilih menu (1-4): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_item(items, &item_count);  // Menambah barang baru
                break;
            case 2:
                update_item(items, item_count);  // Mengubah barang
                break;
            case 3: {
                float total = 0;
                char input_code[20];
                int quantity;

                while (1) {
                    printf("Masukkan kode barang (atau 'exit' untuk keluar): ");
                    scanf("%s", input_code);

                    if (strcmp(input_code, "exit") == 0) {
                        break;
                    }

                    Item* item = find_item(items, item_count, input_code);
                    if (item == NULL) {
                        printf("Barang tidak ditemukan.\n");
                        continue;
                    }

                    printf("Nama Barang: %s\n", item->name);
                    printf("Harga: %.2f\n", item->price);
                    printf("Stok: %d\n", item->stock);

                    printf("Masukkan jumlah: ");
                    scanf("%d", &quantity);

                    if (quantity <= 0 || quantity > item->stock) {
                        printf("Stok tidak mencukupi atau jumlah tidak valid.\n");
                        continue;
                    }

                    item->stock -= quantity;  // Mengurangi stok
                    total += item->price * quantity;
                    printf("Item telah ditambahkan ke keranjang.\n");
                }

                // Input jumlah uang yang dibayar
                float paid_amount;
                printf("Masukkan uang yang dibayar: ");
                scanf("%f", &paid_amount);

                calculate_total_and_change(total, paid_amount);  // Menghitung total dan kembalian
                print_receipt(items, item_count, total, paid_amount);  // Mencetak nota
                break;
            }
            case 4:
                printf("Keluar dari program.\n");
                return 0;
            default:
                printf("Pilihan tidak valid.\n");
                break;
        }
    }

    return 0;
}
