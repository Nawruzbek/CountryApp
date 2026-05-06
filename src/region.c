#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "region.h"
#include "database.h"
#include "utils.h"

int add_region(sqlite3* db, int country_id) {
    Region r;
    char sql[1024];
    
    r.country_id = country_id;
    
    printf("Region name: "); 
    fgets(r.name, sizeof(r.name), stdin);
    r.name[strcspn(r.name, "\n")] = 0;
    
    printf("Region capital: "); 
    fgets(r.capital, sizeof(r.capital), stdin);
    r.capital[strcspn(r.capital, "\n")] = 0;
    
    printf("Region population: "); 
    scanf("%d", &r.population);
    clear_input();
    
    printf("Region square (km2): "); 
    scanf("%lf", &r.square);
    clear_input();
    
    sprintf(sql, "INSERT INTO region (name, capital_region, population_region, square_region, country_id) VALUES ('%s', '%s', %d, %f, %d);",
            r.name, r.capital, r.population, r.square, r.country_id);
    
    if (db_execute(db, sql) != SQLITE_OK) {
        printf("Error adding region!\n");
        return 0;
    }
    
    printf("Region added successfully!\n");
    return 1;
}

void list_regions_by_country(sqlite3* db, int country_id) {
    sqlite3_stmt* stmt;
    const char* sql = "SELECT id, name, capital_region, population_region, square_region FROM region WHERE country_id = ?";
    
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        printf("Error preparing statement!\n");
        return;
    }
    
    sqlite3_bind_int(stmt, 1, country_id);
    
    printf("\n%-3s %-30s %-20s %-15s %-15s\n", "ID", "Region", "Capital", "Population", "Square (km2)");
    printf("--------------------------------------------------------------------------------------------\n");
    
    int has_rows = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        has_rows = 1;
        printf("%-3d %-30s %-20s %-15d %-15.2f\n",
               sqlite3_column_int(stmt, 0),
               sqlite3_column_text(stmt, 1),
               sqlite3_column_text(stmt, 2),
               sqlite3_column_int(stmt, 3),
               sqlite3_column_double(stmt, 4));
    }
    
    if (!has_rows) {
        printf("No regions found for this country.\n");
    }
    
    sqlite3_finalize(stmt);
}

int delete_region(sqlite3* db) {
    int id;
    char sql[256];
    
    printf("Enter region ID to delete: ");
    scanf("%d", &id);
    clear_input();
    
    sprintf(sql, "DELETE FROM region WHERE id = %d", id);
    
    if (db_execute(db, sql) != SQLITE_OK) {
        printf("Error deleting region!\n");
        return 0;
    }
    
    printf("Region deleted successfully!\n");
    return 1;
}

void region_menu(sqlite3* db) {
    int choice, country_id;
    do {
        printf("\n=== Region Menu ===\n");
        printf("1. View regions of a country\n");
        printf("2. Add region to a country\n");
        printf("3. Delete region\n");
        printf("4. Back to main menu\n");
        printf("Choice: ");
        scanf("%d", &choice);
        clear_input();
        
        switch(choice) {
            case 1:
                printf("Enter country ID: ");
                scanf("%d", &country_id);
                clear_input();
                list_regions_by_country(db, country_id);
                break;
            case 2:
                printf("Enter country ID: ");
                scanf("%d", &country_id);
                clear_input();
                add_region(db, country_id);
                break;
            case 3:
                delete_region(db);
                break;
            case 4:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while(choice != 4);
}
