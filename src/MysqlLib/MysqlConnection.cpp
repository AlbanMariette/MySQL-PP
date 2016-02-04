#include "MysqlConnection.h"
#include <iostream>

MysqlConnection::MysqlConnection(ConnectionInfo& info) : _infos(info)
{
	_MySQLConnection = mysql_init(nullptr);
}
bool MysqlConnection::Open()
{
	if (_MySQLConnection == nullptr)
	{
		//TODO : log erreur pas assez de mémoire pour allouer une nouvelle connexion SQL
		std::cout << "erreur pas assez de mémoire" << std::endl;
		return false;
	}
	if (!mysql_real_connect(_MySQLConnection, _infos.GetHost().c_str(), _infos.GetUser().c_str(), _infos.GetPassword().c_str(), _infos.GetDbName().c_str(), 0, NULL, 0))
	{
		//TODO log erreur connexion
		handleMySQLError(mysql_errno(_MySQLConnection));
		return false;
	}
	return true;
}
void MysqlConnection::setAutoCommit(bool autoCommit)
{
	if (!_MySQLConnection)
		return;//TODO log l'erreur
	if (mysql_autocommit(_MySQLConnection, autoCommit))
	{
		handleMySQLError(mysql_errno(_MySQLConnection));
	}
}
void MysqlConnection::syncQuery(std::string query)
{
	if (!_MySQLConnection||query.empty())
		return;
	if (mysql_query(_MySQLConnection, query.c_str()))
	{
		handleMySQLError(mysql_errno(_MySQLConnection));
	}
	else
	{
		MYSQL_RES *result=nullptr;
		unsigned int num_fields=0;
		unsigned int num_rows=0;
		result = mysql_store_result(_MySQLConnection);
		if (result)  // there are rows
		{
			num_fields = mysql_num_fields(result);
			num_rows = mysql_num_rows(result);
			//On ne récupère pas les données mais on peut logger
			//pour prévenir l'utilisateur que la requete renvoyait des données
			//puis on libère la mémoire mysql_free_result(result)
			mysql_free_result(result);
		}
		else  // mysql_store_result() returned nothing; should it have?
		{
			if (mysql_field_count(_MySQLConnection) == 0)
			{
				//la requete n'a pas retournée de données
				num_rows = mysql_affected_rows(_MySQLConnection);
				//on peut logger le nombre de données affectées
			}
			else // mysql_store_result() should have returned data
			{
				handleMySQLError(mysql_errno(_MySQLConnection));
			}
		}

	}
}
std::shared_ptr<ResultSet> MysqlConnection::syncQueryResult(std::string query)
{
	if (!_MySQLConnection || query.empty())
		return nullptr;
	std::shared_ptr<ResultSet> temp = nullptr;
	if (mysql_query(_MySQLConnection, query.c_str()))
	{
		handleMySQLError(mysql_errno(_MySQLConnection));
	}
	else
	{
		MYSQL_RES *result = nullptr;
		result = mysql_store_result(_MySQLConnection);
		if (result)  // there are rows
		{
			temp = std::make_shared<ResultSet>(result);
			if (!temp->loadData())
			{
				temp.reset();
			}
		}
	}
	return temp;
}
void MysqlConnection::handleMySQLError(unsigned int errNo)
{
    switch(errNo)
    {
		case ER_DBACCESS_DENIED_ERROR:
			//erreur côté serveur
			//les identifiants ne sont pas bon
			std::cout << mysql_error(_MySQLConnection) << std::endl;
		break;
        case CR_CONN_HOST_ERROR:
			//erreur côté client
			//impossible de se connecter au serveur distant
			std::cout << mysql_error(_MySQLConnection) << std::endl;
        break;
		
        default:
        break;
    }
}
