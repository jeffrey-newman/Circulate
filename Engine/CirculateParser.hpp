/* 
 * File:   ENInpParser.h
 * Author: jnewman
 *
 * Created on July 20, 2010, 9:05 PM
 */

#ifndef SEWERINPPARSER_H
#define	SEWERINPPARSER_H

#include <vector>
#include <map>
#include <string>
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/fusion/include/std_pair.hpp>
//#include <bits/stl_algobase.h>
#include <boost/lambda/lambda.hpp>
#include <boost/bind.hpp>
#include <boost/tuple/tuple.hpp>
//#include "parser_common.h"
//#include "../data/TSData_InputParserTypes.h"


namespace Circulate
{
    
    struct BAWUMTSDataInfo
    {
        BAWUMTSDataInfo() :
        type(""),
        constructor("")
        {
            
        }
        
        BAWUMTSDataInfo(std::string _type, std::string _constructor) :
        type(_type),
        constructor(_constructor)
        {
            
        }
        
        std::string type;
        std::string constructor;
    };
    
}

BOOST_FUSION_ADAPT_STRUCT( //
                          Circulate::BAWUMTSDataInfo,//
                          (std::string, type)//
                          (std::string, constructor)//
)

namespace Circulate
{
    
    typedef std::pair< std::string, BAWUMTSDataInfo > BAWUM_TSData_InfoPair;
    typedef std::map< std::string, BAWUMTSDataInfo > BAWUM_TSData_InfoMap;
    typedef BAWUM_TSData_InfoMap::iterator BAWUM_TSData_InfoIt;
    
    struct TSDataInfoContents
    {
        TSDataInfoContents(BAWUM_TSData_InfoIt & it)
        : name(it->first), type(it->second.type), constructor(
                                                              it->second.constructor)
        {
            
        }
        
        const std::string & name;
        std::string & type;
        std::string & constructor;
    };
    
    
    
}

namespace Circulate
  {

    struct SEWR_Node
      {
        SEWR_Node():
           xCoord(0), yCoord(0)
          {

          }

        SEWR_Node(std::string & _nodeType, double _xCoord, double _yCoord) :
          nodeType(_nodeType), xCoord(_xCoord), yCoord(_yCoord)
          {

          }

        std::string nodeType;
        double xCoord;
        double yCoord;
      };

    struct SEWR_Link
      {
        SEWR_Link()
          {

          }
        SEWR_Link(std::string _startID, std::string _endID,
            std::string _linkType, std::string _status)
        : startID(_startID), endID(_endID), linkType(_linkType), status(_status)
          {

          }
        std::string startID;
        std::string endID;
        std::string linkType;
        std::string status;
      };
  }

BOOST_FUSION_ADAPT_STRUCT(
    Circulate::SEWR_Node,
    (std::string, nodeType)
    (double, xCoord)
    (double, yCoord)
)

BOOST_FUSION_ADAPT_STRUCT(
    Circulate::SEWR_Link,
    (std::string, startID)
    (std::string, endID)
    (std::string, linkType)
    (std::string, status)
)

//namespace Circulate
//  {
//    struct SEWR_CircCnduit
//      {
//        double roughness;
//        double diameter;
//        double length;
//      };
//
//    struct SEWR_NoStoreNde
//      {
//        double groundElev;
//        double burialDepth;
//        double baseDischarge;
//        std::string fileName;
//      };
//
//    struct SEWR_TankNde
//      {
//        double initialStorage;
//        double baseSurfaceArea;
//        double inflowElevation;
//        double outflowElevation;
//        double overflowElevation;
//        double baseElevation;
//      };
//
//    struct SEWR_DemandNde
//      {
//        double baseDemand;
//        std::string fileName;
//      };
//
//    typedef std::vector< std::pair< std::string, double > >
//        SEWR_TopUpNde_sourcePriorityList;
//
//  }
//

//
//BOOST_FUSION_ADAPT_STRUCT(
//    Circulate::SEWR_CircCnduit,
//    (double, roughness)
//    (double, diameter)
//    (double, length)
//)
//
//BOOST_FUSION_ADAPT_STRUCT(
//    Circulate::SEWR_NoStoreNde,
//    (double, groundElev)
//    (double, burialDepth)
//    (double, baseDischarge)
//    (std::string, fileName)
//)
//
//BOOST_FUSION_ADAPT_STRUCT(
//    Circulate::SEWR_TankNde,
//    (double, initialStorage)
//    (double, baseSurfaceArea)
//    (double, inflowElevation)
//    (double, outflowElevation)
//    (double, overflowElevation)
//    (double, baseElevation)
//)
//
//BOOST_FUSION_ADAPT_STRUCT(
//    Circulate::SEWR_DemandNde,
//    (double, baseDemand)
//    (std::string, fileName)
//)
//


namespace Circulate
  {
    typedef std::map< std::string, SEWR_Node > SEWR_Node_Map;
    typedef SEWR_Node_Map::iterator SEWR_Node_It;

    struct NodeContents
      {

        NodeContents(SEWR_Node_It & it) :
          id(it->first), details(it-> second), nodeType(details.nodeType),
              xCoord(details.xCoord), yCoord(details.yCoord)
          {
          }
        const std::string & id;
        SEWR_Node & details;
        std::string & nodeType;
        double & xCoord;
        double & yCoord;

      };

    typedef std::map< std::string, SEWR_Link > SEWR_Link_Map;
    typedef SEWR_Link_Map::iterator SEWR_Link_It;

    struct LinkContents
      {

        LinkContents(SEWR_Link_It & it) :
          id(it->first), details(it->second), startID(details.startID), endID(
              details.endID), linkType(details.linkType),
              status(details.status)
          {

          }
        const std::string & id;
        SEWR_Link & details;
        std::string & startID;
        std::string & endID;
        std::string & linkType;
        std::string & status;

      };

  //    typedef std::map< std::string, std::string > SEWR_Outfall_Map;
  //    typedef SEWR_Outfall_Map::iterator SEWR_Outfall_It;
  //
  //    struct OutfallContents
  //      {
  //
  //        OutfallContents(SEWR_Outfall_It & it) :
  //          id(it->first), outfall_str_constructor(it->second)
  //          {
  //
  //          }
  //        const std::string & id;
  //        std::string & outfall_str_constructor;
  //      };
  }
//
//namespace Circulate
//  {
//    typedef std::map< std::string, SEWR_CircCnduit > SEWR_CircCnduit_Map;
//    typedef SEWR_CircCnduit_Map::iterator SEWR_CircCnduit_It;
//
//    struct CircCnduitContents
//      {
//
//        CircCnduitContents(SEWR_CircCnduit_It & it) :
//          id(it->first), details(it->second), roughness(details.roughness),
//              diameter(details.diameter), length(details.length)
//          {
//
//          }
//        const std::string & id;
//        SEWR_CircCnduit & details;
//        double & roughness;
//        double & diameter;
//        double & length;
//      };
//
//    typedef std::map< std::string, SEWR_NoStoreNde > SEWR_NoStoreNde_Map;
//    typedef SEWR_NoStoreNde_Map::iterator SEWR_NoStoreNde_It;
//
//    struct NoStoreNdeContents
//      {
//
//        NoStoreNdeContents(SEWR_NoStoreNde_It & it) :
//          id(it->first), details(it->second), groundElev(details.groundElev),
//              burialDepth(details.burialDepth), baseDischarge(
//                  details.baseDischarge), fileName(details.fileName)
//          {
//
//          }
//        const std::string & id;
//        SEWR_NoStoreNde & details;
//        double & groundElev;
//        double & burialDepth;
//        double & baseDischarge;
//        std::string & fileName;
//      };
//
//    typedef std::map< std::string, SEWR_DemandNde > SEWR_DemandNde_Map;
//    typedef SEWR_DemandNde_Map::iterator SEWR_DemandNde_It;
//
//    struct DemandNdeContents
//      {
//
//        DemandNdeContents(SEWR_DemandNde_It & it) :
//          id(it->first), details(it->second), baseDemand(details.baseDemand),
//              fileName(details.fileName)
//          {
//
//          }
//        const std::string & id;
//        SEWR_DemandNde & details;
//        double & baseDemand;
//        std::string & fileName;
//      };
//
//    typedef std::map< std::string, SEWR_TankNde > SEWR_TankNde_Map;
//    typedef SEWR_TankNde_Map::iterator SEWR_TankNde_It;
//
//    struct TankNdeContents
//      {
//        TankNdeContents(SEWR_TankNde_It & it) :
//          id(it->first), details(it->second), initialStorage(
//              details.initialStorage),
//              baseSurfaceArea(details.baseSurfaceArea), inflowElevation(
//                  details.inflowElevation), outflowElevation(
//                  details.outflowElevation), overflowElevation(
//                  details.overflowElevation), baseElevation(
//                  details.baseElevation)
//          {
//          }
//        const std::string & id;
//        SEWR_TankNde & details;
//        double & initialStorage;
//        double & baseSurfaceArea;
//        double & inflowElevation;
//        double & outflowElevation;
//        double & overflowElevation;
//        double & baseElevation;
//      };
//
//  }

namespace Circulate
  {

      /**
       * qi provides parsing functionality and is part of boost spirit
       */
      namespace qi = boost::spirit::qi;
      namespace ascii = boost::spirit::ascii;
      namespace phoenix = boost::phoenix;
      
    typedef std::string::const_iterator Str_it; /**< A string const iterator - used for reading the input of the OptFile */

    typedef std::map< std::string, std::string > SEWR_Component_Map;
    typedef std::pair< std::string, std::string > SEWR_Component_StrPair;
    typedef SEWR_Component_Map::iterator SEWR_Component_It;
    typedef std::map< std::string, SEWR_Component_Map > SEWR_Type_Map;
    typedef std::pair< std::string, SEWR_Component_Map > SEWR_Type_Pair;
    typedef SEWR_Type_Map::iterator SEWR_Type_It;

    struct ComponentMap
      {
        ComponentMap(SEWR_Component_It & it) :
          component_name(it->first), str_constructor(it->second)
          {

          }
        ComponentMap(SEWR_Component_StrPair & str_pair) :
          component_name(str_pair.first), str_constructor(str_pair.second)
          {

          }

        const std::string & component_name;
        std::string & str_constructor;
      };

    struct TypeMap
      {
        TypeMap(SEWR_Type_It & it) :
          type_name(it->first), type_component_map(it->second),
              first_component(type_component_map.begin()), last_component(
                  type_component_map.end())
          {

          }

        TypeMap(SEWR_Type_Pair & pair) :
          type_name(pair.first), type_component_map(pair.second),
              first_component(type_component_map.begin()), last_component(
                  type_component_map.end())
          {

          }

        const std::string & type_name;
        SEWR_Component_Map & type_component_map;
        SEWR_Component_It first_component;
        SEWR_Component_It last_component;
      };

    struct SEWRData_new
      {
        SEWRData_new();
        std::string title;
        SEWR_Node_Map nodeData;
        SEWR_Link_Map linkData;
        SEWR_Type_Map componentData;
        BAWUM_TSData_InfoMap tData_map;
        double viscosity;
        int numTimeSteps;
        int timeStepDuration;

      };

    typedef boost::shared_ptr< SEWRData_new > SEWRData_new_SPtr;
      

      
      /**
       * We will be parsing strings. We define a string iterator as Str_it
       */
      typedef std::string::const_iterator Str_it; /**< A string const iterator - used for reading the input of the OptFile */
      
      /**
       * @brief this defines what the parser should skip in the optFile
       * @details think of these are grammers - they define the rules of
       * how the input file should be formatted. This one defines how
       * comments should be formatted - because these are skipped over, as well as white space
       * @see Boost spirit documentation
       */
      struct Skipper : qi::grammar< Str_it >
      {
          Skipper();
          qi::rule< Str_it > skip_it; /**< Rule that does the work. passes over commetns and whitespace in the file */
          qi::rule<Str_it> comment; /**< Rule that detects comments in the file.*/
          char comment_char; /**< Define what the comment character is. I.e. we follow the Epanet inp file tradition of ';' */
      };
      
      /**
       * @brief a custom skipper that skips over blanks but does not skip over end of lines
       * @details think of these as grammers - they define the rules of
       * how the input file should be formatted. This one defines how
       * comments should be formatted - because these are skipped over, as well as white space, but not end of lines
       * @see Boost spirit documentation
       */
      struct No_eol_skip : qi::grammar< Str_it > /**< Rule that does the work. passes over commetns and whitespace in the file */
      {
          No_eol_skip();
          qi::rule< Str_it > skip_it; /**< Rule that does the work. passes over commetns and whitespace in the file */
          qi::rule<Str_it> comment; /**< Rule that detects comments in the file.*/
          char comment_char; /**< Define what the comment character is. I.e. we follow the Epanet inp file tradition of ';' */
      };

    struct SEWRInpParserNew : boost::spirit::qi::grammar< Str_it, No_eol_skip >
      {
      public:
        SEWRInpParserNew();
        SEWRInpParserNew(SEWRData_new_SPtr _parser_data);

        qi::rule< Str_it, std::string
        (), No_eol_skip > r_white_seperated_string;

        qi::rule< Str_it, std::vector< std::string >
        (), No_eol_skip > r_list_white_seperated_string;

        qi::rule< Str_it, double
        (), No_eol_skip > r_double_then_end_of_line;

        qi::rule< Str_it, int
        (), No_eol_skip > r_int_then_end_of_line;

        qi::rule< Str_it, std::string
        (), No_eol_skip > r_header_new;

        qi::rule< Str_it, std::string
        (), No_eol_skip > r_constructor_new;

        qi::rule< Str_it > r_comment; /**< Rule that detects comments in the file.*/

        char r_comment_char; /**< Define what the comment character is. I.e. we follow the Epanet inp file tradition of ';' */

        qi::rule< Str_it, No_eol_skip > r_start;
        qi::rule< Str_it, No_eol_skip > r_type;
        // For the title section
        qi::rule< Str_it, No_eol_skip > r_title_header;
        qi::rule< Str_it, std::string
        (), No_eol_skip > r_title_text;
        qi::rule< Str_it, No_eol_skip > r_title_rule;
        //std::string title;

        //For the Nodes section
        qi::rule< Str_it, No_eol_skip > r_node_header;
        qi::rule< Str_it, std::string
        (), No_eol_skip > r_node_id;
        qi::rule< Str_it, SEWR_Node
        (), No_eol_skip > r_node_info;
        qi::rule< Str_it, std::pair< std::string, SEWR_Node >
        (), No_eol_skip > r_node_datum;
        qi::rule< Str_it, SEWR_Node_Map
        (), No_eol_skip > r_node_data;
        //SEWR_Node_Map NodeData;

        //For the Links section
        qi::rule< Str_it, No_eol_skip > r_link_header;
        qi::rule< Str_it, std::string
        (), No_eol_skip > r_link_id;
        qi::rule< Str_it, SEWR_Link
        (), No_eol_skip > r_link_info;
        qi::rule< Str_it, std::pair< std::string, SEWR_Link >
        (), No_eol_skip > r_link_datum;
        qi::rule< Str_it, SEWR_Link_Map
        (), No_eol_skip > r_link_data;
        //SEWR_Link_Map LinkData;

        //For the Options section
        qi::rule< Str_it, No_eol_skip > r_option_header;
        // qi::rule<Str_it, std::string(), No_eol_skip> r_hydraulics_rule;
        qi::rule< Str_it, double
        (), No_eol_skip > r_viscosity_rule;
        qi::rule< Str_it, int
        (), No_eol_skip > r_numTimeStep_rule;
        qi::rule< Str_it, double
        (), No_eol_skip > r_timeStepDuration_rule;
        // qi::rule<Str_it, int(), No_eol_skip> r_trials_rule;
        // qi::rule<Str_it, double(), No_eol_skip> r_accuracy_rule;
        // qi::rule<Str_it, std::string(), No_eol_skip> r_unbalanced_rule;
        // qi::rule<Str_it, std::string(), No_eol_skip> pat_id_rule;
        // qi::rule<Str_it, double(), No_eol_skip> demand_mult_rule;
        // std::string hydraulics;
        //double viscosity;
        // int trials;
        // double accuracy;
        // std::string unbalanced;
        // int unbalanced_val;
        // std::string pat_id;
        // double demand_mult;
        qi::rule< Str_it, No_eol_skip > r_options_rule;
        qi::rule< Str_it, No_eol_skip > r_end_rule;
          
          //For the data section
          qi::rule< Str_it, No_eol_skip > r_data_header;
          qi::rule< Str_it, BAWUMTSDataInfo
          (), No_eol_skip > r_data_info;
          qi::rule< Str_it, BAWUM_TSData_InfoPair
          (), No_eol_skip > r_data_datum;
          qi::rule< Str_it, BAWUM_TSData_InfoMap
          (), No_eol_skip > r_data_data;

      private:
        SEWRData_new_SPtr parser_data;

        void
        initialise();

        void
        insert();

        std::string type_name;
        std::string component_name;
        std::string component_constructor_string;
      };

    typedef boost::shared_ptr< SEWRInpParserNew > SEWRInpParserNew_SPtr;

  }

//namespace Circulate
//  {
//
//    struct SEWRData
//      {
//        SEWRData();
//        std::string title;
//        SEWR_Node_Map nodeData;
//        SEWR_Link_Map linkData;
//        SEWR_Outfall_Map outfallData;
//        SEWR_CircCnduit_Map circCnduitData;
//        SEWR_NoStoreNde_Map noStoreNdeData;
//        SEWR_DemandNde_Map demandNdeData;
//        SEWR_TankNde_Map tankData;
//        double viscosity;
//        int numTimeSteps;
//        double timeStepDuration;
//      };
//
//    typedef boost::shared_ptr< SEWRData > SEWRData_SPtr;
//
//    struct SEWRInpParser : boost::spirit::qi::grammar< Str_it, No_eol_skip >
//      {
//      public:
//        SEWRInpParser();
//        SEWRInpParser(SEWRData_SPtr _parser_data);
//        //The highest level rule
//        qi::rule< Str_it, No_eol_skip > r_start;
//
//        //        //Generic rules, used a lot.
//        //        qi::rule< Str_it, std::string
//        //        (), No_eol_skip > r_white_seperated_string;
//        //        qi::rule< Str_it, std::string
//        //        (), No_eol_skip > r_string_then_end_of_line;
//        //        qi::rule< Str_it, std::vector< std::string >
//        //        (), No_eol_skip > r_list_white_seperated_string;
//        //        qi::rule< Str_it, double
//        //        (), No_eol_skip > r_double_then_end_of_line;
//        //        qi::rule< Str_it, int
//        //        (), No_eol_skip > r_int_then_end_of_line;
//        //        qi::rule< Str_it, No_eol_skip > r_headers;
//
//        // to filter out comments where required
//        qi::rule< Str_it > r_comment; /**< Rule that detects comments in the file.*/
//        char r_comment_char; /**< Define what the comment character is. I.e. we follow the Epanet inp file tradition of ';' */
//
//        // For the title section
//        qi::rule< Str_it, No_eol_skip > r_title_header;
//        qi::rule< Str_it, std::string
//        (), No_eol_skip > r_title_text;
//        qi::rule< Str_it, No_eol_skip > r_title_rule;
//        //std::string title;
//
//        //For the Nodes section
//        qi::rule< Str_it, No_eol_skip > r_node_header;
//        qi::rule< Str_it, std::string
//        (), No_eol_skip > r_node_id;
//        qi::rule< Str_it, SEWR_Node
//        (), No_eol_skip > r_node_info;
//        qi::rule< Str_it, std::pair< std::string, SEWR_Node >
//        (), No_eol_skip > r_node_datum;
//        qi::rule< Str_it, SEWR_Node_Map
//        (), No_eol_skip > r_node_data;
//        //SEWR_Node_Map NodeData;
//
//        //For the Links section
//        qi::rule< Str_it, No_eol_skip > r_link_header;
//        qi::rule< Str_it, std::string
//        (), No_eol_skip > r_link_id;
//        qi::rule< Str_it, SEWR_Link
//        (), No_eol_skip > r_link_info;
//        qi::rule< Str_it, std::pair< std::string, SEWR_Link >
//        (), No_eol_skip > r_link_datum;
//        qi::rule< Str_it, SEWR_Link_Map
//        (), No_eol_skip > r_link_data;
//        //SEWR_Link_Map LinkData;
//
//        //For the outfalls section
//        qi::rule< Str_it, No_eol_skip > r_outfall_header;
//        qi::rule< Str_it, std::string
//        (), No_eol_skip > r_outfall_id;
//        qi::rule< Str_it, double
//        (), No_eol_skip > r_outfall_info;
//        qi::rule< Str_it, std::pair< std::string, double >
//        (), No_eol_skip > r_outfall_datum;
//        qi::rule< Str_it, SEWR_Outfall_Map
//        (), No_eol_skip > r_outfall_data;
//        //SEWR_Outfall_Map OutfallData;
//
//        //For the circular conduits section
//        qi::rule< Str_it, No_eol_skip > r_circCnduit_header;
//        qi::rule< Str_it, std::string
//        (), No_eol_skip > r_circCnduit_id;
//        qi::rule< Str_it, SEWR_CircCnduit
//        (), No_eol_skip > r_circCnduit_info;
//        qi::rule< Str_it, std::pair< std::string, SEWR_CircCnduit >
//        (), No_eol_skip > r_circCnduit_datum;
//        qi::rule< Str_it, SEWR_CircCnduit_Map
//        (), No_eol_skip > r_circCnduit_data;
//        //SEWR_CircCnduit_Map CircCnduitData;
//
//        //For the no storage nodes
//        qi::rule< Str_it, No_eol_skip > r_noStoreNode_header;
//        qi::rule< Str_it, std::string
//        (), No_eol_skip > r_noStoreNode_id;
//        qi::rule< Str_it, SEWR_NoStoreNde
//        (), No_eol_skip > r_noStoreNode_info1;
//        qi::rule< Str_it, SEWR_NoStoreNde
//        (), No_eol_skip > r_noStoreNode_info2;
//        qi::rule< Str_it, std::pair< std::string, SEWR_NoStoreNde >
//        (), No_eol_skip > r_noStoreNode_datum1;
//        qi::rule< Str_it, std::pair< std::string, SEWR_NoStoreNde >
//        (), No_eol_skip > r_noStoreNode_datum2;
//        qi::rule< Str_it, SEWR_NoStoreNde_Map
//        (), No_eol_skip > r_noStoreNode_data;
//        //SEWR_NoStoreNde_Map NoStoreNdeData;
//
//
//        //For the demand nodes
//        qi::rule< Str_it, No_eol_skip > r_demandNode_header;
//        qi::rule< Str_it, std::string
//        (), No_eol_skip > r_demandNode_id;
//        qi::rule< Str_it, SEWR_DemandNde
//        (), No_eol_skip > r_demandNode_info1;
//        qi::rule< Str_it, SEWR_DemandNde
//        (), No_eol_skip > r_demandNode_info2;
//        qi::rule< Str_it, std::pair< std::string, SEWR_DemandNde >
//        (), No_eol_skip > r_demandNode_datum1;
//        qi::rule< Str_it, std::pair< std::string, SEWR_DemandNde >
//        (), No_eol_skip > r_demandNode_datum2;
//        qi::rule< Str_it, SEWR_DemandNde_Map
//        (), No_eol_skip > r_demandNode_data;
//        //SEWR_NoStoreNde_Map NoStoreNdeData;
//
//        //For the tank nodes
//        qi::rule< Str_it, No_eol_skip > r_tankNode_header;
//        qi::rule< Str_it, std::string
//        (), No_eol_skip > r_tankNode_id;
//        qi::rule< Str_it, SEWR_TankNde
//        (), No_eol_skip > r_tankNode_info1;
//        qi::rule< Str_it, std::pair< std::string, SEWR_TankNde >
//        (), No_eol_skip > r_tankNode_datum;
//        qi::rule< Str_it, SEWR_TankNde_Map
//        (), No_eol_skip > r_tankNode_data;
//        //SEWR_NoStoreNde_Map NoStoreNdeData;
//
//        //For the Options section
//        qi::rule< Str_it, No_eol_skip > r_option_header;
//        // qi::rule<Str_it, std::string(), No_eol_skip> r_hydraulics_rule;
//        qi::rule< Str_it, double
//        (), No_eol_skip > r_viscosity_rule;
//        qi::rule< Str_it, int
//        (), No_eol_skip > r_numTimeStep_rule;
//        qi::rule< Str_it, double
//        (), No_eol_skip > r_timeStepDuration_rule;
//        // qi::rule<Str_it, int(), No_eol_skip> r_trials_rule;
//        // qi::rule<Str_it, double(), No_eol_skip> r_accuracy_rule;
//        // qi::rule<Str_it, std::string(), No_eol_skip> r_unbalanced_rule;
//        // qi::rule<Str_it, std::string(), No_eol_skip> pat_id_rule;
//        // qi::rule<Str_it, double(), No_eol_skip> demand_mult_rule;
//        // std::string hydraulics;
//        //double viscosity;
//        // int trials;
//        // double accuracy;
//        // std::string unbalanced;
//        // int unbalanced_val;
//        // std::string pat_id;
//        // double demand_mult;
//        qi::rule< Str_it, No_eol_skip > r_options_rule;
//        qi::rule< Str_it, No_eol_skip > r_end_rule;
//
//        SEWRData_SPtr parser_data;
//
//        void
//        initialise();
//
//      };
//
//    typedef boost::shared_ptr< SEWRInpParser > SEWRInpParser_SPtr;
//  }

typedef Circulate::SEWRData_new_SPtr SEWRData_new_SPtr;

SEWRData_new_SPtr
getSEWR_Input(std::string fileName);
typedef SEWRData_new_SPtr
getSEWR_Inputer(std::string);

std::ostream &
operator <<(std::ostream& os, Circulate::SEWRData_new m);

std::ostream &
operator <<(std::ostream& os, SEWRData_new_SPtr m);

std::ostream &
print_inp_sp(std::ostream& os, SEWRData_new_SPtr m);

std::ostream &
print_inp(std::ostream& os, Circulate::SEWRData_new m);

#include <stdexcept>

class IFException : public std::runtime_error
{
public:
    IFException();
    IFException(std::string what);
};

class ObjectiveInputError : public IFException
{
public:
    ObjectiveInputError();
    ObjectiveInputError(std::string what);
};

#endif	/* SEWERINPPARSER_H */

