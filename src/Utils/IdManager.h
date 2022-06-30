//
// Created by Erik on 29/06/22.
//

#ifndef LII_IDMANAGER_H
#define LII_IDMANAGER_H
#include <vector>
#include <unordered_set>


class IdManager
{
public:
    IdManager(const unsigned int &size);
    unsigned int maxSize = 0;
    IdManager();
    unsigned int AquireId();
    unsigned int FreeId(const unsigned int& id);
private:
    unsigned int idGenerator = -1;
    std::unordered_set<unsigned int> idList;
};


#endif //LII_IDMANAGER_H
