//
//  main.cpp
//  PanoramaMaker
//
//  Created by Dmitry Nekrasov on 11.11.16.
//  Copyright © 2016 Dmitry Nekrasov. All rights reserved.
//

#include <iostream>

#include "ParamsParser.hpp"

int main(int argc, char** argv) {
    
    ParamsParser parser(argc, argv);
    
    auto files = parser.getFiles();
    
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
