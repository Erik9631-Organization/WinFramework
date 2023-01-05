//
// Created by erik9 on 1/5/2023.
//

#ifndef LII_PROPERTYMESSAGE_H
#define LII_PROPERTYMESSAGE_H
#include <memory>

template<class PropertyType>
class PropertyMessage
{
private:
    unsigned long long propertyId;
    PropertyType propertyData;
public:
    PropertyMessage(const unsigned long long propertyId, const PropertyType propertyData)
    {
        this->propertyId = propertyId;
        this->propertyData = propertyData;
    }

    const unsigned long long& GetPropertyId() const
    {
        return propertyId;
    }

    const PropertyType& GetPropertyData() const
    {
        return propertyData;
    }
};

};

#endif //LII_PROPERTYMESSAGE_H
