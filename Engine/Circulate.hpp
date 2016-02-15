




/*
 * Conduit.h
 *
 *  Created on: Sep 9, 2011
 *      Author: jnewman
 */


#ifndef RUNTIMEERRORS_H_
#define RUNTIMEERRORS_H_

#include <exception>
#include <stdexcept>

namespace Circulate
{
    class UndefinedCodeException : public std::invalid_argument
    {
    public:
        explicit
        UndefinedCodeException(const std::string & _what) :
        std::invalid_argument(_what)
        {
            
        }
    };
}

#endif /* RUNTIMEERRORS_H_ */

#ifndef SOLVER_H
#define SOLVER_H

//#include <boost/graph/graph_traits.hpp>

#include <fstream>
#include <iostream>
//#include "../data/sewernet_soci.h"
#include "../utils/RuntimeErrors.h"
//#include "CirculateGraph.h"
//#include "../parsers/SewerInpParser.h"
//#include "../utils/debug.h"
//#include "../data/hdf5/c++/src/H5Cpp.h"
//#include "../data/hdf5/src/hdf5.h"

namespace Circulate
   {

      struct error
         {
            std::string type;
            std::string desc;
            std::string loc;
         };

      class CirculateSolver
         {
         public:
            //        HydraulicSolver(std::string sewrInpName);
            CirculateSolver(std::string sewrInpName,
                  std::string nodeExtensionDir, std::string linkExtensionDir);

            void
            solve();

            void
            initialise();

            void
            finalise();

            void
            print(std::ostream & out) const; //print results to text file
            void
            print_to_txt(std::string fileName) const;
//        void
//        print(SQL_db_Sptr sql) const; //print results to database
            void
            print_to_db(std::string fileName) const;
//        void
//        print(H5::H5File h5file) const;
            void
            print_to_h5(std::string h5fileName) const; // The new file format (faster... hopefully?)

            void
            printGraph(std::ostream & out) const;

            void
            printGraph(const std::string & fileName) const;

            //            void
            //            saveResults(std::string file = "results.db") const;

            //********************************************************************//
            //                         GETTERS                                    //
            //********************************************************************//

            int
            getNodeInt(const std::string & id, const std::string & param) const
                  throw (UndefinedCodeException);

            double
            getNodeDouble(const std::string id, const std::string param) const
                  throw (UndefinedCodeException);

            std::string
            getNodeString(const std::string & id, const std::string & param) const
                  throw (UndefinedCodeException);

            bool
            getNodeBool(const std::string & id, const std::string & param) const
                  throw (UndefinedCodeException);

            int
            getLinkInt(const std::string & id, const std::string & param) const
                  throw (UndefinedCodeException);

            double
            getLinkDouble(const std::string & id, const std::string & param) const
                  throw (UndefinedCodeException);

            std::string
            getLinkString(const std::string & id, const std::string & param) const
                  throw (UndefinedCodeException);

            bool
            getLinkBool(const std::string & id, const std::string & param) const
                  throw (UndefinedCodeException);

//        int
//        getNodeInt(const CirculateGraph::NodeID & id, const std::string & param) const
//        throw (UndefinedCodeException);

//        double
//        getNodeDouble(const CirculateGraph::NodeID & id, const std::string & param) const
//        throw (UndefinedCodeException);
//
//        std::string
//        getNodeString(const CirculateGraph::NodeID & id, const std::string & param) const
//        throw (UndefinedCodeException);
//
//        bool
//        getNodeBool(const CirculateGraph::NodeID & id, const std::string & param) const
//        throw (UndefinedCodeException);
//
//        int
//        getLinkInt(const CirculateGraph::LinkID & id, const std::string & param) const
//        throw (UndefinedCodeException);
//
//        double
//        getLinkDouble(const CirculateGraph::LinkID & id, const std::string & param) const
//        throw (UndefinedCodeException);
//
//        std::string
//        getLinkString(const CirculateGraph::LinkID & id, const std::string & param) const
//        throw (UndefinedCodeException);
//
//        bool
//        getLinkBool(const CirculateGraph::LinkID & id, const std::string & param) const
//        throw (UndefinedCodeException);

            //********************************************************************//
            //                         SETTERS                                    //
            //********************************************************************//

            void
            setNodeInt(const std::string & id, const std::string & param, int value)
                  throw (UndefinedCodeException);

            void
            setNodeDouble(const std::string & id, const std::string & param,
                  double & value) throw (UndefinedCodeException);

            void
            setNodeString(const std::string & id, const std::string & param,
                  std::string & value) throw (UndefinedCodeException);

            void
            setNodeBool(const std::string & id, const std::string & param, bool value)
                  throw (UndefinedCodeException);

            void
            setLinkInt(const std::string & id, const std::string & param, int value)
                  throw (UndefinedCodeException);

            void
            setLinkDouble(const std::string & id, const std::string & param,
                  double & value) throw (UndefinedCodeException);

            void
            setLinkString(const std::string & id, const std::string & param,
                  std::string & value) throw (UndefinedCodeException);

            void
            setLinkBool(const std::string & id, const std::string & param, bool value)
                  throw (UndefinedCodeException);

//        void
//        setNodeInt(const CirculateGraph::NodeID & id, const std::string & param, int value)
//        throw (UndefinedCodeException);
//
//        void
//        setNodeDouble(const CirculateGraph::NodeID & id, const std::string & param,
//                      double & value) throw (UndefinedCodeException);
//
//        void
//        setNodeString(const CirculateGraph::NodeID & id, const std::string & param,
//                      std::string & value) throw (UndefinedCodeException);
//
//        void
//        setNodeBool(const CirculateGraph::NodeID & id, const std::string & param,
//                    bool value) throw (UndefinedCodeException);
//
//        void
//        setLinkInt(const CirculateGraph::LinkID & id, const std::string & param, int value)
//        throw (UndefinedCodeException);
//
//        void
//        setLinkDouble(const CirculateGraph::LinkID & id, const std::string & param,
//                      double & value) throw (UndefinedCodeException);
//
//        void
//        setLinkString(const CirculateGraph::LinkID & id, const std::string & param,
//                      std::string & value) throw (UndefinedCodeException);
//
//        void
//        setLinkBool(const CirculateGraph::LinkID & id, const std::string & param,
//                    bool value) throw (UndefinedCodeException);

            //      hydraulicSolver(const hydraulicSolver& orig);
            //      virtual ~hydraulicSolver();
//    private:
//        SEWRData_new_SPtr sewr_inp;
//        CirculateGraph_SPtr sewr_grph;
//        //SEWR_LinkDescMap_SPtr sewr_link_map;
//        //SEWR_NodeDescMap_SPtr sewr_node_map;
//        //OutfallDescMap_SPtr sewr_outfall_map;
//        std::vector< error > errs;
//        //std::string nodeExtensionDir;
//        //std::string linkExtensionDir;
//        //std::string connectString;
//        //soci::session sql;

         };

   }



#endif /* SOLVER_H_ */
