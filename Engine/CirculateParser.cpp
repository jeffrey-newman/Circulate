/* 
 * File:   ENInpParser.cpp
 * Author: jnewman
 * 
 * Created on July 20, 2010, 9:05 PM
 *
 * File is not yet complete. Will continue to implement as required....
 *
 */

#include "SewerInpParser.h"
#include <boost/spirit/include/qi.hpp>
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
//#include <bits/stl_algobase.h>
#include <iostream>
#include <fstream>
#include "parser_exceptions.h"

namespace Circulate
  {

    //Some general parsers we make frequent use of


    SEWRData_new::SEWRData_new() :
      viscosity(0.00000101), numTimeSteps(1), timeStepDuration(86400)
      {
      }

    SEWRInpParserNew::SEWRInpParserNew() :
      SEWRInpParserNew::base_type(r_start), parser_data(new SEWRData_new())
      {
        this->initialise();
      }

    SEWRInpParserNew::SEWRInpParserNew(SEWRData_new_SPtr _parser_data) :
      SEWRInpParserNew::base_type(r_start), parser_data(_parser_data)
      {
        this->initialise();
      }

    void
    SEWRInpParserNew::insert()
      {
        parser_data->componentData[type_name][component_name]
            = component_constructor_string;
      }

    void
    SEWRInpParserNew::initialise()
      {
        using qi::double_;
        using qi::int_;
        using qi::char_;
        using qi::eol;
        using qi::lexeme;
        using qi::space;
        using qi::lit;
        using qi::_val;
        using qi::_1;
        using qi::eps;
        using qi::omit;
        using qi::attr;
        using qi::skip;
        using qi::alnum;
        using qi::no_case;
        using phoenix::ref;
        using phoenix::push_back;
        using phoenix::insert;

        r_white_seperated_string = qi::lexeme[(+(qi::char_ - (qi::space
            | qi::eol)))];

        r_list_white_seperated_string = *r_white_seperated_string >> qi::eol;

        r_double_then_end_of_line = qi::double_ >> qi::eol;

        r_int_then_end_of_line = qi::int_ >> qi::eol;

        char r_comment_char = ';';

        r_comment = qi::lexeme[qi::lit(r_comment_char)
            >> *(qi::char_ - qi::eol) >> qi::eol];

        r_header_new = '[' >> +(qi::char_ - ']') >> ']' >> qi::eol;

        r_constructor_new = qi::lexeme[+(qi::char_ - qi::eol)] >> qi::eol;

        //TITLE
        r_title_header = lit("[TITLE]") >> eol;
        r_title_text = qi::lexeme[+(char_ - qi::lit('['))];
          r_title_rule = r_title_header >> *eol >> r_title_text[phoenix::ref(
            parser_data->title) = _1];

        //NODE
        r_node_header = lit("[NODES]") >> eol;
        r_node_id = r_white_seperated_string;
        r_node_info = r_white_seperated_string >> double_
            >> r_double_then_end_of_line;
        r_node_datum = r_node_id >> r_node_info;
          r_node_data = r_node_header >> *((r_node_datum[insert(phoenix::ref(
            parser_data->nodeData), _1)]) | eol);

        //LINKS
        r_link_header = lit("[LINKS]") >> eol;
        r_link_id = r_white_seperated_string;
        r_link_info = r_white_seperated_string >> r_white_seperated_string
            >> r_white_seperated_string >> r_white_seperated_string >> eol;
        r_link_datum = r_link_id >> r_link_info;
          r_link_data = r_link_header >> *((r_link_datum[insert(phoenix::ref(
            parser_data->linkData), _1)]) | eol);

        //        //OUTFALLS
        //        r_outfall_header = lit("[OUTFALLS]") >> eol;
        //        r_outfall_id = r_white_seperated_string;
        //        r_outfall_info = r_double_then_end_of_line;
        //        r_outfall_datum = r_outfall_id >> r_outfall_info;
        //        r_outfall_data = r_outfall_header >> *((r_outfall_datum[insert(ref(
        //            parser_data->outfallData), _1)]) | eol);

        //OPTIONS
        r_option_header = no_case[lit("[OPTIONS]")] >> eol;
        // r_hydraulics_rule = no_case[lit("HYDRAULICS")] >> r_white_seperated_string[ref(hydraulics) = _1] >> eol;
        r_viscosity_rule = no_case[lit("VISCOSITY")] >> double_[ref(
            parser_data->viscosity) = _1] >> eol;
        r_numTimeStep_rule = no_case[lit("NUM_TIMESTEPS")] >> int_[ref(
            parser_data->numTimeSteps) = _1] >> eol;
        r_timeStepDuration_rule = no_case[lit("TIMESTEP_DURATION")]
            >> int_[ref(parser_data->timeStepDuration) = _1] >> eol;
        // r_trials_rule = no_case[lit("TRIALS")] >> int_[ref(trials) = _1] >> eol;
        // r_accuracy_rule = no_case[lit("ACCURACY")] >> double_[ref(accuracy) = _1] >> eol;
        // r_unbalanced_rule = no_case[lit("UNBALANCED")] >> r_white_seperated_string[ref(unbalanced) = _1] >> int_[ref(unbalanced_val) = _1] >> eol;
        r_options_rule = r_option_header >> *(
        //r_hydraulics_rule |
            r_viscosity_rule | r_numTimeStep_rule | r_timeStepDuration_rule |
            //r_trials_rule |
                //r_accuracy_rule |
                //unbalanced_rule |
                eol);
          
          //DATA
          r_data_header = no_case[lit("[DATA]")] >> eol;
          r_data_info =  r_white_seperated_string >> (r_constructor_new | (attr(std::string("")) >> eol));
          r_data_datum = r_white_seperated_string >> r_data_info;
          r_data_data = r_data_header
          >> *((r_data_datum[insert(phoenix::ref(parser_data->tData_map), _1)]) | eol);
          

        r_type
          = r_header_new[phoenix::ref(type_name) = _1]
          >> *((r_white_seperated_string[phoenix::ref(component_name) = _1]
                >> r_constructor_new[phoenix::ref(component_constructor_string) = _1]
                        - r_header_new)[boost::bind(&SEWRInpParserNew::insert,
                    this)] | eol);

        r_end_rule = lit("[END]") >> eol;

        r_start = *(r_title_rule | r_node_data | r_link_data | r_options_rule
            | r_type | r_end_rule | eol);

      }

  //    void
  //    SEWRInpParser::initialise()
  //      {
  //        using qi::double_;
  //        using qi::int_;
  //        using qi::char_;
  //        using qi::eol;
  //        using qi::lexeme;
  //        using qi::space;
  //        using qi::lit;
  //        using qi::_val;
  //        using qi::_1;
  //        using qi::eps;
  //        using qi::omit;
  //        using qi::attr;
  //        using qi::skip;
  //        using qi::alnum;
  //        using qi::no_case;
  //        using phoenix::ref;
  //        using phoenix::push_back;
  //
  //        //        //Some general parsers we make frequent use of
  //        //        r_headers = lit("[TITLE]") | lit("[JUNCTIONS]") | lit("[OUTFALLS]")
  //        //            | lit("[PIPES]") | lit("[PATTERNS]") | lit("[DISCHARGES]") | lit(
  //        //            "[OPTIONS]") | lit("[COORDINATES]") | lit("[TAGS]") | lit("[END]");
  //        //
  //        //        r_white_seperated_string = lexeme[(+(char_ - (space | eol)))]
  //        //            - r_headers;
  //        //        //white_seperated_string = +alnum - headers;
  //        //        r_list_white_seperated_string = lexeme[*(+(char_ - ((space | eol) | '['
  //        //            | ';')) >> omit[*(space - eol)]) >> eol];
  //        //        //list_white_seperated_string = +white_seperated_string >> eol];
  //        //        //double_then_end_of_line = (lexeme[double_[_val = _1] >> *(space - eol) >> eol])[_val += 0];
  //        //        r_double_then_end_of_line = double_ >> eol;
  //        //        // r_string_then_end_of_line = (lexeme[(+(char_ - ((space - eol) | '[' | ';')) >> omit[*(space - eol)]) >> eol]); THIS ONE DOES NOT SEEM TO WORK???
  //        //        //string_then_end_of_line = r_white_seperated_string >> eol;
  //        //        //int_then_end_of_line = (lexeme[int_[_val = _1] >> *(space - eol) >> eol])[_val += 0];
  //        //        r_int_then_end_of_line = int_ >> eol;
  //        //
  //        //        r_comment_char = ';';
  //        //        r_comment = lexeme[lit(r_comment_char) >> *(qi::char_ - qi::eol)
  //        //            >> qi::eol];
  //
  //        //TITLE
  //        r_title_header = lit("[TITLE]") >> eol;
  //        r_title_text = lexeme[+(char_ - (lit(';') | lit('[')))] - (r_headers
  //            | r_comment);
  //        r_title_rule = r_title_header >> *eol >> r_title_text[ref(
  //            parser_data->title) = _1];
  //
  //        //NODE
  //        r_node_header = lit("[NODES]") >> eol;
  //        r_node_id = r_white_seperated_string;
  //        r_node_info = r_white_seperated_string >> double_
  //            >> r_double_then_end_of_line;
  //        r_node_datum = r_node_id >> r_node_info;
  //        r_node_data = r_node_header >> *((r_node_datum[insert(ref(
  //            parser_data->nodeData), _1)]) | eol);
  //
  //        //LINKS
  //        r_link_header = lit("[LINKS]") >> eol;
  //        r_link_id = r_white_seperated_string;
  //        r_link_info = r_white_seperated_string >> r_white_seperated_string
  //            >> r_white_seperated_string >> r_white_seperated_string >> eol;
  //        r_link_datum = r_link_id >> r_link_info;
  //        r_link_data = r_link_header >> *((r_link_datum[insert(ref(
  //            parser_data->linkData), _1)]) | eol);
  //
  //        //OUTFALLS
  //        r_outfall_header = lit("[OUTFALLS]") >> eol;
  //        r_outfall_id = r_white_seperated_string;
  //        r_outfall_info = r_double_then_end_of_line;
  //        r_outfall_datum = r_outfall_id >> r_outfall_info;
  //        r_outfall_data = r_outfall_header >> *((r_outfall_datum[insert(ref(
  //            parser_data->outfallData), _1)]) | eol);
  //
  //        //CIRCULAR CONDUITS
  //        r_circCnduit_header = lit("[CIRCULAR_CONDUITS]") >> eol;
  //        r_circCnduit_id = r_white_seperated_string;
  //        r_circCnduit_info = double_ >> double_ >> r_double_then_end_of_line;
  //        r_circCnduit_datum = r_circCnduit_id >> r_circCnduit_info;
  //        r_circCnduit_data = r_circCnduit_header
  //            >> *((r_circCnduit_datum[insert(ref(parser_data->circCnduitData),
  //                _1)]) | eol);
  //
  //        //No storage nodes
  //        r_noStoreNode_header = lit("[NO_STORAGE_NODES]") >> eol;
  //        r_noStoreNode_id = r_white_seperated_string;
  //        r_noStoreNode_info1 = double_ >> double_ >> r_double_then_end_of_line
  //            >> attr(std::string("NO_FILE"));
  //        r_noStoreNode_info2 = double_ >> double_ >> double_
  //            >> r_white_seperated_string >> eol;
  //        r_noStoreNode_datum1 = r_noStoreNode_id >> r_noStoreNode_info1;
  //        r_noStoreNode_datum2 = r_noStoreNode_id >> r_noStoreNode_info2;
  //        r_noStoreNode_data = r_noStoreNode_header
  //            >> *((r_noStoreNode_datum1[insert(ref(parser_data->noStoreNdeData),
  //                _1)]) | (r_noStoreNode_datum2[insert(ref(
  //                parser_data->noStoreNdeData), _1)]) | eol);
  //
  //        //Demand nodes
  //        r_demandNode_header = lit("[DEMAND_NODES]") >> eol;
  //        r_demandNode_id = r_white_seperated_string;
  //        r_demandNode_info1 = r_double_then_end_of_line >> attr(std::string(
  //            "NO_FILE"));
  //        r_demandNode_info2 = double_ >> r_white_seperated_string >> eol;
  //        r_demandNode_datum1 = r_demandNode_id >> r_demandNode_info1;
  //        r_demandNode_datum2 = r_demandNode_id >> r_demandNode_info2;
  //        r_demandNode_data = r_demandNode_header
  //            >> *((r_demandNode_datum2[insert(ref(parser_data->demandNdeData),
  //                _1)]) | (r_demandNode_datum1[insert(ref(
  //                parser_data->demandNdeData), _1)]) | eol);
  //
  //        //Tank Nodes
  //        r_tankNode_header = lit("[TANK_NODES]") >> eol;
  //        r_tankNode_id = r_white_seperated_string;
  //        r_tankNode_info1 = double_ >> double_ >> double_ >> double_ >> double_
  //            >> r_double_then_end_of_line;
  //        r_tankNode_datum = r_tankNode_id >> r_tankNode_info1;
  //        r_tankNode_data = r_tankNode_header >> *((r_tankNode_datum[insert(ref(
  //            parser_data->tankData), _1)]) | eol);
  //
  //        //Route downstream links
  //        //No additional information needed....
  //
  //
  //        //OPTIONS
  //        r_option_header = no_case[lit("[OPTIONS]")] >> eol;
  //        // r_hydraulics_rule = no_case[lit("HYDRAULICS")] >> r_white_seperated_string[ref(hydraulics) = _1] >> eol;
  //        r_viscosity_rule = no_case[lit("VISCOSITY")] >> double_[ref(
  //            parser_data->viscosity) = _1] >> eol;
  //        r_numTimeStep_rule = no_case[lit("NUM_TIMESTEPS")] >> int_[ref(
  //            parser_data->numTimeSteps) = _1] >> eol;
  //        r_timeStepDuration_rule = no_case[lit("TIMESTEP_DURATION")]
  //            >> double_[ref(parser_data->timeStepDuration) = _1] >> eol;
  //        // r_trials_rule = no_case[lit("TRIALS")] >> int_[ref(trials) = _1] >> eol;
  //        // r_accuracy_rule = no_case[lit("ACCURACY")] >> double_[ref(accuracy) = _1] >> eol;
  //        // r_unbalanced_rule = no_case[lit("UNBALANCED")] >> r_white_seperated_string[ref(unbalanced) = _1] >> int_[ref(unbalanced_val) = _1] >> eol;
  //
  //        r_options_rule = r_option_header >> *(
  //        //r_hydraulics_rule |
  //            r_viscosity_rule | r_numTimeStep_rule | r_timeStepDuration_rule |
  //            //r_trials_rule |
  //                //r_accuracy_rule |
  //                //unbalanced_rule |
  //                eol);
  //
  //        r_end_rule = lit("[END]") >> eol;
  //
  //        r_start = *(r_title_rule | r_node_data | r_link_data | r_outfall_data
  //            | r_circCnduit_data | r_noStoreNode_data | r_options_rule
  //            | r_demandNode_data | r_tankNode_data | r_end_rule | eol);
  //      }
  //


  //    SEWRInpParser::SEWRInpParser() :
  //      SEWRInpParser::base_type(r_start), parser_data(new SEWRData())
  //      {
  //        this->initialise();
  //      }
  //
  //    SEWRInpParser::SEWRInpParser(SEWRData_SPtr _parser_data) :
  //      SEWRInpParser::base_type(r_start), parser_data(_parser_data)
  //      {
  //        this->initialise();
  //      }
  //
  //    SEWRData::SEWRData() :
  //      viscosity(0.00000101), numTimeSteps(1), timeStepDuration(86400)
  //      {
  //      }
  //
  //  }
  //


  //std::ostream&
  //operator <<(std::ostream& os, Circulate::SEWRData m)
  //  {
  //    os << "[TITLE]  \n";
  //    os << m.title << "\n\n";
  //
  //    os << "[NODES]  \n";
  //    for (Circulate::SEWR_Node_It it = m.nodeData.begin(); it != m.nodeData.end(); ++it)
  //      {
  //        os << Circulate::NodeContents(it).id << "\t" //
  //            << Circulate::NodeContents(it).xCoord << "\t" //
  //            << Circulate::NodeContents(it).yCoord << "\t\n";
  //      }
  //    os << "\n\n";
  //
  //    os << "[LINKS]  \n";
  //    for (Circulate::SEWR_Link_It it = m.linkData.begin(); it != m.linkData.end(); ++it)
  //      {
  //        os << Circulate::LinkContents(it).id << "\t" //
  //            << Circulate::LinkContents(it).startID << "\t" //
  //            << Circulate::LinkContents(it).endID << "\t" //
  //            << Circulate::LinkContents(it).linkType << "\t" //
  //            << Circulate::LinkContents(it).status << "\t\n";
  //      }
  //    os << "\n\n";
  //
  //    os << "[OUTFALLS]  \n";
  //    for (Circulate::SEWR_Outfall_It it = m.outfallData.begin(); it
  //        != m.outfallData.end(); ++it)
  //      {
  //        os << Circulate::OutfallContents(it).id << "\t" //
  //            << Circulate::OutfallContents(it).elevation << "\t\n";
  //      }
  //    os << "\n\n";
  //
  //    os << "[CIRCULAR_CONDUITS]  \n";
  //    for (Circulate::SEWR_CircCnduit_It it = m.circCnduitData.begin(); it
  //        != m.circCnduitData.end(); ++it)
  //      {
  //        os << Circulate::CircCnduitContents(it).id << "\t"
  //            << Circulate::CircCnduitContents(it).roughness << "\t"
  //            << Circulate::CircCnduitContents(it).diameter << "\t"
  //            << Circulate::CircCnduitContents(it).length << "\t\n";
  //      }
  //    os << "\n\n";
  //
  //    os << "[NO_STORAGE_NODES]  \n";
  //    for (Circulate::SEWR_NoStoreNde_It it = m.noStoreNdeData.begin(); it
  //        != m.noStoreNdeData.end(); ++it)
  //      {
  //        os << Circulate::NoStoreNdeContents(it).id << "\t"
  //            << Circulate::NoStoreNdeContents(it).groundElev << "\t"
  //            << Circulate::NoStoreNdeContents(it).burialDepth << "\t"
  //            << Circulate::NoStoreNdeContents(it).baseDischarge << "\t"
  //            << Circulate::NoStoreNdeContents(it).fileName << "\t\n";
  //      }
  //    os << "\n\n";
  //
  //    os << "[DEMAND_NODES]  \n";
  //    for (Circulate::SEWR_DemandNde_It it = m.demandNdeData.begin(); it
  //        != m.demandNdeData.end(); ++it)
  //      {
  //        os << Circulate::DemandNdeContents(it).id << "\t"
  //            << Circulate::DemandNdeContents(it).baseDemand << "\t"
  //            << Circulate::DemandNdeContents(it).fileName << "\t\n";
  //      }
  //    os << "\n\n";
  //
  //    os << "[TANK_NODES]  \n";
  //    for (Circulate::SEWR_TankNde_It it = m.tankData.begin(); it
  //        != m.tankData.end(); ++it)
  //      {
  //        os << Circulate::TankNdeContents(it).id << "\t"
  //            << Circulate::TankNdeContents(it).initialStorage << "\t"
  //            << Circulate::TankNdeContents(it).baseSurfaceArea << "\t"
  //            << Circulate::TankNdeContents(it).inflowElevation << "\t"
  //            << Circulate::TankNdeContents(it).outflowElevation << "\t"
  //            << Circulate::TankNdeContents(it).overflowElevation << "\t"
  //            << Circulate::TankNdeContents(it).baseElevation << "\t\n";
  //      }
  //    os << "\n\n";
  //
  //    os << "[OPTIONS]  \n";
  //    os << "VISCOSITY\t" << m.viscosity << "\t\n";
  //    os << "NUM_TIMESTEPS\t" << m.numTimeSteps << "\t\n";
  //    os << "TIMESTEP_DURATION\t" << m.timeStepDuration << "\t\n";
  //    os << "\n\n";
  //
  //    os << "[END]\t\n" << std::endl;
  //
  //    return os;
  //  }
  //
  //std::ostream&
  //operator <<(std::ostream& os, SEWRData_SPtr m)
  //  {
  //    os << *m;
  //    return os;
  //  }


  }

std::ostream&
operator <<(std::ostream& os, Circulate::SEWRData_new m)
  {
    os << "[TITLE]  \n";
    os << m.title << "\n\n";

    os << "[NODES]  \n";
    for (Circulate::SEWR_Node_It it = m.nodeData.begin(); it != m.nodeData.end(); ++it)
      {
        os << Circulate::NodeContents(it).id << "\t" //
            << Circulate::NodeContents(it).nodeType << "\t" //
            << Circulate::NodeContents(it).xCoord << "\t" //
            << Circulate::NodeContents(it).yCoord << "\t\n";
      }
    os << "\n\n";

    os << "[LINKS]  \n";
    for (Circulate::SEWR_Link_It it = m.linkData.begin(); it != m.linkData.end(); ++it)
      {
        os << Circulate::LinkContents(it).id << "\t" //
            << Circulate::LinkContents(it).startID << "\t" //
            << Circulate::LinkContents(it).endID << "\t" //
            << Circulate::LinkContents(it).linkType << "\t" //
            << Circulate::LinkContents(it).status << "\t\n";
      }
    os << "\n\n";

    for (Circulate::SEWR_Type_It type_it = m.componentData.begin(); type_it
        != m.componentData.end(); ++type_it)
      {
        os << "[" << Circulate::TypeMap(type_it).type_name << "]   \n";
        for (Circulate::SEWR_Component_It component_it =
            Circulate::TypeMap(type_it).first_component; component_it
            != Circulate::TypeMap(type_it).last_component; ++component_it)
          {
            os << Circulate::ComponentMap(component_it).component_name << "\t"
                << Circulate::ComponentMap(component_it).str_constructor
                << "   \n";
          }
        os << "\n\n";
      }

    os << "[OPTIONS]  \n";
    os << "VISCOSITY\t" << m.viscosity << "\t\n";
    os << "NUM_TIMESTEPS\t" << m.numTimeSteps << "\t\n";
    os << "TIMESTEP_DURATION\t" << m.timeStepDuration << "\t\n";
    os << "\n\n";

    os << "[END]\t\n" << std::endl;

    return os;
  }

std::ostream&
operator <<(std::ostream& os, SEWRData_new_SPtr m)
  {
    os << *m;
    return os;
  }

std::ostream &
print_inp_sp(std::ostream& os, SEWRData_new_SPtr m)
  {
    return (os << m);
  }

std::ostream &
print_inp(std::ostream& os, Circulate::SEWRData_new m)
  {
    return (os << m);
  }

