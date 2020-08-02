#include <ros/ros.h>
#include <sensor_msgs/Image.h>

#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>


#include <boost/thread/thread.hpp>
#include <darknet_ros_msgs/BoundingBox.h>
#include <darknet_ros_msgs/BoundingBoxes.h>

using namespace message_filters;

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

void depth_callback(const sensor_msgs::Image::ConstPtr& msg1, const darknet_ros_msgs::BoundingBoxes::ConstPtr& msg2)
{
    float* depths = (float*)(&msg1->data[0]);
    int u = ((msg2->bounding_boxes[0].xmax - msg2->bounding_boxes[0].xmin)/2) + msg2->bounding_boxes[0].xmin; 
    int v = ((msg2->bounding_boxes[0].ymax - msg2->bounding_boxes[0].ymin)/2) + msg2->bounding_boxes[0].ymin;

    int centerIdx = u + msg1->width * v;

    // Output the measure
    // ROS_INFO("Center distance : %g m", depths[centerIdx]);
    // print('depth to person:{dist} m'.format(dist=self.depth_array[a,b]))

    std::cout<<"Bouding Boxes (header):" << msg2->header <<std::endl;
	std::cout<<"Bouding Boxes (image_header):" << msg2->image_header <<std::endl;
	std::cout<<"Bouding Boxes (Class):" << msg2->bounding_boxes[0].Class <<"\t";
	std::cout<<"Center distance : %g m" << depths[centerIdx] <<std::endl;

	std::cout << "\033[2J\033[1;1H";     // clear terminal

}

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


    message_filters::Subscriber<sensor_msgs::Image> depth_sub(n, "/zed/zed_node/depth/depth_registered", 1);
    message_filters::Subscriber<darknet_ros_msgs::BoundingBoxes> object_sub(n, "/darknet_ros/bounding_boxes", 1);
    // 将两个话题的数据进行同步
    typedef sync_policies::ApproximateTime<sensor_msgs::Image, darknet_ros_msgs::BoundingBoxes> syncPolicy;
    Synchronizer<syncPolicy> sync(syncPolicy(10), depth_sub, object_sub);  
    // 指定一个回调函数，就可以实现两个话题数据的同步获取
    sync.registerCallback(boost::bind(&depth_callback, _1, _2));
    
    ros::spin();
    return 0;
}
    