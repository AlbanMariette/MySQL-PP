#ifndef MYSQL_ENVIRONMENT_H
#define MYSQL_ENVIRONMENT_H
#ifdef _WIN32
#include <winsock2.h>
#endif
#include <mysql.h>
#include <stdlib.h>
namespace MYSQL_ENVIRONMENT
{
    /*
     @fn bool init(std::string& error)
     @params error a reference on a string which will be set with an error message if the initiation fail
     @brief function which initialize the sql library. Must be call in the main thread.
     @return bool
     */
    bool init(std::string& error)
    {
        if (mysql_library_init(0, NULL, NULL))
        {
            error = "could not initialize MySQL library";
            return false;
        }
        error = "MySQL library successfuly initalized";
        return true;
    }
    /*
     @fn void stop()
     @params no params
     @brief function which stops the sql library.
     @return void
     */
    void stop()
    {
        mysql_library_end();
    }
}
#endif
