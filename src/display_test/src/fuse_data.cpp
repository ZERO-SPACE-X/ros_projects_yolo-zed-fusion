#include <ros/ros.h>
#include <sensor_msgs/Image.h>

#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>


#include <boost/thread/thread.hpp>
#include <darknet_ros_msgs/BoundingBox.h>
#include <darknet_ros_msgs/BoundingBoxes.h>

#include <fstream>
#include <iostream>
using namespace message_filters;

#define class_num  20
#define DEBUG 1

// void imu_callback(const sensor_msgs::ImuConstPtr &imu_msg_accel, const sensor_msgs::ImuConstPtr &imu_msg_gyro)
// {
//         double t = imu_msg_accel->header.stamp.toSec();
//         double dx = imu_msg_accel->linear_acceleration.x;
//         double dy = imu_msg_accel->linear_acceleration.y;
//         double dz = imu_msg_accel->linear_acceleration.z;
//         double rx = imu_msg_gyro->angular_velocity.x;
//         double ry = imu_msg_gyro->angular_velocity.y;
//         double rz = imu_msg_gyro->angular_velocity.z;
//             Vector3d gyr(rx, ry, rz);
//         Vector3d acc(dx, dy, dz);
//         /**
//         处理函数 ......
//         */
// }
/*
void depth_callback(const darknet_ros_msgs::BoundingBoxes::ConstPtr& detect_msg, const sensor_msgs::Image::ConstPtr& msg)
{
    float* depths = (float*)(&msg->data[0]);

    int u = ((detect_msg->bounding_boxes[0].xmax - detect_msg->bounding_boxes[0].xmin)/2) + detect_msg->bounding_boxes[0].xmin; 
    int v = ((detect_msg->bounding_boxes[0].ymax - detect_msg->bounding_boxes[0].ymin)/2) + detect_msg->bounding_boxes[0].ymin;
    int centerIdx = u + msg->width * v;

    // Output the measure
    // ROS_INFO("Center distance : %g m", depths[centerIdx]);
    // print('depth to person:{dist} m'.format(dist=self.depth_array[a,b]))

    std::cout<<"Bouding Boxes (header):" << detect_msg->header <<std::endl;
	std::cout<<"Bouding Boxes (image_header):" << detect_msg->image_header <<std::endl;
	std::cout<<"Bouding Boxes (Class):" << detect_msg->bounding_boxes[0].Class <<"\t";
	// std::cout<<"Center distance : %g m" << depths[centerIdx] <<std::endl;
    printf("Center distance : %.6f m\n",depths[centerIdx]);
	// std::cout << "\033[2J\033[1;1H";     // clear terminal

}
*/
// 修改为检测多个物体的距离信息
//class_num 默认设定为20，如果检测类别为80 将上面的define 更改下即可


void depth_callback(const darknet_ros_msgs::BoundingBoxes::ConstPtr& detect_msg, const sensor_msgs::Image::ConstPtr& msg)
{
    int u[class_num] = {};
    int v[class_num] = {};
    int centerIdx[class_num] = {};
    #ifdef DEBUG
        int temp1[class_num] ={};
        int temp2[class_num] ={};
        int temp3;
    #endif
    int sizes = msg->data.size();

    float* depths = (float*)(&msg->data[0]);
    //只能在for循环之前提取一次数组的长度，否则在下面两个for运行过程中可能长度发生变化，毕竟是直接从内存中取值，
    //然后会造成访问的位置没有开辟，出现段错误，核心已转储的错误  
    // ---貌似不是这个问题导致的核心转储存，是由于我定义的u,v变量为char类型了，数据溢出变成了负数，然后访问数组中的负数时出错了。导致的核心转储。
    int num = detect_msg->bounding_boxes.size();
    // 看一下视频的宽度
    temp3 = msg->width;
    for (int i = 0; i < num; i++)
    {
        // 看一下输出的数据是否为负数
        temp1[i] = (detect_msg->bounding_boxes[i].xmax - detect_msg->bounding_boxes[i].xmin)/2;
        temp2[i] = (detect_msg->bounding_boxes[i].ymax - detect_msg->bounding_boxes[i].ymin)/2;

        u[i] = ((detect_msg->bounding_boxes[i].xmax - detect_msg->bounding_boxes[i].xmin)/2) + detect_msg->bounding_boxes[i].xmin; 
        v[i] = ((detect_msg->bounding_boxes[i].ymax - detect_msg->bounding_boxes[i].ymin)/2) + detect_msg->bounding_boxes[i].ymin;
        centerIdx[i] = u[i] + msg->width * v[i];
        if (centerIdx[i] < 0) 
        {
            centerIdx[i] = 0;
        }
        else if (centerIdx[i] > sizes /4)
        {
            centerIdx[i] = sizes /4;
        }
    }
    std::cout<<"Bouding Boxes (header):" << detect_msg->header <<std::endl;
    std::cout<<"Bouding Boxes (image_header):" << detect_msg->image_header <<std::endl;
    std::cout<<"Bouding Boxes (Class):" << "\t";

    std::ofstream write;
    std::ifstream read;
    write.open("result.csv", std::ios::app);
    for (int i = 0; i < num; i++)
    {
        
        std::cout << detect_msg->bounding_boxes[i].Class << "\t";
        // std::cout<<"Bouding Boxes (Class):" << detect_msg->bounding_boxes[i].Class <<"\t";
        // std::cout<<"Center distance :  " << centerIdx[i] << "  m" << std::endl;
        std::cout<<"Center distance :  " << depths[centerIdx[i]] << "  m" << std::endl;
        std::cout<<"temp1 :  " << i << ":    " << temp1[i] << std::endl;
        std::cout<<"temp2 :  " << i << ":    " << temp2[i] << std::endl;
        std::cout<<"temp3 :  " << temp3 << std::endl;
        
        if (DEBUG)
            write << i << ","<<"中心点位置" <<","<< centerIdx[i] << ","<< "temp1"<<","<<temp1[i]<<"," <<"temp2"<<","<<temp2[i]<<","<<"temp3"<<","<< temp3<<","<<"x"<<","<<u[i]<<","<<"y"<<","<<v[i]<< std::endl;
        write << detect_msg->bounding_boxes[i].Class << "," << "中心点距离" <<","<< centerIdx[i] <<  std::endl;
        // printf("Center distance : %.6f m\n",depths[centerIdx[i]]);

       
    }
    write.close();
    read.close();
    std::cout << "\033[2J\033[1;1H";     // clear terminal
    
}


// // 测试深度信息数组最大的范围是多少，方式超出数组范围，报核心转储的错误
// // int u[11] = {950000,850000,750000,650000,550000,450000,350000,250000,150000,35000,100000};
// int u[11] = {950000,850000,750000,650000,550000,450000,350000,250000,150000,35000,100000};
// void depth_callback(const darknet_ros_msgs::BoundingBoxes::ConstPtr& detect_msg, const sensor_msgs::Image::ConstPtr& msg)
// {
//     int sizes = msg->data.size();
//     // Get a pointer to the depth values casting the data
//     // pointer to floating point
//     float* depths = (float*)(&msg->data[0]);

//     // Image coordinates of the center pixel
//     // int u = msg->width / 2;
//     // int v = msg->height / 2;

//     // Linear index of the center pixel
//     // int centerIdx = u + msg->width * v;
//     for (char i = 0; i < 11; i++)
//     {
//         // Output the measure
//         //  ROS_INFO("Center distance : %g m", depths[u[i]]);
//         std::cout<<"Center distance :  " << depths[u[i]] << "  m" << std::endl;
//     }
//     std::cout << sizes << std::endl;
//     std::cout << "\033[2J\033[1;1H";     // clear terminal
// }


// void depthCallback(const sensor_msgs::Image::ConstPtr& msg) {

//     // Get a pointer to the depth values casting the data
//     // pointer to floating point
//     float* depths = (float*)(&msg->data[0]);

//     // Image coordinates of the center pixel
//     int u = msg->width / 2;
//     int v = msg->height / 2;

//     // Linear index of the center pixel
//     int centerIdx = u + msg->width * v;

//     // Output the measure
//     ROS_INFO("Center distance : %g m", depths[centerIdx]);
// }

// void sizeCallback(const darknet_ros_msgs::BoundingBoxes::ConstPtr& msg)
// {
//     std::cout<<"Bouding Boxes (header):" << msg->header <<std::endl;
// 	std::cout<<"Bouding Boxes (image_header):" << msg->image_header <<std::endl;
// 	std::cout<<"Bouding Boxes (Class):" << msg->bounding_boxes[0].Class <<std::endl;
// 	std::cout<<"Bouding Boxes (xmin):" << msg->bounding_boxes[0].xmin <<std::endl;
// 	std::cout<<"Bouding Boxes (xmax):" << msg->bounding_boxes[0].xmax <<std::endl;
// 	std::cout<<"Bouding Boxes (ymin):" << msg->bounding_boxes[0].ymin <<std::endl;
// 	std::cout<<"Bouding Boxes (ymax):" << msg->bounding_boxes[0].ymax <<std::endl;
// 	std::cout << "\033[2J\033[1;1H";     // clear terminal
// }

int main(int argc, char** argv)
{
    ros::init(argc, argv, "fuse_data");

    ros::NodeHandle n;


    // 需要用message_filter容器对两个话题的数据发布进行初始化，这里不能指定回调函数
    // message_filters::Subscriber<sensor_msgs::Imu> sub_imu_accel(n,IMU_TOPIC_ACCEL,2000,ros::TransportHints().tcpNoDelay());
    // message_filters::Subscriber<sensor_msgs::Imu> sub_imu_gyro(n,IMU_TOPIC_GYRO,2000,ros::TransportHints().tcpNoDelay());

    message_filters::Subscriber<darknet_ros_msgs::BoundingBoxes> object_sub(n, "/darknet_ros/bounding_boxes", 1);
    message_filters::Subscriber<sensor_msgs::Image> depth_sub(n, "/zed/zed_node/depth/depth_registered", 1);
    
    // 将两个话题的数据进行同步
    // typedef sync_policies::ApproximateTime<sensor_msgs::Image, darknet_ros_msgs::BoundingBoxes> syncPolicy;
    typedef sync_policies::ApproximateTime<darknet_ros_msgs::BoundingBoxes, sensor_msgs::Image> syncPolicy;
    // Synchronizer<syncPolicy> sync(syncPolicy(10), depth_sub, object_sub);  
    Synchronizer<syncPolicy> sync(syncPolicy(10), object_sub, depth_sub); 
    // 指定一个回调函数，就可以实现两个话题数据的同步获取
    sync.registerCallback(boost::bind(&depth_callback, _1, _2));
    
    ros::spin();
    return 0;
}
    