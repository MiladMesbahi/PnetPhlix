#include "Movie.h"

#include <string>
#include <vector>
using namespace std;

Movie::Movie(const string& id, const string& title, const string& release_year,
             const vector<string>& directors, const vector<string>& actors,
             const vector<string>& genres, float rating)
{
    m_id = id;
    m_title = title;
    m_releaseYear = release_year;
    m_rating = rating;
    vector<string>::const_iterator a;
        for (a = directors.begin(); a != directors.end(); a++)
            m_directors.push_back(*a);
        for (a = actors.begin(); a != actors.end(); a++)
            m_actors.push_back(*a);
        for (a = genres.begin(); a != genres.end(); a++)
            m_genres.push_back(*a);
}

string Movie::get_id() const
{
    return m_id;
}

string Movie::get_title() const
{
    return m_title;
}

string Movie::get_release_year() const
{
    return m_releaseYear;
}

float Movie::get_rating() const
{
    return m_rating;
}

vector<string> Movie::get_directors() const
{
    return m_directors;
}

vector<string> Movie::get_actors() const
{
    return m_actors;
}

vector<string> Movie::get_genres() const
{
    return m_genres;
}

//DONE
