#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Point.h>
#include <display_test/Pub_class_distance.h>
#include "std_msgs/String.h"
#include <fstream>

using namespace std;



// ros::Publisher cmdVelPub;
// int main(int argc, char **argv)
// { 
//     ros::init(argc, argv, "talk"); //"talk"必须是nodename 
//     std::string topic = "/turtle1/cmd_vel"; //topic name 
//     ros::NodeHandle n; 
//     // cmdVelPub = n.advertise<geometry_msgs::Twist>(topic, 1); //第一个参数也可以写成"/turtle1/cmd_vel"这样的topic name //第二个参数是发布的缓冲区大小,<geometry_msgs::Twist>是消息类型 
//     cmdVelPub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1);
//     ros::Rate loopRate(2); //与Rate::sleep();配合指定自循环频率 
//     ROS_INFO("talk cpp start...");//输出显示信息 
//     geometry_msgs::Twist speed; // 控制信号载体 Twist message 
//     while (ros::ok())
//     { 
//         speed.linear.x = 1; // 设置线速度为1m/s，正为前进，负为后退 
//         speed.angular.z = 1; // 设置角速度为1rad/s，正为左转，负为右转 
//         cmdVelPub.publish(speed); // 将刚才设置的指令发送给机器人 
//         ros::spinOnce(); 
//         loopRate.sleep();//按loopRate(2)设置的2HZ将程序挂起 
//     } 
//     return 0;
// }


class ControlTurtle
{
// 为了保持C++类数据封装的特性，将成员变量写成私有
// 当然如果是public也是完全没问题的，只是有点破坏数据的封装性
private:
    ros::NodeHandle nh_;
    ros::Subscriber distance_info_;
    // ros::Subscriber sub2;
    ros::Publisher control_;
    // ros::Publisher pub2;

public:
    geometry_msgs::Twist speed;
    geometry_msgs::Point goal;
    // 构造函数中对sub和pub进行初始化
    ControlTurtle(){
        // 注意订阅函数的写法，第三个参数要写成&+类名+callback形式，以及最后增加this
        distance_info_ = nh_.subscribe("/distance_info",1,&ControlTurtle::callback1,this);
        // sub2 = nh.subscribe("topic_str",1,&ControlTurtle::callback2,this);
        control_ = nh_.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1);
        // pub2 = nh.advertise<std_msgs::String>("processed_str",1);
        // 设定图像中心点 640,360
        goal.x = 640;
        goal.y = 360;
        ofstream clearfile; //每次打开的时候先将文件内容清空
        clearfile.open("src/move_turtle/result.csv", ios::out | ios::trunc );
        clearfile.close();
        
    };

    void control_methods(const display_test::Pub_class_distance::ConstPtr& distance_msg)
    {
        if (distance_msg->classes.size() > 0 && distance_msg->id[0] == 0) // 这里需要考虑当检测到两个目标时，如何处理
        {
            ofstream write;
            write.open("src/move_turtle/result.csv", std::ios::app);
            cout<<"读取到目标类别:"<< endl;
            double inc_x = goal.x - distance_msg->x_center[0];
            double inc_y = goal.y - distance_msg->y_center[0];
            double angle_to_goal = atan2(inc_y,inc_x);
            
            cout << "distance:  " << distance_msg->distance[0] << endl;
            cout << "angle_to_goal:  " << angle_to_goal << endl;
            cout << "inc_x" << inc_x << endl;
            cout << "inc_y" << inc_y << endl;

            write << "distance  ," << distance_msg->distance[0]  << ", angle_to_goal(rad)  ," << angle_to_goal << ", inc_x  ," << inc_x<< ", inc_y  ," << inc_y << endl;       
           
            write.close();
            if (!(isinf(distance_msg->distance[0]) || isnan(distance_msg->distance[0]))){
                if (distance_msg->distance[0] > 0.5 && distance_msg->distance[0] < 0.8){
                    speed.linear.x = 0.0;
                    speed.angular.z = 0.0; 
                    cout << "停止"<<endl;
                }
                else if (distance_msg->distance[0] >= 0.8){
                    if (abs(angle_to_goal) > 0.1){       // 这个需要里程计返回的位置信息才可以
                        speed.linear.x = 0.0;
                        speed.angular.z = 0.3;
                        cout << "旋转" << endl;
                    }
                    else{
                        speed.linear.x = 0.5;
                        speed.angular.z = 0.0;
                        cout << "前进" << endl;
                        
                    }
                }
                else
                {
                    speed.linear.x = -0.5;
                    speed.angular.z = 0.0;
                    cout << "后退" << endl;
                }
            }
            else{
                cout << "测距失败"<< endl;
                speed.linear.x = 0.0;
                speed.angular.z = -0.5;
            }
            
            
            
            
            
            // speed.linear.x = 1; // 设置线速度为1m/s，正为前进，负为后退 
            // speed.angular.z = 1; // 设置角速度为1rad/s，正为左转，负为右转 

            std::cout << "\033[2J\033[1;1H";     // clear terminal
            // system("clear");     //这个清屏速度太快了，看不到什么信息
        }
        control_.publish(speed);
    }
    // 回调函数1,作为类的成员函数
    void callback1(const display_test::Pub_class_distance::ConstPtr& distance_msg)
    {   
        cout<<"成功调用回调函数！！" << endl;
        // std_msgs::Float32 pub_flt;
        // pub_flt.data = flt->data+0.4;
        // 控制思路
        control_methods(distance_msg);
        
   
    };
   
};


int main(int argc, char *argv[])
{
    // 初始化ROS并指定节点名称
    ros::init(argc, argv, "control_turtle");

    // // 新建一个处理类对象，程序会自动调用构造函数初始化sub、pub
    ControlTurtle p;

    // 循环执行
    ros::spin();    //  查一下这个的使用原理及方法，什么时候用spinOnce  参考：https://www.cnblogs.com/liu-fa/p/5925381.html
    return 0;
}



// 用类的方法定义topic和subcriber的方法，参考代码：http://zhaoxuhui.top/blog/2019/10/20/ros-note-7.html
/*
# include<ros/ros.h>
# include<std_msgs/String.h>
# include<std_msgs/Float32.h>

class Processer
{
// 为了保持C++类数据封装的特性，将成员变量写成私有
// 当然如果是public也是完全没问题的，只是有点破坏数据的封装性
private:
    ros::NodeHandle nh;
    ros::Subscriber sub1;
    ros::Subscriber sub2;
    ros::Publisher pub1;
    ros::Publisher pub2;

public:
    // 构造函数中对sub和pub进行初始化
    Processer(){
        // 注意订阅函数的写法，第三个参数要写成&+类名+callback形式，以及最后增加this
        sub1 = nh.subscribe("topic_flt",1,&Processer::callback1,this);
        sub2 = nh.subscribe("topic_str",1,&Processer::callback2,this);
        
        pub1 = nh.advertise<std_msgs::Float32>("processed_flt", 1);
        pub2 = nh.advertise<std_msgs::String>("processed_str",1);
    };

    // 回调函数1,作为类的成员函数
    void callback1(const std_msgs::Float32ConstPtr& flt){
        std_msgs::Float32 pub_flt;
        pub_flt.data = flt->data+0.4;
        pub1.publish(pub_flt);

        std::cout<<"receive flt:"<<flt->data<<std::endl;
        std::cout<<"publish flt:"<<pub_flt.data<<std::endl;
    };

    // 回调函数2,作为类的成员函数
    void callback2(const std_msgs::StringConstPtr& str){
        std_msgs::String str_msg;
        str_msg.data = str->data+" hahaha";
        pub2.publish(str_msg);

        std::cout<<"receive str:"<<str->data<<std::endl;
        std::cout<<"publish str:"<<str_msg.data<<std::endl;
    }
};


int main(int argc, char *argv[])
{
    // 初始化ROS并指定节点名称
    ros::init(argc, argv, "subscribe_publish1");

    // // 新建一个处理类对象，程序会自动调用构造函数初始化sub、pub
    Processer p;

    // 循环执行
    ros::spin();
    return 0;
}
*/

// 控制小车移动的代码  参考：https://www.guyuehome.com/5911
// 另一个参考代码 没有列出来  地址为：https://blog.csdn.net/lizilpl/article/details/46757805
/*
#include <iostream>
#include <math.h>

#include <ros/ros.h>
#include <tf/tf.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Point.h>
#include <nav_msgs/Odometry.h>

using namespace std;

double x = 0.0;
double y = 0.0;
double theta = 0.0;
double rot_q = 0.0;
double roll = 0.0;
double pitch = 0.0;

void NewOdom(const nav_msgs::Odometry::ConstPtr& msg)
{
    x = msg->pose.pose.position.x;
    y = msg->pose.pose.position.y;

    rot_q = msg->pose.pose.orientation;
    (roll, pitch, theta) = euler_from_quaternion([rot_q.x, rot_q.y, rot_q.z, rot_q.w]);
}

int main(int argc, char **argv){

ros::init(argc, argv, "speed_controller");
ros::NodeHandle n;//create a handle node

ros::Subscriber sub = n.subscribe("/odometry/filtered", &NewOdom, this);
ros::Publisher pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 1);

ros::Rate loop_rate(10);

geometry_msgs::Twist speed;
geometry_msgs::Point goal;

goal.x = 5;
goal.y = 5;
while(ros::ok())
{
    double inc_x = goal.x -x;
    double inc_y = goal.y -y;

    double angle_to_goal = atan2(inc_y, inc_x);

    if (abs(angle_to_goal - theta) > 0.1){
        speed.linear.x = 0.0;
        speed.angular.z = 0.3;
    }
    else{
        speed.linear.x = 0.5;
        speed.angular.z = 0.0;
    }
    pub.publish(speed);

    ros::spinOnce();
    }

    return 0;
*/