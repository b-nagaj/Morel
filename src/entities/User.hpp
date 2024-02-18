#ifndef USER
#define USER

#include <string>

class User {
    // attributes
    private:
        std::string username;
    
    // methods
    private:
        void SetUsername(std::string u);

    public:
        User(std::string username);
        std::string GetUsername();
        
};

#endif
