#ifndef MYSQL_CONNECTION_H
#define MYSQL_CONNECTION_H
/*
@class MysqlConnection
@brief represent a mysql connection
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
	/*
	@fn MysqlConnection(ConnectionInfo& Info)
	@params Info a reference on the ConnectionInfo Object which encapsulates connections information.
	@brief constructor
	@return no return
	*/
    MysqlConnection(ConnectionInfo& info);
	/*
	@fn bool Open();
	@params no params
	@brief method which return a bool equal true in case the connection is opened and false otherwise
	@return bool
	*/
	bool Open();
	/*
	@fn void setAutoCommit(bool autoCommit)
	@params autoCommit the new value of the auto commit option of the connection
	@brief method which allow user to change the auto-commit option of the connection
	@return void
	*/
	void setAutoCommit(bool autoCommit);
	/*
	@fn void syncQuery(std::string query)
	@params query a string which contains the sql query
	@brief method which allow user to execute a synchronous query on the connection object.
			The query is not verified by the method
	@return void
	*/
	void syncQuery(std::string query);
	/*
	@fn std::shared_ptr<ResultSet> syncQueryResult(std::string query)
	@params query a string which contains the sql query
	@brief method which allow user to execute a synchronous query on the connection object.
			The method return a resultset encapsulated in a smart pointer
			The query is not verified by the method
	@return std::shared_ptr<ResultSet>
	*/
	std::shared_ptr<ResultSet> syncQueryResult(std::string query);
private:
	/*
	@fn void handleMySQLError(unsigned int errNo)
	@params errNo the error number grab with the sql library's function : mysql_errno(MYSQL object)
	@brief method which allow user to grab mysql error and execute actions accordingly.
	@return void
	*/
    void handleMySQLError(unsigned int errNo);
    /*a pointer on the MYSQL connection*/
    MYSQL* _MySQLConnection;
    /*an object of type ConnectionInfo which contain the connection information*/
    ConnectionInfo _infos;
};
#endif
