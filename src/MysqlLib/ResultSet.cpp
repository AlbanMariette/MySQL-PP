#include "ResultSet.h"

Field::Field() : _type(),_data(nullptr)
{

}
void Field::setType(enum_field_types type)
{
    _type = type;
}
void Field::setData(char* data, unsigned long length)
{
	_data = new char[strlen(data)];
	memcpy(_data, data, strlen(data)+1);
}
std::string Field::GetValueAsString()
{
	if (!_data)
		return "";
	const char* cString = static_cast<char const*>(_data);
	return std::string(cString, strlen(cString));
}
int Field::GetValueAsInt()
{
	if (!_data)
		return 0;
	return static_cast<int32>(strtol((char*)_data, NULL, 10));
}
Row::Row(unsigned int fieldCount) : _fieldVector(), _fieldCount(fieldCount)
{
    //TODO: check si fieldCount est nul erreur
    _fieldVector.resize(fieldCount);
}


bool Row::setValue(unsigned int fieldIndex, MYSQL_FIELD& field,char* data)
{
	if (fieldIndex >= _fieldVector.size())//fieldIndex doit etre compris entre 0 inclus et fieldCount exclus
		return false;

	// This value stores somewhat structured data that needs function style casting
    _fieldVector.at(fieldIndex).setType(field.type);
    _fieldVector.at(fieldIndex).setData(data,field.length);
    return true;
}

Field* Row::getField(unsigned int fieldIndex)
{
    if(fieldIndex>=_fieldVector.size())//fieldIndex doit etre compris entre 0 inclus et fieldCount exclus
    return nullptr;
    return &_fieldVector.at(fieldIndex);
}
ResultSet::ResultSet(MYSQL_RES* result) : _result(result), _rowVector()
{
    if(_result)
    {
		_fieldCount = mysql_num_fields(_result);
		_rowCount = mysql_num_rows(_result);
        //on prépare la structure de ligne
        _rowVector.clear();
        //on prépare le tableau dans lequel on va stocker les lignes
        for(unsigned int i =0;i<_rowCount;i++)
        {
            _rowVector.push_back((_fieldCount));
        }
    }
}
bool ResultSet::loadData()
{
	if (!_result)
		return false;
	MYSQL_ROW row = NULL;
	unsigned int rowCounter = 0;
	MYSQL_FIELD *field = mysql_fetch_field(_result);
	while ((row = mysql_fetch_row(_result)))
	{
		//On fait une boucle pour avoir la valeur de chaque champs
		for (unsigned int i = 0; i < _fieldCount; i++)
		{
			//on ajoute la valeur à la ligne
			_rowVector.at(rowCounter).setValue(i, field[i], row[i]);
			std::cout << row[i] << std::endl;
		}
		rowCounter++;
	}
	return true;
}
Row* ResultSet::getRow(unsigned int index)
{
	if (index >= _rowVector.size())
		return nullptr;
	return &_rowVector.at(index);
}
ResultSet::~ResultSet()
{
    mysql_free_result(_result);
}
