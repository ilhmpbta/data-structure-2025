#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <termios.h>
#include "./include/avl_lib.h"

#define filepath "./src/data.bin"
#define backup "./src/data_backup.bin"
#define MENU_LEN 6

AVL record;
char newline_cleaner;

const char* menu_items[MENU_LEN] = {
    "\033[4mA\033[24mdd data                             ",
    "\033[4mU\033[24mpdate data                          ",
    "Show inde\033[4mx\033[24med data                    ",
    "Show U\033[4mn\033[24mindexed Data                  ",
    "\033[4mD\033[24melete data                          ",
    "\033[4mE\033[24mxit                                 "
};

void display_paginated(AVL *record, int choice);
int menu(int pos);

int main(){
    avl_init_from_file(&record);
    
    while (1) {
        int choice = menu(1);
        printf("\033[2J\033[H");
        switch (choice) {
            case 1: {
                char no_komponen_temp[7], nama_temp[26];
                int stok_temp;
                long double harga_temp;
                printf("%-14s: ", "Component ID"); scanf(" %[^\n]s", no_komponen_temp);
                printf("%-14s: ", "Item"); scanf(" %[^\n]s", nama_temp);
                printf("%-14s: ", "Stock"); scanf("%d", &stok_temp);
                printf("%-14s: ", "Price"); scanf("%Lf", &harga_temp);

                printf("\nThe data you have given:\n");
                printf("%-14s: %s\n", "Component ID", no_komponen_temp);
                printf("%-14s: %s\n", "Item", nama_temp);
                printf("%-14s: %d\n", "Stock", stok_temp);
                printf("%-14s: %.2Lf\n", "Price", harga_temp);

                printf("\nWould you like to write the data? (Y/N)\n");
                char yesno; scanf(" %c", &yesno);

                while ((newline_cleaner = getchar()) != '\n' && newline_cleaner != EOF);
                if (yesno == 'Y') avl_insert(&record, createKomponen(no_komponen_temp, nama_temp, stok_temp, harga_temp),1);
            } break;

            case 2: {
                int id;
                char no_komponen_temp[7];
                printf("Input Component ID: "); scanf(" %s", no_komponen_temp);
                id = generateKomponenID(no_komponen_temp);
                Komponen* found = avl_get(&record, id);

                if (found) {
                    Komponen updated = *found;
                    printf("Data found. Input the new data.\n");

                    printf("Updated name   : "); scanf(" %[^\n]s", updated.nama);
                    printf("Updated stock  : "); scanf("%d", &updated.stok);
                    printf("Updated price  : "); scanf("%Lf", &updated.harga);

                    avl_remove(&record, id);
                    avl_insert(&record, updated, 1);
                    
                    printf("\nData [%s] has been updated", updated.no_komponen);
                } else printf("Data not found.\n");

                while ((newline_cleaner = getchar()) != '\n' && newline_cleaner != EOF);
                printf("\nPress Enter to show menu again..."); getchar();
            } break;
            
            case 3: display_paginated(&record, choice); break;
            case 4: display_paginated(&record, choice); break;

            case 5: {
                char no_komponen_temp[7];
                printf("Input component ID: "); scanf(" %s", no_komponen_temp);
                int id = generateKomponenID(no_komponen_temp);
                if (avl_find(&record, id)) {
                    avl_remove(&record, id);
                    printf("Data %s has beem removed successfully.\n", no_komponen_temp);
                } else printf("Data not found.\n");
                
                while ((newline_cleaner = getchar()) != '\n' && newline_cleaner != EOF);
                printf("\nPress Enter to show menu again..."); getchar();
            } break;

            case 6: {
                printf("Saving data backup to data_backup.bin\n");
                FILE *src = fopen(filepath, "rb");
                FILE *dest = fopen(backup, "wb");
                if (src && dest) {
                    char buffer[1024];
                    size_t n;
                    while ((n = fread(buffer, 1, sizeof(buffer), src)))
                        fwrite(buffer, 1, n, dest);
                    fclose(src);
                    fclose(dest);
                } printf("Backup successful!\nExitting.\n");
                return 0;
            } break;
            default: {
                printf("Invalid input"); 
                printf("\nPress Enter to show menu again..."); getchar();
            } break;
        }
    }

    return 0;
}

int menu(int pos) {
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    const char hotkeys[MENU_LEN] = {'a','u','x','n','d','e'};
    
    char c, ansi_end[8];
    printf("\033[2J\033[H");
    printf("      Component database by ilhmpbta      \n==========================================\n");
    for (int i = 0; i < MENU_LEN; ++i) {
        if (i == pos - 1) {
            printf("\033[7m-> ");
            strcpy(ansi_end, "\033[27m");
        } else {
            printf("   ");
            strcpy(ansi_end, " ");
        } printf("%d. %s%s\n", i + 1, menu_items[i], ansi_end);
    } printf("\nUse arrow keys, 1-6, or underlined keywords\nPress Enter to select\n");

    while (1) {
        read(STDIN_FILENO, &c, 1);
        for (int i = 0; i < MENU_LEN; ++i)
        if (c == hotkeys[i] || c == hotkeys[i] - 32) pos = i + 1;
        if (c == '\033') {
            char seq[2];
            if (read(STDIN_FILENO, &seq[0], 1) == 0) continue;
            if (read(STDIN_FILENO, &seq[1], 1) == 0) continue;

            if (seq[0] == '[') {
                if (seq[1] == 'A' && pos > 1) pos--;
                else if (seq[1] == 'B' && pos < MENU_LEN) pos++;
            }
        } else if (c >= '1' && c <= '6') pos = c - '0';
        else if (c == '\n') {
            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
            return pos;
        }

        printf("\033[2J\033[H");
        printf("      Component database by ilhmpbta      \n==========================================\n");
        for (int i = 0; i < MENU_LEN; ++i) {
            if (i == pos - 1) {
                printf("\033[7m-> ");
                strcpy(ansi_end, "\033[27m");
            } else {
                printf("   ");
                strcpy(ansi_end, " ");
            } printf("%d. %s%s\n", i + 1, menu_items[i], ansi_end);
        } printf("\nUse arrow keys, 1-6, or underlined keywords\nPress Enter to select\n");
    }
}

void display_paginated(AVL *record, int choice) {
    const int per_page = 20;
    int total = record->_size;
    if (total == 0) {
        printf("Mp data.\n");
        printf("\nPress Enter to return..."); getchar(); return;
    }

    Komponen *all = malloc(sizeof(Komponen) * total);
    int idx = 0;
    long double total_asset = 0;
    inorder_to_array(record->_root, all, &idx, &total_asset);
    
    int page = 0, max_page = (total - 1) / per_page;
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt; newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    
    while (1) {
        long double page_asset = 0;
        printf("\033[2J\033[H");
        if (choice == 3) {
            printf("==================================================================================\n");
            printf("|                                  Indexed  Menu                                 |\n");
            printf("==================================================================================\n");
        }

        if (choice == 4) {
            printf("=======================================================================\n");
            printf("|                           Unindexed  Menu                           |\n");
            printf("=======================================================================\n");
        }

        for (int i = page * per_page; i < (page + 1) * per_page; i++) {
            Komponen k = all[i];
            page_asset += k.harga * (long double)k.stok;
            if ((i+1) > total && choice == 3) printf("|%80s|\n", " ");
            else if ((i+1) > total && choice == 4) printf("|%69s|\n", " ");
            else if (choice == 3) printf("| %4d | [%s] | %-25s | Stocks: %-4d | Price: %10.2Lf |\n", i + 1, k.no_komponen, k.nama, k.stok, k.harga);
            else if (choice == 4) printf("| %4d | %-25s | Stocks: %-4d | Price: %10.2Lf |\n", i + 1, k.nama, k.stok, k.harga);
        }

        if (choice == 3) printf("==================================================================================\n");
        if (choice == 4) printf("=======================================================================\n");
        printf("Page %3d's Asset: %.2Lf\n", page+1, page_asset);
        printf("Total Asset     : %.2Lf\n", total_asset);
        if (max_page == 0) printf("All data is shown in one page.\nPress q to return.\n");
        if (max_page > 0) printf("Page %d of %d\n←/→ to navigate, q to quit\n", page + 1, max_page + 1);

        char c;
        read(STDIN_FILENO, &c, 1);
        if (c == '\033') {
            char seq[2];
            if (read(STDIN_FILENO, &seq[0], 1) == 0) continue;
            if (read(STDIN_FILENO, &seq[1], 1) == 0) continue;
            if (seq[0] == '[') {
                if (seq[1] == 'C' && page < max_page) page++;
                else if (seq[1] == 'D' && page > 0) page--;
            }
        } else if (c == 'q' || c == 'Q') break;
    }

    free(all);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}
