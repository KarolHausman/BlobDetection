#ifndef BLOBDETECTORCONTOURS_H
#define BLOBDETECTORCONTOURS_H

#include "blobdetector.h"


class BlobDetectorContours : public BlobDetector
{
public:
    BlobDetectorContours();
    virtual ~BlobDetectorContours();

    void detectBlobs(const cv::Mat& input_image, cv::Mat& blobs_image, std::vector<Blob>& blobs, const int& min_intensity = 0, const int& max_intensity = 50);

private:
    uint min_contour_size_;
    double canny_threshold_;



};

#endif // BLOBDETECTORCONTOURS_H
