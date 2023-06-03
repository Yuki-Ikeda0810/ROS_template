#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <ros_template_programs/TimerAction.h>
#include <iostream>

namespace ros_template_programs {
    class ActionClient {
        private:
            ros::NodeHandle nh_;
            ros::NodeHandle pnh_;
            actionlib::SimpleActionClient<ros_template_programs::TimerAction> act_clt_;
            ros_template_programs::TimerGoal goal_;
            bool action_executing_;
            
            void sendGoal();
            void doneCb( const actionlib::SimpleClientGoalState& state, const ros_template_programs::TimerResultConstPtr& result );
            void activeCb( );
            void feedbackCb( const ros_template_programs::TimerFeedbackConstPtr& feedback );
        public:
            ActionClient( );
            void loopCallServer();
    };
}

void ros_template_programs::ActionClient::sendGoal() {
    act_clt_.sendGoal( goal_,
        boost::bind( &ros_template_programs::ActionClient::doneCb, this, _1, _2 ),
        boost::bind( &ros_template_programs::ActionClient::activeCb, this ),
        boost::bind( &ros_template_programs::ActionClient::feedbackCb, this, _1 ) );
}
void ros_template_programs::ActionClient::doneCb( 
    const actionlib::SimpleClientGoalState& state, 
    const ros_template_programs::TimerResultConstPtr& result ) {
    ROS_INFO( "[ %s ]\nFinished!!", ros::this_node::getName().c_str());
    ROS_INFO( "[ %s ]\nTotal_time = %.2f", ros::this_node::getName().c_str(), result->total_time );
    action_executing_ = false;
    ros::Duration(1.0).sleep();

}
void ros_template_programs::ActionClient::activeCb( ) {
    ROS_INFO( "[ %s ]\nGoal just went active...\n", ros::this_node::getName().c_str());
}
void ros_template_programs::ActionClient::feedbackCb( 
    const ros_template_programs::TimerFeedbackConstPtr& feedback ) {
    ROS_INFO( "[ %s ]\nGot Feedback of Progress to Goal\nelapsed_time = %.2f\n", ros::this_node::getName().c_str(), feedback->elapsed_time );
}

ros_template_programs::ActionClient::ActionClient( ) : nh_(), pnh_("~"),  act_clt_( "timer_action_server", true ) {
    ROS_INFO( "[ %s ] Waiting For Server...", ros::this_node::getName().c_str() );
    act_clt_.waitForServer();
    ROS_INFO("[ %s ] Connect to the action server", ros::this_node::getName().c_str());
    action_executing_ = false;
}

void ros_template_programs::ActionClient::loopCallServer( ) {
    ros::Rate loop_rate(1);
    double target_time = pnh_.param<double>("target_time", 10.0);
	while(ros::ok()) {
        if ( !action_executing_ ) {
            goal_.target_time = target_time;
            sendGoal();
            ROS_INFO( "[ %s ] Set a new target_time = %.2f\n", ros::this_node::getName().c_str(), target_time );
            action_executing_ = true;
        } 
		ros::spinOnce();
		loop_rate.sleep();
	}
    return;
}

int main(int argc, char *argv[])  {
    ros::init(argc, argv, "action_client_template");
    ros_template_programs::ActionClient act_clt;
    act_clt.loopCallServer();
    ros::spin();
    return 0;
}