//
//  ComponentBase.cpp
//  CirculateCore
//
//  Created by a1091793 on 16/02/2016.
//
//

#include "ComponentBase.hpp"

namespace Circulate
{
    
    ComponentBase::~ComponentBase()
    {
        //         std::cout << "***************************************************\n";
        //                     std::cout << "****  DESTROYING ComponentBase " << this->name() << std::endl;
        //                     std::cout << "***************************************************\n";
    }
    
    ComponentBase::ComponentBase(std::string _id, std::string _type)
    : m_name(_id), m_type(_type)
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
    
    //    void
    //    ComponentBase::print(H5::H5File h5) const
    //    {
    //
    //    }
    
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
        UndefinedCodeException ex(
                                  "Code " + boost::lexical_cast<std::string > (param)
                                  + " undefined for " + id() + " of type " + type());
        throw ex;
    }
    
    double
    ComponentBase::getDouble(const std::string & param) const throw (UndefinedCodeException)
    {
        UndefinedCodeException ex(
                                  "Code " + boost::lexical_cast<std::string > (param)
                                  + " undefined for " + id() + " of type " + type());
        throw ex;
    }
    
    std::string
    ComponentBase::getString(const std::string & param) const throw (UndefinedCodeException)
    {
        if (boost::iequals(param, "ID"))
        {
            return this->id();
        } else if (boost::iequals(param, "TYPE"))
        {
            return this->type();
        } else
        {
            UndefinedCodeException ex(
                                      "Code " + boost::lexical_cast<std::string > (param)
                                      + " undefined for " + id() + " of type " + type());
            throw ex;
        }
    }
    
    bool
    ComponentBase::getBool(const std::string & param) const throw (UndefinedCodeException)
    {
        UndefinedCodeException ex("Code " + boost::lexical_cast<std::string > (param) + " undefined for " + id() + " of type " + type());
        throw ex;
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
        UndefinedCodeException ex(
                                  "Code " + boost::lexical_cast<std::string > (param)
                                  + " undefined for " + id() + " of type " + type());
        throw ex;
    }
    
    void
    ComponentBase::setDouble(const std::string & param, double & value)
    throw (UndefinedCodeException)
    {
        UndefinedCodeException ex(
                                  "Code " + boost::lexical_cast<std::string > (param)
                                  + " undefined for " + id() + " of type " + type());
        throw ex;
        
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
                                     + " undefined for " + id() + " of type " + type());
    }
    
    std::string
    ComponentBase::id() const
    {
        return (m_name);
    }
    
    std::string
    ComponentBase::type() const
    {
        return (m_type);
    }
    
}