#ifndef CONNECTION_INFO_H
#define CONNECTION_INFO_H
#include <string>
/*
@class ConnectionInfo
@brief class which represents an object containing connection information
*/
class ConnectionInfo
{
public:
    /*
    @fn ConnectionInfo(std::string host, std::string user, std::string password, std::string dbName)
    @params host a string containing the host of the database
            user a string containing the username used for database connection
            password a string containing the password used for database connection
            dbName a string containing the database name.
    @brief constructor
    @return no return
    */
    ConnectionInfo(std::string host, std::string user, std::string password, std::string dbName) :
    ci_host(host), ci_user(user), ci_password(password), ci_dbName(dbName)
    {

    }
    const std::string& GetHost() const{return ci_host;}
    const std::string& GetUser() const{return ci_user;}
    const std::string& GetPassword() const{return ci_password;}
    const std::string& GetDbName() const{return ci_dbName;}
private:
    /*the sql server host name*/
    std::string ci_host;
    /*username*/
    std::string ci_user;
    /*password*/
    std::string ci_password;
    /*database name*/
    std::string ci_dbName;


};
#endif
