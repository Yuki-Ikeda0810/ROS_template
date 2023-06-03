#! /usr/bin/env python
#coding:utf-8

import roslib; roslib.load_manifest('ros_template_programs')
import rospy
import actionlib
from ros_template_programs.msg import TimerAction
from ros_template_programs.msg import TimerGoal
from ros_template_programs.msg import TimerResult
from ros_template_programs.msg import TimerFeedback

class ActionServer():
    def __init__(self):
        self.act_srv = actionlib.SimpleActionServer( 'timer_action_server', TimerAction, execute_cb=None, auto_start=False )
        self.act_srv.register_goal_callback( self.goal_cb )
        self.act_srv.register_preempt_callback( self.preempt_cb )
        self.goal = TimerGoal()
        self.act_srv.start()
        rospy.loginfo('\n [ ' + rospy.get_name() + ' ]\nStart the Server...\n' )

    def goal_cb(self):
        self.goal = self.act_srv.accept_new_goal();
        rospy.loginfo('\n [ ' + rospy.get_name() + ' ]\n Got a new target_time = %.2f\n', self.goal.target_time )
        self.control_cb()
        return  

    def preempt_cb(self):
        rospy.loginfo('\n [ ' + rospy.get_name() + ' ]\nPreempted...\n' )
        result = TimerResult()
        result.total_time = -1.0;
        self.act_srv.setPreempted( result, 'I got Preempted!' );
        return
    
    def control_cb(self):
        if (self.act_srv.is_active() == False or self.act_srv.is_preempt_requested() == True) : return
        rospy.loginfo('\n [ ' + rospy.get_name() + ' ]\nStart Timer\n' )
        feedback = TimerFeedback()
        result = TimerResult()

        init_time = rospy.Time.now().to_sec()
        curt_time = init_time
        target_time = self.goal.target_time
        feedback.elapsed_time = curt_time - init_time

        loop_rate = rospy.Rate(2)
        while ( feedback.elapsed_time < target_time ) :
            curt_time = rospy.Time.now().to_sec()
            feedback.elapsed_time = curt_time - init_time;
            self.act_srv.publish_feedback( feedback )
            rospy.loginfo('\n [ ' + rospy.get_name() + ' ]\npublishFeedback\nelapsed_time = %.2f\n', feedback.elapsed_time )
            loop_rate.sleep()
        result.total_time = feedback.elapsed_time
        rospy.loginfo('\n [ ' + rospy.get_name() + ' ]\nIt is time to end\ntotal_time = %.2f\n', result.total_time )
        self.act_srv.set_succeeded( result )
        return

if __name__ == '__main__':
    try:
        rospy.init_node('action_server_template')
        node = ActionServer()
        rospy.spin()

    except rospy.ROSInterruptException: pass
