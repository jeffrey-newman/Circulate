/* 
 * File:   CirculateController.cpp
 * Author: jnewman
 * 
 * Created on September 27, 2010, 1:09 PM
 */

//#include <soci-sqlite3.h>
#include "Progress.hpp"
#include <boost/timer/timer.hpp>

#include "CirculateController.hpp"
#include "DepthFirstSearchVisitor.hpp"
#include "../Common/Node.hpp"
#include "../Common/Link.hpp"

#include <QObject>
#include <QtPlugin>
#include <QHash>
#include <QPluginLoader>
#include <QTextStream>

//#include "../data/external/soci_SQLite_session.h"

//#include "soci.h"
//#include "soci-sqlite3.h"

//std::string connectString;
//soci::backend_factory const &backEnd = *soci::factory_sqlite3();

namespace Circulate
    {

        //  CirculateController::CirculateController(std::string sewrInpName) :
        //    sewr_grph(new CirculateGraph), sewr_link_map(new SEWR_LinkDescMap()),
        //        sewr_node_map(new SEWR_NodeDescMap()),
        //        sewr_outfall_map(new OutfallDescMap())
        //  {
        //    sewr_inp = getSEWR_Input(sewrInpName);
        //    getGraph(sewr_inp, sewr_grph, sewr_link_map, sewr_node_map,
        //        sewr_outfall_map);
        //  }

        CirculateController::CirculateController(std::string sewrInpName,
                std::string _nodeExtensionDir, std::string _linkExtensionDir, std::string _dataExtensionDir) :
                sewr_inp(getSEWR_Input(sewrInpName))
        //: //sewr_grph(new CirculateGraph(_nodeExtensionDir, _linkExtensionDir))
        //        , nodeExtensionDir(_nodeExtensionDir), linkExtensionDir(
        //                  _linkExtensionDir) //, //
        //connectString(":memory:"), //
        //sql(backEnd, connectString)
            {
                // The link plugins
                QDir link_dir(_linkExtensionDir.c_str());
                QDirIterator iterator1(link_dir.absolutePath(), QDirIterator::Subdirectories);
                while (iterator1.hasNext())
                {
                    iterator1.next();
                    if (!iterator1.fileInfo().isDir())
                    {
                        QString file_name = iterator1.filePath();
                        QPluginLoader plugin_loader(file_name);
                        plugin_loader.load();
                        QObject * plugin = plugin_loader.instance();
                        if (plugin)
                        {
                            //                         ShrFaciltyFactryPtr facilityFactory(qobject_cast<FacilityFactoryInterface *>(plugin));
                            LinkFactoryInterface * link_factory = qobject_cast<LinkFactoryInterface *>(plugin);
                            if (link_factory)
                            {
                                QTextStream(stdout) << "Load of " << link_factory->typify() << " link factory from " << link_dir.absoluteFilePath(file_name).toLatin1().data() << " successful\n";
                                //                             FaciltyFactrySPtr factory(facilityFactory);
                                link_factories.insert(link_factory->typify(), plugin_loader);
                            }
                            else
                            {
                                QTextStream(stdout) << "Load unsuccessful of "
                                << link_dir.absoluteFilePath(file_name).toLatin1().data() << ".Not a facility factory\n";
                            }
                        }
                        else
                        {
                            QTextStream(stdout) << "Load unsuccessful of "
                            << link_dir.absoluteFilePath(file_name).toLatin1().data() << ". Not a plugin\n";
                        }
                    }
                }
                
                // The Node plugins
                QDir node_dir(_nodeExtensionDir.c_str());
                QDirIterator iterator2(node_dir.absolutePath(), QDirIterator::Subdirectories);
                while (iterator2.hasNext())
                {
                    iterator2.next();
                    if (!iterator2.fileInfo().isDir())
                    {
                        QString file_name = iterator2.filePath();
                        QPluginLoader plugin_loader(file_name);
                        plugin_loader.load();
                        QObject * plugin = plugin_loader.instance();
                        if (plugin)
                        {
                            //                         ShrFaciltyFactryPtr facilityFactory(qobject_cast<FacilityFactoryInterface *>(plugin));
                            NodeFactoryInterface * link_factory = qobject_cast<NodeFactoryInterface *>(plugin);
                            if (link_factory)
                            {
                                QTextStream(stdout) << "Load of " << link_factory->typify() << " link factory from " << link_dir.absoluteFilePath(file_name).toLatin1().data() << " successful\n";
                                //                             FaciltyFactrySPtr factory(facilityFactory);
                                link_factories.insert(link_factory->typify(), plugin_loader);
                            }
                            else
                            {
                                QTextStream(stdout) << "Load unsuccessful of "
                                << link_dir.absoluteFilePath(file_name).toLatin1().data() << ".Not a facility factory\n";
                            }
                        }
                        else
                        {
                            QTextStream(stdout) << "Load unsuccessful of "
                            << link_dir.absoluteFilePath(file_name).toLatin1().data() << ". Not a plugin\n";
                        }
                    }
                }
                
                sewr_grph.reset(
                        new CirculateGraph(_nodeExtensionDir, _linkExtensionDir, _dataExtensionDir));
                //sewr_inp = getSEWR_Input(sewrInpName);
                sewr_grph->construct(sewr_inp);
                //getGraph(sewr_inp, sewr_grph, sewr_link_map, sewr_node_map,
                //      sewr_outfall_map, _nodeExtensionDir, _linkExtensionDir); //, sql);
                //init_sql_db();
                
                SEWR_Node_It node;
                for (node = sewr_data->nodeData.begin();
                     node != sewr_data->nodeData.end(); ++node)
                {
                    QString nodeType = NodeContents(node).nodeType;
                    std::string id = NodeContents(node).id;
                    std::string str_constructor =
                    sewr_data->componentData[nodeType][id];
                    
                    std::clog << "creating node " << id << " of type " << nodeType
                    << " at loc: (" << NodeContents(node).xCoord << ", "
                    << NodeContents(node).yCoord << ") With constructor: "
                    << str_constructor << "\n";
                    
                    CirculateGraph::vertex_descriptor v;
                    QHash<QString, QPluginLoader>::const_iterator i = node_factories.find(nodeType);
                    if (i != node_factories.end())
                    {
                        LinkFactoryInterface * link_factory = qobject_cast<LinkFactoryInterface *>(i.value());
                        link_factory->createInstance(id, shared_data, str_constructor);
                        v = boost::add_vertex(temp_vertex, *this);
                        new_node->node_id(v);
                    }
                    else
                    {
                        std::string msg = "trying to construct node of type: "
                        + nodeType
                        + ", but extension for type is not present";
                        throw std::runtime_error(msg);
                    }
                    
                    
                    if (node_factories.count(nodeType) > 0)
                    {
                        NodesMap::iterator nodeConstructorIt = nodes.find(nodeType);
                        if (nodeConstructorIt == nodes.end())
                        {
                            
                        }
                        NodeSPtr new_node(
                                          nodes[nodeType].create(id, shared_data, str_constructor,
                                                                 NodeContents(node).xCoord,
                                                                 NodeContents(node).yCoord));
                        
                        SEWRvertex temp_vertex;
                        
                        this->nodeIDMap.insert(std::make_pair(v, new_node));
                        this->nodeNameMap.insert(
                                                 std::make_pair(new_node->name(), new_node));
                        if (new_node->isOutfall())
                        {
                            outfallVec.push_back(new_node);
                        }
                        if (new_node->isInfall())
                        {
                            infallVec.push_back(new_node);
                        }
                    }
                    else
                    {
                        std::string msg = "trying to construct node of type: "
                        + nodeType + ", but extension for type is not present";
                        throw std::runtime_error(msg);
                    }
                }
                
                SEWR_Link_It link;
                CirculateGraph::LinkID e;
                bool success = false;
                for (link = sewr_data->linkData.begin();
                     link != sewr_data->linkData.end(); ++link)
                {
                    
                    std::string linkType = LinkContents(link).linkType;
                    std::string id = LinkContents(link).id;
                    std::string startID = LinkContents(link).startID;
                    std::string endID = LinkContents(link).endID;
                    std::string str_constructor =
                    sewr_data->componentData[linkType][id];
                    
                    std::clog << "creating " << LinkContents(link).status << " link "
                    << id << " of type " << linkType << " linking " << startID
                    << " to " << endID << " With constructor: "
                    << str_constructor << "\n";
                    
                    LinksMap::iterator linkConstructorIt = links.find(linkType);
                    if (linkConstructorIt == links.end())
                    {
                        std::string msg = "trying to construct link of type: "
                        + linkType + ", but extension for type is not present";
                        throw std::runtime_error(msg);
                    }
                    
                    LinkSPtr new_link(
                                      links[linkType].create(*this, id, startID, endID,
                                                             LinkContents(link).status, str_constructor));
                    
                    //               std::clog << "\tcreated!\n";
                    //               std::clog << "\t\t" << new_link->name() << " from: " << new_link->startNodeID() << " to: " << new_link->endNodeID() << "\n" ;
                    //               std::clog << "\t\t\t i.e. from: " << this->getNode(new_link->startNodeID())->node_id() << " to: " << this->getNode(new_link->endNodeID())->node_id() << "\n";
                    SEWRedge edge;
                    //Make the edge - graph edge direction is opposite to flow direction.
                    boost::tie(e, success) = boost::add_edge(
                                                             this->getNode(new_link->startNodeID()).lock()->node_id(),
                                                             this->getNode(new_link->endNodeID()).lock()->node_id(),
                                                             edge, *this);
                    if (success)
                    {
                        //                   std::clog << "\tpopulating fields of " << id << "\n";
                        new_link->link_id(e);
                        this->linkNameMap.insert(
                                                 std::make_pair(new_link->name(), new_link));
                        this->linkIDMap.insert(std::make_pair(e, new_link));
                        //                  std::clog << "\t\tdone!\n";
                    }
                    else
                    {
                        std::string msg =
                        "trying to construct link of type: " + linkType
                        + ", but either the upstream or downstream node is not present";
                        throw std::runtime_error(msg);
                    }
                    
                }
                
                this->calcOrder();
            }
        
        void
        CirculateController::calcOrder(void)
        {
            
            // First we need to make a vector of vertex descriptors
            std::vector<CirculateGraph::NodeID> vertex_list;
            int sizeoflist = infallVec.size() + outfallVec.size();
            vertex_list.resize(infallVec.size() + outfallVec.size());
            int i = 0;
            for (std::vector< NodeWPtr >::iterator it = infallVec.begin();
                 it != infallVec.end(); ++it)
            {
                vertex_list[i]=it->lock()->node_id();
                ++i;
            }
            for (std::vector< NodeWPtr>::iterator it = outfallVec.begin(); it != outfallVec.end(); ++it)
            {
                vertex_list[i] = it->lock()->node_id();
                ++i;
            }
            
            
            
            calcOrderVec.clear();
            //            GraphCalculationOrder < CirculateGraph::NodeID, CirculateGraph > order_determiniser;
            std::vector< NodeID > nodeOrderVec;
            GraphCalculationOrder order_determiniser(nodeOrderVec);
            
            boost::depth_first_search_VertexList
            (
             *sewr_grph,
             boost::visitor(order_determiniser).root_vertex(vertex_list.front()),
             vertex_list
             );
            
            
            //            for (std::vector< NodeSPtr >::iterator it = infallVec.begin();
            //                  it != infallVec.end(); ++it)
            //                  {
            //               boost::depth_first_search(
            //                     *this,
            //                     boost::visitor(order_determiniser).root_vertex(
            //                           (*it)->node_id()));
            //
            //            }
            
            //Now we build the order in which to calculate.
            for (std::vector< NodeID >::iterator node_it = nodeOrderVec.begin();
                 node_it != nodeOrderVec.end(); ++node_it)
            {
                this->calcOrderVec.push_back(sewr_grph->getNode(*node_it));
                
                CirculateGraph::in_edge_iterator edge, endDE;
                for (boost::tie(edge, endDE) = boost::in_edges(*node_it, *this);
                     edge != endDE; ++edge)
                {
                    this->calcOrderVec.push_back(sewr_grph->getLink(edge));
                    
                }
                
            }
            
        }

        void
        CirculateController::finalise()
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
        CirculateController::initialise()
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
        CirculateController::solve()
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
        CirculateController::print(std::ostream & out) const
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
        CirculateController::print_to_txt(std::string fileName) const
            {
                std::ofstream fileout(fileName.c_str());
                if (fileout.is_open())
                {
                    this->print(fileout);
                }
            }

//        void
//        CirculateController::print(SQL_db_Sptr sql) const
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
//        CirculateController::print_to_db(std::string fileName) const
//            {
//                SQL_db_Sptr db = make_db(fileName);
//                this->print(db);
//            }

        void
        CirculateController::print(H5::H5File h5file) const
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
        CirculateController::print_to_h5(std::string h5fileName) const
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
        CirculateController::printGraph(std::ostream & out) const
            {
                sewr_grph->printGraph(out);
            }

        void
        CirculateController::printGraph(const std::string & fileName) const
            {
                sewr_grph->printGraph(fileName);
            }

        //    void
        //    CirculateController::saveResults(std::string file) const
        //    {
        //        Circulate::loadOrSaveDb(file, true);
        //    }

        int
        CirculateController::getNodeInt(const std::string & id,
                const std::string & param) const throw (UndefinedCodeException)
            {
                return sewr_grph->getNode(id).lock()->getInt(param);
            }

        double
        CirculateController::getNodeDouble(const std::string id,
                const std::string param) const throw (UndefinedCodeException)
            {
//            std::clog << "Getting double parameter: " << param << ", from node: " << id << "\n";
//            std::flush(std::cout);
                return sewr_grph->getNode(id).lock()->getDouble(param);
            }

        std::string
        CirculateController::getNodeString(const std::string & id,
                const std::string & param) const throw (UndefinedCodeException)
            {
                return sewr_grph->getNode(id).lock()->getString(param);
            }

        bool
        CirculateController::getNodeBool(const std::string & id,
                const std::string & param) const throw (UndefinedCodeException)
            {
                return sewr_grph->getNode(id).lock()->getBool(param);
            }

        int
        CirculateController::getLinkInt(const std::string & id,
                const std::string & param) const throw (UndefinedCodeException)
            {
                return sewr_grph->getLink(id).lock()->getInt(param);

            }

        double
        CirculateController::getLinkDouble(const std::string & id,
                const std::string & param) const throw (UndefinedCodeException)
            {
                return sewr_grph->getLink(id).lock()->getDouble(param);
            }

        std::string
        CirculateController::getLinkString(const std::string & id,
                const std::string & param) const throw (UndefinedCodeException)
            {
                return sewr_grph->getLink(id).lock()->getString(param);
            }

        bool
        CirculateController::getLinkBool(const std::string & id,
                const std::string & param) const throw (UndefinedCodeException)
            {
                return sewr_grph->getLink(id).lock()->getBool(param);
            }

        int
        CirculateController::getNodeInt(const CirculateGraph::NodeID & id,
                const std::string & param) const throw (UndefinedCodeException)
            {
                return sewr_grph->getNode(id).lock()->getInt(param);
            }

        double
        CirculateController::getNodeDouble(const CirculateGraph::NodeID & id,
                const std::string & param) const throw (UndefinedCodeException)
            {
                return sewr_grph->getNode(id).lock()->getDouble(param);
            }

        std::string
        CirculateController::getNodeString(const CirculateGraph::NodeID & id,
                const std::string & param) const throw (UndefinedCodeException)
            {
                return sewr_grph->getNode(id).lock()->getString(param);
            }

        bool
        CirculateController::getNodeBool(const CirculateGraph::NodeID & id,
                const std::string & param) const throw (UndefinedCodeException)
            {
                return sewr_grph->getNode(id).lock()->getBool(param);
            }

        int
        CirculateController::getLinkInt(const CirculateGraph::LinkID & id,
                const std::string & param) const throw (UndefinedCodeException)
            {
                return sewr_grph->getLink(id).lock()->getInt(param);
            }

        double
        CirculateController::getLinkDouble(const CirculateGraph::LinkID & id,
                const std::string & param) const throw (UndefinedCodeException)
            {
                return sewr_grph->getLink(id).lock()->getDouble(param);
            }

        std::string
        CirculateController::getLinkString(const CirculateGraph::LinkID & id,
                const std::string & param) const throw (UndefinedCodeException)
            {
                return sewr_grph->getLink(id).lock()->getString(param);
            }

        bool
        CirculateController::getLinkBool(const CirculateGraph::LinkID & id,
                const std::string & param) const throw (UndefinedCodeException)
            {
                return sewr_grph->getLink(id).lock()->getBool(param);
            }

        void
        CirculateController::setNodeInt(const std::string & id,
                const std::string & param, int value)
                        throw (UndefinedCodeException)
            {
                return sewr_grph->getNode(id).lock()->setInt(param, value);
            }

        void
        CirculateController::setNodeDouble(const std::string & id,
                const std::string & param, double & value)
                        throw (UndefinedCodeException, std::runtime_error)
            {
                return sewr_grph->getNode(id).lock()->setDouble(param, value);
            }

        void
        CirculateController::setNodeString(const std::string & id,
                const std::string & param, std::string & value)
                        throw (UndefinedCodeException)
            {
                return sewr_grph->getNode(id).lock()->setString(param, value);
            }

        void
        CirculateController::setNodeBool(const std::string & id,
                const std::string & param, bool value)
                        throw (UndefinedCodeException)
            {
                return sewr_grph->getNode(id).lock()->setBool(param, value);
            }

        void
        CirculateController::setLinkInt(const std::string & id,
                const std::string & param, int value)
                        throw (UndefinedCodeException)
            {
                return sewr_grph->getLink(id).lock()->setInt(param, value);

            }

        void
        CirculateController::setLinkDouble(const std::string & id,
                const std::string & param, double & value)
                        throw (UndefinedCodeException)
            {
                return sewr_grph->getLink(id).lock()->setDouble(param, value);
            }

        void
        CirculateController::setLinkString(const std::string & id,
                const std::string & param, std::string & value)
                        throw (UndefinedCodeException)
            {
                return sewr_grph->getLink(id).lock()->setString(param, value);
            }

        void
        CirculateController::setLinkBool(const std::string & id,
                const std::string & param, bool value)
                        throw (UndefinedCodeException)
            {
                return sewr_grph->getLink(id).lock()->setBool(param, value);
            }

        void
        CirculateController::setNodeInt(const CirculateGraph::NodeID & id,
                const std::string & param, int value)
                        throw (UndefinedCodeException)
            {
                sewr_grph->getNode(id).lock()->setInt(param, value);
            }

        void
        CirculateController::setNodeDouble(const CirculateGraph::NodeID & id,
                const std::string & param, double & value)
                        throw (UndefinedCodeException)
            {
                sewr_grph->getNode(id).lock()->setDouble(param, value);
            }

        void
        CirculateController::setNodeString(const CirculateGraph::NodeID & id,
                const std::string & param, std::string & value)
                        throw (UndefinedCodeException)
            {
                sewr_grph->getNode(id).lock()->setString(param, value);
            }

        void
        CirculateController::setNodeBool(const CirculateGraph::NodeID & id,
                const std::string & param, bool value)
                        throw (UndefinedCodeException)
            {
                sewr_grph->getNode(id).lock()->setBool(param, value);
            }

        void
        CirculateController::setLinkInt(const CirculateGraph::LinkID & id,
                const std::string & param, int value)
                        throw (UndefinedCodeException)
            {
                sewr_grph->getLink(id).lock()->setInt(param, value);
            }

        void
        CirculateController::setLinkDouble(const CirculateGraph::LinkID & id,
                const std::string & param, double & value)
                        throw (UndefinedCodeException)
            {
                sewr_grph->getLink(id).lock()->setDouble(param, value);
            }

        void
        CirculateController::setLinkString(const CirculateGraph::LinkID & id,
                const std::string & param, std::string & value)
                        throw (UndefinedCodeException)
            {
                sewr_grph->getLink(id).lock()->setString(param, value);
            }

        void
        CirculateController::setLinkBool(const CirculateGraph::LinkID & id,
                const std::string & param, bool value)
                        throw (UndefinedCodeException)
            {
                sewr_grph->getLink(id).lock()->setBool(param, value);
            }

        std::vector< std::string >
        CirculateController::getLinkList(std::string linkType)
            {
                return (sewr_grph->getLinkList(linkType));
            }

        std::vector< std::string >
        CirculateController::getNodeList(std::string nodeType)
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
