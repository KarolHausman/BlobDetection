#ifndef BLOBDETECTOR_H
#define BLOBDETECTOR_H
#include <opencv2/opencv.hpp>

/*
 *  struct Blob is resposible for gathering all the data about the blob
 *  found in the image.
 */
struct Blob
{
    Blob();
    Blob(const cv::Point& center, const double& area, const double& circularity):
        center_(center), area_(area), circularity_(circularity)
    {}
    cv::Point center_;
    double area_;
    double circularity_;

    void operator= (const Blob& b2 )
    {
          center_ = b2.center_;
          area_ = b2.area_;
          circularity_ = b2.circularity_;
    }

};
Blob operator- ( const Blob& b1, const Blob& b2);
std::ostream& operator << (std::ostream &o, const Blob& b);
bool operator < (const Blob& b1, const Blob& b2);
bool operator > (const Blob& b1, const Blob& b2);



/*
 *  BlobDetector is an interface that sets all the params
 *  used by all its children
 */
class BlobDetector
{
public:
    BlobDetector():
        min_blob_radius_(10), gaussian_blur_size_(3), max_circularity_to_draw_circle_(1.5),
        min_circularity_to_draw_circle_(0.6), blob_radius_(2){}
    virtual ~BlobDetector(){}

    /*
     *  finds blobs in the input_image, returns a blobs_image with circular blobs marked with big circles
     *  and all the blobs marked with their centers. You have to specify min and max intesities that your
     *  blobs can be
     */
    virtual void detectBlobs(const cv::Mat& input_image, cv::Mat& blobs_image, std::vector<Blob>& blobs, const int& min_intensity, const int& max_intensity) = 0;

    void setGaussianBlurSize(const int& gaussian_blur_size);
    void setMinBlobRadius(const int& min_blob_radius);
    void setMaxCircularityToDrawCircle(const double& max_circularity_to_draw_circle);
    void setMinCircularityToDrawCircle(const double& min_circularity_to_draw_circle);
    void setBlobRadius(const double& blob_radius);

    int getGaussianBlurSize();
    int getMinBlobRadius();
    double getMaxCircularityToDrawCircle();
    double getMinCircularityToDrawCircle();
    double getBlobRadius();




protected:
    // size of the mask for gaussian blur
    int gaussian_blur_size_;
    // min size of the blob to be accepted
    int min_blob_radius_;
    // max circularity for a blob to be accepted as a circular
    double max_circularity_to_draw_circle_;
    // min circularity for a blob to be accepted as a circular
    double min_circularity_to_draw_circle_;
    // radius of the circle that is drawn in each blob center
    double blob_radius_;
};

#endif // BLOBDETECTOR_H
