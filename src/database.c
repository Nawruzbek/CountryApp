#include <stdio.h>
#include <sqlite3.h>
#include "database.h"

sqlite3* db_open(const char* filename) {
    sqlite3* db;
    int rc = sqlite3_open(filename, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return NULL;
    }
    return db;
}

void db_close(sqlite3* db) {
    sqlite3_close(db);
}

int db_execute(sqlite3* db, const char* sql) {
    char* errmsg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &errmsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errmsg);
        sqlite3_free(errmsg);
        return rc;
    }
    return SQLITE_OK;
}
