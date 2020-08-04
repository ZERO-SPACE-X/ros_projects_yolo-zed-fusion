// Generated by gencpp from file display_test/Pub_class_distance.msg
// DO NOT EDIT!


#ifndef DISPLAY_TEST_MESSAGE_PUB_CLASS_DISTANCE_H
#define DISPLAY_TEST_MESSAGE_PUB_CLASS_DISTANCE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace display_test
{
template <class ContainerAllocator>
struct Pub_class_distance_
{
  typedef Pub_class_distance_<ContainerAllocator> Type;

  Pub_class_distance_()
    : classes()
    , distance()
    , x_center()
    , y_center()
    , id()  {
    }
  Pub_class_distance_(const ContainerAllocator& _alloc)
    : classes(_alloc)
    , distance(_alloc)
    , x_center(_alloc)
    , y_center(_alloc)
    , id(_alloc)  {
  (void)_alloc;
    }



   typedef std::vector<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > , typename ContainerAllocator::template rebind<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::other >  _classes_type;
  _classes_type classes;

   typedef std::vector<float, typename ContainerAllocator::template rebind<float>::other >  _distance_type;
  _distance_type distance;

   typedef std::vector<int64_t, typename ContainerAllocator::template rebind<int64_t>::other >  _x_center_type;
  _x_center_type x_center;

   typedef std::vector<int64_t, typename ContainerAllocator::template rebind<int64_t>::other >  _y_center_type;
  _y_center_type y_center;

   typedef std::vector<int16_t, typename ContainerAllocator::template rebind<int16_t>::other >  _id_type;
  _id_type id;





  typedef boost::shared_ptr< ::display_test::Pub_class_distance_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::display_test::Pub_class_distance_<ContainerAllocator> const> ConstPtr;

}; // struct Pub_class_distance_

typedef ::display_test::Pub_class_distance_<std::allocator<void> > Pub_class_distance;

typedef boost::shared_ptr< ::display_test::Pub_class_distance > Pub_class_distancePtr;
typedef boost::shared_ptr< ::display_test::Pub_class_distance const> Pub_class_distanceConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::display_test::Pub_class_distance_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::display_test::Pub_class_distance_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace display_test

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'display_test': ['/home/zero/catkin_ws/src/display_test/msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::display_test::Pub_class_distance_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::display_test::Pub_class_distance_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::display_test::Pub_class_distance_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::display_test::Pub_class_distance_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::display_test::Pub_class_distance_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::display_test::Pub_class_distance_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::display_test::Pub_class_distance_<ContainerAllocator> >
{
  static const char* value()
  {
    return "26a7eb42f6a9f1a1625843bee8a7eb06";
  }

  static const char* value(const ::display_test::Pub_class_distance_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x26a7eb42f6a9f1a1ULL;
  static const uint64_t static_value2 = 0x625843bee8a7eb06ULL;
};

template<class ContainerAllocator>
struct DataType< ::display_test::Pub_class_distance_<ContainerAllocator> >
{
  static const char* value()
  {
    return "display_test/Pub_class_distance";
  }

  static const char* value(const ::display_test::Pub_class_distance_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::display_test::Pub_class_distance_<ContainerAllocator> >
{
  static const char* value()
  {
    return "string[] classes\n\
float32[] distance \n\
int64[] x_center\n\
int64[] y_center\n\
int16[] id\n\
";
  }

  static const char* value(const ::display_test::Pub_class_distance_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::display_test::Pub_class_distance_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.classes);
      stream.next(m.distance);
      stream.next(m.x_center);
      stream.next(m.y_center);
      stream.next(m.id);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct Pub_class_distance_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::display_test::Pub_class_distance_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::display_test::Pub_class_distance_<ContainerAllocator>& v)
  {
    s << indent << "classes[]" << std::endl;
    for (size_t i = 0; i < v.classes.size(); ++i)
    {
      s << indent << "  classes[" << i << "]: ";
      Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.classes[i]);
    }
    s << indent << "distance[]" << std::endl;
    for (size_t i = 0; i < v.distance.size(); ++i)
    {
      s << indent << "  distance[" << i << "]: ";
      Printer<float>::stream(s, indent + "  ", v.distance[i]);
    }
    s << indent << "x_center[]" << std::endl;
    for (size_t i = 0; i < v.x_center.size(); ++i)
    {
      s << indent << "  x_center[" << i << "]: ";
      Printer<int64_t>::stream(s, indent + "  ", v.x_center[i]);
    }
    s << indent << "y_center[]" << std::endl;
    for (size_t i = 0; i < v.y_center.size(); ++i)
    {
      s << indent << "  y_center[" << i << "]: ";
      Printer<int64_t>::stream(s, indent + "  ", v.y_center[i]);
    }
    s << indent << "id[]" << std::endl;
    for (size_t i = 0; i < v.id.size(); ++i)
    {
      s << indent << "  id[" << i << "]: ";
      Printer<int16_t>::stream(s, indent + "  ", v.id[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // DISPLAY_TEST_MESSAGE_PUB_CLASS_DISTANCE_H
