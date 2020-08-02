# ros_projects_yolo-zed-fusion

# 本工程包含的内容

1. darknet_ros
2. zed
3. 将zed的深度信息与yolov2-tiny输出的boundingboxes的信息融合，输出boundingboxes的中心点到zed的距离信息。这个是自己创建的一个新的功能包实现的。如果需要修改基础网络的话，就在darknet对应的cfg和weights中添加权重和配置文件，并在ros.launch中更改启动的cfg文件名称。
4 这里还包含了一个测试用的功能包。准备删除了。现在这个备份版本还没有删除。
