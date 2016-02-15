/*
 * GraphCalculationOrder.h
 *
 *  Created on: Jul 25, 2011
 *      Author: jnewman
 */

#ifndef GRAPHCALCULATIONORDER_H_
#define GRAPHCALCULATIONORDER_H_

#include <boost/graph/depth_first_search.hpp>
#include "CirculateGraph.hpp"

namespace SewerNet
  {

//    class GraphCalculationOrder : public boost::default_dfs_visitor
//      {
//      public:
//        GraphCalculationOrder();
////            virtual
////            ~GraphCalculationOrder();
//
//        template< typename Vertex, typename Graph >
//          void
//          finish_vertex(Vertex v, const Graph & g);
//
//        template< typename Vertex, typename Graph >
//          void
//          start_vertex(Vertex s, const Graph & g) const;
//
//        template< typename Vertex, typename Graph >
//          void
//          discover_vertex(Vertex v, const Graph & g) const;
//
//        void
//        finish_vertex(CirculateGraph::NodeID v, const CirculateGraph & g);
//
//        void
//        start_vertex(CirculateGraph::NodeID v, const CirculateGraph & g) const;
//
//        void
//        discover_vertex(CirculateGraph::NodeID v, const CirculateGraph & g) const;
//      };

  } /* namespace SewerNet */
#endif /* GRAPHCALCULATIONORDER_H_ */
