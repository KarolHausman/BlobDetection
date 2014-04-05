#include "blobdetector.h"


BlobDetector::BlobDetector()
{
}

void BlobDetector::detectBlackBlob(const cv::Mat& input_image, cv::Mat& blobs_image, std::vector<Blob>& blobs)
{
    //thresholding
    //TODO: make params
    cv::Mat bw_image;
    double threshold = 40;
    double maxval = 255;
    cv::threshold(input_image, bw_image, threshold, maxval, cv::THRESH_BINARY);


    //distance transform
    cv::Mat distance_image;
    cv::distanceTransform(bw_image, distance_image, CV_DIST_L2, 3);
    blobs_image = distance_image;

}


void BlobDetector::printImageValues(const cv::Mat& image)
{
    for(int row = 0; row < image.rows; ++row) {
        const unsigned char* inp  = image.ptr<unsigned char>(row);
        for (int col = 0; col < image.cols; ++col) {
            if (*inp++ == 0) {
                std::cout << '1';
            } else {
                std::cout << '0';
            }
        }
        std::cout << std::endl;
    }

}
