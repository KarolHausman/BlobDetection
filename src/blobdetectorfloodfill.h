#ifndef BLOBDETECTORFLOODFILL_H
#define BLOBDETECTORFLOODFILL_H

#include "blobdetector.h"


/*
 *  implements detectBlobs method where it uses
 *  floodfill algorithm to determine all the important information
 *  about the drone
 */
class BlobDetectorFloodFill: public BlobDetector {

public:
    BlobDetectorFloodFill();
    virtual ~BlobDetectorFloodFill();

    void detectBlobs(const cv::Mat& input_image, cv::Mat& blobs_image, std::vector<Blob>& blobs, const int& min_intensity, const int& max_intensity);

private:
    cv::Scalar floodfill_lo_diff_;
    cv::Scalar floodfill_up_diff_;
    int mask_size_distance_transform_;
};

#endif // BLOBDETECTORFLOODFILL_H
