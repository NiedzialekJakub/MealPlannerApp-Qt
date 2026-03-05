#include "databasemanager.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QDir>

DatabaseManager::DatabaseManager() {}

bool DatabaseManager::init()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    qDebug() << "Obecny folder roboczy to:" << QDir::currentPath();
    db.setDatabaseName("../../meal_planner.db");

    if(!db.open())
    {
        qDebug() << "Blad bazy danych: " << db.lastError().text();
        return false;
    }

    qDebug() << "Polaczono z baza danych";

    QSqlQuery query;
    // Włączanie kluczy obcych
    query.exec("PRAGMA foreign_keys = ON");

    // tabela przepisy
    if (!query.exec("CREATE TABLE IF NOT EXISTS recipes ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "name TEXT NOT NULL,"
                    "instruction TEXT,"
                    "category_id INTEGER)")) {
        qDebug() << "Blad tworzenia recipes:" << query.lastError().text();
    }

    // tabela skladniki
    if (!query.exec("CREATE TABLE IF NOT EXISTS ingredients ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "name_pl TEXT NOT NULL UNIQUE,"
                    "name_en TEXT NOT NULL UNIQUE)")) {
        qDebug() << "Blad tworzenia ingredients:" << query.lastError().text();
    }

    // tabela opinie
    if (!query.exec("CREATE TABLE IF NOT EXISTS opinion("
                    "recipe_id INTEGER,"
                    "like_count INTEGER,"
                    "dlike_count INTEGER)")){
        qDebug() << "blad tworzenia opinion: " << query.lastError().text();
    }

    // tabela kalorie
    if (!query.exec("CREATE TABLE IF NOT EXISTS calories("
                    "recipe_id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "recipe_calories INTEGER)")){
        qDebug() << "blad tworzenia calories" << query.lastError().text();
    }

    // tabela czas przygotowania
    if(!query.exec("CREATE TABLE IF NOT EXISTS time("
                    "recipe_id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "prepare_time INTEGER)")){
        qDebug() << "blad tworzenia time " << query.lastError().text();
    }

    return true;
}

void DatabaseManager::addDumnyData()
{
    QSqlQuery query;
    query.exec("SELECT count(*) FROM recipes");
    if(query.next() && query.value(0).toInt() > 0){
        return;
    }

    qDebug() << "Baza pusta wgrywam dane testowe";

    if(!query.exec("INSERT INTO recipes (name, instruction, category_id) VALUES ('PL - Jajecznica EN - Scrambled eggs', 'PL - Wbij jajka na masło i mieszaj.  EN - Crack the eggs into the butter and stir.', '5')"))
        qDebug() << "Blad insert recipes:" << query.lastError().text();

    query.exec("INSERT INTO recipes (name, instruction, category_id) VALUES ('PL - Kanapka z serem EN - Cheese sandwitch', 'PL - Połóż ser na chleb. EN - Put the cheese on the braed.', '4')");

    query.exec("INSERT INTO ingredients (name) VALUES ('Eggs')");
    query.exec("INSERT INTO ingredients (name) VALUES ('Butter')");
    query.exec("INSERT INTO ingredients (name) VALUES ('Bread')");
    query.exec("INSERT INTO ingredients (name) VALUES ('Cheese')");

    query.exec("INSERT INTO recipe_ingredients VALUES (1, 1)");
    query.exec("INSERT INTO recipe_ingredients VALUES (1, 2)");

    query.exec("INSERT INTO recipe_ingredients VALUES (2, 3)");
    query.exec("INSERT INTO recipe_ingredients VALUES (2, 4)");
}

QStringList DatabaseManager::getAllPLRecipes(int category)
{
    QStringList list;
    QSqlQuery query;

    query.prepare("SELECT name FROM recipes WHERE category_id = :cat_id");
    query.bindValue(":cat_id", category);

    if(query.exec()){
        while(query.next()){
            QString fullName = query.value(0).toString();
            int index = fullName.indexOf("EN");

            if(index != -1)
            {
                QString shortName = fullName.left(index);
                list.append(shortName.trimmed());
            } else{
                list.append(fullName);
            }
        }
    }else{
        qDebug() << "Blad pobierania przepisow: " << query.lastError().text();
    }

    return list;
}

QStringList DatabaseManager::getAllENRecipes(int category)
{
    QStringList list;
    QSqlQuery query;

    query.prepare("SELECT name FROM recipes WHERE category_id = :cat_id");
    query.bindValue(":cat_id", category);

    if(query.exec()){
        while(query.next()){
            QString fullName = query.value(0).toString();
            int index = fullName.indexOf("EN");

            if(index != -1)
            {
                QString shortName = fullName.mid(index + 2);
                list.append(shortName.trimmed());
            } else{
                list.append(fullName);
            }
        }
    }else{
        qDebug() << "Blad pobierania przepisow: " << query.lastError().text();
    }

    return list;
}

QStringList DatabaseManager::getAllPLIngredients()
{
    QStringList listIngredients;
    QSqlQuery query;

    query.prepare("SELECT name_pl FROM ingredients ORDER BY id");

    if(query.exec()){
        while(query.next()){
            QString ingredient = query.value(0).toString();
            listIngredients.append(ingredient);
        }
    }else{
        qDebug() << "blad pobierania pl skladnikow: " << query.lastError().text();
    }

    return listIngredients;
}
QStringList DatabaseManager::getAllENIngredients()
{
    QStringList listIngredients;
    QSqlQuery query;

    query.prepare("SELECT name_en FROM ingredients ORDER BY id");

    if(query.exec()){
        while(query.next()){
            QString ingredient = query.value(0).toString();
            listIngredients.append(ingredient);
        }
    }else{
        qDebug() << "blad pobierania en skladnikow: " << query.lastError().text();
    }

    return listIngredients;
}

QString DatabaseManager::getRecipePL(int index)
{
    QString recipe;
    QSqlQuery query;

    query.prepare("SELECT instruction FROM recipes WHERE id = :recipe_id");
    query.bindValue(":recipe_id", index);

    if(query.exec()){
        if(query.next()){
            recipe = query.value(0).toString();
            int index = recipe.indexOf("Składniki");

            if(index != -1){
                recipe = recipe.left(index);
            }
        }
    }else{
        qDebug() << "Blad pobierania przepisu" << query.lastError().text();
    }

    return recipe;
}

QString DatabaseManager::getIngredientsPL(int index)
{
    QString result;
    QSqlQuery query;

    query.prepare("SELECT instruction FROM recipes WHERE id = :recipe_id");
    query.bindValue(":recipe_id", index);

    if(query.exec())
    {
        if(query.next())
        {
            QString fullText = query.value(0).toString();

            int start = fullText.indexOf("Składniki");
            int end = fullText.indexOf("EN", start);

            if(start != -1 && end != -1)
            {
                int lenght = end - start;
                result = fullText.mid(start, lenght);
            }
        }
    }

    return result;
}

QString DatabaseManager::getRecipeEN(int index)
{
    QString result;
    QSqlQuery query;

    query.prepare("SELECT instruction FROM recipes WHERE id = :recipe_id");
    query.bindValue(":recipe_id", index);

    if(query.exec())
    {
        if(query.next())
        {
            QString fullText = query.value(0).toString();

            int posEn = fullText.indexOf("EN");

            if(posEn != -1)
            {
                int start = posEn + 2;
                int end = fullText.indexOf("Ingredients", start);

                if(end != -1){
                    int length = start - end;
                    result = fullText.mid(start, length);
                }
            }
        }
    }

    return result;
}
QString DatabaseManager::getIngredientsEN(int index)
{
    QString result;
    QSqlQuery query;

    query.prepare("SELECT instruction FROM recipes WHERE id = :recipe_id");
    query.bindValue(":recipe_id", index);

    if(query.exec())
    {
        if(query.next())
        {
            QString fullText = query.value(0).toString();
            int start = fullText.indexOf("Ingredients");

            if(start != -1)
            {
                result = fullText.mid(start);
            }
        }
    }

    return result;
}

int DatabaseManager::returnCalories(int index)
{
    int result = 0;
    QSqlQuery query;

    query.prepare("SELECT recipe_calories FROM calories WHERE recipe_id = :id");
    query.bindValue(":id", index);

    if(query.exec() && query.next())
    {
        result = query.value(0).toInt();
    }

    return result;
}

int DatabaseManager::returnPrepareTime(int index)
{
    int result = 0;
    QSqlQuery query;

    query.prepare("SELECT prepare_time FROM time WHERE recipe_id = :id");
    query.bindValue(":id", index);

    if(query.exec() && query.next())
    {
        result = query.value(0).toInt();
    }

    return result;
}

int DatabaseManager::returnRecipeLikes(int index)
{
    int result = 0;
    QSqlQuery query;

    query.prepare("SELECT like_count FROM opinion WHERE recipe_id = :id");
    query.bindValue(":id", index);

    if(query.exec() && query.next())
    {
        result = query.value(0).toInt();
    }

    return result;
}
int DatabaseManager::returnRecipeDlikes(int index)
{
    int result = 0;
    QSqlQuery query;

    query.prepare("SELECT dlike_count FROM opinion WHERE recipe_id = :id");
    query.bindValue(":id", index);

    if(query.exec() && query.next())
    {
        result = query.value(0).toInt();
    }

    return result;
}

void DatabaseManager::addNegativeOpinion(int index)
{
    QSqlQuery query;
    query.prepare("SELECT dlike_count FROM opinion WHERE recipe_id = :id");
    query.bindValue(":id", index);

    if(query.exec()) {
        if(query.next()) {

            QSqlQuery updateQuery;
            updateQuery.prepare("UPDATE opinion SET dlike_count = dlike_count + 1 WHERE recipe_id = :id");
            updateQuery.bindValue(":id", index);

            if(updateQuery.exec()) {
                qDebug() << "Dodano opinię dla ID:" << index;
            } else {
                qDebug() << "BŁĄD ZAPISU (UPDATE):" << updateQuery.lastError().text();
            }
        }
    }
}
void DatabaseManager::addPositiveOpinion(int index)
{
    QSqlQuery query;
    query.prepare("SELECT dlike_count FROM opinion WHERE recipe_id = :id");
    query.bindValue(":id", index);

    if(query.exec()) {
        if(query.next()) {

            QSqlQuery updateQuery;
            updateQuery.prepare("UPDATE opinion SET dlike_count = dlike_count + 1 WHERE recipe_id = :id");
            updateQuery.bindValue(":id", index);

            if(updateQuery.exec()) {
                qDebug() << "Dodano opinię dla ID:" << index;
            } else {
                qDebug() << "BŁĄD ZAPISU (UPDATE):" << updateQuery.lastError().text();
            }

        }
    }
}

QStringList DatabaseManager::getRecipesByIngredientsPL(const QStringList& ingredients)
{
    QStringList result;

    if(ingredients.isEmpty()){
        qDebug() << "pusta lista skladnikow";
        return result;
    }

    QString queryStr = "Select name FROM recipes WHERE ";
    QStringList conditions;

    for(int i=0; i<ingredients.size(); ++i){
        conditions.append("instruction LIKE ?");
    }

    queryStr += conditions.join(" OR ");

    QSqlQuery query;
    query.prepare(queryStr);

    for(int i=0; i<ingredients.size(); ++i){
        query.addBindValue("%ingredients%" + ingredients[i] + "%");
    }

    if(query.exec()){
        while(query.next()){
            QString name = query.value(0).toString();
            QString namePL = name.split(" EN").first().trimmed();
            result.append(namePL);
        }
    }
    else{
        qDebug() << "blad wyszukiwania po lodowce: " << query.lastError().text();
        qDebug() << "zapytanie wygladalo tak: " << query.executedQuery();
    }

    return result;
}

QStringList DatabaseManager::getRecipesByIngredientsEN(const QStringList& ingredients)
{
    QStringList result;

    if(ingredients.isEmpty()){
        qDebug() << "pusta lista skladnikow";
        return result;
    }

    QString queryStr = "Select name FROM recipes WHERE ";
    QStringList conditions;

    for(int i=0; i<ingredients.size(); ++i){
        conditions.append("instruction LIKE ?");
    }

    queryStr += conditions.join(" OR ");

    QSqlQuery query;
    query.prepare(queryStr);

    for(int i=0; i<ingredients.size(); ++i){
        query.addBindValue("%ingredients%" + ingredients[i] + "%");
    }

    if(query.exec()){
        while(query.next()){
            QString name = query.value(0).toString();
            QString namePL = name.split(" EN").last().trimmed();
            result.append(namePL);
        }
    }
    else{
        qDebug() << "blad wyszukiwania po lodowce: " << query.lastError().text();
        qDebug() << "zapytanie wygladalo tak: " << query.executedQuery();
    }

    return result;
}

int DatabaseManager::ReturnIDByRecipeName(QString name)
{
    int result;
    QSqlQuery query;
    query.prepare("Select id FROM recipes WHERE name LIKE :recipeName");
    query.bindValue(":recipeName", "%" + name + "%");

    if(query.exec()){
        if(query.next()){
            result = query.value(0).toInt();
            return result;
        }
    }

    return -1;
}
