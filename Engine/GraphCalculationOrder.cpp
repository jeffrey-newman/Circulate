/*
 * GraphCalculationOrder.cpp
 *
 *  Created on: Jul 25, 2011
 *      Author: jnewman
 */

#include "GraphCalculationOrder.hpp"
#include "CirculateGraph.hpp"
#include "Debug.hpp"

namespace SewerNet
  {

//    GraphCalculationOrder::GraphCalculationOrder()
//      {
//        // TODO Auto-generated constructor stub
//
//      }
//
////      GraphCalculationOrder::~GraphCalculationOrder()
////         {
////            // TODO Auto-generated destructor stub
////         }
//
//    template< typename Vertex, typename Graph >
//      void
//      GraphCalculationOrder::finish_vertex(Vertex v, const Graph & g)
//        {
//
//          g.calcOrder.push_back(g.getNode(v));
//
//          CirculateGraph::in_edge_iterator edge, endDE;
//          for (boost::tie(edge, endDE) = boost::in_edges(v, g); edge != endDE;
//              ++edge)
//                {
//            g.calcOrder.push_back(g.getLink(edge));
//
//          }
//      }
//
//  template< typename Vertex, typename Graph >
//    void
//    GraphCalculationOrder::start_vertex(Vertex v, const Graph & g) const
//      {
//        debug << "Outfall: " << g.getNode(v)->name() << std::endl;
//      }
//
//  template< typename Vertex, typename Graph >
//    void
//    GraphCalculationOrder::discover_vertex(Vertex v, const Graph & g) const
//      {
//        debug << "Discovered vertex: " << g.getNode(v)->name() << std::endl;
//      }
//
//
//    void
//    GraphCalculationOrder::finish_vertex(CirculateGraph::NodeID v, const CirculateGraph & g)
//      {
//
//        g.calcOrderVec.push_back(g.getNode(v));
//
//        CirculateGraph::in_edge_iterator edge, endDE;
//        for (boost::tie(edge, endDE) = boost::in_edges(v, g); edge != endDE;
//            ++edge)
//              {
//          g.calcOrderVec.push_back(g.getLink(edge));
//
//        }
//    }
//
//
//  void
//  GraphCalculationOrder::start_vertex(CirculateGraph::NodeID v, const CirculateGraph & g) const
//    {
//      debug << "Outfall: " << g.getNode(v)->name() << std::endl;
//    }
//
//
//  void
//  GraphCalculationOrder::discover_vertex(CirculateGraph::NodeID v, const CirculateGraph & g) const
//    {
//      debug << "Discovered vertex: " << g.getNode(v)->name() << std::endl;
//    }

} /* namespace SewerNet */
