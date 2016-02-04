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
     @params error reference sur une chaine de caractere qui sera remplie du message d'erreur si la fonction échoue à initialiser mysql
     @brief methode qui initialise la bibliotheque mysql. Cette fonction doit être appelée dans le thread principal.
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
     @brief methode qui arrete la bibliotheque mysql.
     @return void
     */
    void stop()
    {
        mysql_library_end();
    }
}
#endif
