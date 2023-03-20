#include "MovieDatabase.h"
#include "Movie.h"

#include <string>
#include <vector>
#include <cctype>
using namespace std;

// Default constructor for MovieDatabase class
MovieDatabase::MovieDatabase()
{
    m_loaded = false;   // Initialize m_loaded to false indicating that the database is not loaded yet
}

// Destructor for MovieDatabase class
MovieDatabase::~MovieDatabase()
{
    for (int i = 0; i < m_movies.size(); i++)   // Iterate through all Movie objects in m_movies vector
        delete m_movies[i]; // Delete each dynamically allocated Movie object
}

// Method to load movie data from a file
bool MovieDatabase::load(const string& filename)
{
    // Check if the database is already loaded
    if (m_loaded)
        return false;
    
    // Attempt to open the input file
    ifstream infile(filename);
    if (!infile)
    {
        cerr << "Error: Cannot open data.txt!" << endl;
        return false;
    }
    
    // Declare variables to store movie data fields
    string id, userID, name, userName, releaseYear, x; // store either case letter strings
    float rating;
    int n = 0;
   
    // Read each line from the input file
    while (getline(infile, x))
    {
        if (n > 0)
            getline(infile, x);
        n++;
        
        // Read and process the movie data fields
        id = x;
        userID = x;
        // Convert movie ID to lowercase for consistency in data storage
        for (int i = 0; i < id.size(); i++)
            id[i] = tolower(id[i]);
        // Read and process the movie name
        getline(infile, x);
        name = x;
        userName = x;
        // Convert movie name to lowercase for consistency in data storage
        for (int i = 0; i < name.size(); i++)
            name[i] = tolower(name[i]);
        // Read and store the release year
        getline(infile, x);
        releaseYear = x;
        // Initialize variables for processing movie directors
        char ch = ',';
        x = "";
        string u = "";
        vector<string> directors;
        vector<string> userDirectors;
        // Read and process movie directors (split by comma)
        while (ch != '\n')
        {
            infile.get(ch);
            if (ch == ',')
            {
                directors.push_back(x);
                userDirectors.push_back(u);
                x = "";
                u = "";
            }
            else if (ch != '\n'){
                u += ch;
                x += tolower(ch);
            }
        }
        directors.push_back(x);
        userDirectors.push_back(u);
        
        // Initialize variables for processing movie actors
        ch = ',';
        x = "";
        u = "";
        vector<string> actors;
        vector<string> userActors;
        // Read and process movie actors (split by comma)
        while (ch != '\n')
        {
            infile.get(ch);
            if (ch == ',')
            {
                actors.push_back(x);
                userActors.push_back(u);
                x = "";
                u = "";
            }
            else if (ch != '\n')
            {
                u += ch;
                x += tolower(ch);
            }
        }
        actors.push_back(x);
        userActors.push_back(u);
        
        // Initialize variables for processing movie genres
        ch = ',';
        x = "";
        u = "";
        vector<string> genres;
        vector<string> userGenres;
        
        // Read and process movie genres (split by comma)
        while (ch != '\n')
        {
            infile.get(ch);
            if (ch == ',')
            {
                genres.push_back(x);
                userGenres.push_back(u);
                x = "";
                u = "";
            }else if (ch != '\n'){
                u += ch;
                x += tolower(ch);
            }
        }
        genres.push_back(x);
        userGenres.push_back(u);
        // Read and store the movie rating
        infile >> rating;
        infile.ignore(10000, '\n');
        // Create a new Movie object with the processed data
        Movie* mo = new Movie(userID, userName, releaseYear, userDirectors, userActors, userGenres, rating);
        // Add the new Movie object to the list of movies (m_movies)
        m_movies.push_back(mo);
        // Insert the movie into the tmm_movie multimap with the movie ID as the key
        tmm_movie.insert(id, mo);
        // Iterate through the list of directors and insert the movie into the tmm_director multimap with the director as the key
        for (int i = 0; i < directors.size(); i++)
            tmm_director.insert(directors[i], mo);
        // Iterate through the list of actors and insert the movie into the tmm_actor multimap with the actor as the key
        for (int i = 0; i < actors.size(); i++)
            tmm_actor.insert(actors[i], mo);
        // Iterate through the list of genres and insert the movie into the tmm_genre multimap with the genre as the key
        for (int i = 0; i < genres.size(); i++)
            tmm_genre.insert(genres[i], mo);
    }
    // Set m_loaded to true to indicate that the database has been loaded successfully
    m_loaded = true;
    return true;
}

// Method to get a Movie object by its ID
Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    string newID = "";
    for (int i = 0; i < id.size(); i++)
        newID += tolower(id[i]);
    // Check if the ID is in the database and return the corresponding Movie object
    if (!tmm_movie.find(newID).is_valid())
        return nullptr;
    return tmm_movie.find(newID).get_value();
}

// Method to get all movies with a given director
vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    string newDirector = "";
    for (int i = 0; i < director.size(); i++)
        newDirector += tolower(director[i]);
    // Find and return all Movie objects with the given director
    vector<Movie*> result;
    TreeMultimap<string, Movie*>::Iterator a = tmm_director.find(newDirector);
    while (a.is_valid())
    {
        result.push_back(a.get_value());
        a.advance();
    }
    return result;
}

// Method to get all movies with a given actor
vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    string newActor = "";
    for (int i = 0; i < actor.size(); i++)
        newActor += tolower(actor[i]);
   // Find and return all Movie objects with the given actor
    vector<Movie*> result;
    TreeMultimap<string, Movie*>::Iterator a = tmm_actor.find(newActor);
    while (a.is_valid())
    {
        result.push_back(a.get_value());
        a.advance();
    }
    return result;
}
// Method to get all movies with a given genre
vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    string newGenre = "";
    for (int i = 0; i < genre.size(); i++)
        newGenre += tolower(genre[i]);
    // Find and return all Movie objects with the given genre
    vector<Movie*> result;
    TreeMultimap<string, Movie*>::Iterator a = tmm_genre.find(newGenre);
    while (a.is_valid())
    {
        result.push_back(a.get_value());
        a.advance();
    }
    return result;
}

//DONE
