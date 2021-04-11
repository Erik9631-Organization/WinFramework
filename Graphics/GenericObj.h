#pragma once
class GenericObj
{
private:
	void* originalObj;
	void (*CastToOriginalTypeInstance)(void*);
	template<typename originalType>
	static void CastToOriginalType(void* obj)
	{
		throw static_cast<originalType*>(obj);
	}
public:
	template<typename originalType>
	GenericObj(originalType* obj) : originalObj(obj), CastToOriginalTypeInstance((void (*) (void*)) CastToOriginalType<originalType>)
	{

	}

	template<typename type>
	type* Get()
	{
		try
		{
			CastToOriginalTypeInstance(originalObj);
		}
		catch (type* castedType)
		{
			return castedType;
		}
	}
};
