/***************************************************************************************************
 * Copyright Five AI 2021.
 * All rights reserved.
 ***************************************************************************************************/

#pragma once

#include "util/ShmSharedPtr.h"

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <boost/algorithm/string/replace.hpp>

#include <stdexcept>

namespace fiveai { namespace std_msgs { namespace shm
{
    template <typename T>
    using SharedPtr = fiveai::platform::shm::SharedPtr<T>;
}}}

namespace ros { namespace message_traits
{
    template <class T> struct IsFixedSize<fiveai::std_msgs::shm::SharedPtr<T>> : TrueType {};
    template <class T> struct IsFixedSize<fiveai::std_msgs::shm::SharedPtr<T> const> : TrueType {};

    template <class T> struct IsMessage<fiveai::std_msgs::shm::SharedPtr<T>> : TrueType {};
    template <class T> struct IsMessage<fiveai::std_msgs::shm::SharedPtr<T> const> : TrueType {};

    template <class T> struct HasHeader<fiveai::std_msgs::shm::SharedPtr<T>> : FalseType {};
    template <class T> struct HasHeader<fiveai::std_msgs::shm::SharedPtr<T> const> : FalseType {};

    template<class T>
    struct MD5Sum<fiveai::std_msgs::shm::SharedPtr<T>>
    {
        static const char* value()
        {
            // TODO: generate proper MD5 sum
            static const auto sum = std::string("33333333333333333333333333333333_") + MD5Sum<T>::value();
            return sum.c_str();
        }

        static const char* value(const fiveai::std_msgs::shm::SharedPtr<T>&)
        {
            return value();
        }

        static const uint64_t static_value1 = 0x060021388200f6f0ULL;
        static const uint64_t static_value2 = 0xf447d0fcd9c64743ULL;
    };

    template<class T>
    struct DataType<fiveai::std_msgs::shm::SharedPtr<T>>
    {
        static std::string getPointedTypeName()
        {
            const std::string str = DataType<T>::value();
            return boost::replace_all_copy(str, "/", "_");
        }

        static const char* value()
        {
            // TODO: is this thread safe?
            static const auto v = std::string("sensor_msgs/ShmSharedPtr_") + getPointedTypeName();
            return v.c_str();
        }

        static const char* value(const fiveai::std_msgs::shm::SharedPtr<T>&)
        {
            return value();
        }
    };

    template<class T>
    struct Definition<fiveai::std_msgs::shm::SharedPtr<T>>
    {
        static const char* value()
        {
            return "# This message contains shared memory shared pointer";
        }

        static const char* value(const fiveai::std_msgs::shm::SharedPtr<T>&)
        {
           return value();
        }
    };

}} // namespace ros::message_traits

namespace ros { namespace serialization
{
    template<class _T> struct Serializer<fiveai::std_msgs::shm::SharedPtr<_T>>
    {
        template<typename Stream, typename T>
        inline static
        void allInOne(Stream&, T)
        {
            throw std::logic_error{"Shared memory shared pointers are not (de)serializable!"
                                   " This means that they cannot be passed between nodes via "
                                   "ros publish/subscribe mechanisms."};
        }

        ROS_DECLARE_ALLINONE_SERIALIZER
    };

}} // namespace ros::serialization

namespace ros { namespace message_operations
{
    template<class T>
    struct Printer<fiveai::std_msgs::shm::SharedPtr<T>>
    {
        template<typename Stream>
        static
        void stream(Stream& s, const std::string& indent, const fiveai::std_msgs::shm::SharedPtr<T>& p)
        {
            s << indent << "pointer value: " << p.get() << std::endl;
            s << indent << "use count: " << p.use_count() << std::endl;
        }
    };

}} // namespace ros::message_operations