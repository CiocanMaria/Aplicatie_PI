//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include <opencv2/opencv.hpp>
#include "../opencv/build/include/opencv2/imgproc/types_c.h"
#include "../opencv/build/include/opencv2/highgui/highgui_c.h"
using namespace Aplicatie1;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

using namespace cv;
using namespace std;
// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409
Mat image;


MainPage::MainPage()
{
	InitializeComponent();
}


void Aplicatie1::MainPage::ButtonUpload_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
    auto s = (safe_cast<Platform::String^>(imagePath->Text));

    std::wstring fooW(s->Begin());
    std::string fooA(fooW.begin(), fooW.end());
    // LOAD image
    string imagepath = fooA;
    const cv::String path = imagepath;
    image = imread("image.jpg");   //Citeste "image.jpg".
           //"image.jpg" trebuie sa fie in project folder.


    if (!image.data)  // Input invalid
    {
        cout << "Could not open or find the image" << std::endl;
       
    }

    //DISPLAY image
    namedWindow("window"); // Creeaza o fereastra pentru display
    cv::imshow("window", image); // Arata imaginea in ea

    //SAVE image
    imwrite("result.jpg", image);//imaginea va fi salvata "result.jpg"


}
void Aplicatie1::MainPage::Button2_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
    Mat rezultat;
    flip(image, rezultat, 1);
    namedWindow("imagine oglindita");
    imshow("imagine oglindita", rezultat);
   


}
void Aplicatie1::MainPage::Button3_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
    Mat rez;
    rez = image.clone();
    putText(rez, "Text-text-text-text", cv::Point(500, 100), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 100, 143), 1);

    namedWindow("Image Window image");
    imshow("Image Window image", rez);
    waitKey(0);

}
void Aplicatie1::MainPage::Button4_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
    Mat gray;


    // convert RGB image to gray
    cvtColor(image, gray, CV_BGR2GRAY);

    // namedWindow( "Display window", CV_WINDOW_AUTOSIZE );
     //imshow( "Display window", image );

    namedWindow("ALB-NEGRU");
    imshow("ALB-NEGRU", gray);
}
void Aplicatie1::MainPage::Button5_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
    Mat res = image.clone();

    cvtColor(res, res, COLOR_BGR2RGB);

    transform(res, res, Matx33f(0.393, 0.769, 0.189,

        0.349, 0.686, 0.168,

        0.272, 0.534, 0.131));

    cvtColor(res, res, COLOR_RGB2BGR);

    // imshow("original",image);

    imshow("Sepia", res);
}
void Aplicatie1::MainPage::Button6_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
    Mat src1, src2, src3;
    
    // Read image ( same size, same type )
    src1 = imread("image.jpg");
    src2 = imread("image2.jpg");
    src3 = src1 + src2;
    namedWindow("Blend1 Image", 1);
    imshow("Blend1 Image", src3);
}
void Aplicatie1::MainPage::Button7_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
   

}
void Aplicatie1::MainPage::Button8_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{   
    Mat  blurredImage;
    GaussianBlur(image, blurredImage, cv::Size(99, 99), 40.0);

    // Show the blurred image in a named window
    imshow("Blurred Image", blurredImage);
}
void Aplicatie1::MainPage::ButtonFiltruTV_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

    int slider = 0;
    int slider2 = 0;
        int height = image.size().height;
        int width = image.size().width;
        Mat gray;
        cvtColor(image, gray, COLOR_BGR2GRAY);
       
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (rand() % 100 <= 90) {
                    if (rand() % 2 == 0)
                        gray.at<uchar>(i, j) = std::min(gray.at<uchar>(i, j) + rand() % ((int)50 + 1), 255);
                    else
                        gray.at<uchar>(i, j) = std::max(gray.at<uchar>(i, j) - rand() % ((int)50 + 1), 0);
                }
            }
        }

        //imshow("original",image);
        cv::imshow("TV", gray);
}

void Aplicatie1::MainPage::ButtonFiltruHighPass_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

    Mat src1, src2;
    int a;
    Scalar intensity1 = 0;
    src1 = imread("image.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    src2 = src1.clone();
    //Take the Mask Size less than the size of an Image
    a = 2;

    for (int i = 0; i < src1.rows - a; i++)
    {
        for (int j = 0; j < src1.cols - a; j++)
        {
            Scalar intensity2 = 0;
            for (int p = 0; p < a; p++)
            {
                for (int q = 0; q < a; q++)
                {
                    intensity1 = src1.at<uchar>(i + p, j + q);
                    if ((p == (a - 1) / 2) && (q == (a - 1) / 2))
                    {
                        intensity2.val[0] += (a * a - 1) * intensity1.val[0];
                    }
                    else
                    {
                        intensity2.val[0] += (-1) * intensity1.val[0];
                    }
                }
            }
            src2.at<uchar>(i + (a - 1) / 2, j + (a - 1) / 2) = intensity2.val[0] / (a * a);
        }
    }


    //Display the High Pass Filtered Image
    namedWindow("High Pass Filtered Image");
    imshow("High Pass Filtered Image", src2);


}



void Aplicatie1::MainPage::ComboBox_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e)
{
    
    auto s = (safe_cast<ComboBoxItem^>(comboBox->SelectedItem))->Content->ToString();

    if (s == "filter 1")
    {
        Mat RGB2XYZ_image;
        cvtColor(image, RGB2XYZ_image, CV_RGB2XYZ);
        namedWindow("RGB2XYZ image");
        imshow("RGB2XYZ image", RGB2XYZ_image);
    }
    if (s == "filter 2")
    {
        Mat BGR2XYZ_image;
        cvtColor(image, BGR2XYZ_image, CV_BGR2XYZ);
        namedWindow("BGR2XYZ image", CV_WINDOW_AUTOSIZE);
        imshow("BGR2XYZ image", BGR2XYZ_image);
    }
    if (s == "filter 3")
    {
        Mat BGR2Luv_image;
        cvtColor(image, BGR2Luv_image, CV_BGR2Luv);
        namedWindow("BGR2Luv image", CV_WINDOW_AUTOSIZE);
        imshow("BGR2Luv image", BGR2Luv_image);


    }
    if (s == "filter 4")
    {
        Mat RGB2Luv_image;
        cvtColor(image, RGB2Luv_image, CV_RGB2Luv);
        namedWindow("RGB2Luv image", CV_WINDOW_AUTOSIZE);
        imshow("RGB2Luv image", RGB2Luv_image);
    } 
    if (s == "filter 5")
    {
        Mat BGR2Lab_image;
        cvtColor(image, BGR2Lab_image, CV_BGR2Lab);

        namedWindow("BGR2Lab image", CV_WINDOW_AUTOSIZE);
        imshow("BGR2Lab image", BGR2Lab_image);


    }

    if (s == "filter 6")
    {
        Mat RGB2Lab_image;
        cvtColor(image, RGB2Lab_image, CV_RGB2Lab);
        namedWindow("RGB2Lab image", CV_WINDOW_AUTOSIZE);
        imshow("RGB2Lab image", RGB2Lab_image);
    }

    if (s == "filter 7")
    {
        Mat BGR2YCrCb_image;
        cvtColor(image, BGR2YCrCb_image, CV_BGR2YCrCb);

        namedWindow("BGR2YCrCb image", CV_WINDOW_AUTOSIZE);
        imshow("BGR2YCrCb image", BGR2YCrCb_image);

    }
    if (s == "filter 8")
    {
        Mat RGB2YCrCb_image;
        cvtColor(image, RGB2YCrCb_image, CV_RGB2YCrCb);
        namedWindow("RGB2YCrCb image", CV_WINDOW_AUTOSIZE);
        imshow("RGB2YCrCb image", RGB2YCrCb_image);
    }
}
