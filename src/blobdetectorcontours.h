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

    void setMinContourSize(const uint& min_contour_size);
    uint getMinContourSize();
    void setCannyThreshold(const uint& canny_threshold);
    uint getCannyThreshold();

private:
    // min contour size that is accepted as a potential blob
    uint min_contour_size_;
    // lower canny threshold, upper one is set to be twice as big
    double canny_threshold_;



};

#endif // BLOBDETECTORCONTOURS_H
