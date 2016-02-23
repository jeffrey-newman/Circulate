//
//  NodeBase.hpp
//  CirculateCore
//
//  Created by a1091793 on 17/01/2016.
//
//

#ifndef NodeBase_h
#define NodeBase_h

#include "Component.hpp"

namespace Circulate
{
    
    
    class Node : public Component
    {
    public:
        virtual Record flowIn() = 0;
        virtual Record flowOut() = 0;
        virtual double flowDepth() = 0;
        virtual double surfaceElevation() = 0;
        virtual double entranceDepth() = 0;
        virtual double exitDepth() = 0;
        virtual double baseDepth() = 0;
        virtual double baseElevation() = 0; /**<deprecated */
        virtual double entranceElevation() = 0; /**< deprecated */
        virtual double exitElevation() = 0; /**< deprecated */
        virtual CirculateGraph::NodeID node_id() = 0;
        virtual double xCoord() = 0;
        virtual double yCoord() = 0;
        
        virtual bool isStorage() = 0;
        virtual bool isSupply() = 0;
        virtual bool isDemand() = 0;
        virtual bool isOutfall() = 0;
        virtual bool isInfall() = 0;
        
        virtual bool hasConverged() = 0;
        
        virtual ~Node() {}
        
        virtual double request(double amount) = 0;
        
        virtual void initialise(std::string const_str) = 0;
        virtual void preTimestepOps() = 0;
        virtual bool step() = 0;
        virtual void postTimestepOps() = 0; //such as recording results
        virtual void finalise() = 0;
        
        virtual void print(std::ostream & out) const = 0;
        virtual Recorder & results() const = 0;
        
        virtual int getInt(const std::string & param) const throw (UndefinedCodeException) = 0;
        virtual double getDouble(const std::string & param) const throw (UndefinedCodeException) = 0;
        virtual std::string getString(const std::string & param) const throw (UndefinedCodeException) = 0;
        virtual bool getBool(const std::string & param) const throw (UndefinedCodeException) = 0;
        
        virtual void setInt(const std::string & param, int value) throw (UndefinedCodeException) = 0;
        virtual void setDouble(const std::string & param, double & value) throw (UndefinedCodeException) = 0;
        virtual void setString(const std::string & param, std::string & value)  throw (UndefinedCodeException) = 0;
        virtual void setBool(const std::string & param, bool value) throw (UndefinedCodeException)  = 0;
        
        virtual std::string makeLabel() const = 0;
        
    };
    
    typedef boost::shared_ptr< Node > NodeSPtr;
    typedef boost::weak_ptr< Node > NodeWPtr;
    
   
}

#endif //NodeBase_h


