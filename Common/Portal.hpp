//
//  Portal.hpp
//  CirculateCommon
//
//  Created by a1091793 on 16/02/2016.
//
//

#ifndef Portal_hpp
#define Portal_hpp

#include <string>
#include "Node.hpp"
#include "Link.hpp"
#include "Time.hpp"
#include <boost/weak_ptr.hpp>

namespace Circulate
{
    class Portal
    {
        //Map of links SPtr and nodes SPtr
        std::map<std::string, NodeSPtr> nodes;
        std::map<std::string, LinkSPtr> links;
                
        //Circulate Clock
        CirculateClock & clock;
        
        
    public:
        
        Portal();
        double now();
        double timeInDay();
        NodeWPtr getNode(std::string id);
        LinkWPtr getLink(std::string id);
        void assignNode(std::string id, NodeSPtr node);
        void assignLink(std::string id, LinkSPtr link);
        
    };
}



#endif /* Portal_hpp */
