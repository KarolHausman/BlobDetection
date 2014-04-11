#ifndef BLOBEVALUATOR_H
#define BLOBEVALUATOR_H

#include "blobdetectorfloodfill.h"

class BlobEvaluator
{
public:
    BlobEvaluator();

    void compare_blobs (const std::vector <Blob>& gen_blobs, const std::vector <Blob>& detected_blobs, double& center, double& area, double& circularity);
    void evaluate (BlobDetectorFloodFill& blob_detector, const int& images_number, double& center_error, double& area_error, double& circularity_error);
    void generateBlobImages(const int& images_number, const int& circles_number, const int& rect_number, std::vector <cv::Mat>& images);
    void generateKnownBlobImage(cv::Mat& image, std::vector <Blob>& blobs);
};

#endif // BLOBEVALUATOR_H
