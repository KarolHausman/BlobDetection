#ifndef BLOBDETECTORFLOODFILL_H
#define BLOBDETECTORFLOODFILL_H

#include "blobdetector.h"

class BlobDetectorFloodFill: public BlobDetector {

public:
    BlobDetectorFloodFill();
    virtual ~BlobDetectorFloodFill();

    void detectBlobs(const cv::Mat& input_image, cv::Mat& blobs_image, std::vector<Blob>& blobs, const int& min_intensity = 0, const int& max_intensity = 50);

private:
    cv::Scalar floodfill_lo_diff_;
    cv::Scalar floodfill_up_diff_;
    int mask_size_distance_transform_;
};

#endif // BLOBDETECTORFLOODFILL_H
