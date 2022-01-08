#include "image.h"
#include <opencv2/opencv.hpp>

void image::extract_features(){
    //cv::Ptr<cv::ORB> detector;
    cv::Ptr<cv::FeatureDetector> detector = cv::ORB::create();
    cv::Mat image_data = cv::imread(image_path, cv::IMREAD_GRAYSCALE);
    detector->detect(image_data, key_points);
    detector->compute(image_data, key_points, descriptors);
    detector.release();
}

std::vector<cv::DMatch> image::match_features(const image &image2){
    cv::BFMatcher brue_force_matcher = cv::BFMatcher(cv::NORM_HAMMING, true);
    std::vector<cv::DMatch> matches;
    brue_force_matcher.match((const cv::OutputArray)descriptors, (const cv::OutputArray)image2.descriptors,  matches);
    std::vector<cv::DMatch>::iterator it = matches.begin();

    while(it != matches.end()){
        if(it->distance > 0.1) matches.erase(it);
        else it = it++;
    }
    
    return matches;
}
