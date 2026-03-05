#ifndef RECIPENUMBER_H
#define RECIPENUMBER_H

class RecipeNumber
{
private:
    RecipeNumber();
    RecipeNumber(const RecipeNumber&) = delete;
    RecipeNumber& operator=(const RecipeNumber&) = delete;

public:
    static RecipeNumber& getInstance();

    int recipeIdToDisplay;
    int categoryID;
};

#endif // RECIPENUMBER_H
