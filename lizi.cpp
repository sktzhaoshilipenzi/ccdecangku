#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/viz.hpp> 
#include <opencv2/calib3d.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
int main()
{
      viz::Viz3d window("window"); 
      window.showWidget("Coordinate", viz::WCoordinateSystem()); //创建平面 
      viz::WPlane plane; //添加平面，并设置一个ID为plane 
      window.showWidget("plane", plane); //创建一个1*3的rotation vector 
      Mat rvec = Mat::zeros(1, 3, CV_32F); //动画的本质：调整部件位姿并循环显示，控制条件是窗口没被停止，也就是主动按下了q或者e键 
    while(!window.wasStopped()) 
    {
        rvec.at<float>(0, 0) = 0.f; 
        rvec.at<float>(0, 1) += CV_PI * 0.01f; 
        rvec.at<float>(0, 2) = 0.f; 
        Mat rmat; //罗德里格斯公式，将罗德里格斯向量转换成旋转矩阵 
        Rodrigues(rvec, rmat); //构造仿射变换类型的pose，这个类型暂且看做OpenCV中的位姿类型，两个参数，一个旋转，一个平移 
        Affine3f pose(rmat, Vec3f(0, 0, 0)); //这一句就是整个可视化窗口能够动起来的核心语句了， //说白了就是利用循环来不断调整上面plane部件的位姿，达到动画的效果 //另外这里就利用到了平面的ID，来表征调整的是平面的位姿 
        window.setWidgetPose("plane", pose); //控制单帧暂留时间，调整time参数的效果就是平面转的快慢，本质上就是每一个位姿的停留显示时间。 
        window.spinOnce(1, false); 
    }
}


