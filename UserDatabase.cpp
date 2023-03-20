#include "UserDatabase.h"
#include "User.h"
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// Constructor initializes the UserDatabase object with no users loaded
UserDatabase::UserDatabase()
{
    m_loaded = false;
}

// Destructor deallocates memory for all User objects in the database
UserDatabase::~UserDatabase()
{
    for (int i = 0; i < m_users.size(); i++)
        delete m_users[i];
}

// load function reads the user data from a file and populates the UserDatabase
bool UserDatabase::load(const string& filename)
{
    if (m_loaded)
        return false;
    ifstream infile(filename);
    if (!infile)
        return false;
    string x, name, email;
    int q;
    int k = 0;
    // Read user data from the file line by line
    while (getline(infile, x))
    {
        if (k > 0)
            getline(infile, x);
        vector<string> movies;
        name = x; // Read the user's name
        getline(infile, x);
        email = x; // Read the user's email
        infile >> q; // Read the number of movies in the user's watch history
        infile.ignore(10000, '\n');
        k++;
        // Read the movie IDs from the user's watch history
        for (int j = 0; j < q; j++)
        {
            getline(infile, x);
            movies.push_back(x);
        }
        // Create a new User object and add it to the database
        User* u = new User(name, email, movies);
        m_users.push_back(u);
        tmm.insert(email, u); // Insert the user into the TreeMultimap
    }
    m_loaded = true;
    return true;
}

// get_user_from_email function retrieves a user from the database using their email address
User* UserDatabase::get_user_from_email(const string& email) const
{
    if (!tmm.find(email).is_valid())
        return nullptr; // Return nullptr if the email is not found in the TreeMultimap
    return tmm.find(email).get_value(); // Return the User object associated with the email address
}

