//
//  Portal.cpp
//  CirculateCommon
//
//  Created by a1091793 on 16/02/2016.
//
//

#include "Portal.hpp"

namespace Circulate
{
    Portal::Portal():
    clock(CirculateClock::getInstance())
    {
        
    }
    
    double
    Portal::now()
    {
        return (clock.now());
    }
    
    double
    Portal::timeInDay()
    {
        return (clock.timeInDay());
    }
    
    NodeWPtr
    Portal::getNode(std::string id)
    {
        std::map<std::string, NodeSPtr>::iterator it = nodes.find(id);
        if (it != nodes.end())
        {
            return NodeWPtr(it->second);
        }
    }
    
    LinkWPtr
    Portal::getLink(std::string id)
    {
        std::map<std::string, LinkSPtr>::iterator it = links.find(id);
        if (it != links.end())
        {
            return LinkWPtr(it->second);
        }
    }
    
    void
    Portal::assignNode(std::string id, NodeSPtr node)
    {
        nodes.insert(std::make_pair(id, node));
    }
    
    void
    Portal::assignLink(std::string id, LinkSPtr link)
    {
        links.insert(std::make_pair(id, link));
    }
}

