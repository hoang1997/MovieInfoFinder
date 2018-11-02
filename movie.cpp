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
    boxOffice = obj["BoxOffice"].toString();
    country = obj["Country"].toString();
    dvd = obj["DVD"].toString();
    director = obj["Director"].toString();
    genre = obj["Genre"].toString();
    language = obj["Language"].toString();
    metascore = obj["Metascore"].toString();
    plot = obj["Plot"].toString();
    poster = obj["Poster"].toString();
    production = obj["Production"].toString();
    rated = obj["Rated"].toString();
    released = obj["Released"].toString();
    runtime = obj["Runtime"].toString();
    title = obj["Title"].toString();
    type = obj["Type"].toString();
    website = obj["Website"].toString();
    writer = obj["Writer"].toString();
    year = obj["Year"].toString();
    imdbRating = obj["imdbRating"].toString();
    imdbVotes = obj["imdbVotes"].toString();
}
