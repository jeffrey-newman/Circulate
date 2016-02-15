/*
 * Component.h
 *
 *  Created on: Jul 20, 2011
 *      Author: jnewman
 */

#ifndef COMPONENT_H_
#define COMPONENT_H_

/*
 * File:   Conduit.h
 * Author: jnewman
 *
 * Created on September 28, 2010, 9:08 AM
 */


#include <ostream>
#include <string>
#include "CirculateGraph.hpp"
//#include "../utils/RuntimeErrors.h"
//#include "../utils/PhysicalConstants.h"
//#include "../engine/hydraulicSolver.h"
//#include "../utils/property.h"
//#include "../data/external/sewernet_soci.h"
//#include "../data/external/hdf5-1.8.12/src/hdf5.h"
//#include "../data/external/hdf5-1.8.12/c++/src/H5Cpp.h"
//#include "../data/external/hdf5-1.8.12/hl/src/hdf5_hl.h"
#include "../Common/Common.hpp"


namespace Circulate
{
    class Component
    {
    public:
        virtual ~Component();
        
        virtual void initialise(CirculateGraph & grph) = 0;
        virtual void preTimestepOps(CirculateGraph & grph) = 0;
        virtual bool step(CirculateGraph & grph) = 0;
        virtual void postTimestepOps(CirculateGraph & grph) = 0;
        virtual void finalise(CirculateGraph & grph) = 0;
        
        virtual void print(std::ostream & out) = 0;
        virtual DataType results() = 0;

        
        virtual int getInt(const std::string & param) = 0;
        virtual double getDouble(const std::string & param) = 0;
        virtual std::string getString(const std::string & param) = 0;
        virtual bool getBool(const std::string & param) = 0;
        
        virtual void setInt(const std::string & param, int value) = 0;
        virtual void setDouble(const std::string & param, double & value) = 0;
        virtual void setString(const std::string & param, std::string & value) = 0;
        virtual void setBool(const std::string & param, bool value) =0;
        
        virtual std::string makeLabel() = 0;
        
    };
    
    

    class ComponentBase : private Component
    {
    public:
        property< std::string > name;
        property< std::string > type;
        property< int > err;

        ComponentBase(std::string _id, std::string _type);

        virtual ~Component();

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
        print(std::ostream & out);
        
        virtual DataType
        results();
        
        virtual int
        getInt(const std::string & param);
        
        virtual double
        getDouble(const std::string & param);
        
        virtual std::string
        getString(const std::string & param);
        
        virtual bool
        getBool(const std::string & param);

        virtual void
        setInt(const std::string & param, int value);
        
        virtual void
        setDouble(const std::string & param, double & value);
        
        virtual void
        setString(const std::string & param, std::string & value);
        
        virtual void
        setBool(const std::string & param, bool value);


        virtual std::string
        makeLabel() const;


    protected:
        //        SQL_db_Sptr sql;

    private:
        //        std::vector< LinkData > link_records;

    };
}





#endif /* COMPONENT_H_ */
