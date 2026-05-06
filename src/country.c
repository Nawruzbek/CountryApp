#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "country.h"
#include "database.h"
#include "region.h"
#include "utils.h"

int add_country(sqlite3* db) {
    Country c;
    char sql[1024];
    
    printf("\n--- Add New Country ---\n");
    printf("Name: "); 
    fgets(c.name, sizeof(c.name), stdin);
    c.name[strcspn(c.name, "\n")] = 0;
    
    printf("Capital: "); 
    fgets(c.capital, sizeof(c.capital), stdin);
    c.capital[strcspn(c.capital, "\n")] = 0;
    
    printf("Language: "); 
    fgets(c.language, sizeof(c.language), stdin);
    c.language[strcspn(c.language, "\n")] = 0;
    
    printf("Population: "); 
    scanf("%d", &c.population);
    clear_input();
    
    printf("Square (km2): "); 
    scanf("%lf", &c.square);
    clear_input();
    
    printf("Currency: "); 
    fgets(c.currency, sizeof(c.currency), stdin);
    c.currency[strcspn(c.currency, "\n")] = 0;
    
    printf("Head of country: "); 
    fgets(c.head, sizeof(c.head), stdin);
    c.head[strcspn(c.head, "\n")] = 0;
    
    sprintf(sql, "INSERT INTO country (name, capital, language, population_country, square_country, currency, head_country) VALUES ('%s', '%s', '%s', %d, %f, '%s', '%s');",
            c.name, c.capital, c.language, c.population, c.square, c.currency, c.head);
    
    if (db_execute(db, sql) != SQLITE_OK) {
        printf("Error adding country!\n");
        return 0;
    }
    
    printf("Country added successfully!\n");
    
    int last_id = sqlite3_last_insert_rowid(db);
    
    printf("\nDo you want to add regions for this country? (y/n): ");
    char answer;
    scanf(" %c", &answer);
    clear_input();
    
    if (answer == 'y' || answer == 'Y') {
        int num_regions;
        printf("How many regions do you want to add? ");
        scanf("%d", &num_regions);
        clear_input();
        
        for(int i = 0; i < num_regions; i++) {
            printf("\n--- Region %d ---\n", i+1);
            add_region(db, last_id);
        }
    }
    
    return 1;
}

void list_countries(sqlite3* db) {
    sqlite3_stmt* stmt;
    const char* sql = "SELECT id, name, capital, population_country, square_country, currency, head_country FROM country";
    
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        printf("Error preparing statement!\n");
        return;
    }
    
    printf("\n%-3s %-30s %-20s %-15s %-15s %-15s %-20s\n", "ID", "Country", "Capital", "Population", "Square (km2)", "Currency", "Head");
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    
    int count = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        count++;
        printf("%-3d %-30s %-20s %-15d %-15.2f %-15s %-20s\n",
               sqlite3_column_int(stmt, 0),
               sqlite3_column_text(stmt, 1),
               sqlite3_column_text(stmt, 2),
               sqlite3_column_int(stmt, 3),
               sqlite3_column_double(stmt, 4),
               sqlite3_column_text(stmt, 5),
               sqlite3_column_text(stmt, 6));
    }
    
    if (count == 0) {
        printf("No countries found.\n");
    }
    
    sqlite3_finalize(stmt);
}

void show_statistics(sqlite3* db) {
    sqlite3_stmt* stmt;
    
    printf("\n=== STATISTICS ===\n");
    
    // Total population
    const char* sql_pop = "SELECT SUM(population_country) FROM country";
    sqlite3_prepare_v2(db, sql_pop, -1, &stmt, 0);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        printf("Total world population: %lld\n", sqlite3_column_int64(stmt, 0));
    }
    sqlite3_finalize(stmt);
    
    // Average square
    const char* sql_avg = "SELECT AVG(square_country) FROM country";
    sqlite3_prepare_v2(db, sql_avg, -1, &stmt, 0);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        printf("Average country square: %.2f km2\n", sqlite3_column_double(stmt, 0));
    }
    sqlite3_finalize(stmt);
    
    // Most populated country
    const char* sql_max = "SELECT name, MAX(population_country) FROM country";
    sqlite3_prepare_v2(db, sql_max, -1, &stmt, 0);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        printf("Most populated country: %s\n", sqlite3_column_text(stmt, 0));
    }
    sqlite3_finalize(stmt);
    
    // Total regions
    const char* sql_reg = "SELECT COUNT(*) FROM region";
    sqlite3_prepare_v2(db, sql_reg, -1, &stmt, 0);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        printf("Total regions: %d\n", sqlite3_column_int(stmt, 0));
    }
    sqlite3_finalize(stmt);
}

int delete_country(sqlite3* db) {
    int id;
    char sql[256];
    
    list_countries(db);
    
    printf("\nEnter country ID to delete: ");
    scanf("%d", &id);
    clear_input();
    
    sprintf(sql, "DELETE FROM country WHERE id = %d", id);
    
    if (db_execute(db, sql) != SQLITE_OK) {
        printf("Error deleting country!\n");
        return 0;
    }
    
    printf("Country and all its regions deleted successfully!\n");
    return 1;
}

void country_menu(sqlite3* db) {
    int choice;
    do {
        printf("\n=== Country Menu ===\n");
        printf("1. List all countries\n");
        printf("2. Add new country\n");
        printf("3. Delete country\n");
        printf("4. Show statistics (SELECT queries)\n");
        printf("5. Back to main menu\n");
        printf("Choice: ");
        scanf("%d", &choice);
        clear_input();
        
        switch(choice) {
            case 1:
                list_countries(db);
                break;
            case 2:
                add_country(db);
                break;
            case 3:
                delete_country(db);
                break;
            case 4:
                show_statistics(db);
                break;
            case 5:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid choice! Please enter 1-5\n");
        }
    } while(choice != 5);
}
