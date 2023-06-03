#include <ros/ros.h>
#include <nodelet/nodelet.h>
#include <pluginlib/class_list_macros.h>
#include <std_msgs/String.h>

namespace ros_template_programs {
    class PluginNodeletTopicSubscriber : public nodelet::Nodelet {
        private:
            ros::NodeHandle nh_;
            ros::Subscriber sub_;

        public:
            virtual void onInit();
            void chatter_callback(const std_msgs::String& string_msg);
    };
}

void ros_template_programs::PluginNodeletTopicSubscriber::onInit() {
    NODELET_INFO("Listener Init");
    nh_ = getNodeHandle();
    sub_ = nh_.subscribe("pub_msg", 10, &PluginNodeletTopicSubscriber::chatter_callback, this);
}

void ros_template_programs::PluginNodeletTopicSubscriber::chatter_callback(const std_msgs::String& msg) {
    NODELET_INFO("recieve: %s", msg.data.c_str());
}


PLUGINLIB_EXPORT_CLASS(ros_template_programs::PluginNodeletTopicSubscriber, nodelet::Nodelet)