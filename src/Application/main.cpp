#include <iostream>
/*
    point d'entrée du programme
*/
#include "MysqlEnvironment.h"
#include "MysqlConnection.h"
#include <cstdlib>
int main()
{
    std::cout<<"lancement du programme mysql"<<std::endl;
    std::string error;
    if(!MYSQL_ENVIRONMENT::init(error))
    {
        std::cout<<error.c_str()<<std::endl;
        return 1;
    }
	ConnectionInfo info("localhost", "username", "password", "base");
	MysqlConnection connection(info);
	if (!connection.Open())
	{
		std::cout << "erreur lors de la tentative d'ouverture" << std::endl;
		return -1;
	}
	//on va faire une requete
    std::cout<<error.c_str()<<std::endl;
	std::shared_ptr<ResultSet> result = connection.syncQueryResult("SELECT * FROM base");
	unsigned int rowCount = result->getRowCount();
	unsigned int fieldCount = 0;
	std::cout << "il y a " << rowCount << " row" << std::endl;
	if (rowCount > 0)
	{
		for (unsigned int i = 0; i < rowCount; i++)
		{
			fieldCount = result->getRow(i)->getFieldCount();
			for (unsigned int j = 0; j < fieldCount; j++)
			{
				if (result->getRow(i)->getField(j)->getType() == enum_field_types::MYSQL_TYPE_VAR_STRING)
				{
					std::cout << result->getRow(i)->getField(j)->GetValueAsString() << std::endl;
					std::cout << "string" << std::endl;
				}
				else
				{
					std::cout << result->getRow(i)->getField(j)->GetValueAsInt() << std::endl;

				}
				
			}
			std::cout << std::endl;
		}
	}
		

    MYSQL_ENVIRONMENT::stop();
    return 0;
}
