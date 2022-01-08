#include <vector>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <boost/filesystem.hpp>
#include "image.h"



class reconstruction_manager{
    public:
        reconstruction_manager(){}
        void add_parameters(std::vector<std::string> *vector);
        void set_image_formats(std::string &formats);
        bool is_accepted_image_format(std::string path);
        void Find_image_paths();
        void reconstruct_scene();
        void ORB_extraction();
        void Image_reconstruction();
        void Feature_matching();
    
    private:
        bool full_reconstruct = false;
        bool recursive_path_image_fetch = false;
        std::vector<std::string> image_type = {".png"};
        std::string image_path = "C:\\Users\\sebas\\Documents\\proyectos_cv\\imagenes_panoramicas\\imagenes_panoramicass";
        std::vector<std::string> image_paths;
        std::unordered_map<int, image> images;
        std::unordered_map<int, std::vector<cv::DMatch>> image_matches;
};


