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

    cv::Scalar getFloodfillLoDiff();
    cv::Scalar getFloodfillUpDiff();
    int getMaskSizeDistanceTransform();
    void setFloodfillLoDiff(const cv::Scalar& floodfill_lo_diff);
    void setFloodfillUpDiff(const cv::Scalar& floodfill_up_diff);
    void setMaskSizeDistanceTransform(const int& mask_size_distance_transform);


private:
    // lower difference for the floodfill algorithm to proceed
    cv::Scalar floodfill_lo_diff_;
    // upper difference for the floodfill algorithm to proceed
    cv::Scalar floodfill_up_diff_;
    // size of the mask for the distance transform. used to determine the center of the blob
    int mask_size_distance_transform_;
};

#endif // BLOBDETECTORFLOODFILL_H
