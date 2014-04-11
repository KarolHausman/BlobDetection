#include "blobevaluator.h"
#include <numeric>


BlobEvaluator::BlobEvaluator()
{
}

void BlobEvaluator::compare_blobs (const std::vector <Blob>& gen_blobs, const std::vector <Blob>& detected_blobs, double& center, double& area, double& circularity)
{
    center = 1;
    area = 2;
    circularity = 1;
}


void BlobEvaluator::evaluate (BlobDetectorFloodFill& blob_detector, const int& images_number, double& center_error, double& area_error, double& circularity_error)
{

    std::vector <double> center_errors;
    std::vector <double> area_errors;
    std::vector <double> circularity_errors;

    std::vector <Blob> gen_blobs;
    std::vector <Blob> detected_blobs;
    for (uint i=0; i < images_number; i++)
    {
        cv::Mat gen_image;
        gen_blobs.clear();
        generateKnownBlobImage( gen_image, gen_blobs );

        cv::Mat blobs_image;
        detected_blobs.clear();
        blob_detector.detectBlobs(gen_image, blobs_image, detected_blobs);

        compare_blobs(gen_blobs, detected_blobs, center_error, area_error, circularity_error);
        center_errors.push_back(center_error);
        area_errors.push_back(area_error);
        circularity_errors.push_back(circularity_error);

    }

    double sum = std::accumulate(center_errors.begin(), center_errors.end(), 0.0);
    center_error =  sum / center_errors.size();

    sum = std::accumulate(area_errors.begin(), area_errors.end(), 0.0);
    area_error =  sum / area_errors.size();

    sum = std::accumulate(circularity_errors.begin(), circularity_errors.end(), 0.0);
    circularity_error =  sum / circularity_errors.size();

}



void BlobEvaluator::generateBlobImages(const int& images_number, const int& circles_number, const int& rect_number, std::vector <cv::Mat>& images)
{
    for (uint i=0; i < images_number; i++)
    {
        int rows = rand() % 600 + 60;
        int cols = rand() % 600 + 60;

        cv::Mat image = cv::Mat(rows, cols, CV_8U);
        cv::randu(image, cv::Scalar(60), cv::Scalar(255));

        for(uint j = 0; j < circles_number; j++)
        {
            int radius =(int) (rand() % (std::min(rows,cols) / 4) +5);
            int xc = rand() % (cols - 1) + 1;
            int yc = rand() % (rows - 1) + 1;
            cv::Point circle_center = cv::Point(xc, yc);
            cv::circle(image, circle_center, radius, cv::Scalar(0), -1);
        }

        for(uint k = 0; k < rect_number; k++)
        {
            int xr = rand() % (cols - 1) + 1;
            int yr = rand() % (rows - 1) + 1;
            int hr = rand() % (cols - 1) + 1;
            int wr = rand() % (rows - 1) + 1;

            cv::Rect rect = cv::Rect(xr, yr, hr, wr);
            cv::rectangle(image, rect, cv::Scalar(0), -1);
        }

        cv::blur(image, image, cv::Size(5, 5));

        cv::namedWindow( "generated", CV_WINDOW_AUTOSIZE );
        cv::imshow( "generated", image );
        cv::waitKey(0);

    }
}

void BlobEvaluator::generateKnownBlobImage(cv::Mat& image, std::vector <Blob>& blobs)
{
    int rows = rand() % 400 + 200;
    int cols = rand() % 400 + 200;

    image = cv::Mat(rows, cols, CV_8U);
    image.setTo(cv::Scalar(255));

    bool stop = false;

    for(uint i = 0; i < 10; i++)
    {
        stop = false;
        int radius =(int) (rand() % (std::min(rows,cols) / 8) +50);
        int xc = rand() % (cols - 2*radius) + radius;
        int yc = rand() % (rows - 2*radius) + radius;


        cv::Point circle_center = cv::Point(xc, yc);
        for (std::vector< Blob>::iterator itr = blobs.begin(); itr != blobs.end(); itr++)
        {
            if( cv::norm(itr->center_ - circle_center) < radius + sqrt(itr->area_/ M_PI) + 2)
            {
                stop = true;
                break;
            }
        }

        if ( stop )
        {
            continue;
        }


        cv::circle(image, circle_center, radius, cv::Scalar(0), -1);
        Blob blob(circle_center, M_PI * radius * radius, 1);
        blobs.push_back(blob);


    }
}
