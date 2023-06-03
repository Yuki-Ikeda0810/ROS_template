#include <ros/ros.h>
#include <std_msgs/String.h>
#include <iostream>

namespace ros_template_programs {
    class TopicPublisher {
        private:
            ros::NodeHandle nh_;
            ros::NodeHandle pnh_;
            ros::Publisher pub_msg_;
            std_msgs::String msg_;

        public:
            TopicPublisher( );
            void loopPublish();
    };
}

ros_template_programs::TopicPublisher::TopicPublisher( ) : nh_(), pnh_("~") {
    msg_.data = pnh_.param<std::string>("message", "Hello, World!");
    pub_msg_ = nh_.advertise<std_msgs::String>("pub_msg", 1);
}

void ros_template_programs::TopicPublisher::loopPublish( ) {
    ros::Rate loop_rate(1);
	while(ros::ok()) {
        pub_msg_.publish(msg_);
        ROS_INFO("\n[%s] Message Published\n%s\n", ros::this_node::getName().c_str(), msg_.data.c_str() );
		ros::spinOnce();
		loop_rate.sleep();
	}
    return;
}

int main(int argc, char *argv[])  {
    ros::init(argc, argv, "topic_publisher_template");
    ros_template_programs::TopicPublisher topic_pub;
    topic_pub.loopPublish();
    ros::spin();
    return 0;
}