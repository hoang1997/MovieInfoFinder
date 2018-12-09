![Move Finder Logo](https://github.com/hoang1997/MovieInfoFinder/blob/master/Logo2.png?raw=true)
Movie Info Finder is an opensource movie database and wishlisting tool designed to easily allow users to sort through movies using their favourite existing database and store these images in a wishlist. It allows uses to leave personal comments on movies stored in their wishlist and even allows them to generate a random movie. Movie Info Finder even takes advantage of using IMDB id's to improve compatability with more databases in the future. 

## Installation
Movie Info Finder is easy to install. Simply download the code repository if you want to be able to build it yourself and or [click here](https://github.com/hoang1997/MovieInfoFinder/blob/master/Logo2.png?raw=true) to download the latest official build. 

Its important that you have these dependencies installed to be able to make your own build of the program or want to fork it and contribute to the project:

 - Qt 5.12 or above (Open Source Edition or above)
 - C++ 17 or above
 
## Setup
The only necessary setup that needs to be performed for Movie Info Finder is to get an api key from one of our two prefered databases. When initially opening the program you will be asked to enter two API keys. They can be obtained from here:
 - http://www.omdbapi.com
 - https://www.themoviedb.org

## Databases
Movie Info Finder lets you select between 2 different open source databases, OMDB, and TMDB. The both provide the similiar information and movie info finder formats them in the same way, but if you have a preferrred database we encourage you to use that. If the database you prefer currently isn't supported it shouldn't be to difficult to implement youself. Feel free to submit a pull request when you're done.

## Wishlists
WIshlists are the most important part of Movie Info Finder. To add a movie to you wishlist simply press the add to wihslist button after searching a specific movie. It doesn't matter which database you use. After you open your wishlist you can see each movie youve added, delete movies from your wishlist, and even add personal comments like "10/10" or "Watch with Karen". 



