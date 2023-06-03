#include <ros/ros.h>
#include <ros_template_programs/Expression.h>
#include <ros_template_programs/Calculation.h>
#include <iostream>

namespace ros_template_programs {
    class ServiceClient {
        private:
            ros::NodeHandle nh_;
            ros::NodeHandle pnh_;
            ros::ServiceClient client_;

        public:
            ServiceClient( );
            void loopCallServer();
    };
}

ros_template_programs::ServiceClient::ServiceClient( ) : nh_(), pnh_("~") {
    ros::service::waitForService("calculate_two_numbers", ros::Duration(5.0));
    ROS_INFO("[%s] Connect to the service server", ros::this_node::getName().c_str());
    client_ = nh_.serviceClient<ros_template_programs::Calculation>("calculate_two_numbers");
}

void ros_template_programs::ServiceClient::loopCallServer( ) {
    ros::Rate loop_rate(1);
    int count = 0;
    ros_template_programs::Expression ex;
    ex.a = pnh_.param<double>("a", 1);
    ex.b = pnh_.param<double>("b", 1);
	while(ros::ok()) {
        if ( count%4 == 0 ) {
            ex.calculate = "+";
        } else if ( count%4 == 1 ) {
            ex.calculate = "-";
        } else if ( count%4 == 2 ) {
            ex.calculate = "*";
        } else {
            ex.calculate = "/";
        }
        ros_template_programs::Calculation srv;
        srv.request.expression = ex;
        ROS_INFO("[%s] Call the calculate_two_numbers server\nExpression :%.2f %s %.2f", 
            ros::this_node::getName().c_str(), ex.a, ex.calculate.c_str(), ex.b);
        if (client_.call(srv)) {
            ROS_INFO("Result: %.2f\n", srv.response.result);
        } else {
            ROS_ERROR("Failed to call service calculate_two_numbers\n");
        }
        count++;
		ros::spinOnce();
		loop_rate.sleep();
	}
    return;
}

int main(int argc, char *argv[])  {
    ros::init(argc, argv, "service_client_template");
    ros_template_programs::ServiceClient srv_clt;
    srv_clt.loopCallServer();
    ros::spin();
    return 0;
}