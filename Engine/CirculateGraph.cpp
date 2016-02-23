/*
 * CirculateGraph.cpp
 *
 *  Created on: Jul 25, 2011
 *      Author: jnewman
 */


//#include <boost/extension/factory.hpp>
//#include <boost/extension/shared_library.hpp>
//#include <boost/extension/type_map.hpp>
//#include <boost/extension/extension.hpp>
//#include <boost/extension/factory_map.hpp>
//#include <boost/extension/filesystem.hpp>
//#include <boost/function.hpp>
//#include <boost/timer/timer.hpp>

#include <boost/graph/graphviz.hpp>
#include <boost/graph/depth_first_search.hpp>

#include "TruncatedDepthFirstSearch.hpp"
#include "CirculateGraph.hpp"
//#include "GraphCalculationOrder.h"
#include "../Common/Common.hpp"



namespace Circulate
   {

      CirculateGraph::CirculateGraph(std::string node_extension_loc,
                         std::string link_extension_loc,  std::string dataExtensionLoc ) :
            BaseGraph()
         {
             
             
             

         }

      CirculateGraph::~CirculateGraph()
         {
//            std::clog << "***************************************************\n"
//                  "****\tDeleting sewer graph\n"
//                  "***************************************************\n";
//
//            for (std::map< LinkName, LinkSPtr >::iterator it =
//                  linkNameMap.begin(); it != linkNameMap.end(); ++it)
//            {
//               std::clog << it->second->name() << ": " << it->second.use_count() << "\n";
//               it->second.reset();
//
//            }
//
//            for (std::map< NodeName, NodeSPtr >::iterator it =
//                  nodeNameMap.begin(); it != nodeNameMap.end(); ++it)
//            {
//               std::clog << it->second->name() << ": " << it->second.use_count() << "\n";
//               it->second.reset();
//
//            }
//
//            linkNameMap.clear();
//            linkIDMap.clear();
//            nodeNameMap.clear();
//            nodeIDMap.clear();
//            calcOrderVec.clear();
//            outfallVec.clear();
//            infallVec.clear();
//
//            nodes.clear();
//            links.clear();

            // TODO Auto-generated destructor stub
         }

      void
      CirculateGraph::printGraph(const std::string & fileName)
         {
            std::ofstream fileout(fileName.c_str());
            if (fileout.is_open())
            {
               printGraph(fileout);
               fileout.close();
            }
         }

      void
      CirculateGraph::printGraph(std::ostream & out)
         {

            boost::timer::auto_cpu_timer t;

            std::map< LinkID, LinkName > eid2e_id;
            std::map< LinkID, std::string > eid2type;
            std::map< LinkID, std::string > eid2startNodeID;
            std::map< LinkID, std::string > eid2endNodeID;
            std::map< LinkID, std::string > eid2status;
            std::map< LinkID, std::string > eid2Label;

            std::map< NodeID, NodeName > vid2v_id;
            std::map< NodeID, std::string > vid2type;
            std::map< NodeID, double > vid2xCoord;
            std::map< NodeID, double > vid2yCoord;
            std::map< NodeID, std::string > vid2Label;

            boost::associative_property_map< std::map< LinkID, LinkName > > e_id_map(
                  eid2e_id);
            boost::associative_property_map< std::map< LinkID, std::string > > etype_map(
                  eid2type);
            boost::associative_property_map< std::map< LinkID, std::string > > startNodeID_map(
                  eid2startNodeID);
            boost::associative_property_map< std::map< LinkID, std::string > > endNodeID_map(
                  eid2endNodeID);
            boost::associative_property_map< std::map< LinkID, std::string > > status_map(
                  eid2status);
            boost::associative_property_map< std::map< LinkID, std::string > > elabel_map(
                  eid2Label);

            boost::associative_property_map< std::map< NodeID, NodeName > > v_id_map(
                  vid2v_id);
            boost::associative_property_map< std::map< NodeID, std::string > > vtype_map(
                  vid2type);
            boost::associative_property_map< std::map< NodeID, double > > xCoord_map(
                  vid2xCoord);
            boost::associative_property_map< std::map< NodeID, double > > yCoord_map(
                  vid2yCoord);
            boost::associative_property_map< std::map< NodeID, std::string > > nlabel_map(
                  vid2Label);

            //iterate over graphs links and nodes....
            LinkIterator link, endlink;
            for (boost::tie(link, endlink) = boost::edges(*this);
                  link != endlink; ++link)
            {

               eid2e_id.insert(
                     std::make_pair(this->getLink(link).lock()->link_id(),
                           this->getLink(link).lock()->name()));
               eid2type.insert(
                     std::make_pair(this->getLink(link).lock()->link_id(),
                           this->getLink(link).lock()->type()));
               eid2startNodeID.insert(
                     std::make_pair(this->getLink(link).lock()->link_id(),
                           this->getLink(link).lock()->startNodeID()));
               eid2endNodeID.insert(
                     std::make_pair(this->getLink(link).lock()->link_id(),
                           this->getLink(link).lock()->endNodeID()));
               eid2status.insert(
                     std::make_pair(this->getLink(link).lock()->link_id(),
                           this->getLink(link).lock()->status()));
               eid2Label.insert(
                     std::make_pair(this->getLink(link).lock()->link_id(),
                           this->getLink(link).lock()->makeLabel()));
            }

            NodeIterator node, endnode;
            for (boost::tie(node, endnode) = boost::vertices(*this);
                  node != endnode; ++node)
            {

               vid2v_id.insert(
                     std::make_pair(this->getNode(node).lock()->node_id(),
                           this->getNode(node).lock()->name()));
               vid2type.insert(
                     std::make_pair(this->getNode(node).lock()->node_id(),
                           this->getNode(node).lock()->type()));
               vid2xCoord.insert(
                     std::make_pair(this->getNode(node).lock()->node_id(),
                           this->getNode(node).lock()->xCoord()));
               vid2yCoord.insert(
                     std::make_pair(this->getNode(node).lock()->node_id(),
                           this->getNode(node).lock()->yCoord()));
               vid2Label.insert(
                     std::make_pair(this->getNode(node).lock()->node_id(),
                           this->getNode(node).lock()->makeLabel()));
            }

            boost::dynamic_properties dp;
            dp.property("e_id", e_id_map);
            dp.property("e_type", etype_map);
            dp.property("startNodeID", startNodeID_map);
            dp.property("endNodeID", endNodeID_map);
            dp.property("status", status_map);
            dp.property("label", elabel_map);
            dp.property("v_id", v_id_map);
            dp.property("v_type", vtype_map);
            dp.property("xCoord", xCoord_map);
            dp.property("yCoord", yCoord_map);
            dp.property("label", nlabel_map);
            boost::write_graphviz_dp(out, *this, dp, "v_id");

            std::cout << "Printing graph timer:\t";
         }

      void
      CirculateGraph::construct(SEWRData_new_SPtr sewr_data)
         {

            boost::timer::auto_cpu_timer t;

            this->linkNameMap.clear();
            this->linkIDMap.clear();
            this->nodeNameMap.clear();
            this->nodeIDMap.clear();
            this->calcOrderVec.clear();
            this->outfallVec.clear();
            this->infallVec.clear();

            this->numTimeSteps = sewr_data->numTimeSteps;
            this->timeStepDuration = sewr_data->timeStepDuration;
            this->viscosity = sewr_data->viscosity;
             
            shared_data.addTSDataSpec(sewr_data->tData_map);

            

//            std::cout << "Constructing model timer:\t";

         }

      

      LinkWPtr
      CirculateGraph::getLink(const LinkID link)
         {
            std::map< LinkID, LinkWPtr >::iterator linkIt = linkIDMap.find(
                  link);
            if (linkIt == linkIDMap.end())
            {
               std::string msg = "could not find link: "
                     + boost::lexical_cast< std::string >(link);
               throw std::runtime_error(msg);
            }
            else
            {
               return (linkIt->second);
            }

         }

      LinkWPtr
      CirculateGraph::getLink(const LinkIterator linkIt)
         {
            std::map< LinkID, LinkWPtr >::iterator link = linkIDMap.find(
                  *linkIt);
            if (link == linkIDMap.end())
            {
               std::string msg = "could not find link: "
                     + boost::lexical_cast< std::string >(*linkIt);
               throw std::runtime_error(msg);
            }
            else
            {
               return (link->second);
            }
         }

      LinkWPtr
      CirculateGraph::getLink(const CirculateGraph::out_edge_iterator link_outedgeIt)
         {
            std::map< LinkID, LinkWPtr >::iterator linkIt = linkIDMap.find(
                  *link_outedgeIt);
            if (linkIt == linkIDMap.end())
            {
               std::string msg = "could not find link: "
                     + boost::lexical_cast< std::string >(*link_outedgeIt);
               throw std::runtime_error(msg);
            }
            else
            {
               return (linkIt->second);
            }
         }

      LinkWPtr
      CirculateGraph::getLink(const CirculateGraph::in_edge_iterator link_inedgeIt)
         {
            std::map< LinkID, LinkWPtr >::iterator linkIt = linkIDMap.find(
                  *link_inedgeIt);
            if (linkIt == linkIDMap.end())
            {
               std::string msg = "could not find link: "
                     + boost::lexical_cast< std::string >(*link_inedgeIt);
               throw std::runtime_error(msg);
            }
            else
            {
               return (linkIt->second);
            }
         }

      LinkWPtr
      CirculateGraph::getLink(const LinkName name)
         {
            std::map< LinkName, LinkSPtr >::iterator linkIt = linkNameMap.find(
                  name);
            if (linkIt == linkNameMap.end())
            {
               std::string msg = "could not find link: " + name;
               throw std::runtime_error(msg);
            }
            else
            {
               return (linkIt->second);
            }
         }

      NodeWPtr
      CirculateGraph::getNode(const NodeID node)
         {
//            std::clog << "getting node by node ID: " << node << "\n";
//            std::flush(std::cout);
            std::map< NodeID, NodeWPtr >::iterator nodeIt = nodeIDMap.find(
                  node);
            if (nodeIt == nodeIDMap.end())
            {
               std::string msg = "Could not find node: "
                     + boost::lexical_cast< std::string >(node);
               throw std::runtime_error(msg);
            }
            else
            {
               return nodeIt->second;
            }

         }

      NodeWPtr
      CirculateGraph::getNode(const NodeIterator nodeIt)
         {
//            std::clog << "getting node by nodeIt: " << *nodeIt << "\n";
//            std::flush(std::clog);
            std::map< NodeID, NodeWPtr >::iterator node = nodeIDMap.find(
                  *nodeIt);
            if (node == nodeIDMap.end())
            {
               std::string msg = "Could not find node: "
                     + boost::lexical_cast< std::string >(*nodeIt);
               throw std::runtime_error(msg);
            }
            else
            {
               return node->second;
            }
         }

      NodeWPtr
      CirculateGraph::getNode(const NodeName name)
         {
//            std::clog << "getting node by name: " << name << "\n";
//            std::flush(std::clog);
//            std::clog << "available nodes: ";
//            std::flush(std::clog);
//            std::clog << nodeNameMap.size() << ": ";
//            std::flush(std::cout);
//            for (std::map< NodeName, NodeSPtr >::iterator nde = nodeNameMap.begin();
//                  nde != nodeNameMap.end(); ++nde)
//                  {
//               std::cout << nde->first;
//            }
//            std::clog << "\n";
//            std::flush(std::clog);

            std::map< NodeName, NodeSPtr >::iterator node = nodeNameMap.find(
                  name);
//            std::clog << "received an iterator to a node...\n";
//            std::flush(std::clog);
            if (node == nodeNameMap.end())
            {
               std::string msg = "Could not find node: " + name;
               throw std::runtime_error(msg);
            }
            else
            {
               return node->second;
            }
         }

      int
      CirculateGraph::num_upstream_links(const NodeID v_id) const
         {
            return boost::out_degree(v_id, *this);
         }

      int
      CirculateGraph::num_upstream_links_supply_node(const NodeID v_id) const
         {
            return boost::out_degree(v_id, *this);
         }

      int
      CirculateGraph::num_downstream_links_demand_node(const NodeID v_id) const
         {
            return boost::out_degree(v_id, *this);
         }

      int
      CirculateGraph::num_downstream_links(const NodeID v_id) const
         {
            return boost::in_degree(v_id, *this);
         }

      int
      CirculateGraph::num_downstream_links_supply_node(const NodeID v_id) const
         {
            return boost::in_degree(v_id, *this);
         }

      int
      CirculateGraph::num_upstream_links_demand_node(const NodeID v_id) const
         {
            return boost::in_degree(v_id, *this);
         }

      const std::vector< ComponentWPtr > &
      CirculateGraph::getCalcOrder()
         {
            return calcOrderVec;
         }

      GraphCalculationOrder::GraphCalculationOrder(
            std::vector< CirculateGraph::NodeID > & _nodeOrderVec) :
            nodeOrderVec(_nodeOrderVec)
         {
            // TODO Auto-generated constructor stub

         }

      //      GraphCalculationOrder::~GraphCalculationOrder()
      //         {
      //            // TODO Auto-generated destructor stub
      //         }

      //         template< typename Vertex, typename Graph >
      //           void
      //           GraphCalculationOrder::finish_vertex(Vertex v, const Graph & g)
      //             {
      //
      //               g.calcOrderVec.push_back(g.getNode(v));
      //
      //               CirculateGraph::in_edge_iterator edge, endDE;
      //               for (boost::tie(edge, endDE) = boost::in_edges(v, g); edge != endDE;
      //                   ++edge)
      //                     {
      //                 g.calcOrderVec.push_back(g.getLink(edge));
      //
      //               }
      //           }
      //
      //       template< typename Vertex, typename Graph >
      //         void
      //         GraphCalculationOrder::start_vertex(Vertex v, const Graph & g) const
      //           {
      //             debug << "Outfall: " << g.getNode(v)->name() << std::endl;
      //           }
      //
      //       template< typename Vertex, typename Graph >
      //         void
      //         GraphCalculationOrder::discover_vertex(Vertex v, const Graph & g) const
      //           {
      //             debug << "Discovered vertex: " << g.getNode(v)->name() << std::endl;
      //           }

      void
      GraphCalculationOrder::finish_vertex(CirculateGraph::NodeID v,
            const CirculateGraph & g)
         {
            nodeOrderVec.push_back(v);
            //            g.calcOrderVec.push_back(g.getNode(v));
            //
            //            CirculateGraph::in_edge_iterator edge, endDE;
            //            for (boost::tie(edge, endDE) = boost::in_edges(v, g); edge != endDE;
            //                  ++edge)
            //                  {
            //               g.calcOrderVec.push_back(g.getLink(edge));
            //
            //            }
         }

      void
      GraphCalculationOrder::start_vertex(CirculateGraph::NodeID v,
            const CirculateGraph & g) const
         {
            //debug << "Outfall: " << g.getNode(v)->name() << std::endl;
         }

      void
      GraphCalculationOrder::discover_vertex(CirculateGraph::NodeID v,
            const CirculateGraph & g) const
         {
            //debug << "Discovered vertex: " << g.getNode(v)->name() << std::endl;
         }

      std::vector< std::string >
      CirculateGraph::getLinkList(std::string type)
         {
            std::vector< std::string > results;
            BOOST_FOREACH(ConstLinkNameSPtrPair & link, linkNameMap)
                  {
//                  std::clog << link.second->type() << "\n";
                     if (link.second->type() == type)
                     {
                        results.push_back(link.first);
                     }
                  }
//            std::clog << results.size();
            return (results);
         }

      std::vector< std::string >
      CirculateGraph::getNodeList(std::string type)
         {
            std::vector< std::string > results;
            BOOST_FOREACH(ConstNodeNameSPtrPair & node, nodeNameMap)
                  {
                     //                  std::clog << link.second->type() << "\n";
                     if (node.second->type() == type)
                     {
                        results.push_back(node.first);
                     }
                  }
            //            std::clog << results.size();
            return (results);
         }

      LinkWPtr
      CirculateGraph::getLink(const LinkID link) const
         {
            std::map< LinkID, LinkWPtr >::const_iterator linkIt =
                  linkIDMap.find(link);
            if (linkIt == linkIDMap.end())
            {
               std::string msg = "could not find link: "
                     + boost::lexical_cast< std::string >(link);
               throw std::runtime_error(msg);
            }
            else
            {
               return (linkIt->second);
            }

         }

      LinkWPtr
      CirculateGraph::getLink(const LinkIterator linkIt) const
         {
            std::map< LinkID, LinkWPtr >::const_iterator link = linkIDMap.find(
                  *linkIt);
            if (link == linkIDMap.end())
            {
               std::string msg = "could not find link: "
                     + boost::lexical_cast< std::string >(*linkIt);
               throw std::runtime_error(msg);
            }
            else
            {
               return (link->second);
            }
         }

      LinkWPtr
      CirculateGraph::getLink(const CirculateGraph::out_edge_iterator link_outedgeIt) const
         {
            std::map< LinkID, LinkWPtr >::const_iterator linkIt =
                  linkIDMap.find(*link_outedgeIt);
            if (linkIt == linkIDMap.end())
            {
               std::string msg = "could not find link: "
                     + boost::lexical_cast< std::string >(*link_outedgeIt);
               throw std::runtime_error(msg);
            }
            else
            {
               return (linkIt->second);
            }
         }

      LinkWPtr
      CirculateGraph::getLink(const CirculateGraph::in_edge_iterator link_inedgeIt) const
         {
            std::map< LinkID, LinkWPtr >::const_iterator linkIt =
                  linkIDMap.find(*link_inedgeIt);
            if (linkIt == linkIDMap.end())
            {
               std::string msg = "could not find link: "
                     + boost::lexical_cast< std::string >(*link_inedgeIt);
               throw std::runtime_error(msg);
            }
            else
            {
               return (linkIt->second);
            }
         }

      LinkWPtr
      CirculateGraph::getLink(const LinkName name) const
         {
            std::map< LinkName, LinkSPtr >::const_iterator linkIt =
                  linkNameMap.find(name);
            if (linkIt == linkNameMap.end())
            {
               std::string msg = "could not find link: " + name;
               throw std::runtime_error(msg);
            }
            else
            {
               return (linkIt->second);
            }
         }

      NodeWPtr
      CirculateGraph::getNode(const NodeID node) const
         {
            //            std::cout << "getting node by node ID: " << node << "\n";
            //            std::flush(std::cout);
            std::map< NodeID, NodeWPtr >::const_iterator nodeIt =
                  nodeIDMap.find(node);
            if (nodeIt == nodeIDMap.end())
            {
               std::string msg = "Could not find node: "
                     + boost::lexical_cast< std::string >(node);
               throw std::runtime_error(msg);
            }
            else
            {
               return nodeIt->second;
            }

         }

      NodeWPtr
      CirculateGraph::getNode(const NodeIterator nodeIt) const
         {
            //            std::cout << "getting node by nodeIt: " << *nodeIt << "\n";
            //            std::flush(std::cout);
            std::map< Nod                std::string msg = "Could not find node: "
                     + boost::lexical_cast< std::string >(*nodeIt);
               throw std::runtime_error(msg);
            }
            else
            {
               return node->second;
            }
         }

      NodeWPtr
      CirculateGraph::getNode(const NodeName name) const
         {
            //            std::cout << "getting node by name: " << name << "\n";
            //            std::flush(std::cout);
            //            std::cout << "available nodes: ";
            //            std::flush(std::clog);
            //            std::clog << nodeNameMap.size() << ": ";
            //            std::flush(std::cout);
            //            for (std::map< NodeName, NodeSPtr >::iterator nde = nodeNameMap.begin();
            //                  nde != nodeNameMap.end(); ++nde)
            //                  {
            //               std::clog << nde->first;
            //            }
            //            std::cout << "\n";
            //            std::flush(std::cout);

            std::map< NodeName, NodeSPtr >::const_iterator node =
                  nodeNameMap.find(name);
            //            std::cout << "received an iterator to a node...\n";
            //            std::flush(std::cout);
            if (node == nodeNameMap.end())
            {
               std::string msg = "Could not find node: " + name;
               throw std::runtime_error(msg);
            }
            else
            {
               return node->second;
            }
         }

   } /* namespace Circulate */
