#ifndef USERDATABASE_INCLUDED
#define USERDATABASE_INCLUDED
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "treemm.h"

class User;

// UserDatabase class for managing and storing user data
class UserDatabase
{
  public:
    UserDatabase(); // Constructor
    ~UserDatabase(); // Destructor
    bool load(const std::string& filename); // Load user data from a file
    User* get_user_from_email(const std::string& email) const; // Get a user from their email address

  private:
    TreeMultimap<std::string, User*> tmm; // TreeMultimap for efficient searching
    std::vector<User*> m_users; // Vector for storing User pointers
    bool m_loaded; // Flag to indicate whether the database is already loaded
};

#endif // USERDATABASE_INCLUDED

