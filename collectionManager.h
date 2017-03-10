#ifndef COLLECTIONMANAGER_H
#define COLLECTIONMANAGER_H

namespace cm {
      struct card {
        std::string name;
        std::string id;
        std::string className;
        int count;
    };

    extern std::vector<card> collection;

    void fillSearchCollection();
}

#endif 