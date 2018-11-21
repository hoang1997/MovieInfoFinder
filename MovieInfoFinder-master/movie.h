#ifndef MOVIE_H
#define MOVIE_H
#include <QtGui>
#include <QtCore>

class movie
{
private:
   QJsonObject obj;
public:
   QString actors,awards,boxOffice,country,dvd,director,genre,language,metascore,plot,poster,production,rated,
   ratings,released,response,runtime,title,type,website,writer,year,imdbID,imdbRating,imdbVotes;

   void setObj(const QJsonObject &obj);

   void setInfo();


};

#endif // MOVIE_H
