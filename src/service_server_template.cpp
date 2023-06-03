#include <ros/ros.h>
#include <ros_template_programs/Expression.h>
#include <ros_template_programs/Calculation.h>
#include <iostream>

namespace ros_template_programs {
    class ServiceServer {
        private:
            ros::NodeHandle nh_;
            ros::NodeHandle pnh_;
            ros::ServiceServer service_;
            bool calculate(ros_template_programs::Calculation::Request &req,
                ros_template_programs::Calculation::Response &res);

        public:
            ServiceServer( );
    };
}

bool ros_template_programs::ServiceServer::calculate(
    ros_template_programs::Calculation::Request &req,
    ros_template_programs::Calculation::Response &res) {
    ros_template_programs::Expression ex = req.expression;
    if ( ex.calculate == "+" ) {
        res.result = ex.a + ex.b;
    } else if ( ex.calculate == "-" ) {
        res.result = ex.a - ex.b;
    } else if ( ex.calculate == "*" ) {
        res.result = ex.a * ex.b;
    } else {
        res.result = ex.a / ex.b;
    }
    ROS_INFO("[%s] Received a call from a client\nRequest: %.2f %s %.2f", 
        ros::this_node::getName().c_str(), ex.a, ex.calculate.c_str(), ex.b);
    ROS_INFO("sending back response: [%.f]\n", res.result);
    return true;
}

ros_template_programs::ServiceServer::ServiceServer( ) : nh_(), pnh_("~") {
    service_ = nh_.advertiseService("calculate_two_numbers", &ros_template_programs::ServiceServer::calculate, this);
    ROS_INFO("[%s] Ready to calculate_two_numbers.", ros::this_node::getName().c_str());
}

int main(int argc, char *argv[])  {
    ros::init(argc, argv, "service_server_template");
    ros_template_programs::ServiceServer srv_srv;
    ros::spin();
    return 0;
}