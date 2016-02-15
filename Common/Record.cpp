//
//  Record.cpp
//  CirculateCommon
//
//  Created by a1091793 on 30/12/2015.
//
//

#include <stdio.h>
#include "Record.hpp"

namespace Circulate
{
    Record::Record() :
    time_val(0), flow_val(0)
    {
        
    }
    
    Record::Record(TimeStamp _time, double _flow) :
    time_val(_time), flow_val(_flow)
    {
        
    }
    
    Record::Record(TimeStamp _time, double _flow, std::map<std::string, double> _properties) :
    time_val(_time), flow_val(_flow), properties(_properties)
    {
        
    }

    Record::~Record()
    {
        // do nothing at this stage.
        // The base class destructor will be called, will not it?
    }
    
    void
    Record::clear()
    {
        flow_val = 0;
        properties.clear();
    }
    
//    Record::operator double()
//    {
//        return flow_val;
//    }
//    
//    inline void
//    operator()(double const & _value)
//    {
//        flow_val = _value;
//    }
//    
//    inline double
//    operator()(void) const
//    {
//        return flow_val;
//    }
    
    double
    Record::flow(void) const
    {
        return flow_val;
    }
    
    double
    Record::time(void) const
    {
        return time_val.getTime().first;
    }
    
    double
    Record::duration(void) const
    {
        return time_val.getTime().second;
    }
    
    void
    Record::flow(double _flow)
    {
        flow_val = _flow;
    }
    
    void
    Record::stampTime(TimeStamp _time)
    {
        time_val = _time;
    }
    
    boost::optional< const double & >
    Record::operator()(std::string _a_property_name) const
    {
        PropertyMap::const_iterator it = properties.find(_a_property_name);
        if (it != this->end())
        {
            return (boost::optional< const double & >(it->second));
        }
        return (boost::optional< const double & >());
    }
    
    boost::optional< double & >
    Record::operator()(std::string _a_property_name)
    {
        PropertyMap::iterator it = properties.find(_a_property_name);
        if (it != this->end())
        {
            return (boost::optional< double & >(it->second));
        }
        return (boost::optional< double & >());
    }
    
    void
    Record::operator=(Record const & _other)
    {
        this->flow_val = _other.flow_val;
        this->time_val = _other.time_val;
        properties.operator =(_other.properties);
    }
    
    
//    typedef Record::iterator PropertyIt;
//    typedef Record::const_iterator ConstPropertyIt;
    
    std::ostream &
    operator <<(std::ostream & out, Record & _record)
    {
        out << _record.flow_val;
        return (out);
    }
    
    const std::string &
    name_of(ConstPropertyIt & _propertyIt)
    {
        return (_propertyIt->first);
    }
    
    const double &
    value_of(ConstPropertyIt & _propertyIt)
    {
        return (_propertyIt->second);
    }
    
    const std::string &
    name_of(PropertyIt & _propertyIt)
    {
        return (_propertyIt->first);
    }
    
    double &
    value_of(PropertyIt & _propertyIt)
    {
        return (_propertyIt->second);
    }
    
//    inline Record
//    operator +(const Record & left, const double & right)
//    {
//        Record newRecord = left;
//        newRecord.flow_val += right;
//        if (newRecord.flow_val < 0)
//        {
//            
//            std::cerr << "Error after arithmetic in addition, Value of flow"
//            " required to be >= 0; Assigning to 0\n";
//            newRecord.flow_val = 0;
//            
//        }
//        return (newRecord);
//    }
//    
//    inline Record
//    operator +(const double & left, const Record & right)
//    {
//        Record newRecord = right;
//        newRecord.flow_val += left;
//        if (newRecord.flow_val < 0)
//        {
//            
//            std::cerr << "Error after arithmetic in addition, Value of flow"
//            " required to be >= 0; Assigning to 0\n";
//            newRecord.flow_val = 0;
//            
//        }
//        return (newRecord);
//    }
    
    Record
    operator +(const Record & left, const Record & right)
    {
        Record newRecord;
        
        // Do not need to check as all values in a record will be positive. We do not have antimattetr!
        if (!(left.properties.empty() && right.properties.empty()))
        {
            //               std::clog << "left is not empty, neighter right" << std::endl;
            if (left.properties.size() > right.properties.size())
            {
                //                  std::clog << "left is bigger" << std::endl;
                newRecord = left;
                newRecord.flow_val += right.flow_val;
                // add those from right...
                ConstPropertyIt right_it = right.properties.begin();
                ConstPropertyIt right_end = right.properties.end();
                for (; right_it != right_end; ++right_it)
                {
                    PropertyIt new_it = newRecord.properties.find(name_of(right_it));

                    if (new_it != newRecord.properties.end())
                    {
                        value_of(new_it) += value_of(right_it);

                    }
                    else
                    {
                        
                        newRecord.properties.insert(
                                         std::make_pair(name_of(right_it),
                                                        value_of(right_it)));
                    }
                }
            }
            else // if (right.size() > left.size())
            {
                //                  std::clog << "Right is bigger or equal size" << std::endl;
                newRecord = right;
                newRecord.flow_val += left.flow_val;
                
                
                // add those from right...
                ConstPropertyIt left_it = left.properties.begin();
                ConstPropertyIt left_end = left.properties.end();
                for (; left_it != left_end; ++left_it)
                {
                    PropertyIt new_it = newRecord.find(name_of(left_it));
                    //                     std::clog << "Finding " << name_of(left_it) << std::endl;
                    if (new_it != newRecord.end())
                    {
                        value_of(new_it) += value_of(left_it);
                    }
                    else
                    {
                        newRecord.properties.insert(
                                         std::make_pair(name_of(left_it),
                                                        value_of(left_it)));
                    }
                }
            }
        }
        else
        {
            //               std::clog << "record was empty" << std::endl;
            newRecord.flow_val = left.flow_val + right.flow_val;
        }
        return (newRecord);
    }
    
//    inline Record
//    operator -(const Record & left, const double & right)
//    {
//        Record newRecord = left;
//        newRecord.flow_val -= right;
//        if (newRecord.flow_val < 0)
//        {
//            
//            std::cerr << "Error after arithmetic in subtraction, Value of flow"
//            " required to be >= 0; Assigning to 0\n";
//            newRecord.flow_val = 0;
//            
//        }
//        return (newRecord);
//    }
//    
//    inline Record
//    operator -(const double & left, const Record & right)
//    {
//        Record newRecord = right;
//        newRecord.flow_val -= left;
//        if (newRecord.flow_val < 0)
//        {
//            
//            std::cerr << "Error after arithmetic in subtraction, Value of flow"
//            " required to be >= 0; Assigning to 0\n";
//            newRecord.flow_val = 0;
//            
//            
//        }
//        return (newRecord);
//    }
//    
//    inline Record
//    operator -(const Record & left, const Record & right)
//    {
//        Record newRecord;
//        //                newRecord.flow = left.flow - right.flow;
//        // Do not need to check as all values in a record will be positive. We do not have antimattetr!
//        //                if (newRecord.flow < 0)
//        //                {
//        //
//        //                    std::cerr << "Error after arithmetic, Value of flow"
//        //                            " required to be >= 0; Assigning to 0\n";
//        //                    newRecord.flow = 0;
//        //
//        //                }
//        if (!(left.empty() && right.empty()))
//        {
//            if (left.size() > right.size())
//            {
//                newRecord = left;
//                newRecord.flow_val -= right.flow_val;
//                // add those from right...
//                ConstPropertyIt right_it = right.begin();
//                ConstPropertyIt right_end = right.end();
//                for (; right_it != right_end; ++right_it)
//                {
//                    PropertyIt new_it = newRecord.find(name_of(right_it));
//                    if (right_it != right.end())
//                    {
//                        value_of(new_it) -= value_of(right_it);
//                        // Do not need to check as all values in a record will be positive. We do not have antimattetr!
//                        //                                if (value_of(new_it) < 0)
//                        //                                {
//                        //                                    std::cerr
//                        //                                            << "Error after arithmetic, Value of "
//                        //                                            << name_of(new_it)
//                        //                                            << " required to be >= 0; Assigning to 0\n";
//                        //                                    value_of(new_it) = 0;
//                        //
//                        //                                }
//                    }
//                    else
//                    {
//                        newRecord.insert(
//                                         std::make_pair(name_of(right_it),
//                                                        value_of(right_it)));
//                    }
//                }
//            }
//            else // if (right.size() > left.size())
//            {
//                newRecord = right;
//                newRecord.flow_val -= left.flow_val;
//                // add those from right...
//                ConstPropertyIt left_it = left.begin();
//                ConstPropertyIt left_end = left.end();
//                for (; left_it != left_end; ++left_it)
//                {
//                    PropertyIt new_it = newRecord.find(name_of(left_it));
//                    if (left_it != left.end())
//                    {
//                        value_of(new_it) -= value_of(left_it);
//                        // Do not need to check as all values in a record will be positive. We do not have antimattetr!
//                        //                                if (value_of(new_it) < 0)
//                        //                                {
//                        //                                    std::cerr
//                        //                                            << "Error after arithmetic, Value of "
//                        //                                            << name_of(new_it)
//                        //                                            << " required to be >= 0; Assigning to 0\n";
//                        //                                    value_of(new_it) = 0;
//                        //
//                        //                                }
//                    }
//                    else
//                    {
//                        newRecord.insert(
//                                         std::make_pair(name_of(left_it),
//                                                        value_of(left_it)));
//                    }
//                }
//            }
//        }
//        else
//        {
//            newRecord.flow_val = left.flow_val - right.flow_val;
//        }
//        return (newRecord);
//    }
//    
//    inline Record
//    operator *(const Record & left, const double & right)
//    {
//        Record newRecord = left;
//        if (right > 0)
//        {
//            newRecord.flow_val *= right;
//            PropertyIt it = newRecord.begin();
//            PropertyIt end = newRecord.end();
//            for (; it != end; ++it)
//            {
//                value_of(it) *= right;
//            }
//        }
//        else
//        {
//            std::cerr << "Error after arithmetic in multiplication, Value of flow"
//            " required to be >= 0; Did not change value of flow\n";
//        }
//        return (newRecord);
//    }
    
    Record
    operator *(const double & left, const Record & right)
    {
        Record newRecord = right;
        if (left > 0)
        {
            newRecord.flow_val *= left;
            PropertyIt it = newRecord.begin();
            PropertyIt end = newRecord.end();
            for (; it != end; ++it)
            {
                value_of(it) *= left;
            }
        }
        else
        {
            std::cerr << "Error after arithmetic in multiplication, Value of flow"
            " required to be >= 0; Did not change value of flow\n";
        }
        
        return (newRecord);
    }
    
//    inline Record
//    operator *(const Record & left, const Record & right)
//    {
//        Record newRecord;
//        if (!(left.empty() && right.empty()))
//        {
//            if (left.size() > right.size())
//            {
//                newRecord = left;
//                newRecord.flow_val *= right.flow_val;
//                // add those from right...
//                ConstPropertyIt right_it = right.begin();
//                ConstPropertyIt right_end = right.end();
//                for (; right_it != right_end; ++right_it)
//                {
//                    PropertyIt new_it = newRecord.find(name_of(right_it));
//                    if (right_it != right.end())
//                    {
//                        value_of(new_it) *= value_of(right_it);
//                    }
//                    else
//                    {
//                        newRecord.insert(
//                                         std::make_pair(name_of(right_it),
//                                                        value_of(right_it)));
//                    }
//                }
//            }
//            else // if (right.size() > left.size())
//            {
//                newRecord = right;
//                newRecord.flow_val *= left.flow_val;
//                // add those from right...
//                ConstPropertyIt left_it = left.begin();
//                ConstPropertyIt left_end = left.end();
//                for (; left_it != left_end; ++left_it)
//                {
//                    PropertyIt new_it = newRecord.find(name_of(left_it));
//                    if (left_it != left.end())
//                    {
//                        value_of(new_it) *= value_of(left_it);
//                    }
//                    else
//                    {
//                        newRecord.insert(
//                                         std::make_pair(name_of(left_it),
//                                                        value_of(left_it)));
//                    }
//                }
//            }
//        }
//        else
//        {
//            newRecord.flow_val = left.flow_val * right.flow_val;
//        }
//        return (newRecord);
//    }
    
//    inline Record
//    operator *(const Record & left, const int & right)
//    {
//        Record newRecord = left;
//        if (right > 0)
//        {
//            newRecord.flow_val *= right;
//            PropertyIt it = newRecord.begin();
//            PropertyIt end = newRecord.end();
//            for (; it != end; ++it)
//            {
//                value_of(it) *= right;
//            }
//        }
//        else
//        {
//            std::cerr << "Error after arithmetic in multiplication, Value of flow"
//            " required to be >= 0; Did not change value of flow\n";
//        }
//        return (newRecord);
//    }
//    
//    inline Record
//    operator *(const int & left, const Record & right)
//    {
//        Record newRecord = right;
//        if (left > 0)
//        {
//            newRecord.flow_val *= left;
//            PropertyIt it = newRecord.begin();
//            PropertyIt end = newRecord.end();
//            for (; it != end; ++it)
//            {
//                value_of(it) *= left;
//            }
//        }
//        else
//        {
//            std::cerr << "Error after arithmetic in multiplication, Value of flow"
//            " required to be >= 0; Did not change value of flow\n";
//        }
//        
//        return (newRecord);
//    }
//    
//    
//    
//    inline Record
//    operator /(const Record & left, const double & right)
//    {
//        Record newRecord = left;
//        if (right > 0)
//        {
//            newRecord.flow_val /= right;
//            PropertyIt it = newRecord.begin();
//            PropertyIt end = newRecord.end();
//            for (; it != end; ++it)
//            {
//                value_of(it) /= right;
//            }
//        }
//        else
//        {
//            std::cerr << "Error after arithmetic in division, Value of flow"
//            " required to be >= 0; Did not change value of flow\n";
//        }
//        return (newRecord);
//    }
//    
//    inline Record
//    operator /(const int & left, const Record & right)
//    {
//        Record newRecord = right;
//        if (left > 0)
//        {
//            newRecord.flow_val /= left;
//            PropertyIt it = newRecord.begin();
//            PropertyIt end = newRecord.end();
//            for (; it != end; ++it)
//            {
//                value_of(it) /= left;
//            }
//        }
//        else
//        {
//            std::cerr << "Error after arithmetic in division, Value of flow"
//            " required to be >= 0; Did not change value of flow\n";
//        }
//        return (newRecord);
//    }
//    
//    inline Record
//    operator /(const Record & left, const int & right)
//    {
//        Record newRecord = left;
//        if (right > 0)
//        {
//            newRecord.flow_val /= right;
//            PropertyIt it = newRecord.begin();
//            PropertyIt end = newRecord.end();
//            for (; it != end; ++it)
//            {
//                value_of(it) /= right;
//            }
//        }
//        else
//        {
//            std::cerr << "Error after arithmetic in division, Value of flow"
//            " required to be >= 0; Did not change value of flow\n";
//        }
//        return (newRecord);
//    }
//    
//    inline Record
//    operator /(const double & left, const Record & right)
//    {
//        Record newRecord = right;
//        if (left > 0)
//        {
//            newRecord.flow_val /= left;
//            PropertyIt it = newRecord.begin();
//            PropertyIt end = newRecord.end();
//            for (; it != end; ++it)
//            {
//                value_of(it) /= left;
//            }
//        }
//        else
//        {
//            std::cerr << "Error after arithmetic in division, Value of flow"
//            " required to be >= 0; Did not change value of flow\n";
//        }
//        return (newRecord);
//    }
//    
//    inline Record
//    operator /(const Record & left, const Record & right)
//    {
//        Record newRecord;
//        
//        if (!(left.empty() && right.empty()))
//        {
//            if (left.size() > right.size())
//            {
//                newRecord = left;
//                newRecord.flow_val /= right.flow_val;
//                // add those from right...
//                ConstPropertyIt right_it = right.begin();
//                ConstPropertyIt right_end = right.end();
//                for (; right_it != right_end; ++right_it)
//                {
//                    PropertyIt new_it = newRecord.find(name_of(right_it));
//                    if (new_it != newRecord.end())
//                    {
//                        value_of(new_it) /= value_of(right_it);
//                    }
//                    else
//                    {
//                        newRecord.insert(
//                                         std::make_pair(name_of(right_it),
//                                                        value_of(right_it)));
//                    }
//                }
//            }
//            else // if (right.size() > left.size())
//            {
//                newRecord = right;
//                newRecord.flow_val = left.flow_val / right.flow_val;
//                // add those from right...
//                ConstPropertyIt left_it = left.begin();
//                ConstPropertyIt left_end = left.end();
//                for (; left_it != left_end; ++left_it)
//                {
//                    PropertyIt new_it = newRecord.find(name_of(left_it));
//                    if (new_it != newRecord.end())
//                    {
//                        double newvalue = value_of(left_it) / value_of(new_it);
//                        value_of(new_it) = newvalue;
//                    }
//                    else
//                    {
//                        newRecord.insert(
//                                         std::make_pair(name_of(left_it),
//                                                        value_of(left_it)));
//                    }
//                }
//            }
//        }
//        return (newRecord);
//    }
    
}