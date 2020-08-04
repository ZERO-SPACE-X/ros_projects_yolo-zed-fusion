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

#include "display_test/Pub_class_distance.h"
using namespace message_filters;

#define class_num  20
#define DEBUG 0



// ros::Publisher PointCloudInfo_pub;
ros::Publisher DistanceInfo_pub;
// ros::Publisher ImageInfo_pub;
// darknet_ros_msgs::BoundingBoxes syn_pointcloud;

// 修改为检测多个物体的距离信息
//class_num 默认设定为20，如果检测类别为80 将上面的define 更改下即可
void depth_callback(const darknet_ros_msgs::BoundingBoxes::ConstPtr& detect_msg, const sensor_msgs::Image::ConstPtr& msg)
{
    display_test::Pub_class_distance distance_msg;
    // syn_pointcloud = *detect_msg;
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
    if (DEBUG)
    {
        temp3 = msg->width;
    }
    
    
    for (int i = 0; i < num; i++)
    {
        // 看一下输出的数据是否为负数
        if(DEBUG)
        {
            temp1[i] = (detect_msg->bounding_boxes[i].xmax - detect_msg->bounding_boxes[i].xmin)/2;
            temp2[i] = (detect_msg->bounding_boxes[i].ymax - detect_msg->bounding_boxes[i].ymin)/2;
        }
        

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
    // std::ifstream read;
    write.open("result-test.csv", std::ios::app);
    for (int i = 0; i < num; i++)
    {
        
        std::cout << detect_msg->bounding_boxes[i].Class << "\t";
        // std::cout<<"Bouding Boxes (Class):" << detect_msg->bounding_boxes[i].Class <<"\t";
        // std::cout<<"Center distance :  " << centerIdx[i] << "  m" << std::endl;
        
        std::cout<<"Center distance :  " << depths[centerIdx[i]] << "  m" << std::endl;
        if(DEBUG)
        {
            std::cout<<"temp1 :  " << i << ":    " << temp1[i] << std::endl;
            std::cout<<"temp2 :  " << i << ":    " << temp2[i] << std::endl;
            std::cout<<"temp3 :  " << temp3 << std::endl;
        }
        std::cout<<"X distance :  " << u[i] << "  pixel" << std::endl;
        std::cout<<"Y distance :  " << v[i] << "  pixel" << std::endl;
        
        if (DEBUG)
            write << i << ","<<"中心点位置" <<","<< centerIdx[i] << ","<< "temp1"<<","<<temp1[i]<<"," <<"temp2"<<","<<temp2[i]<<","<<"temp3"<<","<< temp3<<","<<"x"<<","<<u[i]<<","<<"y"<<","<<v[i]<< std::endl;
        else  //逗号不用非得单独在一个<< <<区间中写如，可以在名称后面添加  "Y distance :  ,"，因为csv文件靠的是逗号来分割，不管在哪里写 都会分开的
            write << detect_msg->bounding_boxes[i].Class << "," << detect_msg->bounding_boxes[i].id << "," << "Center distance :  " <<","<< depths[centerIdx[i]] <<"," << "X distance :  " << "," << u[i] <<"," << "Y distance :  ," << v[i] <<  std::endl;
        // printf("Center distance : %.6f m\n",depths[centerIdx[i]]);

        // distance_msg.classes[i] = detect_msg->bounding_boxes[i].Class; //使用这种方法会出核心转储的问题，估计又是数组边界的问题
        // distance_msg.distance[i] = depths[centerIdx[i]];

        distance_msg.classes.push_back(detect_msg->bounding_boxes[i].Class);
        distance_msg.id.push_back(detect_msg->bounding_boxes[i].id);
        distance_msg.x_center.push_back(u[i]);
        distance_msg.y_center.push_back(u[i]);
        distance_msg.distance.push_back(depths[centerIdx[i]]);
        
        
    }
    write.close();
    // read.close();

    // PointCloudInfo_pub.publish(syn_pointcloud);
    DistanceInfo_pub.publish(distance_msg);
    // 使用完之后需要将数据清掉 如果这个消息变量定义在函数体的外面的话，在每次回调函数中使用完之后需要clear下，否则数据是累加的，因为使用了vector的push_back的方法插入的数据
    // distance_msg.classes.clear();   
    // distance_msg.distance.clear();  
    std::cout << "\033[2J\033[1;1H";     // clear terminal
    
}

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

    // PointCloudInfo_pub = n.advertise<darknet_ros_msgs::BoundingBoxes>("/djq_pc", 10);
    DistanceInfo_pub = n.advertise<display_test::Pub_class_distance>("/distance_info", 1);

    ros::spin();
    return 0;
}
