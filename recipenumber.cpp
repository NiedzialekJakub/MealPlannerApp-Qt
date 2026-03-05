#include "recipenumber.h"

RecipeNumber::RecipeNumber()
{

}

RecipeNumber& RecipeNumber::getInstance()
{
    static RecipeNumber instance;
    return instance;
}
