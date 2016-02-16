/*
 * CirculateGraph.h
 *
 *  Created on: Jul 25, 2011
 *      Author: jnewman
 */

#ifndef CirculateGraph_H_
#define CirculateGraph_H_

#include <vector>
#include <map>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>

#include <boost/shared_ptr.hpp>

//#include <boost/extension/factory.hpp>
//#include <boost/extension/shared_library.hpp>
//#include <boost/extension/type_map.hpp>
//#include <boost/extension/extension.hpp>
//#include <boost/extension/factory_map.hpp>
//#include <boost/extension/filesystem.hpp>
#include <boost/function.hpp>

#include "CirculateParser.hpp"
//#include "GraphCalculationOrder.h"
//#include "../data/SharedData.h"


#include <QObject>
#include <QtPlugin>
#include <QHash>
#include <QPluginLoader>


namespace Circulate
   {

      struct SEWRvertex
         {
            SEWRvertex()
               {

               }
            std::string tag;

         };
      struct SEWRedge
         {
            SEWRedge()
               {

               }
            std::string tag;
         };

      typedef boost::adjacency_list< boost::vecS, boost::vecS,
            boost::bidirectionalS, SEWRvertex, SEWRedge > BaseGraph;

      class Component;
      typedef boost::shared_ptr< Component > ComponentSPtr;
      typedef boost::weak_ptr< Component > ComponentWPtr;

      class Node;
      typedef boost::shared_ptr< Node > NodeSPtr;
      typedef boost::weak_ptr< Node > NodeWPtr;

      class Link;
      typedef boost::shared_ptr< Link > LinkSPtr;
      typedef boost::weak_ptr< Link > LinkWPtr;

      class CirculateGraph;
      typedef boost::shared_ptr< CirculateGraph > CirculateGraph_SPtr;
      typedef boost::scoped_ptr< CirculateGraph > CirculateGraph_ScPtr;

//      class GraphCalculationOrder;

      class CirculateGraph : public BaseGraph
         {
            //friend class GraphCalculationOrder;
         public:
            typedef BaseGraph::edge_descriptor LinkID;
            typedef BaseGraph::vertex_descriptor NodeID;
            typedef BaseGraph::edge_iterator LinkIterator;
            typedef BaseGraph::vertex_iterator NodeIterator;
            typedef std::string LinkName;
            typedef std::string NodeName;
            typedef boost::graph_traits< CirculateGraph >::out_edge_iterator SupplyUpstreamLinkIt;
            typedef boost::graph_traits< CirculateGraph >::out_edge_iterator DemandDownstreamLinkIt;
            typedef boost::graph_traits< CirculateGraph >::in_edge_iterator SupplyDownstreamLinkIt;
            typedef boost::graph_traits< CirculateGraph >::in_edge_iterator DemandUpstreamLinkIt;

            /**
             *  Constructor of Circulate graph. From the three directories, we recurse through subdirectories finding the respective plugins.
             */
            CirculateGraph(std::string nodeExtensionLoc,
                     std::string linkExtensionLoc, std::string dataExtensionLoc);

            virtual
            ~CirculateGraph();

            bool
            addLink();

            void
            construct(SEWRData_new_SPtr sewr_data);

            LinkWPtr
            getLink(const LinkID link);

            LinkWPtr
            getLink(const LinkIterator linkIt);

            LinkWPtr
            getLink(const CirculateGraph::out_edge_iterator link_outedgeIt);

            LinkWPtr
            getLink(const CirculateGraph::in_edge_iterator link_inedgeIt);

            LinkWPtr
            getLink(const LinkName name);

            LinkWPtr
            getLink(const LinkID link) const;

            LinkWPtr
            getLink(const LinkIterator linkIt) const;

            LinkWPtr
            getLink(const CirculateGraph::out_edge_iterator link_outedgeIt) const;

            LinkWPtr
            getLink(const CirculateGraph::in_edge_iterator link_inedgeIt) const;

            LinkWPtr
            getLink(const LinkName name) const;

            NodeWPtr
            getNode(const NodeID node);

            NodeWPtr
            getNode(const NodeIterator nodeIt);

            NodeWPtr
            getNode(const NodeName name);

////        NodeWPtr
////        getNode(const NodeID node);
//
//        NodeWPtr
//        getNode(const NodeIterator nodeIt);
//
//        NodeWPtr
//        getNode(const NodeName name);

            NodeWPtr
            getNode(const NodeID node) const;

            NodeWPtr
            getNode(const NodeIterator nodeIt) const;

            NodeWPtr
            getNode(const NodeName name) const;

//        NodeWPtr
//        getNode(const NodeID node) const;
//
//        NodeWPtr
//        getNode(const NodeIterator nodeIt) const;
//
//        NodeWPtr
//        getNode(const NodeName name) const;

            int
            num_upstream_links(const NodeID v_id) const;

            int
            num_upstream_links_supply_node(const NodeID v_id) const;

            int
            num_downstream_links_demand_node(const NodeID v_id) const;

            int
            num_downstream_links(const NodeID v_id) const;

            int
            num_downstream_links_supply_node(const NodeID v_id) const;

            int
            num_upstream_links_demand_node(const NodeID v_id) const;

            void
            printGraph(const std::string & fileName);

            void
            printGraph(std::ostream & out);

            const std::vector< ComponentWPtr > &
            getCalcOrder(void);

            std::vector< std::string >
            getLinkList(std::string type);

            std::vector< std::string >
            getNodeList(std::string type);

            /**
             * The time at which the simulation is at. Incremented at the end of a time step
             * IUWMod keeps track of time in 1 second increments!
             */
            int currentTimeNumber;
            int numTimeSteps;
            int timeStepDuration;
            bool converged;
            double viscosity;

         private:

            void
            calcOrder(void);

            typedef std::pair< LinkName, LinkSPtr > LinkNameSPtrPair;
            typedef std::pair< const LinkName, LinkSPtr > ConstLinkNameSPtrPair;
            typedef std::pair< NodeName, NodeSPtr > NodeNameSPtrPair;
            typedef std::pair< const NodeName, NodeSPtr > ConstNodeNameSPtrPair;

            std::map< LinkName, LinkSPtr > linkNameMap;
            std::map< LinkID, LinkWPtr > linkIDMap;
            std::map< NodeName, NodeSPtr > nodeNameMap;
            std::map< NodeID, NodeWPtr > nodeIDMap;
            std::vector< ComponentWPtr > calcOrderVec;
            std::vector< NodeWPtr > outfallVec;
            std::vector< NodeWPtr > infallVec;
             
             

//            typedef std::map< std::string,
//                  boost::extensions::factory< Node, std::string, SharedData&, std::string,
//                        double, double > > NodesMap;
//
//            typedef std::map< std::string,
//                  boost::extensions::factory< Link, CirculateGraph &, std::string,
//                        std::string, std::string, std::string, std::string > > LinksMap;
//
//            boost::extensions::type_map types;
//            NodesMap nodes;
//            LinksMap links;
//            SharedData & shared_data;
             
             QHash<QString, QPluginLoader> link_factories;
             QHash<QString, QPluginLoader> node_factories;
             QHash<QString, QPluginLoader> data_factories;

         };

      class GraphCalculationOrder : public boost::default_dfs_visitor
         {
         public:
            GraphCalculationOrder(
                  std::vector< CirculateGraph::NodeID > & _nodeOrderVec);
            //            virtual
            //            ~GraphCalculationOrder();

//            template< typename Vertex, typename Graph >
//               void
//               finish_vertex(Vertex v, Graph & g);
//
//            template< typename Vertex, typename Graph >
//               void
//               start_vertex(Vertex s, const Graph & g) const;
//
//            template< typename Vertex, typename Graph >
//               void
//               discover_vertex(Vertex v, const Graph & g) const;

            void
            finish_vertex(CirculateGraph::NodeID v, const CirculateGraph & g);

            void
            start_vertex(CirculateGraph::NodeID v, const CirculateGraph & g) const;

            void
            discover_vertex(CirculateGraph::NodeID v, const CirculateGraph & g) const;

         private:
            std::vector< CirculateGraph::NodeID > & nodeOrderVec;
         };

   } /* namespace Circulate */
#endif /* CirculateGraph_H_ */
