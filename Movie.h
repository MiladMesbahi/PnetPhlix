#ifndef MOVIE_INCLUDED
#define MOVIE_INCLUDED

#include <string>
#include <vector>

// Movie class to store and manage movie information
class Movie
{
  public:
    // Constructor to initialize a Movie object with given parameters
    Movie(const std::string& id, const std::string& title,
          const std::string& release_year,
          const std::vector<std::string>& directors,
          const std::vector<std::string>& actors,
          const std::vector<std::string>& genres, float rating);

    // Getter methods for various movie properties
    std::string get_id() const;
    std::string get_title() const;
    std::string get_release_year() const;
    float get_rating() const;
    std::vector<std::string> get_directors() const;
    std::vector<std::string> get_actors() const;
    std::vector<std::string> get_genres() const;

  private:
    // Private member variables to store movie properties
    std::string m_id;
    std::string m_title;
    std::string m_releaseYear;
    float m_rating;
    std::vector<std::string> m_directors;
    std::vector<std::string> m_actors;
    std::vector<std::string> m_genres;
};

#endif // MOVIE_INCLUDED

//DONE

