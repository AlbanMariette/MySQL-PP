#ifndef CONNECTION_INFO_H
#define CONNECTION_INFO_H
#include <string>
/*
@class ConnectionInfo
@brief classe representant des informations permettant une connexion à une base de donnée
*/
class ConnectionInfo
{
public:
    /*
    @fn ConnectionInfo(std::string host, std::string user, std::string password, std::string dbName)
    @params host une chaîne de caractère représentant l'hôte de la base de donnée
            user le nom d'utilisateur permettant la connexion à la base de donnée
            password le mot de passe permettant la connexion à la base de donnée
            dbName le nom de la base sur laquelle on souhaite se connecter
    @brief constructeur d'un objet contenant les informations nécessaires à une connexion à une base de donnée
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
    /*l'hôte du serveur SQL*/
    std::string ci_host;
    /*le nom d'utilisateur*/
    std::string ci_user;
    /*le mot de passe*/
    std::string ci_password;
    /*le nom de la base de donnée*/
    std::string ci_dbName;


};
#endif
