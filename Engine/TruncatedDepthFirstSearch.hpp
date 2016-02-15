/*
 * new_depth_first_search.h
 *
 *  Created on: Dec 2, 2011
 *      Author: jnewman
 */

#ifndef TRUNCATED_DEPTH_FIRST_SEARCH_H_
#define TRUNCATED_DEPTH_FIRST_SEARCH_H_

//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Copyright 2003 Bruce Barr
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

// Nonrecursive implementation of depth_first_visit_impl submitted by
// Bruce Barr, schmoost <at> yahoo.com, May/June 2003.
//#ifndef BOOST_GRAPH_RECURSIVE_DFS_HPP
//#define BOOST_GRAPH_RECURSIVE_DFS_HPP

#include <boost/graph/depth_first_search.hpp>
#include <QtCore>
#include "CirculateGraph.hpp"

namespace boost {

template<class VertexListGraph, class DFSVisitor, class ColorMap>
void truncated_depth_first_search(const VertexListGraph& g, DFSVisitor vis,
		ColorMap color,
		typename graph_traits<VertexListGraph>::vertex_descriptor start_vertex) {
	typedef typename graph_traits<VertexListGraph>::vertex_descriptor Vertex;
	function_requires<DFSVisitorConcept<DFSVisitor, VertexListGraph> >();
	typedef typename property_traits<ColorMap>::value_type ColorValue;
	typedef color_traits<ColorValue> Color;

	typename graph_traits<VertexListGraph>::vertex_iterator ui, ui_end;
	for (boost::tie(ui, ui_end) = vertices(g); ui != ui_end; ++ui) {
		Vertex u = implicit_cast<Vertex>(*ui);
		put(color, u, Color::white());
		vis.initialize_vertex(u, g);
	}

//          if (start_vertex != implicit_cast< Vertex >(*vertices(g).first))
//          {
	// JN 11 Mar 2012: I do not understand this. Why do I not do the depth first search impl. if the start vertex is the first vertex in the graph.
	// What is so special... it seemeds that vertices(g).first returns the first node I insert into the graph structure!
	// According to the boost doc, this if statement should be doing: "if there is a starting vertex s" then "call DFS-VISIT(G, s)"
	vis.start_vertex(start_vertex, g);
	detail::depth_first_visit_impl(g, start_vertex, vis, color,
			detail::nontruth2());
//          }

	// vis.finish_vertex(start_vertex, g);

//    for (boost::tie(ui, ui_end) = vertices(g); ui != ui_end; ++ui) {
//      Vertex u = implicit_cast<Vertex>(*ui);
//      ColorValue u_color = get(color, u);
//      if (u_color == Color::white()) {       vis.start_vertex(u, g);
//        detail::depth_first_visit_impl(g, u, vis, color, detail::nontruth2());
//      }
//    }
}

template<class VertexListGraph, class DFSVisitor, class ColorMap>
void truncated_depth_first_search(const VertexListGraph& g, DFSVisitor vis,
		ColorMap color) {
	typedef typename boost::graph_traits<VertexListGraph>::vertex_iterator vi;
	std::pair<vi, vi> verts = vertices(g);
	if (verts.first == verts.second) {
		qDebug() << "No vertices in graph";
		return;
	}

	truncated_depth_first_search(g, vis, color, *verts.first);
}

// Named Parameter Variant
template<class VertexListGraph, class P, class T, class R>
void truncated_depth_first_search(const VertexListGraph& g,
		const bgl_named_params<P, T, R>& params) {
	typedef typename boost::graph_traits<VertexListGraph>::vertex_iterator vi;
	std::pair<vi, vi> verts = vertices(g);
	if (verts.first == verts.second) {
		qDebug() << "No vertices in graph";
		qDebug() << *(verts.first);
		return;
	}
	using namespace boost::graph::keywords;
	typedef bgl_named_params<P, T, R> params_type;
	BOOST_GRAPH_DECLARE_CONVERTED_PARAMETERS(params_type, params)
	truncated_depth_first_search(g,
			arg_pack[_visitor | make_dfs_visitor(null_visitor())],
			boost::detail::make_color_map_from_arg_pack(g, arg_pack),
			arg_pack[_root_vertex | *vertices(g).first]);
}
    
    
    
    

template<class VertexListGraph, class DFSVisitor, class ColorMap>
void depth_first_search_VertexList(const VertexListGraph& g, DFSVisitor vis,
		ColorMap color,
		std::vector<typename graph_traits<VertexListGraph>::vertex_descriptor> & vertexList) {
	typedef typename graph_traits<VertexListGraph>::vertex_descriptor Vertex;
	function_requires<DFSVisitorConcept<DFSVisitor, VertexListGraph> >();
	typedef typename property_traits<ColorMap>::value_type ColorValue;
	typedef color_traits<ColorValue> Color;

	typename graph_traits<VertexListGraph>::vertex_iterator ui, ui_end;
	for (boost::tie(ui, ui_end) = vertices(g); ui != ui_end; ++ui) {
		Vertex u = implicit_cast<Vertex>(*ui);
		put(color, u, Color::white());
		vis.initialize_vertex(u, g);
	}

	//          if (start_vertex != implicit_cast< Vertex >(*vertices(g).first))
	//          {
	// JN 11 Mar 2012: I do not understand this. Why do I not do the depth first search impl. if the start vertex is the first vertex in the graph.
	// What is so special... it seemeds that vertices(g).first returns the first node I insert into the graph structure!
	// According to the boost doc, this if statement should be doing: "if there is a starting vertex s" then "call DFS-VISIT(G, s)"

    if (vertexList.empty()) {
		qDebug() << "No vertices in vector";
		return;
	}
    
    
	Vertex start_vertex = *(vertexList.begin());
	vis.start_vertex(start_vertex, g);

	for (typename std::vector<Vertex>::iterator it = vertexList.begin();
			it != vertexList.end(); ++it)
	{
      detail::depth_first_visit_impl(g, *it, vis, color,
				detail::nontruth2());
	}

	// vis.finish_vertex(start_vertex, g);

	//    for (boost::tie(ui, ui_end) = vertices(g); ui != ui_end; ++ui) {
	//      Vertex u = implicit_cast<Vertex>(*ui);
	//      ColorValue u_color = get(color, u);
	//      if (u_color == Color::white()) {       vis.start_vertex(u, g);
	//        detail::depth_first_visit_impl(g, u, vis, color, detail::nontruth2());
	//      }
	//    }
}
    
  template<typename VertexListGraph, typename DFSVisitor>
    void depth_first_search_VertexList(const VertexListGraph& g,
                                       const DFSVisitor vis,
                                       std::vector<typename graph_traits<VertexListGraph>::vertex_descriptor > & VertexList)
    {
          // we need to make, somehow, the colour map from arg_pack...
      
          ///SOme thing does not work here..........
      typedef typename boost::property_map<VertexListGraph, boost::vertex_color_t>::type color_map_t;
      color_map_t colourMap;
      depth_first_search_VertexList(g, vis, boost::color_map(colourMap), VertexList);
      
      
    }


// Named Parameter Variant
template<class VertexListGraph, class P, class T, class R>
void depth_first_search_VertexList(const VertexListGraph& g,
		const bgl_named_params<P, T, R>& params,
		std::vector<typename graph_traits<VertexListGraph>::vertex_descriptor > & VertexList) {
	typedef typename boost::graph_traits<VertexListGraph>::vertex_iterator vi;
	std::pair<vi, vi> verts = vertices(g);
	if (verts.first == verts.second) {
		qDebug() << "No vertices in graph";
		qDebug() << *(verts.first);
		return;
	}
	using namespace boost::graph::keywords;
	typedef bgl_named_params<P, T, R> params_type;
	BOOST_GRAPH_DECLARE_CONVERTED_PARAMETERS(params_type, params)
	depth_first_search_VertexList(g,
			arg_pack[_visitor | make_dfs_visitor(null_visitor())],
			boost::detail::make_color_map_from_arg_pack(g, arg_pack),
			VertexList);
}



}    // namespace boost

//#ifdef BOOST_GRAPH_USE_MPI
//#  include <boost/graph/distributed/depth_first_search.hpp>
//#endif

#endif /* TRUNCATED_DEPTH_FIRST_SEARCH_H_ */
