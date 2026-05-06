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
