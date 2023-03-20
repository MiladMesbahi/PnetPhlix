#ifndef USER_INCLUDED
#define USER_INCLUDED

#include <string>
#include <vector>
#include "treemm.h"

// User class to represent a user with full name, email, and watch history
class User
{
  public:
    // Constructor to initialize a User object with full name, email, and watch history
    User(const std::string& full_name, const std::string& email,
         const std::vector<std::string>& watch_history);

    // Get the user's full name
    std::string get_full_name() const;

    // Get the user's email address
    std::string get_email() const;

    // Get the user's watch history
    std::vector<std::string> get_watch_history() const;

  private:
    // Private member variables to store the user's full name, email, and watch history
    std::string m_full_name;
    std::string m_email;
    std::vector <std::string> m_watch_history;
};

#endif // USER_INCLUDED

//DONE

