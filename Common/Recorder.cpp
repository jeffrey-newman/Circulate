/*
 * Recorder.cpp
 *
 *  Created on: May 28, 2012
 *      Author: jeff
 */

#include <string>
#include <iostream>
#include <sstream>
#include <boost/foreach.hpp>
#include "Time.hpp"
#include "Recorder.hpp"




namespace Circulate
   {
            Recorder::Recorder(std::string _dataset_name,
                  double _fill_value) :
                  dataset_name(_dataset_name), //
                  fill_val(_fill_value)                
               {
                  // TODO Auto-generated constructor stub
                   interpolatorIt = records.begin().operator++();
                   previousIt = records.begin();

               }

            Recorder::~Recorder()
               {
                  // TODO Auto-generated destructor stub
               }

//            Record &
//            Recorder::getRecord(int time_duration)
//               {
//                  if (records.find(time_duration))
//               }

//            void
//            Recorder::storeRecord(double _flow)
//               {
////                   if (dataset_name == "Rain")
////                   {
////                       std::cout << "Storing a rain";
////                   }
//                  Record newRecord(_flow);
////                  newRecord.setTime(BAWUMTime_Singleton::getInstance().now());
//                  records.push_back(newRecord);
//                   interpolatorIt = records.begin().operator++();
//                   previousIt = records.begin();
//                   
//               }

            void
            Recorder::storeRecord(Record _record)
               {
//                   if (dataset_name == "Rain")
//                   {
//                       std::cout << "Storing a rain";
//                   }
//                  _record.setTime(BAWUMTime_Singleton::getInstance().now());
                  records.push_back(_record);
                   interpolatorIt = records.begin().operator++();
                   previousIt = records.begin();
               }
             
//             void
//             Recorder::storeRecord(std::pair<double
//                                   , double> & _val)
//             {
////                 if (dataset_name == "Rain")
////                 {
////                     std::cout << "Storing a rain";
////                 }
//                 Record newRecord(_val.first, _val.second);
//                 records.push_back(newRecord);
//                 interpolatorIt = records.begin().operator++();
//                 previousIt = records.begin();
//             }
       
             void
             Recorder::storeRecord(TimeStamp _time, double _val)
             {
//                 if (dataset_name == "Rain")
//                 {
//                     std::cout << "Storing a rain";
//                 }
//                 if (dataset_name == "Evap")
//                 {
//                     std::cout << "Storing a evap";
//                 }
                 Record newRecord(_time, _val);
                 records.push_back(newRecord);
                 interpolatorIt = records.begin().operator++();
                 previousIt = records.begin();
             }
             

            const std::list< Record > &
            Recorder::getRecords() const
               {
                  return records;
               }

            double
            Recorder::volume(double duration) const
               {
                  int size = records.size();
                  std::list< Record > ::const_reverse_iterator it = records.rbegin();
                  int records_read = 0;
                  double sum_flow = 0;
                   double duration_count = 0;
                  while(duration_count < duration && records_read < size)
                  {
                     sum_flow += it->flow();
                      duration_count += it->duration();
                     ++records_read;
                     ++it;
                  }
                  return sum_flow;
               }
       
//       double
//       Recorder::volume(double time_start, double time_end) const
//       {
//           
//       }
       
             double
             Recorder::operator[](double _time)
             {
                 if (interpolatorIt == records.end())
                 {
                     std::cout << "InterpolatorIt == records.end()";
                 }
                 if (previousIt == records.begin().operator--())
                 {
                     std::cout << "previousIt == --(records.begin())";
                 }
                 while ((interpolatorIt != records.end()) and (previousIt != records.begin().operator--()))
                 {
                     double previousTime = previousIt->time();
                     double currentTime = interpolatorIt->time();
                     
                     if (previousTime <= _time && _time  <= currentTime)
                     {
                         //We have found it.
                         if (_time == currentTime)
                         {
                             return (interpolatorIt->flow());
                         }
                         if (_time == previousTime)
                         {
                             return (previousIt->flow());
                         }
                         double previousVal = previousIt->flow();
                         double currentVal = interpolatorIt->flow();
                         return (previousVal + (currentVal - previousVal)*(_time - previousTime)/(currentTime - previousTime));
                     }
                     if (_time > currentTime)
                     {
                         ++interpolatorIt;
                         ++previousIt;
                     }
                     else
                     {
                         --previousIt;
                         --interpolatorIt;
                     }
                 }
                 if ( interpolatorIt == records.end())
                 {
                     if (_time > previousIt->time())
                     {
                         std::stringstream err_msg;
                         err_msg << "Error in " << this->dataset_name << "; Requested time: " << _time << "; Last recorder data at time: " << previousIt->time();
                         throw std::runtime_error(err_msg.str());
                     }
                     previousIt = records.begin();
                     interpolatorIt = ++previousIt;
                     return (this->operator[](_time));
                 }
                 if ( previousIt == records.begin())
                 {
                     if (_time < previousIt->time())
                     {
                         std::stringstream err_msg;
                         err_msg << "Error in " << this->dataset_name << "; Requested time: " << _time << "; First recorded data at time: " << previousIt->time();
                         throw std::runtime_error(err_msg.str());
                     }
                     interpolatorIt = records.end();
                     previousIt = --(interpolatorIt);
                     return (this->operator[](_time));
                 }
                 return (-999);
             }
             
//            void
//            Recorder::storeRecord(int time_designator, Record & _value)
//               {
//                  // Find where to store the record
//
//                  //Store the record
//                  _value.setTime(time_designator);
//
//               }

//            void
//            Recorder::storeRecord(int _time_begin, int _time_end, Record & _value)
//               {
//
//               }

//            void
//            Recorder::print(std::string _h5_fileName,
//                  std::string dataset_name)
//               {
//                  this->print(_h5_fileName, dataset_name, no_addtnl_vars);
//               }
//

//            void
//            Recorder::print(std::string _h5_fileName,
//                  std::string dataset_name,
//                  std::vector< std::string > additional_variables
////                  =                        no_addtnl_vars //
//                  )
//               {
//
//                  std::cout << "printing " << records.size()
//                        << " records to h5 file with name" << dataset_name
//                        << "\n";
//
////                  typedef struct simpledata
////                     {
////                        int timestamp;
////                        double flow;
////                     } simpledata;
//
//                  int rank = 2;
//
//                  //Infill all records so that all records have the same set of properties
////                  BOOST_FOREACH(Record & rcd, records)
////                        {
////                           BOOST_FOREACH(Record::value_type & property, rcd)
////                                 {
////                                    // Check whether all records have this property
////                                    BOOST_FOREACH(Record & rcd2, records)
////                                          {
////                                             // If the record does not have this property, give it one
////                                             Record::iterator it = rcd2.find(
////                                                   property.first);
////                                             if (it == rcd2.end())
////                                             {
////                                                rcd2.insert(
////                                                      std::make_pair(
////                                                            property.first,
////                                                            0.00));
////                                             }
////                                          }
////                                 }
////                        }
//
////Create the data array.
//                  std::cout << "Create the data array.\n";
//                  double * time_data = new double[records.size()];
//                  double * flow_data = new double[records.size()];
//                  int i = 0;
//                  BOOST_FOREACH(Record & rcd, records)
//                        {
//                           time_data[i] = rcd.getTime();
//                           flow_data[i] = rcd();
//
//                           std::cout << time_data[i] << "\t" << flow_data[i]
//                                 << "\n";
//                           ++i;
//                        }
//                  try
//                  {
////                      H5::Exception::dontPrint();
//
//                     /*
//                      * Create a new file if one doesn't exist. If file exists try and get its file handle
//                      */
//                     const H5std_string FILE_NAME(_h5_fileName);
//
//                     H5FileMapType::iterator h5FileIt = h5FileMap.find(
//                           FILE_NAME);
//                     if (h5FileIt == h5FileMap.end())
//                     {
//                        //                        std::cout << "making a new file\n";
//                        std::pair< H5FileMapType::iterator, bool > insertReturn =
//                              h5FileMap.insert(
//                                    std::make_pair(
//                                          FILE_NAME,
//                                          new H5::H5File(FILE_NAME,
//                                                H5F_ACC_TRUNC)));
//                        if (insertReturn.second == true) h5FileIt =
//                              insertReturn.first;
//                     }
//                     if (h5FileIt != h5FileMap.end())
//                     {
//                        H5::H5File * file = h5FileIt->second;
//
//                        /*
//                         * Create the data space with unlimited dimensions.
//                         */
//                        hsize_t dims[2];
//                        dims[0] = records.size();
//                        dims[1] = 2; // dataset dimensions at creation
//                        hsize_t maxdims[2] =
//                           { records.size(), H5S_UNLIMITED };
//                        H5::DataSpace mspace1(rank, dims, maxdims);
//
//                        /*
//                         * Modify dataset creation properties, i.e. enable chunking.
//                         */
//                        H5::DSetCreatPropList cparms;
//                        hsize_t chunk_dims[2] =
//                           { 1440, 1 };
//                        cparms.setChunk(rank, chunk_dims);
//
//                        /*
//                         * Set fill value for the dataset
//                         */
//                        cparms.setFillValue(H5::PredType::NATIVE_DOUBLE,
//                              &fill_val);
//
//                        /*
//                         * Create a new dataset within the file using cparms
//                         * creation properties.
//                         */
//                        H5::DataSet dataset = file->createDataSet(dataset_name,
//                              H5::PredType::NATIVE_DOUBLE, mspace1, cparms);
//
//                        /*
//                         * Select a hyperslab.
//                         */
//
//                        hsize_t size[2];
//                        size[0] = records.size();
//                        size[1] = 1;
//                        H5::DataSpace mspace2(rank, size);
//
//                        H5::DataSpace fspace1 = dataset.getSpace();
//                        hsize_t offset[2];
//                        offset[0] = 0;
//                        offset[1] = 0;
//                        fspace1.selectHyperslab(H5S_SELECT_SET, size, offset);
//
//                        dataset.write(time_data, H5::PredType::NATIVE_DOUBLE,
//                              mspace2, fspace1);
//
//                        offset[0] = 0;
//                        offset[1] = 1;
//                        fspace1.selectHyperslab(H5S_SELECT_SET, size, offset);
//
//                        dataset.write(flow_data, H5::PredType::NATIVE_DOUBLE,
//                              mspace2, fspace1);
//
//                        if (additional_variables.size() > 0)
//                        {
//                           double ** additional_data =
//                                 new double*[additional_variables.size()];
//                           for (int var = 0; var < additional_variables.size();
//                                 ++var)
//                           {
//                              additional_data[var] = new double[records.size()];
//                           };
//
//                           i = 0;
//                           BOOST_FOREACH(Record & rcd, records)
//                                 {
//                                    int add_data_index = 0;
//                                    BOOST_FOREACH(std::string & var_name, additional_variables)
//                                          {
//                                             Record::iterator it = rcd.find(
//                                                   var_name);
//                                             if (it != rcd.end())
//                                             {
//                                                additional_data[add_data_index][i] =
//                                                      it->second;
//                                             }
//                                             else
//                                             {
//                                                additional_data[add_data_index][i] =
//                                                      0;
//                                             }
//                                             ++add_data_index;
//                                          }
//                                    ++i;
//                                 }
//
//                           /*
//                            * Extend the dataset. Dataset becomes records.size() x additional_variables.size() + 2.
//                            */
//                           hsize_t dims2[2];
//                           dims2[0] = records.size();
//                           dims2[1] = additional_variables.size() + 2;
//                           dataset.extend(dims2);
//
//                           fspace1 = dataset.getSpace();
//                           int add_data_index = 0;
//                           BOOST_FOREACH(std::string & var_name, additional_variables)
//                                 {
//                                    offset[0] = 0;
//                                    offset[1] = add_data_index + 2;
//                                    std::cout << "printing " << var_name
//                                          << "at offset: " << offset[0]
//                                          << " and " << offset[1] << "\n";
//                                    fspace1.selectHyperslab(H5S_SELECT_SET,
//                                          size, offset);
//                                    dataset.write(
//                                          additional_data[add_data_index],
//                                          H5::PredType::NATIVE_DOUBLE, mspace2,
//                                          fspace1);
//                                    add_data_index++;
//                                 }
//
//                           for (int var = 0; var < additional_variables.size();
//                                 ++var)
//                           {
//                              delete[] additional_data[var];
//                           };
//                           delete[] additional_data;
//                           ;
//                        }
//
//                        /*
//                         * Create a new dataset within the file using defined dataspace and
//                         * datatype and default dataset creation properties.
//                         */
//
////                        H5::CompType mtype1(sizeof(simpledata));
////                        mtype1.insertMember("time",
////                              HOFFSET(simpledata, timestamp),
////                              H5::PredType::NATIVE_INT);
////                        mtype1.insertMember("flow", HOFFSET(simpledata, flow),
////                              H5::PredType::NATIVE_DOUBLE);
////                        simpledata fill_val;
////                        fill_val.flow = 0;
////                        fill_val.timestamp = -1;
////                        cparms.setFillValue(mtype1, &fill_val);
////                        //                        int fill_val = 0;
////                        //                        cparms.setFillValue(H5::PredType::NATIVE_INT,
////                        //                              &fill_val);
////                        /*
////                         * Extend the dataset. This call assures that dataset is at least 3 x 3.
////                         */
////                        hsize_t size[2];
////                        size[0] = 1;
////                        size[1] = records.size();
////                        dataset.extend(size);
////
////                        /*
////                         * Select a hyperslab.
////                         */
////                        H5::DataSpace fspace1 = dataset.getSpace();
////                        hsize_t offset[2];
////                        offset[0] = 0;
////                        offset[1] = 0;
////                        hsize_t dims1[2];
////                        dims1[0] = 1;
////                        dims1[1] = records.size();
////                        fspace1.selectHyperslab(H5S_SELECT_SET, dims1, offset);
////
////                        //                     = group.createDataSet(dataSetName,
////                        //                           mtype1, dataspace);
////                        dataset.write(data, mtype1, dataspace, fspace1);
//                        //                     std::string groupName = "/" + dataset_name;
////                     std::cout << "Create the data space.\n";
//                        //                     std::cout << "Create the data group.\n";
//                        //                     H5::Group group(_h5.createGroup(groupName));
////                     std::cout << "Create the data type.\n";
//                        //                     std::string dataSetName = groupName + "/data";
////                     std::cout << "creating the file\n";
//                        delete[] time_data;
//                        delete[] flow_data;
//                     }
//                  }
//                  catch (H5::FileIException & error)
//                  {
//                     std::cout << error.getDetailMsg() << "\n";
//                     error.printError();
//
//                  } // catch failure caused by the DataSet operations
//                  catch (H5::DataSetIException & error)
//                  {
//                     std::cout << error.getDetailMsg() << "\n";
//                     error.printError();
//
//                  } // catch failure caused by the DataSpace operations
//                  catch (H5::DataSpaceIException & error)
//                  {
//                     std::cout << error.getDetailMsg() << "\n";
//                     error.printError();
//
//                  } // catch failure caused by the DataSpace operations
//                  catch (H5::DataTypeIException & error)
//                  {
//                     std::cout << error.getDetailMsg() << "\n";
//                     error.printError();
//
//                  }
//
//               }

   } /* namespace Circulate */
