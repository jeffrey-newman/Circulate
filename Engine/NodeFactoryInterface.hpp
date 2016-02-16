//
//  NodeFactoryInterface.hpp
//  CirculateCore
//
//  Created by a1091793 on 17/01/2016.
//
//

#ifndef NodeFactoryInterface_hpp
#define NodeFactoryInterface_hpp

#include "Component.hpp"

namespace Circulate
{
    class NodeFactoryInterface
    {
    public:
        
        virtual ~ NodeFactoryInterface() {}
        
        virtual FacilityISPtr createInstance(std::string _id, SharedData & shared_data, double _xCoord, double _yCoord, SEWRgrph & graph,std::string _constructor) = 0;
        
        virtual void destroyInstance(std::string _id) = 0;
        
        virtual QString typify() = 0;
    };
}

#define NodeFactoryInterface_iid "au.edu.adelaide.civeng.iuwmod.NodeFactoryInterface/1.0"
Q_DECLARE_INTERFACE(Circulate::NodeFactoryInterface, NodeFactoryInterface_iid)

#endif //NodeFactoryInterface_hpp