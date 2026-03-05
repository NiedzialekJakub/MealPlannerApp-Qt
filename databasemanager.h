#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <QSqlDatabase>
#include <QStringList>

struct Recipe{
    int id;
    QString name;
    QString instruction;
};

class DatabaseManager
{
public:
    DatabaseManager();

    bool init();

    void addDumnyData();

    QStringList getAllPLRecipes(int category);
    QStringList getAllENRecipes(int category);

    QString getRecipePL(int index);
    QString getIngredientsPL(int index);
    QString getRecipeEN(int index);
    QString getIngredientsEN(int index);

    int returnRecipeLikes(int index);
    int returnRecipeDlikes(int index);
    void addNegativeOpinion(int index);
    void addPositiveOpinion(int index);

    int returnCalories(int index);
    int returnPrepareTime(int index);

    QStringList getAllPLIngredients();
    QStringList getAllENIngredients();

    QStringList getRecipesByIngredientsPL(const QStringList& ingredients);
    QStringList getRecipesByIngredientsEN(const QStringList& ingredients);

    int ReturnIDByRecipeName(QString name);
private:
    QSqlDatabase db;
};

#endif // DATABASEMANAGER_H
