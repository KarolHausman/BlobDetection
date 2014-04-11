#ifndef BLOBDETECTORCONTOURS_H
#define BLOBDETECTORCONTOURS_H

#include "blobdetector.h"

/*
 *  implements detectBlobs method where it uses
 *  contours to determine all the important information
 *  about the drone. Contours are filtered based on their convexity.
 */
class BlobDetectorContours : public BlobDetector
{
public:
    BlobDetectorContours();
    virtual ~BlobDetectorContours();

    void detectBlobs(const cv::Mat& input_image, cv::Mat& blobs_image, std::vector<Blob>& blobs, const int& min_intensity, const int& max_intensity);

private:
    uint min_contour_size_;
    double canny_threshold_;



};

#endif // BLOBDETECTORCONTOURS_H
