//
//  LinkFactoryInterface.hpp
//  CirculateCore
//
//  Created by a1091793 on 17/01/2016.
//
//

#ifndef LinkFactoryInterface_hpp
#define LinkFactoryInterface_hpp


#include "Component.hpp"

namespace Circulate
{
    class LinkFactoryInterface
    {
    public:
        
        virtual ~LinkFactoryInterface() {}
        
        virtual FacilityISPtr createInstance(std::string _id, Portal & portal, std::string _startNodeID, std::string _endNodeID,
                                             std::string _status, SEWRgrph & graph, std::string _constructor) = 0;
        
        virtual void destroyInstance(std::string _id) = 0;
        
        virtual QString typify() = 0;
    };
}

#define LinkFactoryInterface_iid "au.edu.adelaide.civeng.iuwmod.LinkFactoryInterface/1.0"
Q_DECLARE_INTERFACE(Circulate::LinkFactoryInterface, LinkFactoryInterface_iid)


#endif //LinkFactoryInterface_hpp