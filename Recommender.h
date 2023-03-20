#ifndef RECOMMENDER_INCLUDED
#define RECOMMENDER_INCLUDED

#include <string>
#include <vector>

class UserDatabase;
class MovieDatabase;

// Struct to represent a movie and its compatibility score for a user
struct MovieAndRank
{
    // Constructor to initialize a MovieAndRank object with movie ID and compatibility score
    MovieAndRank(const std::string& id, int score)
     : movie_id(id), compatibility_score(score)
    {}

    std::string movie_id; // ID of the movie
    int compatibility_score; // Compatibility score for the movie
};

// Recommender class to generate movie recommendations for users
class Recommender
{
  public:
    // Constructor to initialize a Recommender object with user and movie databases
    Recommender(const UserDatabase& user_database,
                const MovieDatabase& movie_database);

    // Recommend movies for a user based on their email and the number of movies to recommend
    std::vector<MovieAndRank> recommend_movies(const std::string& user_email,
                                               int movie_count) const;

  private:
    // Private member variables to store pointers to the user and movie databases
    const MovieDatabase* m_movieDB;
    const UserDatabase* m_userDB;
};

#endif // RECOMMENDER_INCLUDED

//DONE

