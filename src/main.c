#include <stdio.h>
#include <stdlib.h>
#include "auth.h"
#include "database.h"
#include "country.h"
#include "region.h"

void show_main_menu() {
    printf("\n=== MAIN MENU ===\n");
    printf("1. Countries\n");
    printf("2. Regions\n");
    printf("3. Exit\n");
    printf("Choice: ");
}

int main() {
    printf("=== CountryApp ===\n");
    
    if (!login()) {
        printf("Access denied\n");
        return 1;
    }
    
    sqlite3* db = db_open("countries.db");
    if (!db) {
        printf("Failed to open database!\n");
        return 1;
    }
    
    int choice;
    do {
        show_main_menu();
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                country_menu(db);
                break;
            case 2:
                region_menu(db);
                break;
            case 3:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while(choice != 3);
    
    db_close(db);
    return 0;
}
