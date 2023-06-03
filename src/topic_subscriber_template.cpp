#include <ros/ros.h>
#include <std_msgs/String.h>
#include <iostream>

namespace ros_template_programs {
    class TopicSubscriber {
        private:
            ros::NodeHandle nh_;
            ros::NodeHandle pnh_;
            ros::Subscriber sub_msg_;
            void callbackMessage( const std_msgs::StringConstPtr &msg );

        public:
            TopicSubscriber( );
            void loopPublish();
    };
}

void ros_template_programs::TopicSubscriber::callbackMessage( const std_msgs::StringConstPtr &msg ) {
    ROS_INFO ( "\n[%s] Message Subscribed\n%s\n", ros::this_node::getName().c_str(), msg->data.c_str() );
    return;
}

ros_template_programs::TopicSubscriber::TopicSubscriber( ) : nh_(), pnh_("~") {
    sub_msg_ = nh_.subscribe( "pub_msg", 1, &ros_template_programs::TopicSubscriber::callbackMessage, this );
}

int main(int argc, char *argv[])  {
    ros::init(argc, argv, "topic_subscriber_template");
    ros_template_programs::TopicSubscriber topic_sub;
    ros::spin();
    return 0;
}