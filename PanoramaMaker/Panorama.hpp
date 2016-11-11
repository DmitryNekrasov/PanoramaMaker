//
//  Panorama.hpp
//  PanoramaMaker
//
//  Created by Dmitry Nekrasov on 11.11.16.
//  Copyright © 2016 Dmitry Nekrasov. All rights reserved.
//

#pragma once

#include <string>
#include <vector>

#include <opencv2/core/core.hpp>

namespace pm {
    
cv::Mat makePanorama(const std::vector<std::string>& _files);
void writeImage(const std::string& _path, const cv::Mat& _image);
    
} // pm
