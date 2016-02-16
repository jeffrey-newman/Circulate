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

class Portal {
  //Map of links SPtr
  //Map of nodes SPtr
    
  //Circulate Clock

public:
    double now();
    double timeInDay();
    NodeWPtr getNode(std::string id);
    LinkWPtr getLink(std::string id);
    void assignNode(std::string id, NodeSPtr node);
    void assignLink(std::string id, LinkSPtr link);
    
};

#endif /* Portal_hpp */
