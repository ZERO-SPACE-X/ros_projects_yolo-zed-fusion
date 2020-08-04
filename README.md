# ros_projects_yolo-zed-fusion

# 本工程包含的内容

1. darknet_ros
2. zed
3. 将zed的深度信息与yolov2-tiny输出的boundingboxes的信息融合，输出boundingboxes的中心点到zed的距离信息。这个是自己创建的一个新的功能包实现的，功能包的名称为display_test,节点名称为fuse_data。如果需要修改基础网络的话，就在darknet对应的cfg和weights中添加权重和配置文件，并在ros.launch中更改启动的cfg文件名称。
4. 这里还包含了一个测试用的功能包。准备删除了。现在这个备份版本还没有删除。
5. 添加了一个新的节点publish_distance，这个节点完成了订阅融合后的信息，并且将信息发布出去，方便别的节点订阅使用，这个节点完成了如下工作：
    - 自定义了一个msg结构
    - 可以完成输出检测的类别，及对应的boundingbox的中心点到zed的距离，中心点的x，y坐标（相对于整个图像的）
    