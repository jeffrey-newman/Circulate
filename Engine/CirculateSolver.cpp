/* 
 * File:   CirculateSolver.cpp
 * Author: jnewman
 * 
 * Created on September 27, 2010, 1:09 PM
 */

//#include <soci-sqlite3.h>
#include "Progress.hpp"
#include <boost/timer/timer.hpp>

#include "CirculateSolver.hpp"
#include "DepthFirstSearchVisitor.hpp"
#include "Node.h"
#include "Link.h"

//#include "../data/external/soci_SQLite_session.h"

//#include "soci.h"
//#include "soci-sqlite3.h"

//std::string connectString;
//soci::backend_factory const &backEnd = *soci::factory_sqlite3();

namespace Circulate
    {

        //  CirculateSolver::CirculateSolver(std::string sewrInpName) :
        //    sewr_grph(new CirculateGraph), sewr_link_map(new SEWR_LinkDescMap()),
        //        sewr_node_map(new SEWR_NodeDescMap()),
        //        sewr_outfall_map(new OutfallDescMap())
        //  {
        //    sewr_inp = getSEWR_Input(sewrInpName);
        //    getGraph(sewr_inp, sewr_grph, sewr_link_map, sewr_node_map,
        //        sewr_outfall_map);
        //  }

        CirculateSolver::CirculateSolver(std::string sewrInpName,
                std::string _nodeExtensionDir, std::string _linkExtensionDir, std::string _dataExtensionDir) :
                sewr_inp(getSEWR_Input(sewrInpName))
        //: //sewr_grph(new CirculateGraph(_nodeExtensionDir, _linkExtensionDir))
        //        , nodeExtensionDir(_nodeExtensionDir), linkExtensionDir(
        //                  _linkExtensionDir) //, //
        //connectString(":memory:"), //
        //sql(backEnd, connectString)
            {
                sewr_grph.reset(
                        new CirculateGraph(_nodeExtensionDir, _linkExtensionDir, _dataExtensionDir));
                //sewr_inp = getSEWR_Input(sewrInpName);
                sewr_grph->construct(sewr_inp);
                //getGraph(sewr_inp, sewr_grph, sewr_link_map, sewr_node_map,
                //      sewr_outfall_map, _nodeExtensionDir, _linkExtensionDir); //, sql);
                //init_sql_db();
            }

        void
        CirculateSolver::finalise()
            {

                typedef boost::graph_traits< CirculateGraph >::edge_iterator EdgeIt;
                EdgeIt edge, endE;
                for (boost::tie(edge, endE) = boost::edges(*sewr_grph);
                        edge != endE; ++edge)
                {
                    sewr_grph->getLink(edge).lock()->finalise(*sewr_grph);
                }

                typedef boost::graph_traits< CirculateGraph >::vertex_iterator VerIt;
                VerIt vertex, endV;
                for (boost::tie(vertex, endV) = boost::vertices(*sewr_grph);
                        vertex != endV; ++vertex)
                {
                    sewr_grph->getNode(vertex).lock()->finalise(*sewr_grph);
                }

            }

        void
        CirculateSolver::initialise()
            {
                //init_sql_db();

                //reinitialise all values on edges...
                typedef boost::graph_traits< CirculateGraph >::edge_iterator EdgeIt;
                EdgeIt edge, endE;
                for (boost::tie(edge, endE) = boost::edges(*sewr_grph);
                        edge != endE; ++edge)
                {
                    sewr_grph->getLink(edge).lock()->initialise(*sewr_grph);
                }

                //reinitialise all values on nodes...
                typedef boost::graph_traits< CirculateGraph >::vertex_iterator VerIt;
                VerIt vertex, endV;
                for (boost::tie(vertex, endV) = boost::vertices(*sewr_grph);
                        vertex != endV; ++vertex)
                {
                    sewr_grph->getNode(vertex).lock()->initialise(*sewr_grph);
                }

                //reinitialise graph properties... current time, numtime steps. time step duration

                sewr_grph->currentTimeNumber = 0;
                //These values would have been read in from file.... I suppose...
                //(*sewr_grph)[boost::graph_bundle].numTimeSteps = this->;
                //(*sewr_grph)[boost::graph_bundle].timeStepDuration = this->;

            }

        void
        CirculateSolver::solve()
            {
                boost::timer::auto_cpu_timer t;
                try
                {

                    dfs_visitor vis(sewr_grph->converged);
                    //Initialise the system
                    this->initialise();
                    //Do the depth first search to calc flows in all pipes, and storages at each node. For each system with an outfall.
                    //boost::depth_first_search(*sewr_grph, boost::visitor(vis), std::vector<boost::default_color_type>(boost::num_vertices(*sewr_grph)), );

                    std::clog << "solving:\n";

                    progress_display show_progress(sewr_grph->numTimeSteps);
                    //For each timestep in the simulation....
                    while (sewr_grph->currentTimeNumber < sewr_grph->numTimeSteps)
                    {
                        //std::clog << "\ttime: " << sewr_grph->currentTime << "\n";
                        //pre-timestep ops on edges...
                        typedef boost::graph_traits< CirculateGraph >::edge_iterator EdgeIt;
                        EdgeIt edge, endE;
                        for (boost::tie(edge, endE) = boost::edges(*sewr_grph);
                                edge != endE; ++edge)
                        {
                            sewr_grph->getLink(edge).lock()->preTimestepOps(
                                    *sewr_grph);
                        }

                        //pre-timestep ops on links...
                        typedef boost::graph_traits< CirculateGraph >::vertex_iterator VerIt;
                        VerIt vertex, endV;
                        for (boost::tie(vertex, endV) = boost::vertices(
                                *sewr_grph); vertex != endV; ++vertex)
                        {
                            sewr_grph->getNode(vertex).lock()->preTimestepOps(
                                    *sewr_grph);
                        }

                        //Repeat until stable solution
                        //(*sewr_grph)[boost::graph_bundle].

//                        int convergenceCount = 0;
                        do
                        {
                            sewr_grph->converged = true;
                            // Now the depth first search...

//                            std::cout << "start: ";

                            for (std::vector< ComponentWPtr >::const_iterator it =
                                    sewr_grph->getCalcOrder().begin();
                                    it != sewr_grph->getCalcOrder().end(); ++it)
                            {
//                            	std::cout << "\t" << it->lock()->name();
                                // std::clog << "\t\tnode: " << (*it)->name() << "\n";
                                bool indi_converged = it->lock()->operator()(
                                        *sewr_grph);
//                                if (!indi_converged)
//                                {
//                                	std::cout << " \n" << it->lock()->name() << " did not converge!\n";
//                                }
                                sewr_grph->converged = sewr_grph->converged
                                        && indi_converged;
                            }
//                            ++convergenceCount;

                        }
                        while //((*sewr_grph)[boost::graph_bundle].
                        (sewr_grph->converged == false);
//                        std::cout << "end \n convergence count: " << convergenceCount << "\n";



                        //post-timestep ops on edges...
                      for (boost::tie(edge, endE) = boost::edges(*sewr_grph);                            edge != endE; ++edge)
                        {
                            sewr_grph->getLink(edge).lock()->postTimestepOps(
                                    *sewr_grph);
                        }

                        //post-timestep ops on links...
                        for (boost::tie(vertex, endV) = boost::vertices(
                                *sewr_grph); vertex != endV; ++vertex)
                        {
                            //                        std::clog << getNode(vertex, sewr_grph)->id()
                            //                              << ": post time step ops\n";
                            sewr_grph->getNode(vertex).lock()->postTimestepOps(
                                    *sewr_grph);
                        }

                        ++(sewr_grph->currentTimeNumber);
                        ++show_progress;
                    }

                    this->finalise();
                }
//                catch (soci::soci_error const & e)
//                {
//                    std::clog << "***** DB ERROR: " << e.what() << std::endl;
//                }
                catch (std::runtime_error & e)
                {
                    std::clog << "***** ERROR: " << e.what() << std::endl;
                }
                std::cout << "Engine clock:\t";
            }

        void
        CirculateSolver::print(std::ostream & out) const
            {

                //print values from nodes...
                typedef boost::graph_traits< CirculateGraph >::vertex_iterator VerIt;
                VerIt vertex, endV;
                for (boost::tie(vertex, endV) = boost::vertices(*sewr_grph);
                        vertex != endV; ++vertex)
                {
                    out << std::endl;
                    sewr_grph->getNode(vertex).lock()->print(out);
                }

                //print values from edges...
                typedef boost::graph_traits< CirculateGraph >::edge_iterator EdgeIt;
                EdgeIt edge, endE;
                for (boost::tie(edge, endE) = boost::edges(*sewr_grph);
                        edge != endE; ++edge)
                {
                    out << std::endl;
                    sewr_grph->getLink(edge).lock()->print(out);
                }
            }

        void
        CirculateSolver::print_to_txt(std::string fileName) const
            {
                std::ofstream fileout(fileName.c_str());
                if (fileout.is_open())
                {
                    this->print(fileout);
                }
            }

//        void
//        CirculateSolver::print(SQL_db_Sptr sql) const
//            {
//                //print values from nodes...
//                typedef boost::graph_traits< CirculateGraph >::vertex_iterator VerIt;
//                VerIt vertex, endV;
//                for (boost::tie(vertex, endV) = boost::vertices(*sewr_grph);
//                        vertex != endV; ++vertex)
//                {
//                    std::clog << "Printing from "
//                            << sewr_grph->getNode(vertex).lock()->name()
//                            << std::endl;
//                    sewr_grph->getNode(vertex).lock()->print(sql);
//                }
//
//                //print values from edges...
//                typedef boost::graph_traits< CirculateGraph >::edge_iterator EdgeIt;
//                EdgeIt edge, endE;
//                for (boost::tie(edge, endE) = boost::edges(*sewr_grph);
//                        edge != endE; ++edge)
//                {
//                    std::clog << "Printing from "
//                            << sewr_grph->getLink(edge).lock()->name()
//                            << std::endl;
//                    //sewr_grph->getLink(edge).lock()->print(sql);
//                }
//
//            }

//        void
//        CirculateSolver::print_to_db(std::string fileName) const
//            {
//                SQL_db_Sptr db = make_db(fileName);
//                this->print(db);
//            }

        void
        CirculateSolver::print(H5::H5File h5file) const
            {
                typedef boost::graph_traits< CirculateGraph >::vertex_iterator VerIt;
                typedef boost::graph_traits< CirculateGraph >::edge_iterator EdgeIt;

                boost::timer::auto_cpu_timer t;

                try
                {
                    H5::Exception::dontPrint();
                    //print values from nodes...
                    VerIt vertex, endV;
                    progress_display show_progress(
                            boost::num_edges(*sewr_grph)
                                    + boost::num_vertices(*sewr_grph));
                    for (boost::tie(vertex, endV) = boost::vertices(*sewr_grph);
                            vertex != endV; ++vertex)
                    {
//                  std::clog << "Printing h5 from "
//                        << sewr_grph->getNode(vertex).lock()->name() << std::endl;
                        sewr_grph->getNode(vertex).lock()->print(h5file);
                        ++show_progress;
                    }

                    //print values from edges...

                    EdgeIt edge, endE;
                    for (boost::tie(edge, endE) = boost::edges(*sewr_grph);
                            edge != endE; ++edge)
                    {
//                  std::clog << "Printing h5 from "
//                        << sewr_grph->getLink(edge).lock()->name() << std::endl;
                        sewr_grph->getLink(edge).lock()->print(h5file);
                        ++show_progress;
                    }

                }
//             catch failure caused by the H5File operations
                catch (H5::FileIException & error)
                {
                    error.printError();
                    //return -1;
                }
                // catch failure caused by the DataSet operations
                catch (H5::DataSetIException & error)
                {
                    error.printError();
//                return -1;
                }
                // catch failure caused by the DataSpace operations
                catch (H5::DataSpaceIException & error)
                {
                    error.printError();
//                return -1;
                }
                // catch failure caused by the DataSpace operations
                catch (H5::DataTypeIException & error)
                {
                    error.printError();
//                return -1;
                }

                std::cout << "Print to H5 timer:\t";

            }

        void
        CirculateSolver::print_to_h5(std::string h5fileName) const
            {
                try
                {
                    H5::Exception::dontPrint();

                    H5::H5File file(h5fileName, H5F_ACC_TRUNC);

                    this->print(file);
                } // catch failure caused by the H5File operations
                catch (H5::FileIException & error)
                {
                    error.printError();
                }
            }

        void
        CirculateSolver::printGraph(std::ostream & out) const
            {
                sewr_grph->printGraph(out);
            }

        void
        CirculateSolver::printGraph(const std::string & fileName) const
            {
                sewr_grph->printGraph(fileName);
            }

        //    void
        //    CirculateSolver::saveResults(std::string file) const
        //    {
        //        Circulate::loadOrSaveDb(file, true);
        //    }

        int
        CirculateSolver::getNodeInt(const std::string & id,
                const std::string & param) const throw (UndefinedCodeException)
            {
                return sewr_grph->getNode(id).lock()->getInt(param);
            }

        double
        CirculateSolver::getNodeDouble(const std::string id,
                const std::string param) const throw (UndefinedCodeException)
            {
//            std::clog << "Getting double parameter: " << param << ", from node: " << id << "\n";
//            std::flush(std::cout);
                return sewr_grph->getNode(id).lock()->getDouble(param);
            }

        std::string
        CirculateSolver::getNodeString(const std::string & id,
                const std::string & param) const throw (UndefinedCodeException)
            {
                return sewr_grph->getNode(id).lock()->getString(param);
            }

        bool
        CirculateSolver::getNodeBool(const std::string & id,
                const std::string & param) const throw (UndefinedCodeException)
            {
                return sewr_grph->getNode(id).lock()->getBool(param);
            }

        int
        CirculateSolver::getLinkInt(const std::string & id,
                const std::string & param) const throw (UndefinedCodeException)
            {
                return sewr_grph->getLink(id).lock()->getInt(param);

            }

        double
        CirculateSolver::getLinkDouble(const std::string & id,
                const std::string & param) const throw (UndefinedCodeException)
            {
                return sewr_grph->getLink(id).lock()->getDouble(param);
            }

        std::string
        CirculateSolver::getLinkString(const std::string & id,
                const std::string & param) const throw (UndefinedCodeException)
            {
                return sewr_grph->getLink(id).lock()->getString(param);
            }

        bool
        CirculateSolver::getLinkBool(const std::string & id,
                const std::string & param) const throw (UndefinedCodeException)
            {
                return sewr_grph->getLink(id).lock()->getBool(param);
            }

        int
        CirculateSolver::getNodeInt(const CirculateGraph::NodeID & id,
                const std::string & param) const throw (UndefinedCodeException)
            {
                return sewr_grph->getNode(id).lock()->getInt(param);
            }

        double
        CirculateSolver::getNodeDouble(const CirculateGraph::NodeID & id,
                const std::string & param) const throw (UndefinedCodeException)
            {
                return sewr_grph->getNode(id).lock()->getDouble(param);
            }

        std::string
        CirculateSolver::getNodeString(const CirculateGraph::NodeID & id,
                const std::string & param) const throw (UndefinedCodeException)
            {
                return sewr_grph->getNode(id).lock()->getString(param);
            }

        bool
        CirculateSolver::getNodeBool(const CirculateGraph::NodeID & id,
                const std::string & param) const throw (UndefinedCodeException)
            {
                return sewr_grph->getNode(id).lock()->getBool(param);
            }

        int
        CirculateSolver::getLinkInt(const CirculateGraph::LinkID & id,
                const std::string & param) const throw (UndefinedCodeException)
            {
                return sewr_grph->getLink(id).lock()->getInt(param);
            }

        double
        CirculateSolver::getLinkDouble(const CirculateGraph::LinkID & id,
                const std::string & param) const throw (UndefinedCodeException)
            {
                return sewr_grph->getLink(id).lock()->getDouble(param);
            }

        std::string
        CirculateSolver::getLinkString(const CirculateGraph::LinkID & id,
                const std::string & param) const throw (UndefinedCodeException)
            {
                return sewr_grph->getLink(id).lock()->getString(param);
            }

        bool
        CirculateSolver::getLinkBool(const CirculateGraph::LinkID & id,
                const std::string & param) const throw (UndefinedCodeException)
            {
                return sewr_grph->getLink(id).lock()->getBool(param);
            }

        void
        CirculateSolver::setNodeInt(const std::string & id,
                const std::string & param, int value)
                        throw (UndefinedCodeException)
            {
                return sewr_grph->getNode(id).lock()->setInt(param, value);
            }

        void
        CirculateSolver::setNodeDouble(const std::string & id,
                const std::string & param, double & value)
                        throw (UndefinedCodeException, std::runtime_error)
            {
                return sewr_grph->getNode(id).lock()->setDouble(param, value);
            }

        void
        CirculateSolver::setNodeString(const std::string & id,
                const std::string & param, std::string & value)
                        throw (UndefinedCodeException)
            {
                return sewr_grph->getNode(id).lock()->setString(param, value);
            }

        void
        CirculateSolver::setNodeBool(const std::string & id,
                const std::string & param, bool value)
                        throw (UndefinedCodeException)
            {
                return sewr_grph->getNode(id).lock()->setBool(param, value);
            }

        void
        CirculateSolver::setLinkInt(const std::string & id,
                const std::string & param, int value)
                        throw (UndefinedCodeException)
            {
                return sewr_grph->getLink(id).lock()->setInt(param, value);

            }

        void
        CirculateSolver::setLinkDouble(const std::string & id,
                const std::string & param, double & value)
                        throw (UndefinedCodeException)
            {
                return sewr_grph->getLink(id).lock()->setDouble(param, value);
            }

        void
        CirculateSolver::setLinkString(const std::string & id,
                const std::string & param, std::string & value)
                        throw (UndefinedCodeException)
            {
                return sewr_grph->getLink(id).lock()->setString(param, value);
            }

        void
        CirculateSolver::setLinkBool(const std::string & id,
                const std::string & param, bool value)
                        throw (UndefinedCodeException)
            {
                return sewr_grph->getLink(id).lock()->setBool(param, value);
            }

        void
        CirculateSolver::setNodeInt(const CirculateGraph::NodeID & id,
                const std::string & param, int value)
                        throw (UndefinedCodeException)
            {
                sewr_grph->getNode(id).lock()->setInt(param, value);
            }

        void
        CirculateSolver::setNodeDouble(const CirculateGraph::NodeID & id,
                const std::string & param, double & value)
                        throw (UndefinedCodeException)
            {
                sewr_grph->getNode(id).lock()->setDouble(param, value);
            }

        void
        CirculateSolver::setNodeString(const CirculateGraph::NodeID & id,
                const std::string & param, std::string & value)
                        throw (UndefinedCodeException)
            {
                sewr_grph->getNode(id).lock()->setString(param, value);
            }

        void
        CirculateSolver::setNodeBool(const CirculateGraph::NodeID & id,
                const std::string & param, bool value)
                        throw (UndefinedCodeException)
            {
                sewr_grph->getNode(id).lock()->setBool(param, value);
            }

        void
        CirculateSolver::setLinkInt(const CirculateGraph::LinkID & id,
                const std::string & param, int value)
                        throw (UndefinedCodeException)
            {
                sewr_grph->getLink(id).lock()->setInt(param, value);
            }

        void
        CirculateSolver::setLinkDouble(const CirculateGraph::LinkID & id,
                const std::string & param, double & value)
                        throw (UndefinedCodeException)
            {
                sewr_grph->getLink(id).lock()->setDouble(param, value);
            }

        void
        CirculateSolver::setLinkString(const CirculateGraph::LinkID & id,
                const std::string & param, std::string & value)
                        throw (UndefinedCodeException)
            {
                sewr_grph->getLink(id).lock()->setString(param, value);
            }

        void
        CirculateSolver::setLinkBool(const CirculateGraph::LinkID & id,
                const std::string & param, bool value)
                        throw (UndefinedCodeException)
            {
                sewr_grph->getLink(id).lock()->setBool(param, value);
            }

        std::vector< std::string >
        CirculateSolver::getLinkList(std::string linkType)
            {
                return (sewr_grph->getLinkList(linkType));
            }

        std::vector< std::string >
        CirculateSolver::getNodeList(std::string nodeType)
            {
                return (sewr_grph->getNodeList(nodeType));
            }

        dfs_visitor::dfs_visitor(bool & _convergedFlag) :
                convergedFlag(_convergedFlag)
            {
            }

    //      template< typename Vertex, typename Graph >
    //         void
    //         dfs_visitor::finish_vertex(Vertex v, const Graph & g)
    //            {
    //               debug << "Applying mass balance at node " << g.getNode(v)->name()
    //                     << std::endl;
    //               // Mass balance at the node (route flows downstream)
    //               //g[boost::graph_bundle].converged = g[boost::graph_bundle].converged && getNode(v, g)->operator ()(g);
    //               convergedFlag = convergedFlag && g.getNode(v)->operator ()(g);
    //               // Distribute the discharge downstream (calculate flows in downstream channels
    //               debug << "Routing flows downstream at node "
    //                     << g.getNode(v)->id() << std::endl;
    //               SupplyDownstreamLinkIt down_edge, endDE;
    //               for (boost::tie(down_edge, endDE) = boost::in_edges(v, g);
    //                     down_edge != endDE; ++down_edge)
    //                     {
    //                  debug << "    To edge: " << g.getLink(down_edge)->name()
    //                        << std::endl;
    //                  // g[boost::graph_bundle].converged = g[boost::graph_bundle].converged && getLink(down_edge, g)->operator ()(g);
    //                  convergedFlag = convergedFlag
    //                        && g.getLink(down_edge)->operator ()(g);
    //               }
    //            }
    //
    //      template< typename Vertex, typename Graph >
    //         void
    //         dfs_visitor::start_vertex(Vertex s, const Graph & g) const
    //            {
    //               debug << "Outfall: " << g.getNode(s)->name() << std::endl;
    //            }
    //
    //      template< typename Vertex, typename Graph >
    //         void
    //         dfs_visitor::discover_vertex(Vertex v, const Graph & g) const
    //            {
    //               debug << "Discovered vertex: " << g.getNode(v)->name()
    //                     << std::endl;
    //            }
    }
