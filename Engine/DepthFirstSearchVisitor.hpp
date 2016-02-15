/*
 * DepthFirstSearchVisitor.h
 *
 *  Created on: Apr 7, 2011
 *      Author: jnewman
 */

#ifndef DEPTHFIRSTSEARCHVISITOR_H_
#define DEPTHFIRSTSEARCHVISITOR_H_

#include <boost/graph/depth_first_search.hpp>

namespace SewerNet
  {

    class dfs_visitor : public boost::default_dfs_visitor
      {
      public:
        dfs_visitor(bool & _convergedFlag);

        template< typename Vertex, typename Graph >
          void
          finish_vertex(Vertex v, const Graph & g);

        template< typename Vertex, typename Graph >
          void
          start_vertex(Vertex s, const Graph & g) const;

        template< typename Vertex, typename Graph >
          void
          discover_vertex(Vertex v, const Graph & g) const;

      private:
        bool & convergedFlag;
      };
  }

#endif /* DEPTHFIRSTSEARCHVISITOR_H_ */
