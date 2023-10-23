#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Buku
{
    char kode[100];
    char nama[100];
    char jenis[100];
    float harga;
};

struct Pembelian
{
    char nama[100];
    int jumlah;
};

int menu()
{
    int choice;
    int valid_input = 0;

    do
    {
        printf("\nAPLIKASI MONITORING BUKU\n");
        printf("------------------------\n\n");
        printf("MENU\n");
        printf("1. Input Data Buku\n");
        printf("2. View History\n");
        printf("3. View Buku\n");
        printf("4. Pembelian\n");
        printf("5. Delete History\n");
        printf("6. Delete Buku\n");
        printf("7. Exit\n");
        printf("\n");
        printf("Masukkan nomor menu untuk memilih menu di atas: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("\nInput tidak valid. Silakan coba lagi.\n");
            fflush(stdin);
        }
        else
        {
            valid_input = 1;
        }
    } while (!valid_input);

    printf("\n");

    return choice;
}

void show_file(FILE *data, char *fname)
{
    data = fopen(fname, "r");

    if (data == NULL)
    {
        perror("Gagal membuka file.");
        exit(1);
    }

    int display;

    do
    {
        display = fgetc(data);

        if (feof(data))
            break;

        printf("%c", display);
    } while (true);

    printf("\n");
    fclose(data);
}

void delete_book(int indeks)
{
    FILE *file = fopen("databuku.txt", "r");
    if (file == NULL)
    {
        printf("File databuku.txt tidak ditemukan atau tidak dapat dibaca.\n");
        return;
    }

    char tempFileName[] = "temp_databuku.txt";
    FILE *tempFile = fopen(tempFileName, "w");

    char line[1000];
    int currentIndeks = 0;

    while (fgets(line, sizeof(line), file))
    {
        if (line[0] == '\n')
        {
            currentIndeks++;
        }

        if (currentIndeks != indeks)
        {
            fprintf(tempFile, "%s", line);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("databuku.txt");
    rename(tempFileName, "databuku.txt");
}

void delete_history(int indeks)
{
    FILE *file = fopen("pembelian.txt", "r");
    if (file == NULL)
    {
        printf("File databuku.txt tidak ditemukan atau tidak dapat dibaca.\n");
        return;
    }

    char tempFileName[] = "temp_pembelian.txt";
    FILE *tempFile = fopen(tempFileName, "w");

    char line[1000];
    int currentIndeks = 0;

    while (fgets(line, sizeof(line), file))
    {
        if (line[0] == '\n')
        {
            currentIndeks++;
        }

        if (currentIndeks != indeks)
        {
            fprintf(tempFile, "%s", line);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("pembelian.txt");
    rename(tempFileName, "pembelian.txt");
}

int main()
{

    FILE *databuku;
    FILE *pembelian;
    char fname_databuku[20] = "databuku.txt";
    char fname_pembelian[20] = "pembelian.txt";

    int pilih;
    int back;
    int indeks;

    struct Buku buku;

    do
    {
        pilih = menu();

        switch (pilih)
        {

        case 1:
            databuku = fopen(fname_databuku, "a");

            if (databuku == NULL)
            {
                printf("Gagal membuka file.\n");
                return 1;
            }

            printf("\n1. INPUT BUKU\n");
            printf("-------------\n\n");

            printf("Masukkan data buku:\n\n");
            printf("Kode Buku: ");
            scanf("%s", buku.kode);
            fprintf(databuku, "Kode Buku: %s\n", buku.kode);

            printf("Nama Buku: ");
            scanf(" %[^\n]", buku.nama);
            fprintf(databuku, "Nama Buku: %s\n", buku.nama);

            printf("Jenis Buku: ");
            scanf(" %[^\n]", buku.jenis);
            fprintf(databuku, "Jenis Buku: %s\n", buku.jenis);

            printf("Harga: ");
            scanf("%f", &buku.harga);
            fprintf(databuku, "Harga: %.2f\n\n", buku.harga);

            fclose(databuku);

            printf("\nData buku telah disimpan dalam databuku.txt.\n");

            break;

        case 2:
            printf("\n2. VIEW HISTORY\n");
            printf("---------------\n\n");
            show_file(pembelian, fname_pembelian);

            printf("Klik 0 untuk kembali: ");
            scanf("%d", &back);
            if (back == 0)
            {
                break;
            }
            else
            {
                return 1;
            }

        case 3:
            printf("\n2. VIEW BUKU\n");
            printf("------------\n\n");
            show_file(databuku, fname_databuku);

            printf("Klik 0 untuk kembali: ");
            scanf("%d", &back);
            if (back == 0)
            {
                break;
            }
            else
            {
                return 1;
            }

        case 4:
            show_file(databuku, fname_databuku);

            struct Pembelian pembelian_item;
            pembelian = fopen(fname_pembelian, "a");

            if (pembelian == NULL)
            {
                printf("Gagal membuka file pembelian.txt.\n");
                return 1;
            }

            printf("\n2. PEMBELIAN\n");
            printf("------------\n\n");

            printf("Masukkan Nama Buku yang akan dibeli: ");
            scanf(" %[^\n]", pembelian_item.nama);
            printf("Masukkan Jumlah yang akan dibeli: ");
            scanf("%d", &pembelian_item.jumlah);

            databuku = fopen(fname_databuku, "r");
            if (databuku == NULL)
            {
                printf("Gagal membuka file databuku.txt.\n");
                return 1;
            }
            char buku_info[200];
            while (fgets(buku_info, sizeof(buku_info), databuku))
            {
                if (strstr(buku_info, pembelian_item.nama) != NULL)
                {

                    printf("\nRincian Pembelian:\n");
                    printf("Nama Buku: %s\n", pembelian_item.nama);
                    printf("Jumlah: %d\n", pembelian_item.jumlah);

                    fprintf(pembelian, "Nama Buku: %s\n", pembelian_item.nama);
                    fprintf(pembelian, "Jumlah: %d\n\n", pembelian_item.jumlah);

                    break;
                }
            }
            fclose(databuku);
            fclose(pembelian);

            printf("\nData pembelian telah disimpan dalam pembelian.txt.\n");

            break;

        case 5:

            show_file(pembelian, fname_pembelian);

            printf("\n5. DELETE HISTORY\n");
            printf("----------------\n\n");
            printf("Indeks pembelian yang ingin dihapus: ");
            scanf("%d", &indeks);
            delete_history(indeks);
            printf("\nPembelian dengan indeks %d telah dihapus.\n", indeks);
            break;

        case 6:

            show_file(databuku, fname_databuku);

            printf("\n6. DELETE BUKU\n");
            printf("--------------\n\n");
            printf("Indeks buku yang ingin dihapus: ");
            scanf("%d", &indeks);
            delete_book(indeks);
            printf("\nBuku dengan indeks %d telah dihapus.\n", indeks);
            break;

        case 7:
            printf("\nKeluar dari program.\n\n");
            break;

        default:
            printf("\nPilihan tidak valid. Silakan coba lagi.\n");
            break;
        }

    } while (pilih != 7);
    return 0;
}
