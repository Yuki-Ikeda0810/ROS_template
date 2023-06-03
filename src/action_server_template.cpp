#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <ros_template_programs/TimerAction.h>
#include <iostream>

namespace ros_template_programs {
    class ActionServer {
        private:
            ros::NodeHandle nh_;
            ros::NodeHandle pnh_;
            actionlib::SimpleActionServer<ros_template_programs::TimerAction> act_srv_;
            ros_template_programs::TimerGoal goal_;
            double init_time;

            void goalCb() ;
            void preemptCb();
            void controlCb();

        public:
            ActionServer( );
    };
}

void ros_template_programs::ActionServer::goalCb() {
    goal_ = *act_srv_.acceptNewGoal();
    ROS_INFO("[ %s ] Got a new target_time = %.2f", ros::this_node::getName().c_str(), goal_.target_time);
    controlCb();
    return;
}

void ros_template_programs::ActionServer::preemptCb() {
    ROS_INFO("[ %s ] Preempted\n", ros::this_node::getName().c_str() );
    ros_template_programs::TimerResult result;
    result.total_time = -1.0;
    act_srv_.setPreempted( result, "I got Preempted!" );
    return;
}

void ros_template_programs::ActionServer::controlCb() {
    if ( !act_srv_.isActive() || act_srv_.isPreemptRequested() ) return;
    ROS_INFO( "[ %s ]\nStart Timer", ros::this_node::getName().c_str() );

    ros_template_programs::TimerFeedback feedback;
    ros_template_programs::TimerResult result;

    double init_time = ros::Time::now().toSec();
    double curt_time = ros::Time::now().toSec();
    double target_time = goal_.target_time;
    feedback.elapsed_time = curt_time - init_time;

    ros::Rate loop_rate(2);
    while ( feedback.elapsed_time < target_time ) {
        curt_time = ros::Time::now().toSec();
        feedback.elapsed_time = curt_time - init_time;
        act_srv_.publishFeedback( feedback );
        ROS_INFO( "[ %s ]\npublishFeedback\nelapsed_time = %.2f\n", ros::this_node::getName().c_str(), feedback.elapsed_time );
        ros::spinOnce();
        loop_rate.sleep();
    }
    result.total_time = feedback.elapsed_time;
    ROS_INFO("[ %s ]\nIt's time to end\ntotal_time = %.2f\n", ros::this_node::getName().c_str(), result.total_time );
    act_srv_.setSucceeded( result );
    
    return;
}

ros_template_programs::ActionServer::ActionServer( ) : nh_(), pnh_("~"), act_srv_( nh_, "timer_action_server", false ) {
    act_srv_.registerGoalCallback( boost::bind( &ros_template_programs::ActionServer::goalCb, this ) );
    act_srv_.registerPreemptCallback ( boost::bind( &ros_template_programs::ActionServer::preemptCb, this ) );
    act_srv_.start();
    ROS_INFO( "[ %s ] Start the Server...\n", ros::this_node::getName().c_str() );
}

int main(int argc, char *argv[])  {
    ros::init(argc, argv, "action_server_template");
    ros_template_programs::ActionServer act_srv;
    ros::spin();
    return 0;
}