#ifndef BLOBEVALUATOR_H
#define BLOBEVALUATOR_H

#include "blobdetector.h"


/*
 *  class to evaluate different BlobDetectors
 *
 */
class BlobEvaluator
{
public:
    BlobEvaluator();
    virtual ~BlobEvaluator();

    /*
     *  evaluates performance of a given blob detector with number of images
     *  returns avg center error, area error and circularity error
     */
    void evaluate (BlobDetector& blob_detector, const int& images_number, double& center_error, double& area_error, double& circularity_error, double& avg_duration);
    /*
     *  generates random vector of images with number of circles and rectangles on it. No ground truth available
     */
    void generateBlobImages(const int& images_number, const int& circles_number, const int& rect_number, std::vector <cv::Mat>& images);
    /*
     *  generates images with fully circular blobs. it also returns a ground truth data with generated blobs
     */
    void generateKnownBlobImage(cv::Mat& image, std::vector <Blob>& blobs);

private:
    template<typename T> void getMean (const std::vector<T>& v, double& m);
    /*
     *  compares two blobs vectors and returns mean of all the errors.
     */
    void compare_blobs (const std::vector <Blob>& gen_blobs, const std::vector <Blob>& detected_blobs, double& center_error, double& area_error, double& circularity_error);

    int min_intensity_;
    int max_intensity_;

};

#endif // BLOBEVALUATOR_H
