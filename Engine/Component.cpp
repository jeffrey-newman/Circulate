/*
 * ComponentBase.cpp
 *
 *  Created on: Jul 21, 2011
 *      Author: jnewman
 */

#include "Component.hpp"
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

namespace Circulate
{

   ComponentBase::~ComponentBase()
      {
//         std::cout << "***************************************************\n";
//                     std::cout << "****  DESTROYING ComponentBase " << this->name() << std::endl;
//                     std::cout << "***************************************************\n";
      }

    ComponentBase::ComponentBase(std::string _id, std::string _type)
    : name(_id), type(_type)
    {

    }

    void
    ComponentBase::print(std::ostream& out) const
    {

    }

//    void
//    ComponentBase::print(SQL_db_Sptr sql) const
//    {
//
//    }

    void
    ComponentBase::print(H5::H5File h5) const
    {

    }

    void
    ComponentBase::initialise(CirculateGraph & grph)
    {
        //      link_records.clear();
    }

    void
    ComponentBase::finalise(CirculateGraph & grph)
    {
        //do nothing...
    }

    int
    ComponentBase::getInt(const std::string & param) const throw (UndefinedCodeException)
    {
        throw UndefinedCodeException(
                                     "Code " + boost::lexical_cast<std::string > (param)
                                     + " undefined for " + name() + " of type " + type());
    }

    double
    ComponentBase::getDouble(const std::string & param) const throw (UndefinedCodeException)
    {
        throw UndefinedCodeException(
                                     "Code " + boost::lexical_cast<std::string > (param)
                                     + " undefined for " + name() + " of type " + type());
    }

    std::string
    ComponentBase::getString(const std::string & param) const throw (UndefinedCodeException)
    {
        if (boost::iequals(param, "ID"))
        {
            return this->name();
        } else if (boost::iequals(param, "TYPE"))
        {
            return this->type();
        } else
        {
            throw UndefinedCodeException(
                                         "Code " + boost::lexical_cast<std::string > (param)
                                         + " undefined for " + name() + " of type " + type());
        }
    }

    bool
    ComponentBase::getBool(const std::string & param) const throw (UndefinedCodeException)
    {
        throw UndefinedCodeException(
                                     "Code " + boost::lexical_cast<std::string > (param)
                                     + " undefined for " + name() + " of type " + type());
    }

    void
    ComponentBase::preTimestepOps(CirculateGraph & grph)
    {
    }

    void
    ComponentBase::postTimestepOps(CirculateGraph & grph)
    {

    }

    void
    ComponentBase::setInt(const std::string & param, int value)
    throw (UndefinedCodeException)
    {
        throw UndefinedCodeException(
                                     "Code " + boost::lexical_cast<std::string > (param)
                                     + " undefined for " + name() + " of type " + type());
    }

    void
    ComponentBase::setDouble(const std::string & param, double & value)
    throw (UndefinedCodeException)
    {
        throw UndefinedCodeException(
                                     "Code " + boost::lexical_cast<std::string > (param)
                                     + " undefined for " + name() + " of type " + type());

    }

    void
    ComponentBase::setString(const std::string & param, std::string & value)
    throw (UndefinedCodeException)
    {

    }

    void
    ComponentBase::setBool(const std::string & param, bool value)
    throw (UndefinedCodeException)
    {
        throw UndefinedCodeException(
                                     "Code " + boost::lexical_cast<std::string > (param)
                                     + " undefined for " + name() + " of type " + type());
    }

    std::string
    ComponentBase::makeLabel() const
       {
          return (this->name());
       }

}

