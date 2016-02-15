/* 
 * File:   node.h
 * Author: jnewman
 *
 * Created on September 28, 2010, 12:47 PM
 */

#ifndef NODE_H
#define	NODE_H

#include <ostream>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <boost/smart_ptr.hpp>
#include "../engine/Component.h"
#include "../utils/property.h"
#include "../engine/CirculateGraph.h"
#include "../utils/RuntimeErrors.h"
#include "../data/SharedData.h"
//#include "../engine/hydraulicSolver.h"
//#include "../data/external/sewernet_soci.h"

namespace Circulate
{

    //      struct NodeData
    //         {
    //         NodeData(int _time, double _flowIn, double _flowOut, double _flowDepth) :
    //               time(_time), flowIn(_flowIn), flowOut(_flowOut), flowDepth(
    //                     _flowDepth)
    //            {
    //            }
    //         int time;
    //         double flowIn;
    //         double flowOut;
    //         double flowDepth;
    //         };
    
    class Node : public Component
    {
    public:
        virtual ~Node();
        virtual double request(double amount) = 0;
        
        virtual void initialise(CirculateGraph & grph) = 0;
        virtual void preTimestepOps(CirculateGraph & grph) = 0;
        virtual bool operator ()(CirculateGraph & grph) = 0;
        virtual void postTimestepOps(CirculateGraph & grph) = 0; //such as recording results
        virtual void finalise(CirculateGraph & grph) = 0;
        
        virtual void print(std::ostream & out) const = 0;
        virtual void print(H5::H5File h5) const = 0;
        
        virtual int getInt(const std::string & param) const throw (UndefinedCodeException) = 0;
        virtual double getDouble(const std::string & param) const throw (UndefinedCodeException) = 0;
        virtual std::string getString(const std::string & param) const throw (UndefinedCodeException) = 0;
        virtual bool getBool(const std::string & param) const throw (UndefinedCodeException) = 0;
        
        virtual void setInt(const std::string & param, int value) throw (UndefinedCodeException) = 0;
        virtual void setDouble(const std::string & param, double & value) throw (UndefinedCodeException) = 0;
        virtual void setString(const std::string & param, std::string & value) throw (UndefinedCodeException) = 0;
        virtual void setBool(const std::string & param, bool value) throw (UndefinedCodeException) = 0;
        
        virtual std::string makeLabel() const = 0;
        
        
        

//        
//        /**
//         * Old constructor for backward compatibility
//         * @param _id
//         * @param _type
//         * @param _xCoord
//         * @param _yCoord
//         */
//        Node(std::string _id, SharedData & _shared_data,  std::string _type, double _xCoord = 0,
//             double _yCoord = 0);
//        
//        /**
//         * New constructor
//         * @param amount
//         * @return
//         */
//        Node(std::string _id, SharedData & _shared_data, std::string _type,
//             bool _isDemand, bool _isStorage, bool _isSupply, bool _isOutfall, bool _isInfall,
//             double _xCoord = 0, double _yCoord = 0
//             );
        
        
    };
    
    typedef boost::shared_ptr< Node > NodeSPtr;
    typedef boost::weak_ptr< Node > NodeWPtr;

    class Node : public Component
    {
    public:
        Record flowIn;
        Record flowOut;
        property< double > flowDepth;
        property< double > surfaceElevation;
        property< double > entranceDepth;
        property< double > exitDepth;
        property< double > baseDepth;
        property< double > baseElevation; /**<deprecated */
        property< double > entranceElevation; /**< deprecated */
        property< double > exitElevation; /**< deprecated */
        property< CirculateGraph::NodeID > node_id;
        property< double > xCoord;
        property< double > yCoord;
        
        property< bool > isStorage;
        property< bool > isSupply;
        property< bool > isDemand;
        property< bool > isOutfall;
        property< bool > isInfall;

        property< bool > hasConverged;

        /**
         * Old constructor for backward compatibility
         * @param _id
         * @param _type
         * @param _xCoord
         * @param _yCoord
         */
        Node(std::string _id, SharedData & _shared_data,  std::string _type, double _xCoord = 0,
             double _yCoord = 0);
        
        /**
         * New constructor
         * @param amount
         * @return 
         */
        Node(std::string _id, SharedData & _shared_data, std::string _type,
               bool _isDemand, bool _isStorage, bool _isSupply, bool _isOutfall, bool _isInfall,
               double _xCoord = 0, double _yCoord = 0
               );

        virtual
        ~Node();

        /**
         * To determine whether this node can supply how much water you wish to take from it
         * @param amount the amount of water. 
         * @return 0.000 if request is not possible, otherwise the amount of water that can be requested if the request is possible
         * @details If returns true, the amount you request is registered, thereby reducing the available water for other subsequent requesting nodes.
         */
        virtual double
        request(double amount);

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
        //        void
        //        record();
        //        SQL_db_Sptr sql;
    protected:
        SharedData & shared_data;

    private:
        //        std::vector< NodeData > node_records;

    };

    typedef boost::shared_ptr< Node > NodeSPtr;
    typedef boost::weak_ptr< Node > NodeWPtr;
}

#endif	/* NODE_H */

#ifndef _NodeFactoryInterfance_h
#define _NodeFactoryInterfance_h

namespace Circulate
{
    class NodeFactoryInterface
    {
    public:
        
        virtual ~ NodeFactoryInterface() {}
        
        virtual FacilityISPtr createInstance(std::string _id, SharedData & shared_data, std::string _constructor) = 0;
        
        virtual void destroyInstance(std::string _id) = 0;
        
        virtual QString typify() = 0;
    };
    
    
}
}

#define FacilityFactoryInterface_iid "au.edu.adelaide.civeng.iuwmod.FacilityFactoryInterface/1.0"

Q_DECLARE_INTERFACE(Circulate::WaterUseModel::FacilityFactoryInterface, FacilityFactoryInterface_iid)


#endif

