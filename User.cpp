#include "User.h"

#include <string>
#include <vector>
using namespace std;

// User constructor initializing full name, email, and watch history
User::User(const string& full_name, const string& email,
           const vector<string>& watch_history)
{
    m_full_name = full_name;
    m_email = email;
    // Iterate through watch_history and add movies to the user's watch history
    for (vector<string>::const_iterator movie = watch_history.begin(); movie != watch_history.end(); movie++)
        m_watch_history.push_back(*movie);
}

// Get the user's full name
string User::get_full_name() const
{
    return m_full_name;
}

// Get the user's email address
string User::get_email() const
{
    return m_email;
}

// Get the user's watch history
vector<string> User::get_watch_history() const
{
    return m_watch_history;
}

//DONE

