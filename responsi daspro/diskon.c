#include <stdio.h>
#include <time.h>
#include <string.h>

#define MAX_BARANG 100
#define MAX_STRUK 1000

typedef struct {
    char nama[50];
    int harga;
} Barang;

typedef struct {
    char barang[MAX_BARANG][50];
    int harga[MAX_BARANG];
    int qty[MAX_BARANG];
    int jumlahBarang;
    double total;
    double pajak;
    double totalAkhir;
    double uang;
    double kembali;
    double diskon;
    char tanggal[80];
    char waktu[80];
} Struk;

Barang daftarBarang[MAX_BARANG] = {
    {"Bayam", 5000},
    {"Wortel", 3000},
    {"Kangkung", 4000},
    {"Sawi", 4500},
    {"Brokoli", 6000},
    {"Kol", 3500},
    {"Tauge", 2000},
    {"Seledri", 4000},
    {"Buncis", 18000},
    {"Selada", 8000},
    {"Kentang", 9000},
    {"Asparagus", 23000},
    {"Jamur Enoki", 32000},
    {"Kacang Polong", 28000},
    {"Jagung", 23000},
    {"Cabai Kecil", 14000},
    {"Cabai Besar", 17000},
    {"Jahe", 15000},
    {"Kunyit", 14000},
    {"Kencur", 13000},
    {"Tomat", 8500},
    {"Timun", 7500},
    {"Kacang Panjang", 6000},
    {"Bawang Merah", 12000},
    {"Bawang Putih", 10000}
};
int jumlahBarangToko = 25;

Struk riwayatStruk[MAX_STRUK];
int jumlahStruk = 0;

void tampilkanTanggalWaktu(char *bufferTanggal, char *bufferWaktu) {
    time_t waktuSekarang;
    struct tm *waktuInfo;

    time(&waktuSekarang);
    waktuInfo = localtime(&waktuSekarang);

    strftime(bufferTanggal, 80, "%d-%m-%Y", waktuInfo);
    strftime(bufferWaktu, 80, "%H:%M:%S", waktuInfo);
}

void cetakStruk(char (*barang)[50], int *harga, int *qty, int jumlahBarang, double total, double diskon, double pajak, double totalAkhir, double uang, double kembali) {
    if (jumlahStruk < MAX_STRUK) {
        for (int i = 0; i < jumlahBarang; i++) {
            strcpy(riwayatStruk[jumlahStruk].barang[i], barang[i]);  
            riwayatStruk[jumlahStruk].harga[i] = harga[i];
            riwayatStruk[jumlahStruk].qty[i] = qty[i];
        }
        riwayatStruk[jumlahStruk].jumlahBarang = jumlahBarang;
        riwayatStruk[jumlahStruk].total = total;
        riwayatStruk[jumlahStruk].diskon = diskon;
        riwayatStruk[jumlahStruk].pajak = pajak;
        riwayatStruk[jumlahStruk].totalAkhir = totalAkhir;
        riwayatStruk[jumlahStruk].uang = uang;
        riwayatStruk[jumlahStruk].kembali = kembali;
        tampilkanTanggalWaktu(riwayatStruk[jumlahStruk].tanggal, riwayatStruk[jumlahStruk].waktu);
        jumlahStruk++;
    }

    printf("\n========================================\n");
    printf("            Struk Belanja\n");
    printf("          TOKO SAYUR ELIAS\n");
    printf("========================================\n");
    char bufferTanggal[80], bufferWaktu[80];
    tampilkanTanggalWaktu(bufferTanggal, bufferWaktu);
    printf("Tanggal: %s | Waktu: %s\n", bufferTanggal, bufferWaktu);
    printf("----------------------------------------\n");
    printf("Pesanan        Qty       Harga\n");
    printf("----------------------------------------\n");

    for (int i = 0; i < jumlahBarang; i++) {
        if (*(qty + i) > 0) {
            printf("%-14s %3d     Rp %6d\n", barang[i], *(qty + i), *(harga + i));
        }
    }

    double diskonValue = total * (diskon / 100);
    printf("----------------------------------------\n");
    printf("Subtotal:                Rp %6.2f\n", total);

    if (diskon > 0) {
        printf("Diskon (%.0f%%):           -Rp %6.2f\n", diskon, diskonValue);
        printf("Subtotal Setelah Diskon: Rp %6.2f\n", total - diskonValue);
    }

    printf("Pajak (10%%):             Rp %6.2f\n", pajak);
    printf("----------------------------------------\n");
    printf("Total:                   Rp %6.2f\n", totalAkhir);
    printf("Uang pembayaran:         Rp %6.2f\n", uang);
    printf("Kembalian:               Rp %6.2f\n", kembali);
    printf("========================================\n");
    printf("  Terima Kasih Sudah Berbelanja!\n");
    printf("========================================\n");
}

void lihatRiwayatStruk() {
    if (jumlahStruk == 0) {
        printf("Tidak ada riwayat struk yang tersimpan.\n");
        return;
    }

    int pilihan;
    do {
        printf("Daftar riwayat struk:\n");
        for (int i = 0; i < jumlahStruk; i++) {
            printf("%d. Tanggal: %s | Waktu: %s\n", i + 1, riwayatStruk[i].tanggal, riwayatStruk[i].waktu);
        }

        printf("Pilih nomor struk yang ingin dilihat (1 - %d, 0 untuk kembali): ", jumlahStruk);
        scanf("%d", &pilihan);

        if (pilihan == 0) {
            return; 
        }

        if (pilihan < 1 || pilihan > jumlahStruk) {
            printf("Nomor struk tidak valid. Silakan coba lagi.\n");
            continue; 
        }

        printf("\n========================================\n");
        printf("Struk ke-%d\n", pilihan);
        printf("Tanggal: %s | Waktu: %s\n", riwayatStruk[pilihan - 1].tanggal, riwayatStruk[pilihan - 1].waktu);
        printf("----------------------------------------\n");
        printf("Pesanan        Qty       Harga\n");
        printf("----------------------------------------\n");

        for (int j = 0; j < riwayatStruk[pilihan - 1].jumlahBarang; j++) {
            printf("%-14s %3d     Rp %6d\n", riwayatStruk[pilihan - 1].barang[j], riwayatStruk[pilihan - 1].qty[j], riwayatStruk[pilihan - 1].harga[j]);
        }

        double diskonValue = riwayatStruk[pilihan - 1].total * (riwayatStruk[pilihan - 1].diskon / 100);
        printf("----------------------------------------\n");
        printf("Subtotal:                Rp %6.2f\n", riwayatStruk[pilihan - 1].total);

        if (riwayatStruk[pilihan - 1].diskon > 0) {
            printf("Diskon (%.0f%%):           -Rp %6.2f\n", riwayatStruk[pilihan - 1].diskon, diskonValue);
            printf("Subtotal Setelah Diskon: Rp %6.2f\n", riwayatStruk[pilihan - 1].total - diskonValue);
        }

        printf("Pajak (10%%):             Rp %6.2f\n", riwayatStruk[pilihan - 1].pajak);
        printf("Total:                   Rp %6.2f\n", riwayatStruk[pilihan - 1].totalAkhir);
        printf("Uang pembayaran:         Rp %6.2f\n", riwayatStruk[pilihan - 1].uang);
        printf("Kembalian:               Rp %6.2f\n", riwayatStruk[pilihan - 1].kembali);
        printf("========================================\n");

    } while (pilihan != 0); 
}

void tambahBarang() {
    if (jumlahBarangToko >= MAX_BARANG) {
        printf("Daftar barang penuh, tidak dapat menambah barang baru.\n");
        return;
    }
    
    printf("Masukkan nama barang: ");
    scanf(" %[^\n]", daftarBarang[jumlahBarangToko].nama);
    printf("Masukkan harga barang: ");
    scanf("%d", &daftarBarang[jumlahBarangToko].harga);
    jumlahBarangToko++;
    printf("Barang berhasil ditambahkan.\n");
}

void hapusBarang() {
    printf("Daftar barang:\n");
    for (int i = 0; i < jumlahBarangToko; i++) {
        printf("%d. %s - Rp %d\n", i + 1, daftarBarang[i].nama, daftarBarang[i].harga);
    }
    
    int index;
    printf("Pilih nomor barang yang ingin dihapus: ");
    scanf("%d", &index);
    
    if (index < 1 || index > jumlahBarangToko) {
        printf("Nomor barang tidak valid.\n");
        return;
    }
    
    for (int i = index - 1; i < jumlahBarangToko - 1; i++) {
        daftarBarang[i] = daftarBarang[i + 1];
    }
    jumlahBarangToko--;
    printf("Barang berhasil dihapus.\n");
}

void lihatBarang() {
    printf("Daftar Barang:\n");
    printf("=============================\n");
    printf("No   Nama Barang     Harga\n");
    printf("=============================\n");
    for (int i = 0; i < jumlahBarangToko; i++) {
        printf("%-4d %-14s Rp %d\n", i + 1, daftarBarang[i].nama, daftarBarang[i].harga);
    }
}  

void kasir() {
    int ulangiTransaksi = 1;

    while (ulangiTransaksi) {
        int qty[MAX_BARANG] = {0};
        int pilihan;
        double total = 0.0;
        double diskon, pajak, totalAkhir, uang, kembali;

        lihatBarang();
        printf("Masukkan barang yang ingin dibeli (0 untuk selesai, -1 untuk menghapus barang dari keranjang):\n");
        while (1) {
            printf("Pilih nomor barang: ");
            scanf("%d", &pilihan);

            if (pilihan == 0) break; 
            if (pilihan == -1) { 
                printf("Barang yang ada di keranjang:\n");
                for (int i = 0; i < jumlahBarangToko; i++) {
                    if (qty[i] > 0) {
                        printf("%d. %s - Qty: %d - Harga: Rp %d\n", i + 1, daftarBarang[i].nama, qty[i], daftarBarang[i].harga);
                    }
                }

                int nomorHapus;
                printf("Masukkan nomor barang yang ingin dihapus dari keranjang: ");
                scanf("%d", &nomorHapus);

                if (nomorHapus < 1 || nomorHapus > jumlahBarangToko || qty[nomorHapus - 1] == 0) {
                    printf("Nomor barang tidak valid atau belum ada di keranjang.\n");
                    continue;
                }

                printf("Masukkan jumlah yang ingin dikurangi dari %s (saat ini: %d): ", daftarBarang[nomorHapus - 1].nama, qty[nomorHapus - 1]);
                int jumlahHapus;
                scanf("%d", &jumlahHapus);

                if (jumlahHapus >= qty[nomorHapus - 1]) {
                    total -= daftarBarang[nomorHapus - 1].harga * qty[nomorHapus - 1];
                    qty[nomorHapus - 1] = 0;
                } else {
                    qty[nomorHapus - 1] -= jumlahHapus;
                    total -= daftarBarang[nomorHapus - 1].harga * jumlahHapus;
                }
                printf("Barang berhasil dikurangi dari keranjang.\n");
                continue;
            }

            if (pilihan < 1 || pilihan > jumlahBarangToko) {
                printf("Nomor barang tidak valid.\n");
                continue;
            }

            printf("Masukkan jumlah: ");
            int jumlah;
            scanf("%d", &jumlah);
            qty[pilihan - 1] += jumlah;
            total += daftarBarang[pilihan - 1].harga * jumlah;
        }

        char pilihanDiskon;
        printf("Apakah Ada diskon? (y/n): ");
        scanf(" %c", &pilihanDiskon);

        if (pilihanDiskon == 'y' || pilihanDiskon == 'Y') {
            do {
                printf("Masukkan diskon (dalam %%): ");
                scanf("%lf", &diskon);
                if (diskon < 0 || diskon > 100) {
                    printf("Diskon harus antara 0 dan 100.\n");
                }
            } while (diskon < 0 || diskon > 100);
        } else {
            diskon = 0;
        }

        double diskonValue = total * (diskon / 100);
        pajak = (total - diskonValue) * 0.10;
        totalAkhir = (total - diskonValue) + pajak;

        printf("Total pembayaran: Rp %.2f\n", totalAkhir);
        printf("Masukkan uang pembayaran: ");
        scanf("%lf", &uang);
        kembali = uang - totalAkhir;

        char barangDibeli[MAX_BARANG][50];
        int hargaDibeli[MAX_BARANG];
        int qtyDibeli[MAX_BARANG];
        int indexBarangDibeli = 0;

        for (int i = 0; i < jumlahBarangToko; i++) {
            if (qty[i] > 0) {
                strcpy(barangDibeli[indexBarangDibeli], daftarBarang[i].nama);
                hargaDibeli[indexBarangDibeli] = daftarBarang[i].harga;
                qtyDibeli[indexBarangDibeli] = qty[i];
                indexBarangDibeli++;
            }
        }

        cetakStruk(barangDibeli, hargaDibeli, qtyDibeli, indexBarangDibeli, total, diskon, pajak, totalAkhir, uang, kembali);

        printf("\nApakah Anda ingin melakukan transaksi lain? (1 untuk Ya, 0 untuk Kembali ke Menu Utama): ");
        scanf("%d", &ulangiTransaksi);
    }
}

int main() {
    int keluar = 0;

    while (!keluar) {
        printf("\nMenu Utama:\n");
        printf("1. Tambah Barang\n");
        printf("2. Hapus Barang\n");
        printf("3. Lihat Barang\n");
        printf("4. Lihat Riwayat Struk\n"); 
        printf("5. Kasir\n");
        printf("6. Keluar\n");
        printf("Pilih opsi: ");
        int opsi;
        scanf("%d", &opsi);

        switch (opsi) {
            case 1:
                tambahBarang();
                break;
            case 2:
                hapusBarang();
                break;
            case 3:
                lihatBarang();
                break;
            case 4:
                lihatRiwayatStruk();
                break;
            case 5:
                kasir();
                break;
            case 6:
                keluar = 1;
                break;
            default:
                printf("Opsi tidak valid.\n");
                break;
        }
    }

    return 0;
}