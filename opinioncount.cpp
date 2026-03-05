#include "opinioncount.h"

OpinionCount::OpinionCount() {}

double OpinionCount::returnOpinionPercentage(int likes, int dlikes)
{
    double doubleLikes = static_cast<double>(likes);
    double doubleDLikes = static_cast<double>(dlikes);
    double sum = doubleLikes + doubleDLikes;
    return doubleLikes / sum * 100;
}
