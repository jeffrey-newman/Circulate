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
        
        virtual void print(std::ostream & out) = 0;
        virtual DataType results() = 0;
        
        virtual int getInt(const std::string & param) = 0;
        virtual double getDouble(const std::string & param) = 0;
        virtual std::string getString(const std::string & param) = 0;
        virtual bool getBool(const std::string & param) = 0;
        
        virtual void setInt(const std::string & param, int value) = 0;
        virtual void setDouble(const std::string & param, double & value) = 0;
        virtual void setString(const std::string & param, std::string & value)  = 0;
        virtual void setBool(const std::string & param, bool value)  = 0;
        
        virtual std::string makeLabel() const = 0;
        
    };
    
    typedef boost::shared_ptr< Node > NodeSPtr;
    typedef boost::weak_ptr< Node > NodeWPtr;
    
   


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

#endif /* NodeBase_h */
