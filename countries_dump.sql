PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;
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
INSERT INTO country VALUES(2,'Russia','Moscow','Russian',146000000,171000000.0,'Ruble','Putin');
INSERT INTO country VALUES(3,'Belarus','Minsk','Belarusian',9250000,207600.0,'Belarusian Ruble','Lukashenko');
CREATE TABLE region (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL,
    capital_region TEXT,
    population_region INTEGER,
    square_region REAL,
    country_id INTEGER,
    FOREIGN KEY (country_id) REFERENCES country(id) ON DELETE CASCADE
);
INSERT INTO region VALUES(1,'Moscow Oblast','Moscow',8500000,44300.0,2);
INSERT INTO region VALUES(2,'Leningrad Oblast','Saint Petersburg',6000000,84500.0,2);
INSERT INTO region VALUES(3,'Krasnodar Krai','Krasnodar',5500000,76000.0,2);
INSERT INTO region VALUES(4,'Minsk Region','Minsk',1400000,39800.0,3);
INSERT INTO region VALUES(5,'Brest Region','Brest',1300000,32700.0,3);
INSERT INTO region VALUES(6,'Gomel Region','Gomel',1400000,40300.0,3);
INSERT INTO sqlite_sequence VALUES('country',4);
INSERT INTO sqlite_sequence VALUES('region',6);
COMMIT;
