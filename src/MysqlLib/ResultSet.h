#ifndef RESULT_SET_H
#define RESULT_SET_H
#include <my_global.h>
#include <mysql.h>
#include <mysqld_error.h>
#include <errmsg.h>
#include <vector>
#include <iostream>
/*
@class Field
@brief classe representing a field
*/
class Field
{
public:
    Field();
    void setType(enum_field_types type);
	void setData(char* data, unsigned long length);
    const enum_field_types getType() const{return _type;}
	char* getData() const
	{
		return _data;
	}
	std::string GetValueAsString();
	int GetValueAsInt();
	~Field()
	{
	}
private:
    /*le type de données du champ*/
    enum_field_types _type;
    /*les données*/
    char* _data;
	/*la longueur de donnée*/
	unsigned long _length;


};
/*
@class Row
@brief classe représentant une ligne d'enregistrement MySQL
*/
class Row
{
public:
    /*
     @fn Row(unsigned int fieldCount)
     @params fieldCount le nombre de champ dans la ligne
     @brief constructeur
     @return no return
     */
    Row(unsigned int fieldCount);
    /*
    @fn bool setValue(unsigned int fieldIndex,MYSQL_FIELD& field,char* data)
    @params fieldIndex l'index du champ sur la ligne
            field une reference sur une structure MYSQL_FIELD
            data une chaine de caractère contenant les données
    @brief méthode qui permet de définir la valeur d'un index
           retourne true si succes
           retourne false dans le cas contraire
    @return bool
    */
    bool setValue(unsigned int fieldIndex, MYSQL_FIELD& field,char* data);
    /*
     @fn Field* getField(unsigned int fieldIndex)
     @params fieldIndex l'index du champ que l'on veut récupérer
     @brief méthode permettant d'accéder au champ dont l'index est FieldIndex
            retourne un pointeur sur le champ désiré ou nullptr
     @return Field
     */
    Field* getField(unsigned int fieldIndex);
	unsigned int getFieldCount()const
	{
		return _fieldCount;
	}
private:
    std::vector<Field> _fieldVector;
    unsigned int _fieldCount;
};
/*
@class ResultSet
@brief classe représentant un résultat d'une requete SQL
*/
class ResultSet
{
public:
    ResultSet(MYSQL_RES* result);
    /*
     @fn bool loadData()
     @params no params
     @brief methode qui charge les données de la structure passée en paramètre de la classe
            retourne true si le chargement est un succès
            retourne false dans le cas contraire
     @return bool
     */
    bool loadData();
	unsigned int getRowCount() const
	{
		return _rowCount;
	}
	Row* getRow(unsigned int index);
    ~ResultSet();
private:
    /*un pointeur sur la structure contenant les données*/
    MYSQL_RES* _result;
    /*le nombre de ligne*/
    unsigned int _rowCount;
    /*le nombre de champs*/
    unsigned int _fieldCount;
    /*le vecteur contenant les lignes et leurs données*/
    std::vector<Row> _rowVector;

};
#endif
