#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "Movie.h"
#include "User.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;
// Recommender constructor, initializes user and movie databases
Recommender::Recommender(const UserDatabase& user_database,
                         const MovieDatabase& movie_database)
{
    m_userDB = &user_database;
    m_movieDB = &movie_database;
}
// Generates movie recommendations for a given user email based on the user's watch history
vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    // Retrieve user watch history
    vector<string> user_movies = m_userDB->get_user_from_email(user_email)->get_watch_history();
    // Create a map to store movie ratings
    unordered_map<Movie*, int> ratings;
    // Iterate through the user's watch history
    for (int i = 0; i < user_movies.size(); i++){
        Movie* mo = m_movieDB->get_movie_from_id(user_movies[i]);
        vector<string> directors = mo->get_directors();

        // Calculate movie ratings based on directors
        for (int j = 0; j < directors.size(); j++){
            vector<Movie*> oMovies = m_movieDB->get_movies_with_director(directors[j]);
            for (int k = 0; k < oMovies.size(); k++){
                ratings[oMovies[k]] += 20;
            }
        }

        // Calculate movie ratings based on actors
        vector<string> actors = mo->get_actors();
        for (int j = 0; j < actors.size(); j++){
            vector<Movie*> tMovies = m_movieDB->get_movies_with_actor(actors[j]);
            for (int k = 0; k < tMovies.size(); k++){
                ratings[tMovies[k]] += 30;
            }
        }
       
        // Calculate movie ratings based on genres
        vector<string> genres = mo->get_genres();
        for (int j = 0; j < genres.size(); j++){
            vector<Movie*> thMovies = m_movieDB->get_movies_with_genre(genres[j]);
            for (int k = 0; k < thMovies.size(); k++){
                ratings[thMovies[k]] += 1;
            }
        }
    }

    // Store movies and their corresponding ratings in a vector
    vector<MovieAndRank> recommendations;
    for (auto a = ratings.begin(); a != ratings.end(); a++)
    {
        MovieAndRank movierank = MovieAndRank(a->first->get_id(), a->second);
        recommendations.push_back(movierank);
    }

    // Sort the recommendations based on ratings and movie title
    sort(recommendations.begin(), recommendations.end(), [this] (const MovieAndRank& b, const MovieAndRank& c){
            if (b.compatibility_score != c.compatibility_score)
                return b.compatibility_score > c.compatibility_score;
            else
                return m_movieDB->get_movie_from_id(b.movie_id)->get_title() < m_movieDB->get_movie_from_id(b.movie_id)->get_title();
        }
    );
   
    // Initialize an empty vector to store the final movie recommendations
    vector<MovieAndRank> r;
    // Keep track of the number of movies inserted into the final recommendation list
    int insert = 0;
    // Index variable for iterating through the sorted recommendations list
    int i = 0;
    // Continue adding recommendations until the required movie_count is reached
    while (insert < movie_count)
    {
        // Flag to check if the current movie has already been watched by the user
        bool watchedMovie = false;
        // Iterate through the user's watched movies
        for (int j = 0; j < user_movies.size(); j++){
            // If the current recommendation matches a watched movie, set the flag to true
            if (recommendations[i].movie_id == user_movies[j]){
                watchedMovie = true;
            }
        }
        
        // If the movie has not been watched, add it to the final recommendation list
        if (!watchedMovie){
            r.push_back(recommendations[i]);
            insert++; // Increment the counter for inserted recommendations
        }
        i++; // Move on to the next recommendation in the sorted list
    }
    // Return the final recommendation list containing 'movie_count' number of movies
    return r;
}

//DONE
