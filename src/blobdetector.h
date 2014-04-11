#ifndef BLOBDETECTOR_H
#define BLOBDETECTOR_H
#include <opencv2/opencv.hpp>


struct Blob
{
    Blob();
    Blob(const cv::Point& center, const double& area, const double& circularity):
        center_(center), area_(area), circularity_(circularity)
    {}
    cv::Point center_;
    double area_;
    double circularity_;
};

class BlobDetector
{
public:
    BlobDetector():
        circle_brightness_(175), min_blob_radius_(10), gaussian_blur_size_(3), blob_brightness_(255),
        max_circularity_to_draw_circle_(1.4), min_circularity_to_draw_circle_(0.6), blob_radius_(2){}
    virtual ~BlobDetector(){}

    virtual void detectBlobs(const cv::Mat& input_image, cv::Mat& blobs_image, std::vector<Blob>& blobs, const int& min_intensity = 0, const int& max_intensity = 50) = 0;

protected:
    int gaussian_blur_size_;
    int min_blob_radius_;
    int circle_brightness_;
    int blob_brightness_;
    int max_circularity_to_draw_circle_;
    int min_circularity_to_draw_circle_;
    double blob_radius_;
};

#endif // BLOBDETECTOR_H
