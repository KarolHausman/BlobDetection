#ifndef BLOBDETECTOR_H
#define BLOBDETECTOR_H
#include <opencv2/opencv.hpp>



struct Blob
{
    Blob();
    Blob(const cv::Point& center, const double& area, const double& circularity):
        center_(center), area_(area), circularity_(circularity)
    {}
    cv::Point center_;
    double area_;
    double circularity_;
};


class BlobDetector
{
public:
    BlobDetector();

    void detectBlobs(const cv::Mat& input_image, cv::Mat& blobs_image, std::vector<Blob>& blobs, const int& min_intensity = 0, const int& max_intensity = 50);
    void detectBlobsContours(const cv::Mat& input_image, cv::Mat& blobs_image, std::vector<Blob>& blobs, const int& min_intensity = -1, const int& max_intensity = -1);
    void detectBlobsLaplacian(const cv::Mat& input_image, cv::Mat& blobs_image, std::vector<Blob>& blobs);
    void generateBlobImages(const int& images_number, const int& circles_number, const int& rect_number, std::vector <cv::Mat>& images);
    void generateKnownBlobImage(cv::Mat& image, std::vector <Blob>& blobs);


private:
    void buildLaplacianPyramid(const cv::Mat& input_image, std::vector< cv::Mat >& pyramid, cv::Mat& smallest_level, const int& levels);
    void buildGaussianPyramid(const cv::Mat& input_image, std::vector< cv::Mat >& pyramid, cv::Mat& smallest_level, const int& levels);



};

#endif // BLOBDETECTOR_H
