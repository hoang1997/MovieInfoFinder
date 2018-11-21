#include "movie.h"

void movie::setObj(const QJsonObject &val)
{
    obj = val;
    setInfo();
}

void movie::setInfo()
{
    actors = obj["Actors"].toString();
    awards = obj["Awards"].toString();
    director = obj["Director"].toString();
    genre = obj["Genre"].toString();
    plot = obj["Plot"].toString();
    poster = obj["Poster"].toString();
    production = obj["Production"].toString();
    rated = obj["Rated"].toString();
    released = obj["Released"].toString();
    runtime = obj["Runtime"].toString();
    title = obj["Title"].toString();
    writer = obj["Writer"].toString();
    year = obj["Year"].toString();
    imdbRating = obj["imdbRating"].toString();
}
