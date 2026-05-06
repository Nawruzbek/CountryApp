#ifndef COUNTRY_H
#define COUNTRY_H

#include <sqlite3.h>

typedef struct {
    int id;
    char name[100];
    char capital[100];
    char language[100];
    int population;
    double square;
    char currency[50];
    char head[100];
} Country;

int add_country(sqlite3* db);
void list_countries(sqlite3* db);
int delete_country(sqlite3* db);
void country_menu(sqlite3* db);

#endif
