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
#include "Portal.hpp"
#include "Error.hpp"
#include "Recorder.hpp"
#include <boost/smart_ptr.hpp>


namespace Circulate
{
    class Component
    {
    public:
        virtual ~Component();
        
        virtual void initialise(Portal & portal) = 0;
        virtual void preTimestepOps() = 0;
        virtual bool step() = 0;
        virtual void postTimestepOps() = 0;
        virtual void finalise() = 0;
        
        virtual void print(std::ostream & out) const = 0;
        virtual Recorder & results() const = 0;

        
        virtual int getInt(const std::string & param) const throw (UndefinedCodeException) = 0;
        virtual double getDouble(const std::string & param) const throw (UndefinedCodeException) = 0;
        virtual std::string getString(const std::string & param) const throw (UndefinedCodeException) = 0;
        virtual bool getBool(const std::string & param) const throw (UndefinedCodeException) = 0;
        
        virtual void setInt(const std::string & param, int value) throw (UndefinedCodeException) = 0;
        virtual void setDouble(const std::string & param, double & value)  throw (UndefinedCodeException) = 0;
        virtual void setString(const std::string & param, std::string & value)  throw (UndefinedCodeException) = 0;
        virtual void setBool(const std::string & param, bool value)  throw (UndefinedCodeException) = 0;
        
        virtual std::string id() const = 0;
        virtual std::string type() const = 0;
        
    };
    
    typedef boost::shared_ptr< Component > ComponentSPtr;
    typedef boost::weak_ptr< Component > ComponentWPtr;
}





#endif /* COMPONENT_H_ */
