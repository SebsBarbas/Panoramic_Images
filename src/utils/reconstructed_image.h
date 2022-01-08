#include "image.h"

class reconstructed_image : public image{
    public:
    reconstructed_image();
    private:
    cv::Mat final_image;
};