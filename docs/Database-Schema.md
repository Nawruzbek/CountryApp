# Схема базы данных

## ER-диаграмма

```
┌─────────────────────────────────┐
│           country               │
├─────────────────────────────────┤
│ id (PK)         INTEGER         │
│ name            TEXT NOT NULL   │
│ capital         TEXT            │
│ language        TEXT            │
│ population_country INTEGER      │
│ square_country  REAL            │
│ currency        TEXT            │
│ head_country    TEXT            │
└─────────────────────────────────┘
               │
               │ 1 : N
               ▼
┌─────────────────────────────────┐
│           region                │
├─────────────────────────────────┤
│ id (PK)         INTEGER         │
│ name            TEXT NOT NULL   │
│ capital_region  TEXT            │
│ population_region INTEGER       │
│ square_region   REAL            │
│ country_id (FK) INTEGER         │
└─────────────────────────────────┘
```

## SQL схема

```sql
CREATE TABLE country (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL,
    capital TEXT,
    language TEXT,
    population_country INTEGER,
    square_country REAL,
    currency TEXT,
    head_country TEXT
);

CREATE TABLE region (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL,
    capital_region TEXT,
    population_region INTEGER,
    square_region REAL,
    country_id INTEGER,
    FOREIGN KEY (country_id) REFERENCES country(id) ON DELETE CASCADE
);
```

## Связи
- **country (1) → region (N)** через внешний ключ country_id
- При удалении страны (DELETE CASCADE) автоматически удаляются все её регионы
