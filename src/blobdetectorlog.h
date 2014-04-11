#ifndef BLOBDETECTORLOG_H
#define BLOBDETECTORLOG_H

#include "blobdetector.h"

class BlobDetectorLoG
{
public:
    BlobDetectorLoG();

    void detectBlobs(const cv::Mat& input_image, cv::Mat& blobs_image, std::vector<Blob>& blobs, const int& min_intensity = 0, const int& max_intensity = 50);

private:

    void buildLaplacianPyramid(const cv::Mat& input_image, std::vector< cv::Mat >& pyramid, cv::Mat& smallest_level, const int& levels);
    void buildGaussianPyramid(const cv::Mat& input_image, std::vector< cv::Mat >& pyramid, cv::Mat& smallest_level, const int& levels);



};

#endif // BLOBDETECTORLOG_H
