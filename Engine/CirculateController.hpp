/* 
 * File:   hydraulicSolver.h
 * Author: jnewman
 *
 * Created on September 27, 2010, 1:09 PM
 */

#ifndef HYDRAULICSOLVER_H
#define	HYDRAULICSOLVER_H


#include <fstream>
#include <iostream>
#include "CirculateGraph.hpp"
#include "CirculateParser.hpp"
#include "../Common/Common.hpp"
#include "H5Cpp.h"
//#include "../data/hdf5/src/hdf5.h"

namespace Circulate
    {

//        static const int ID = 0;
//        static const int TYPE = 1;
//
//        static const int UPSTREAM_NODE_ID = 2;
//        static const int DOWNSTREAM_NODE_ID = 3;
//        static const int STATUS = 4;
//
//        static const int XCOORD = 5;
//        static const int YCOORD = 6;
//
//        static const int UPSTREAM_FLOW = 7;
//        static const int DOWNSTREAM_FLOW = 8;
//        static const int UPSTREAM_FLOW_DEPTH = 9;
//        static const int DOWNSTREAM_FLOW_DEPTH = 10;
//        static const int UPSTREAM_FLOW_VELOCITY = 11;
//        static const int DOWNSTREAM_FLOW_VELOCITY = 12;
//
//        static const int FLOW_IN = 13;
//        static const int FLOW_OUT = 14;
//        static const int FLOW_DEPTH = 15;
//        static const int BASE_ELEVATION = 16;
//        static const int ENTRANCE_ELEVATION = 17;
//        static const int EXIT_ELEVATION = 18;
//
//        static const int NET_TOP_UP = 19;
//
//        static const int STORAGE_VOLUME = 20;
//        static const int BASE_SURFACE_AREA = 21;
//        static const int TANK_INFLOW_ELEVATION = 22;
//        static const int TANK_OVERFLOW_ELEVATION = 23;
//        static const int TANK_OUTFLOW_ELEVATION = 24;
//        static const int MAXIMUM_CAPACITY = 25;
//        static const int MINIMUM_CAPACITY = 26;
//
//        static const int NET_DEMAND = 27;
//        static const int NET_PRODUCTION = 28;
//
//        static const int PEAK_FLOW_IN = 29;
//        static const int PEAK_FLOW_OUT = 30;
//        static const int NET_FLOW_IN = 31;
//        static const int NET_FLOW_OUT = 32;

        struct error
            {
                std::string type;
                std::string desc;
                std::string loc;
            };

        class CirculateController
            {
            public:
                //        HydraulicSolver(std::string sewrInpName);
                CirculateController(std::string input_file_path,
                        std::string node_extension_dir,
                        std::string link_extension_dir,
                        std::string data_extension_dir);

                void
                solve();

                void
                initialise();

                void
                finalise();

                void
                print(std::ostream & out) const; //print results to text file
                
                void
                print2H5(std::string h5fileName) const; // The new file format (faster... hopefully?)

                void
                printGraph(std::ostream & out) const;

                void
                printGraph(const std::string & fileName) const;

                //********************************************************************//
                //                         GETTERS                                    //
                //********************************************************************//

                int
                getNodeInt(const std::string & id,
                        const std::string & param) const
                                throw (UndefinedCodeException);

                double
                getNodeDouble(const std::string id,
                        const std::string param) const
                                throw (UndefinedCodeException);

                std::string
                getNodeString(const std::string & id,
                        const std::string & param) const
                                throw (UndefinedCodeException);

                bool
                getNodeBool(const std::string & id,
                        const std::string & param) const
                                throw (UndefinedCodeException);

                int
                getLinkInt(const std::string & id,
                        const std::string & param) const
                                throw (UndefinedCodeException);

                double
                getLinkDouble(const std::string & id,
                        const std::string & param) const
                                throw (UndefinedCodeException);

                std::string
                getLinkString(const std::string & id,
                        const std::string & param) const
                                throw (UndefinedCodeException);

                bool
                getLinkBool(const std::string & id,
                        const std::string & param) const
                                throw (UndefinedCodeException);

                int
                getNodeInt(const CirculateGraph::NodeID & id,
                        const std::string & param) const
                                throw (UndefinedCodeException);

                double
                getNodeDouble(const CirculateGraph::NodeID & id,
                        const std::string & param) const
                                throw (UndefinedCodeException);

                std::string
                getNodeString(const CirculateGraph::NodeID & id,
                        const std::string & param) const
                                throw (UndefinedCodeException);

                bool
                getNodeBool(const CirculateGraph::NodeID & id,
                        const std::string & param) const
                                throw (UndefinedCodeException);

                int
                getLinkInt(const CirculateGraph::LinkID & id,
                        const std::string & param) const
                                throw (UndefinedCodeException);

                double
                getLinkDouble(const CirculateGraph::LinkID & id,
                        const std::string & param) const
                                throw (UndefinedCodeException);

                std::string
                getLinkString(const CirculateGraph::LinkID & id,
                        const std::string & param) const
                                throw (UndefinedCodeException);

                bool
                getLinkBool(const CirculateGraph::LinkID & id,
                        const std::string & param) const
                                throw (UndefinedCodeException);

                //********************************************************************//
                //                         SETTERS                                    //
                //********************************************************************//

                void
                setNodeInt(const std::string & id, const std::string & param,
                        int value) throw (UndefinedCodeException);

                void
                setNodeDouble(const std::string & id, const std::string & param,
                        double & value) throw (UndefinedCodeException,
                                std::runtime_error);

                void
                setNodeString(const std::string & id, const std::string & param,
                        std::string & value) throw (UndefinedCodeException);

                void
                setNodeBool(const std::string & id, const std::string & param,
                        bool value) throw (UndefinedCodeException);

                void
                setLinkInt(const std::string & id, const std::string & param,
                        int value) throw (UndefinedCodeException);

                void
                setLinkDouble(const std::string & id, const std::string & param,
                        double & value) throw (UndefinedCodeException);

                void
                setLinkString(const std::string & id, const std::string & param,
                        std::string & value) throw (UndefinedCodeException);

                void
                setLinkBool(const std::string & id, const std::string & param,
                        bool value) throw (UndefinedCodeException);

                void
                setNodeInt(const CirculateGraph::NodeID & id,
                        const std::string & param, int value)
                                throw (UndefinedCodeException);

                void
                setNodeDouble(const CirculateGraph::NodeID & id,
                        const std::string & param, double & value)
                                throw (UndefinedCodeException);

                void
                setNodeString(const CirculateGraph::NodeID & id,
                        const std::string & param, std::string & value)
                                throw (UndefinedCodeException);

                void
                setNodeBool(const CirculateGraph::NodeID & id,
                        const std::string & param, bool value)
                                throw (UndefinedCodeException);

                void
                setLinkInt(const CirculateGraph::LinkID & id,
                        const std::string & param, int value)
                                throw (UndefinedCodeException);

                void
                setLinkDouble(const CirculateGraph::LinkID & id,
                        const std::string & param, double & value)
                                throw (UndefinedCodeException);

                void
                setLinkString(const CirculateGraph::LinkID & id,
                        const std::string & param, std::string & value)
                                throw (UndefinedCodeException);

                void
                setLinkBool(const CirculateGraph::LinkID & id,
                        const std::string & param, bool value)
                                throw (UndefinedCodeException);

                std::vector< std::string >
                getLinkList(std::string linkType);

                std::vector< std::string >
                getNodeList(std::string nodeType);

                //	hydraulicSolver(const hydraulicSolver& orig);
                //	virtual ~hydraulicSolver();
            private:
                SEWRData_new_SPtr sewr_inp;
                CirculateGraph_SPtr sewr_grph;
                //SEWR_LinkDescMap_SPtr sewr_link_map;
                //SEWR_NodeDescMap_SPtr sewr_node_map;
                //OutfallDescMap_SPtr sewr_outfall_map;
                std::vector< error > errs;
                //std::string nodeExtensionDir;
                //std::string linkExtensionDir;
                //std::string connectString;
                //soci::session sql;
                
                void
                calcOrder();
                
                QHash<QString, QPluginLoader> link_factories;
                QHash<QString, QPluginLoader> node_factories;
                QHash<QString, QPluginLoader> data_factories;
                std::vector< ComponentWPtr > calcOrderVec;
                std::vector< NodeWPtr > outfallVec;
                std::vector< NodeWPtr > infallVec;
                

            };

    }

#endif	/* HYDRAULICSOLVER_H */

