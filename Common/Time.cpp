
#include "Time.hpp"
#include "Constants.hpp"

namespace Circulate
{
    
//    const char * sharedMemoryName = "BAWUMSharedMemory";
    //            int BAWUMTime_Singleton::current_time = 0;
    //            int BAWUMTime_Singleton::initialTime = 0;
    
    CirculateClock::CirculateClock():
    current_time(0), days_since_start(0), weekday_number(1), time_in_day(0)
    {
        
    }
    
    void
    CirculateClock::updateInternalState()
    {
        if (time_in_day >= MINUTES_IN_DAY)
        {
            time_in_day = time_in_day - MINUTES_IN_DAY;
            ++(days_since_start);
            ++(weekday_number);
        }
        if (weekday_number == 8)
        {
            weekday_number = 1;
        }
    }
    
    CirculateClock&
    CirculateClock::getInstance()
    {
        // The only instance
        // Guaranteed to be lazy initialized
        // Guaranteed that it will be destroyed correctly
        static CirculateClock instance;
        return instance;
    }
    
    
    void
    CirculateClock::incrementOneMinute()
    {
        //                  std::cout << "incrementing time: " << std::endl;
        current_time += 1.0;
        time_in_day += 1.0;
        this->updateInternalState();
        
        //                  std::cout << "time now equals: " << *current_time << std::endl;
    }
    
    void
    CirculateClock::incrementOneHour()
    {
        //                  std::cout << "incrementing time: " << std::endl;
        current_time += MINUTES_IN_HOUR;
        time_in_day += MINUTES_IN_HOUR;
        this->updateInternalState();
        
        //                  std::cout << "time now equals: " << *current_time << std::endl;
    }
    
    void
    CirculateClock::incrementOneDay()
    {
        //                  std::cout << "incrementing time: " << std::endl;
        current_time += MINUTES_IN_DAY;
        time_in_day += MINUTES_IN_DAY;
        this->updateInternalState();
        
        //                  std::cout << "time now equals: " << *current_time << std::endl;
    }
    
    double
    CirculateClock::now()
    {
        //                  std::cout << "Address: " << current_time << "\n";
        //                  std::cout << "time now equals: " << *current_time << std::endl;
        return (current_time);
    }
    
    double
    CirculateClock::timeInDay()
    {
        //                  std::cout << "Address: " << current_time << "\n";
        //                  std::cout << "time now equals: " << *current_time << std::endl;
        return (time_in_day);
    }

    
    
    boost::tuple< int, int, int, double >
    CirculateClock::days_hours_minutes_seconds(double _time_d)
    {
        int _time = int(_time_d);
        int days = _time / MINUTES_IN_DAY;
        int hour_minutes = _time % MINUTES_IN_DAY;
        int hours = hour_minutes / MINUTES_IN_HOUR;
        int minutes = hour_minutes % MINUTES_IN_HOUR;
        double seconds = (_time_d - double (_time) ) * SECONDS_IN_MINUTE;
        return (boost::make_tuple(days, hours, minutes, seconds));
        
    }
    
    std::pair< int, double>
    CirculateClock::days_minutes(double _time)
    {
        int days = _time / MINUTES_IN_DAY;
        double minutes = _time - (days * MINUTES_IN_DAY);
        return (std::make_pair(days, minutes));
        
        
        
    }
    
    
    TimeStamp::TimeStamp(double _time1, double _time2, ConstructType _type) :
    start_time(_time1), type(period)
    {
        if(_type == elapsed)
        {
            end_time = _time1 + _time2;
            elapsed = _time2;
        }
        else
        {
            end_time = _time2;
            elapsed = _time2 - _time1;
        }
    }
    
    TimeStamp::TimeStamp(double _time):
    start_time(_time), end_time(_time), elapsed(0), type(point)
    {
        
    }
    
    std::pair< double, double>
    TimeStamp::getTime() const
    {
        return (std::pair<double, double>(start_time, elapsed));
    }
}