#ifndef REGION_H
#define REGION_H

#include <sqlite3.h>

typedef struct {
    int id;
    char name[100];
    char capital[100];
    int population;
    double square;
    int country_id;
} Region;

int add_region(sqlite3* db, int country_id);
void list_regions_by_country(sqlite3* db, int country_id);
int delete_region(sqlite3* db);
void region_menu(sqlite3* db);

#endif
