;
/**
 * Main.cpp
 *
 *  Created on: Mar 22, 2011
 *      Author: jnewman
 */


#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iosfwd>
#include <ostream>

#include <QtCore>

#include <boost/program_options.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/filesystem.hpp>
#include "../parsers/parser_exceptions.h"

#include "hydraulicSolver.h"

namespace po = boost::program_options;
namespace fs = boost::filesystem;

int
main(int argc, char **argv)
{
    fs::path init_path = fs::initial_path();
    QCoreApplication app (argc, argv);
    QDir pluginsDir(qApp->applicationDirPath());
    fs::path exec_path = fs::system_complete(fs::path(argv[0]));
    fs::path qapp_path = pluginsDir.absolutePath().toStdString();
    //get const char * of this directiory:
   
    
    std::string config_file_name = "sewr.cfg";

    //look for configuration file
    //1st try run directory
    fs::path config_file = init_path / config_file_name;
    //2nd try executable directory
    if (!fs::exists(config_file))
    {
        config_file = exec_path / config_file_name;
        if (!fs::exists(config_file))
        {
            config_file = qapp_path / config_file_name;
            if (!fs::exists(config_file))
            {
                std::clog << "Did not find configuration file: Searched for:\n";
                std::clog << "\t" << (init_path / config_file_name) <<"\n";
                std::clog << "\t" << (exec_path / config_file_name) <<"\n";
                std::clog << "\t" << config_file << "\n";
            }
        }
    }
        
    if (fs::exists(config_file))
    {
        std::clog << "Using config file: " << config_file << "\n";
    }


    po::options_description desc("Allowed options");
    desc.add_options() //
            ("help", "produce help message")//
            ("inp,i", po::value<std::string > (), "input file")//
            ("out,o", po::value<std::string > ()->default_value("out.rpt"),
            "output report file") //
            (
            "linkExtensionDirectory,l",
            po::value<std::string > (), "system")//
            (
            "nodeExtensionDirectory,n",
            po::value<std::string > (), "system")//
            (
             "TSDataExtensionDirectory,d",
             po::value<std::string > (), "system");//;

    po::positional_options_description p;
    p.add("inp", -1);

    po::variables_map vm;
    po::store(
              po::command_line_parser(argc, argv).options(desc).positional(p).run(),
              vm);
    if (fs::exists(config_file))
    {
        std::ifstream f(config_file.c_str());
        if (f.is_open())
        {
            po::store(po::parse_config_file(f, desc, false), vm);
        }
    }

    po::notify(vm);

    if (vm.count("help"))
    {
        std::cout << desc << "\n";
        return EXIT_SUCCESS;
    }

    std::string inpFileName;
    if (vm.count("inp"))
    {
        inpFileName = vm["inp"].as<std::string > ();
        std::clog << "Running SEWR on input file" << inpFileName << "\n";
    } else
    {
        std::clog << "Input file required. Invalid options.\n";
        std::clog << desc << "\n";
        return EXIT_SUCCESS;
    }

    std::string outfileName;
    if (vm.count("out"))
    {
        outfileName = vm["out"].as<std::string > ();
        std::clog << "Output will go to file: " << outfileName << "\n";
    } else
    {
        outfileName = "";
        std::clog << "Output file not specified. Output will go to file: "
                << outfileName;
    }

    fs::path link_extensions_dir_path;
    fs::path node_extensions_dir_path;
    fs::path tsdata_extensions_dir_path;

    if (vm.count("linkExtensionDirectory"))
    {
        link_extensions_dir_path = fs::path(
                                             vm["linkExtensionDirectory"].as<std::string > ());
    }
    
    if (!fs::exists(link_extensions_dir_path))
    {
        link_extensions_dir_path = init_path / "LinkExtensions";
        if (!fs::exists(link_extensions_dir_path))
        {
            link_extensions_dir_path = exec_path / "LinkExtensions";
            if (!fs::exists(link_extensions_dir_path))
            {
                link_extensions_dir_path = qapp_path / "LinkExtensions";
                if (!fs::exists(link_extensions_dir_path))
                {
                    std::clog << "Did not find link extension directory: Searched for:\n";
                    if (vm.count("linkExtensionDirectory"))
                    {
                        std::clog << "\t" << vm["linkExtensionDirectory"].as<std::string>() <<"\n";
                    }
                    std::clog << "\t" << (init_path / "LinkExtensions") <<"\n";
                    std::clog << "\t" << (exec_path / "LinkExtensions") <<"\n";
                    std::clog << "\t" << link_extensions_dir_path << "\n";
                    return EXIT_FAILURE;
                }
            }
        }
    }


    if (vm.count("nodeExtensionDirectory"))
    {
        node_extensions_dir_path = fs::path(
                                            vm["nodeExtensionDirectory"].as<std::string > ());
    }
    
    if (!fs::exists(node_extensions_dir_path))
    {
        node_extensions_dir_path = init_path / "NodeExtensions";
        if (!fs::exists(node_extensions_dir_path))
        {
            node_extensions_dir_path = exec_path / "NodeExtensions";
            if (!fs::exists(node_extensions_dir_path))
            {
                node_extensions_dir_path = qapp_path / "NodeExtensions";
                if (!fs::exists(node_extensions_dir_path))
                {
                    std::clog << "Did not find node extension directory: Searched for:\n";
                    if (vm.count("nodeExtensionDirectory"))
                    {
                        std::clog << "\t" << vm["nodeExtensionDirectory"].as<std::string>() <<"\n";
                    }
                    std::clog << "\t" << (init_path / "NodeExtensions") <<"\n";
                    std::clog << "\t" << (exec_path / "NodeExtensions") <<"\n";
                    std::clog << "\t" << node_extensions_dir_path << "\n";
                    return EXIT_FAILURE;
                }
            }
        }
    }
    
    if (vm.count("TSDataExtensionDirectory"))
    {
        tsdata_extensions_dir_path = fs::path(
                                            vm["TSDataExtensionDirectory"].as<std::string > ());
    }
    
    if (!fs::exists(tsdata_extensions_dir_path))
    {
        tsdata_extensions_dir_path = init_path / "TSDataExtensions";
        if (!fs::exists(tsdata_extensions_dir_path))
        {
            tsdata_extensions_dir_path = exec_path / "TSDataExtensions";
            if (!fs::exists(tsdata_extensions_dir_path))
            {
                tsdata_extensions_dir_path = qapp_path / "TSDataExtensions";
                if (!fs::exists(tsdata_extensions_dir_path))
                {
                    std::clog << "Did not find node extension directory: Searched for:\n";
                    if (vm.count("tsdata_extensions_dir_path"))
                    {
                        std::clog << "\t" << vm["nodeExtensionDirectory"].as<std::string>() <<"\n";
                    }
                    std::clog << "\t" << (init_path / "TSDataExtensions") <<"\n";
                    std::clog << "\t" << (exec_path / "TSDataExtensions") <<"\n";
                    std::clog << "\t" << node_extensions_dir_path << "\n";
                    return EXIT_FAILURE;
                }
            }
        }
    }
    

    

    try
    {

        Circulate::HydraulicSolver mySolver(inpFileName,
                                           node_extensions_dir_path.string(),
                                           link_extensions_dir_path.string(),
                                           tsdata_extensions_dir_path.string());
        mySolver.solve();
        mySolver.printGraph(inpFileName + ".dot");
        mySolver.print_to_txt(outfileName);
        //mySolver.print_to_db(std::string("results"));
        mySolver.print_to_h5(std::string("h5results.h5"));

    } catch (ObjectiveInputError e)
    {
        std::clog << "Problem with input file\n";
        std::clog << e.what();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;

}
