//
//  ParamsParser.hpp
//  PanoramaMaker
//
//  Created by Dmitry Nekrasov on 11.11.16.
//  Copyright © 2016 Dmitry Nekrasov. All rights reserved.
//

#pragma once

#include <string>
#include <vector>

#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>

namespace po = boost::program_options;

class ParamsParser {
public:
    ParamsParser(int argc, char** argv);
    
    std::string getPath() const;
    std::string getMask() const;
    std::vector<std::string> getFiles() const;
    
private:
    po::options_description m_Description;
    po::variables_map m_VariablesMap;
    bool m_HasHelp;
    bool m_HasPath;
    bool m_HasMask;
};
