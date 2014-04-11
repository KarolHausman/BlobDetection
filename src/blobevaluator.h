#ifndef BLOBEVALUATOR_H
#define BLOBEVALUATOR_H

#include "blobdetector.h"

class BlobEvaluator
{
public:
    BlobEvaluator();

    void evaluate (BlobDetector& blob_detector, const int& images_number, double& center_error, double& area_error, double& circularity_error, double& avg_duration);
    void generateBlobImages(const int& images_number, const int& circles_number, const int& rect_number, std::vector <cv::Mat>& images);
    void generateKnownBlobImage(cv::Mat& image, std::vector <Blob>& blobs);

private:
    template<typename T> void getMean (const std::vector<T>& v, double& m);
    void compare_blobs (const std::vector <Blob>& gen_blobs, const std::vector <Blob>& detected_blobs, double& center_error, double& area_error, double& circularity_error);


};

#endif // BLOBEVALUATOR_H
