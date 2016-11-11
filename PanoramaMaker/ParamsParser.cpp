//
//  ParamsParser.cpp
//  PanoramaMaker
//
//  Created by Dmitry Nekrasov on 11.11.16.
//  Copyright © 2016 Dmitry Nekrasov. All rights reserved.
//

#include "ParamsParser.hpp"

#include <iostream>

#include <boost/algorithm/string/replace.hpp>
#include <boost/filesystem.hpp>
#include <boost/range/adaptors.hpp>

ParamsParser::ParamsParser(int argc, char** argv)
: m_Description("Options")
{
    m_Description.add_options()
    ("help,h", "Show help")
    ("path,p", po::value<std::string>(), "Input path to the folder with images")
    ("mask,m", po::value<std::string>(), "Input file mask")
    ;
    
    po::parsed_options parsed = po::command_line_parser(argc, argv).options(m_Description).allow_unregistered().run();
    po::store(parsed, m_VariablesMap);
    po::notify(m_VariablesMap);
    
    m_HasHelp = m_VariablesMap.count("help") > 0;
    m_HasPath = m_VariablesMap.count("path") > 0;
    m_HasMask = m_VariablesMap.count("mask") > 0;
}

std::string ParamsParser::getPath() const {
    std::string path;
    if (m_HasPath) {
        path = m_VariablesMap["path"].as<std::string>();
    }
    return path;
}

std::string ParamsParser::getMask() const {
    std::string mask;
    if (m_HasMask) {
        mask = m_VariablesMap["mask"].as<std::string>();
    }
    return mask;
}

static std::vector<std::string> getFiles(const std::string& _path, const std::string& _file_mask) {
    
    const boost::regex my_filter(boost::replace_all_copy(_file_mask, "*", ".*"));
    
    std::vector<std::string> files;
    
    for (const auto& entry : boost::make_iterator_range(boost::filesystem::directory_iterator(_path))) {
        if (boost::regex_match(entry.path().filename().string(), my_filter)) {
            files.push_back(entry.path().string());
        }
    }
    
    return files;
}

std::vector<std::string> ParamsParser::getFiles() const {
    std::string path, mask;
    
    if (m_HasHelp) {
        std::cout << m_Description << std::endl;
        exit(0);
    } else {
        if (m_HasPath) {
            path = m_VariablesMap["path"].as<std::string>();
        } else {
            std::cout << "path!" << std::endl;
            exit(-1);
        }
        
        if (m_HasMask) {
            mask = m_VariablesMap["mask"].as<std::string>();
        } else {
            std::cout << "mask!" << std::endl;
            exit(-1);
        }
    }
    
    return ::getFiles(path, mask);
}
