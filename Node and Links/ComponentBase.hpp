//
//  ComponentBase.hpp
//  CirculateCore
//
//  Created by a1091793 on 16/02/2016.
//
//

#ifndef ComponentBase_hpp
#define ComponentBase_hpp

#include <stdio.h>
#include "../engine/Component.hpp"
namespace Circulate
{
    
    class ComponentBase : private Component
    {
    public:
        
        
        ComponentBase(std::string _id, std::string _type);
        
        virtual ~ComponentBase();
        
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
        print(std::ostream & out) const;
        
        virtual Recorder &
        results() const;
        
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
        setDouble(const std::string & param, double & value) throw (UndefinedCodeException);
        
        virtual void
        setString(const std::string & param, std::string & value) throw (UndefinedCodeException);
        
        virtual void
        setBool(const std::string & param, bool value) throw (UndefinedCodeException);
        
        
        virtual std::string
        id() const;
        
        virtual std::string
        type() const;
        
        
    protected:
        //        SQL_db_Sptr sql;
        
    private:
        //        std::vector< LinkData > link_records;
        std::string m_name;
        std::string m_type;
        
    };
    
}

#endif /* ComponentBase_hpp */
