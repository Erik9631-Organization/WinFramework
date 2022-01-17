#pragma once
#include "Primitive.h"

class Field : public Primitive
{
private:
	void* fieldAddress;
public:
	Field(std::string name, void* field);

	template<typename Type>
	void SetValue(Type value);

	template<typename Type>
	Type GetValue();
};

inline Field::Field(std::string name, void* field) : Primitive(name)
{
	fieldAddress = field;
}


template<typename Type>
void Field::SetValue(Type value)
{
	Type* valueReference = (Type*)fieldAddress;
	*valueReference = value;
}

template<typename Type>
Type Field::GetValue()
{
	return (Type)fieldAddress;
}
