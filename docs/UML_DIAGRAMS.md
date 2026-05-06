# UML Диаграммы CountryApp

## Список диаграмм для Draw.io

| № | Диаграмма | Файл | Статус |
|---|-----------|------|--------|
| 1 | ER-диаграмма | `diagrams/er-diagram.png` | ❌ |
| 2 | Use Case (верхнеуровневая) | `diagrams/use-case-high-level.png` | ❌ |
| 3 | Use Case (управление Country) | `diagrams/use-case-country.png` | ❌ |
| 4 | Диаграмма классов | `diagrams/class-diagram.png` | ❌ |
| 5 | Состояний (Login) | `diagrams/state-login.png` | ❌ |
| 6 | Деятельности (Login) | `diagrams/activity-login.png` | ❌ |
| 7 | Деятельности (Add Country) | `diagrams/activity-add-country.png` | ❌ |
| 8 | Последовательности (Add Country) | `diagrams/sequence-add-country.png` | ❌ |
| 9 | Развертывания | `diagrams/deployment.png` | ❌ |

## Инструкция по созданию

### 1. ER-диаграмма
- Таблица `country`: id, name, capital, language, population_country, square_country, currency, head_country
- Таблица `region`: id, name, capital_region, population_region, square_region, country_id
- Связь: 1 : N

### 2. Use Case диаграммы
- Актеры: User (Admin)
- Use Cases: Login, Manage Countries, Manage Regions, View Statistics

### 3. Диаграмма классов
- (C) CountryController
- (C) RegionController  
- (I) CountryInput
- (I) RegionInput
- (Entity) User
- (Entity) Country
- (Entity) Region

### 4. Диаграмма состояний Login
- Состояния: EnteringUsername → EnteringPassword → CheckingCredentials → [success/fail]

### 5. Диаграммы деятельности
- Login: поток действий для аутентификации
- Add Country: поток действий для добавления страны и регионов

### 6. Диаграмма последовательности
- Объекты: User → CountryInput → CountryController → Database → Country

### 7. Диаграмма развертывания
- Компоненты: Console (User PC) → Application Server → SQLite Database
