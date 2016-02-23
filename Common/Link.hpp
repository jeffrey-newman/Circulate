//
//  LinkBase.hpp
//  CirculateCore
//
//  Created by a1091793 on 17/01/2016.
//
//

#ifndef LinkBase_h
#define LinkBase_h


#include "Component.hpp"

namespace Circulate
{

    
    class Node;
    typedef boost::shared_ptr< Node > NodeSPtr;
    typedef boost::weak_ptr< Node > NodeWPtr;
    
    class Link;

    
    
    class Link : public Component
    {
    public:
        
        /* Not sure if I need or want all of these variables/functions */
//        std::string id() = 0;
//        CirculateGraph::LinkID linkId() = 0
//        std::string type() = 0;
//        std::string startNodeID() = 0;
//        std::string endNodeID() = 0;
//        std::string status() = 0;
//        Record upstreamflow() = 0;
//        Record downstreamflow() = 0;
//        double upstreamflowDepth() = 0;
//        double downstreamflowDepth() = 0;
//        double upstreamflowVelocity() = 0;
//        double downstreamflowVelocity() = 0;
        
        virtual bool
        isSupply() = 0;
        
        virtual bool
        isDemand() = 0;
        
        virtual ~Link() {}
        
//        Link(CirculateGraph & _graph, std::string _id, std::string _type,
//             std::string _startNodeID, std::string _endNodeID,
//             std::string _status);
//        
//        Link(CirculateGraph & _graph, std::string _id, std::string _type,
//             std::string _startNodeID, std::string _endNodeID,
//             std::string _status, bool _isSupplyLink, bool _isDemandLink);
        
        virtual void
        initialise(std::string & const_string) = 0;
        
//        virtual void
//        initialise_within_graph()
        
        virtual void
        preTimestepOps() = 0;
        virtual bool
        step(CirculateGraph & grph) = 0;
        virtual void
        postTimestepOps(CirculateGraph & grph) = 0; //such as recording results
        virtual void
        finalise(CirculateGraph & grph) = 0;
        
        virtual void print(std::ostream & out) const = 0;
        virtual Recorder & results() const = 0;
        
        virtual int
        getInt(const std::string & param) const throw (UndefinedCodeException) = 0;
        virtual double
        getDouble(const std::string & param) const throw (UndefinedCodeException) = 0;
        virtual std::string
        getString(const std::string & param) const throw (UndefinedCodeException) = 0;
        virtual bool
        getBool(const std::string & param) const throw (UndefinedCodeException)  = 0;
        
        virtual void
        setInt(const std::string & param, int value) throw (UndefinedCodeException) = 0;
        virtual void
        setDouble(const std::string & param, double & value) throw (UndefinedCodeException) = 0;
        virtual void
        setString(const std::string & param, std::string & value) throw (UndefinedCodeException) = 0;
        virtual void
        setBool(const std::string & param, bool value) throw (UndefinedCodeException) = 0;
        
        virtual std::string id() const = 0;
        virtual std::string type() const = 0;
        
        
    };
    
    typedef boost::shared_ptr< Link > LinkSPtr;
    typedef boost::weak_ptr< Link > LinkWPtr;
    
    
}


#endif /* LinkBase_h */
