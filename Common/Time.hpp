



#ifndef TIME_H_
#define TIME_H_

#include <boost/tuple/tuple.hpp>
//#include <pair>

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//       BASE UNIT OF TIME IS MINUTES                                         //
//                                                                            //
//                                                                            //
////////////////////////////portal////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace Circulate
{
    
    
    /*
     * C++ Singleton
     * Limitation: Single Threaded Design
     * See: http://www.aristeia.com/Papers/DDJ_Jul_Aug_2004_revised.pdf
     *      For problems associated with locking in multi threaded applications
     *
     * Limitation:
     * If you use this Singleton (A) within a destructor of another Singleton (B)
     * This Singleton (A) must be fully constructed before the constructor of (B)
     * is called.
     */
    class CirculateClock
    {
    private:
        // Private Constructor
        CirculateClock();
        // Stop the compiler generating methods of copy the object
        CirculateClock(CirculateClock const& copy); // Not Implemented
        CirculateClock&
        operator=(CirculateClock const& copy); // Not Implemented
        
        void
        updateInternalState();
        
        
//        boost::interprocess::managed_shared_memory segment;
//        std::pair< int *,
//        boost::interprocess::managed_shared_memory::size_type > res;
//        
//        std::pair< bool *,
//        boost::interprocess::managed_shared_memory::size_type > resBool;
        
        double current_time;
        int days_since_start;
        int weekday_number;
        double time_in_day;
        
        
        
    public:
        static CirculateClock&
        getInstance();
        
        void
        incrementOneMinute();
        
        void
        incrementOneHour();
        
        void
        incrementOneDay();
        
        void
        increment(double period);
        
        double
        now();
        
        double
        timeInDay();
        
        static boost::tuple< int, int, int, double >
        days_hours_minutes_seconds(double _time);
        
        static std::pair< int, double>
        days_minutes(double _time);
    };

    enum TimeType{point, period};
    enum ConstructType{bounds, elapsed};
    
    
    
    class TimeStamp
    {
    private:
        
        double start_time;
        double end_time;
        double elapsed;
        TimeType type;
        
    public:
        TimeStamp(double _time1, double _time2, ConstructType _type = ConstructType::elapsed);
        
        TimeStamp(double _time);
        
        std::pair<double, double>
        getTime() const;
        
    };
}


#endif