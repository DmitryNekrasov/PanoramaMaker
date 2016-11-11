//
//  main.cpp
//  PanoramaMaker
//
//  Created by Dmitry Nekrasov on 11.11.16.
//  Copyright © 2016 Dmitry Nekrasov. All rights reserved.
//

#include <iostream>

#include "Panorama.hpp"
#include "ParamsParser.hpp"

static const std::string g_OutFileName = "panorama.jpg";

int main(int argc, char** argv) {
    
    ParamsParser parser(argc, argv);
    
    auto files = parser.getFiles();
    if (files.size() == 0) {
        std::cout << "Files not found" << std::endl;
        exit(-1);
    }
    
    auto result = pm::makePanorama(files);
    
    std::string out_path = parser.getPath() + "_" + g_OutFileName;
    pm::writeImage(out_path, result);
    std::cout << "\nResult is saved in " << out_path << std::endl;
    
    return 0;
}
