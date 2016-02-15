/*
 * Record.h
 *
 *  Created on: Feb 20, 2012
 *      Author: jeff
 */

/**
 * Record is the class for holding information about a
 * flow. I.e. it will contain the value of the flow, in
 * addition to other components within the flow of interest,
 * such as phosphorous, nitrogen, suspended solids, etc.
 * These additional components will be in mass flow rate, to
 * make the arithmetic consistent. A function will be provided
 * to allow the conversion to a concentration.
 *
 * In addition, it functions to also hold sub-timestep
 * values... but this will not be implemented at this stage
 * untill a need arises.
 *
 * It also defines much arithmetic operations, such that
 * it can also be used as a variable between timesteps.
 */

#ifndef RECORD_H_
#define RECORD_H_

    //#include <boost/foreach.hpp>
#include <iostream>
#include <ostream>
#include <boost/optional.hpp>
#include <map>
#include "Time.hpp"

namespace Circulate
{
    
        //        typedef std::set< std::string > NamesSet;
        //        typedef std::vector< double > PropertyValues;
    typedef std::map< std::string, double > PropertyMap;
    
    typedef std::pair< std::string, double > PropertyPair;
    
    /** Class for storing the flow or flow volume, and associated properties of the flow. I
     *  will contain the value of the flow, in addition to other components within the flow of
     * interest, such as phosphorous, nitrogen, suspended solids, etc. Whether it is the flow
     *  rate or flow volume depends on the Time type stored with the class. If the time type is
     * of type point, then it is the flow rate, and the properties associated with the record
     *  will be of mass flow rate. If it is the flow volume, then the properties will be in 
     *  mass.
     * @author Jeffrey Newman
     * @version 2
     *
     */
    class Record : public PropertyMap
    {
    public:
      
      friend std::ostream &
      operator <<(std::ostream & out, Record & _record);
      
      friend Record
      operator +(const Record & left, const Record & right);
      
      friend Record
      operator +(const Record & left, const double & right);
      
      friend Record
      operator +(const double & left, const Record & right);
      
      friend Record
      operator -(const Record & left, const double & right);
      
      friend Record
      operator -(const double & left, const Record & right);
      
      friend Record
      operator -(const Record & left, const Record & right);
      
      friend Record
      operator *(const Record & left, const double & right);
      
      friend Record
      operator *(const double & left, const Record & right);
      
      
      friend Record
      operator *(const Record & left, const int & right);
      
      friend Record
      operator *(const int & left, const Record & right);
      
      friend Record
      operator *(const Record & left, const Record & right);
      
      friend Record
      operator /(const Record & left, const double & right);
      
      friend Record
      operator /(const double & left, const Record & right);
      
      friend Record
      operator /(const Record & left, const int & right);
      
      friend Record
      operator /(const int & left, const Record & right);
      
      friend Record
      operator /(const Record & left, const Record & right);
      
        
        Record();
      
        Record(TimeStamp _time, double _flow);
        
        Record(TimeStamp _time, double _flow, std::map<std::string, double> _properties);
      
//      Record(double _flow, std::string & _a_property_name,
//             double _a_property_value);
      
      virtual
        ~Record();
      
      void
        clear();
      
      operator double();
      
//      inline double
//        operator()(void);
      
      double
        flow(void) const;
        
        void
        flow(double _flow);
        
        double
        time(void) const;
        
        double
        duration(void) const;
        
        void
        stampTime(TimeStamp _time);
      
      boost::optional< const double & >
        operator()(std::string _a_property_name) const;
      
      boost::optional< double & >
        operator()(std::string _a_property_name);
      
      void
        operator=(Record const & _other);
      
      
    private:
      TimeStamp time_val;
      double flow_val;
      PropertyMap properties;
    };
    
    typedef PropertyMap::iterator PropertyIt;
    typedef PropertyMap::const_iterator ConstPropertyIt;
    
    std::ostream &
    operator <<(std::ostream & out, Record & _record);
    
    const std::string &
    name_of(ConstPropertyIt & _propertyIt);
    
    const double &
    value_of(ConstPropertyIt & _propertyIt);
    
    const std::string &
    name_of(PropertyIt & _propertyIt);
    
    double &
    value_of(PropertyIt & _propertyIt);
    
    
    
        Record
    operator +(const Record & left, const Record & right);
    
//        inline Record
//    operator -(const Record & left, const double & right);
//    
//        inline Record
//    operator -(const Record & left, const Record & right);
//    
//        inline Record
//    operator *(const double & left, const Record & right);
    
        Record
    operator *(const Record & left, const int & right);
    
        
        
//        inline Record
//    operator /(const Record & left, const double & right);
//    
//        inline Record
//    operator /(const int & left, const Record & right);
//    
//        inline Record
//    operator /(const Record & left, const int & right);
//    
//        inline Record
//    operator /(const double & left, const Record & right);
//    
//        inline Record
//    operator /(const Record & left, const Record & right);
    
        }
        
#endif /* RECORD_H_ */
