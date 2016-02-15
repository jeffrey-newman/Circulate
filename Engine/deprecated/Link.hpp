/* 
 * File:   Conduit.h
 * Author: jnewman
 *
 * Created on September 28, 2010, 9:08 AM
 */

#ifndef CONDUIT_H
#define	CONDUIT_H

#include <ostream>
#include <boost/smart_ptr.hpp>
#include "../engine/Component.h"

namespace Circulate
{

    //      struct LinkData
    //         {
    //         LinkData(int _time, double _upstreamflow, double _downstreamflow,
    //               double _upstreamflowdepth, double _downstreamflowdepth,
    //               double _upstreamflowvelocity, double _downstreamflowvelocity) :
    //               time(_time), upstreamflow(_upstreamflow), downstreamflow(
    //                     _downstreamflow), upstreamflowDepth(_upstreamflowdepth), downstreamflowDepth(
    //                     _downstreamflowdepth), upstreamflowVelocity(
    //                     _upstreamflowvelocity), downstreamflowVelocity(
    //                     _downstreamflowvelocity)
    //            {
    //
    //            }
    //         int time;
    //         double upstreamflow;
    //         double downstreamflow;
    //         double upstreamflowDepth;
    //         double downstreamflowDepth;
    //         double upstreamflowVelocity;
    //         double downstreamflowVelocity;
    //         };
    
    
    class Link
    {
        
    };
    

    class Link : public Component
    {
    public:
        // property< std::string > id;
        property< CirculateGraph::LinkID > link_id;
        //  property< std::string > type;
        property< std::string > startNodeID;
        property< std::string > endNodeID;
        property< std::string > status;
        Record upstreamflow;
        Record downstreamflow;
        property< double, nonnegative< double > > upstreamflowDepth;
        property< double, nonnegative< double > > downstreamflowDepth;
        property< double, nonnegative< double > > upstreamflowVelocity;
        property< double, nonnegative< double > > downstreamflowVelocity;
        //  property< int > err;
        
        
        property < bool > isSupply;
        property < bool > isDemand;

        Link(CirculateGraph & _graph, std::string _id, std::string _type,
             std::string _startNodeID, std::string _endNodeID,
             std::string _status);

        Link(CirculateGraph & _graph, std::string _id, std::string _type,
             std::string _startNodeID, std::string _endNodeID,
             std::string _status, bool _isSupplyLink, bool _isDemandLink);
        
        virtual void
        initialise(CirculateGraph & grph);
        virtual void
        preTimestepOps(CirculateGraph & grph);
        virtual bool
        operator ()(CirculateGraph & grph) = 0;
        virtual void
        postTimestepOps(CirculateGraph & grph); //such as recording results
        virtual void
        finalise(CirculateGraph & grph);

        virtual void
        print(std::ostream & out) const; //print results to text file
//        virtual void
//        print(SQL_db_Sptr sql) const; //print results to database
        virtual void
        print(H5::H5File h5) const; // The new file format (faster... hopefully?)

        virtual int
        getInt(const std::string & param) const throw (UndefinedCodeException);
        virtual double
        getDouble(const std::string & param) const throw (UndefinedCodeException);
        virtual std::string
        getString(const std::string & param) const throw (UndefinedCodeException);
        virtual bool
        getBool(const std::string & param) const throw (UndefinedCodeException);

        virtual void
        setInt(const std::string & param, int value) throw (UndefinedCodeException);
        virtual void
        setDouble(const std::string & param, double & value)
        throw (UndefinedCodeException);
        virtual void
        setString(const std::string & param, std::string & value)
        throw (UndefinedCodeException);
        virtual void
        setBool(const std::string & param, bool value) throw (UndefinedCodeException);

        virtual std::string
        makeLabel() const;

    protected:

    private:
        //        std::vector< LinkData > link_records;

    };
    typedef boost::shared_ptr< Link > LinkSPtr;
    typedef boost::weak_ptr< Link > LinkWPtr;
}

#endif	/* CONDUIT_H */

//
//  FacilityFactoryInterfance.h
//
//
//  Created by Jeffrey Newman on 10/07/13.
//
//

#ifndef _LinkFactoryInterfance_h
#define _LinkFactoryInterfance_h

namespace Circulate
{
        class LinkFactoryInterface
        {
        public:
            
            virtual ~ LinkFactoryInterface() {}
            
            virtual FacilityISPtr createInstance(std::string _id, SharedData & shared_data, std::string _constructor) = 0;
            
            virtual void destroyInstance(std::string _id) = 0;
            
            virtual QString typify() = 0;
        };
        
        
    }
}

#define FacilityFactoryInterface_iid "au.edu.adelaide.civeng.iuwmod.FacilityFactoryInterface/1.0"

Q_DECLARE_INTERFACE(Circulate::WaterUseModel::FacilityFactoryInterface, FacilityFactoryInterface_iid)


#endif

