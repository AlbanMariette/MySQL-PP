#ifndef MYSQL_CONNECTION_H
#define MYSQL_CONNECTION_H
/*
@class MysqlConnection
@brief représente une connection à mysql
*/
#include <my_global.h>
#include <mysql.h>
#include <mysqld_error.h>
#include <errmsg.h>
#include <memory>
#include "ConnectionInfo.h"
#include "ResultSet.h"
class MysqlConnection
{
public:
    MysqlConnection(ConnectionInfo& info);
	bool Open();
	void setAutoCommit(bool autoCommit);
	void syncQuery(std::string query);
	std::shared_ptr<ResultSet> syncQueryResult(std::string query);
private:
    void handleMySQLError(unsigned int errNo);
    /*un pointeur sur la connexion à la base de donnée*/
    MYSQL* _MySQLConnection;
    /*les infos de connexions*/
    ConnectionInfo _infos;
};
#endif
