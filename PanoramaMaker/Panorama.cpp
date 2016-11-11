//
//  Panorama.cpp
//  PanoramaMaker
//
//  Created by Dmitry Nekrasov on 11.11.16.
//  Copyright © 2016 Dmitry Nekrasov. All rights reserved.
//

#include "Panorama.hpp"

#include <iostream>

#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/nonfree/features2d.hpp>

namespace pm {
    
static cv::Mat addFrame(const cv::Mat& _current_frame, const cv::Mat& _add_frame, const cv::Mat& _homography) {
    cv::Mat result;
    cv::warpPerspective(_current_frame, result, _homography, { _current_frame.cols + _add_frame.cols, _current_frame.rows });
    _add_frame.copyTo(cv::Mat(result, { 0, 0, _add_frame.cols, _add_frame.rows }));
    return result;
}

cv::Mat makePanorama(const std::vector<std::string>& _files) {
    size_t center_index = _files.size() / 2;
    
    std::vector<cv::Mat> images;
    images.reserve(_files.size() + 1);
    
    for (size_t i = 0; i < _files.size(); i++) {
        cv::Mat current = cv::imread(_files[i]);
        if (i <= center_index) {
            cv::Mat flip;
            cv::flip(current, flip, 1);
            images.emplace_back(flip);
        }
        if (i >= center_index) {
            images.emplace_back(current);
        }
    }
    
    size_t images_count = images.size();
    
    std::vector<std::vector<cv::KeyPoint>> key_points(images_count);
    std::vector<cv::Mat> descriptors(images_count);
    
    cv::SiftFeatureDetector sift;
    
    for (size_t i = 0; i < images_count; i++) {
        std::cout << "Calculate descriptors " << i << std::endl;
        sift.detect(images[i], key_points[i]);
        sift.compute(images[i], key_points[i], descriptors[i]);
    }
    
    std::cout << std::endl;
    
    std::vector<cv::Mat> homography;
    
    cv::FlannBasedMatcher matcher;
    
    for (size_t i = 0; i < images_count - 2; i++) {
        size_t from = i + (i < center_index ? 0 : 2);
        size_t to = i + 1;
        
        std::cout << "Calculate homography from " << from << " to " << to << std::endl;
        
        std::vector<std::vector<cv::DMatch>> matches;
        matcher.knnMatch(descriptors[from], descriptors[to], matches, 2);
        
        std::vector<cv::Point2f> pts_from, pts_to;
        for (const auto& match : matches) {
            if (match[0].distance / match[1].distance < 0.9) {
                pts_from.emplace_back(key_points[from][match[0].queryIdx].pt);
                pts_to.emplace_back(key_points[to][match[0].trainIdx].pt);
            }
        }
        
        homography.emplace_back(cv::findHomography(pts_from, pts_to, CV_RANSAC));
    }
    
    std::cout << "\nGluing frames..." << std::endl;
    
    cv::Mat flip_left_result = images[0];
    for (size_t i = 0; i < center_index; i++) {
        flip_left_result = addFrame(flip_left_result, images[i + 1], homography[i]);
    }
    
    cv::Mat right_result = images[images_count - 1];
    for (size_t i = images_count - 1; i > center_index + 1; i--) {
        right_result = addFrame(right_result, images[i - 1], homography[i - 2]);
    }
    
    cv::Mat left_result;
    cv::flip(flip_left_result, left_result, 1);
    
    int center_image_cols = images[center_index].cols;
    cv::Mat result(left_result.rows, left_result.cols + right_result.cols - center_image_cols, left_result.type());
    left_result.copyTo(cv::Mat(result, { 0, 0, left_result.cols, left_result.rows }));
    right_result.copyTo(cv::Mat(result, { left_result.cols - center_image_cols, 0, right_result.cols, right_result.rows }));
    
    return result;
}
    
void writeImage(const std::string& _path, const cv::Mat& _image) {
    cv::imwrite(_path, _image);
}
    
} // pm
