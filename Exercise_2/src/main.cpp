#include <iostream>
#include <boost/program_options.hpp>
#include "project_version.h"

using boost::program_options::options_description;
using boost::program_options::parse_command_line;


int main(int argc, char** argv)
{
    options_description option_description{"Allowed options"};
    option_description.add_options()
        ("help,h", "produce help message")
        ("version", "show version");

    boost::program_options::variables_map variable_map;
    boost::program_options::store(parse_command_line(argc, argv, option_description),
                                  variable_map);
    boost::program_options::notify(variable_map);

    if (variable_map.count("help"))
    {
        std::cout << option_description << std::endl;
        return 1;
    }

    if (variable_map.count("version"))
    {
        std::cout << "version: "
                  << HomeAutomation::version_major
                  << "."
                  << HomeAutomation::version_minor
                  << "."
                  << HomeAutomation::version_patch
                  << std::endl;
        return 1;
    }
  return 0;
}
