//
// Created by Erik on 16/04/22.
//

#ifndef LII_AUTOID_H
#define LII_AUTOID_H

namespace Utils
{
    class AutoId
    {
    private:
        static unsigned long long int id;
    public:
        static unsigned long long int AquireId();
        static void Reset(const unsigned long long int &id = 0);
    };

}


#endif //LII_AUTOID_H
