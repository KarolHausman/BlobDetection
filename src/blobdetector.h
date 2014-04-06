#ifndef BLOBDETECTOR_H
#define BLOBDETECTOR_H
#include <opencv2/opencv.hpp>


struct Blob
{
    Blob();
    Blob(const cv::KeyPoint& center, const double& area, const double& circularity):
        center_(center), area_(area), circularity_(circularity)
    {}
    cv::KeyPoint center_;
    double area_;
    double circularity_;
};


class BlobDetector
{
public:
    BlobDetector();

    void detectBlackBlob(const cv::Mat& input_image, cv::Mat& blobs_image, std::vector<Blob>& blobs);

};

#endif // BLOBDETECTOR_H
