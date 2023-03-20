#ifndef MOVIEDATABASE_INCLUDED
#define MOVIEDATABASE_INCLUDED

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <vector>
#include "treemm.h"

class Movie;

// MovieDatabase class to store and manage movie information
class MovieDatabase
{
  public:
    // Constructor to initialize an empty MovieDatabase object
    MovieDatabase();
    // Destructor to clean up dynamically allocated memory
    ~MovieDatabase();

    // Load movie data from a file into the database
    bool load(const std::string& filename);

    // Get a pointer to a movie object from its ID
    Movie* get_movie_from_id(const std::string& id) const;

    // Get a list of movies directed by a specific director
    std::vector<Movie*> get_movies_with_director(const std::string& director) const;

    // Get a list of movies featuring a specific actor
    std::vector<Movie*> get_movies_with_actor(const std::string& actor) const;

    // Get a list of movies belonging to a specific genre
    std::vector<Movie*> get_movies_with_genre(const std::string& genre) const;

  private:
    // TreeMultimap for storing movies indexed by movie ID, director, actor, and genre
    TreeMultimap<std::string, Movie*> tmm_movie;
    TreeMultimap<std::string, Movie*> tmm_director;
    TreeMultimap<std::string, Movie*> tmm_actor;
    TreeMultimap<std::string, Movie*> tmm_genre;

    std::vector<Movie*> m_movies; // Store movies for deletion in the destructor
    bool m_loaded; // Flag to indicate whether the database has been loaded
};

#endif // MOVIEDATABASE_INCLUDED

//DONE

