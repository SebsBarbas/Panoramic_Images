#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/core/mat.hpp>
#include <vector>

class image{

    public:
        image(){};
        image(std::string &image_path, int index):image_path(image_path),idx(index){};
        ~image(){};
        //Function to extract features from the image
        void extract_features();
        //Find the keypoint matching of features between images
        std::vector<cv::DMatch> match_features(const image &image2);

    private:
        int idx;
        std::string image_path;
        std::vector<cv::KeyPoint> key_points;
        cv::Mat descriptors;    
};