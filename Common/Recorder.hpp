/*
 * Recorder.h
 *
 *  Created on: May 28, 2012
 *      Author: jeff
 */

#ifndef Recorder_H_
#define Recorder_H_

#include <string>
#include <vector>
#include <list>
#include "Record.hpp"

namespace Circulate
   {
            class Recorder
               {
               public:

                  /**
                   * Constructor.
                   * @param _group_name The name of the group under which this data recorder will insert data within h5 files
                   */
                  Recorder(std::string _dataset_name = "no_name_dataset",
                        double _fill_value = 0);

                  virtual
                  ~Recorder();

//                  /**
//                   * Gets the net flow for so many minutes in the past from the present
//                   * @param time_duration the number of minutes in the past to sum over
//                   * @return A record with the summed amounts
//                   */
//                  Record &
//                  getRecord(int time_duration);

//                  /**
//                   * Save the value of flow for the current time step
//                   * @param _flow the flow volume in the current time step
//                   */
//                  void
//                  storeRecord(double _val);
                   
                   /**
                    * Save the value of flow for the current time step
                    * @param _flow the flow volume in the current time step
                    * @param _time, the time of the record
                    */
                   void
                   storeRecord(TimeStamp _time, double _val);
                   
//                   /**
//                    * Save the value of flow for the current time step
//                    * @param _flow the flow volume in the current time step
//                    * @param _time, the time of the record
//                    */
//                   void
//                   storeRecord(std::pair<double, double> & _val);


                  /**
                   * Save a record for the current time step
                   * @param _record the record to be saved for the current time step
                   */
                  void
                  storeRecord(Record _record);

                  /**
                   * This function returns the net water use over the previous
                   * so many minutes.
                   * @param _duration The length of time over which water use is summed into the 'past'
                   * @return the sum water use.
                   * @todo only works for period type records.
                   */
                  double
                  volume(double _duration) const;


                   double
                   operator[](double time);

//                  /**
//                   * Save a record to a designated time step.
//                   * @param time_designator The time for which the record is mapped to
//                   * @param _value The flow record.
//                   */
//                  void
//                  storeRecord(int time_designator, Record & _value);

//                  /**
//                   * Save the same record to all time steps in a time interval
//                   * @param _time_begin The beginning timestep of the interval (inclusive)
//                   * @param _time_end the finishing timestep of the interval (inclusive)
//                   * @param _value the flow record
//                   */
//                  void
//                  storeRecord(int _time_begin, int _time_end, Record & _value);

//                  /**
//                   * Print to file, in this case using Hf5.
//                   * @param _h5 the Hf5 c++ api object to save results to.
//                   */
//                  void
//                  print(H5::H5File * _h5, std::string dataset_name);

//                  /**
//                   * Print to file, in this case using Hf5.
//                   * @param _h5 the Hf5 c++ api object to save results to.
//                   */
//                  void
//                  print(std::string _h5_fileName, std::string dataset_name);
//
//                  /**
//                   *
//                   * @param _h5_fileName
//                   * @param dataset_name
//                   * @param additional_variables
//                   */
//                  void
//                  print(std::string _h5_fileName, std::string dataset_name,
//                        std::vector< std::string > additional_variables);

                  const std::list< Record > &
                  getRecords() const;

                  std::vector< std::string > variables_to_print;
                  std::string dataset_name;
                  double fill_val;
                   
                   std::list<Record>::const_iterator interpolatorIt;
                   std::list<Record>::const_iterator previousIt;

               private:
                  std::list< Record > records;

               };

   } /* namespace Circulate */
#endif /* Recorder_H_ */
