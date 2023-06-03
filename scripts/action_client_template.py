#! /usr/bin/env python
#coding:utf-8

import roslib; roslib.load_manifest('ros_template_programs')
import rospy
import actionlib
from ros_template_programs.msg import TimerAction
from ros_template_programs.msg import TimerGoal
from ros_template_programs.msg import TimerResult
from ros_template_programs.msg import TimerFeedback


class ActionClient():
    def __init__(self):
        self.client = actionlib.SimpleActionClient( 'timer_action_server', TimerAction)
        self.goal = TimerGoal()
        self.action_executing = False
        
    def send_goal(self):
        self.client.send_goal(
            self.goal,
            self.done_cb,
            self.active_cb,
            self.feedback_cb
        )
        return

    def done_cb(self, state, result):
        rospy.loginfo('\n [ ' + rospy.get_name() + ' ]\nFinished!!\n' )
        rospy.loginfo('\n [ ' + rospy.get_name() + ' ]\nTotal_time = %.2f\n', result.total_time )
        action_executing = False
        return
    
    def active_cb(self):
        rospy.loginfo('\n [ ' + rospy.get_name() + ' ]\nGoal just went active...\n' )
        return
    
    def feedback_cb(self, feedback):
        rospy.loginfo('\n [ ' + rospy.get_name() + ' ]\nGot Feedback of Progress to Goal\nelapsed_time = %.2f\n', feedback.elapsed_time )
        return

    def loop_call_server(self):
        loop_rate = rospy.Rate(1)
        rospy.loginfo('\n [ ' + rospy.get_name() + ' ]\nWaiting For Server...\n' )
        self.client.wait_for_server()
        target_time = rospy.get_param( rospy.get_name() + '/target_time', 10.0)
        while not rospy.is_shutdown():
            if self.action_executing == False:
                self.goal.target_time = target_time;
                self.send_goal()
                rospy.loginfo('\n [ ' + rospy.get_name() + ' ]\nSet a new target_time = %.2f\n', self.goal.target_time )
                self.action_executing = True
            loop_rate.sleep()
        return

if __name__ == '__main__':
    try:
        rospy.init_node('action_client_template')
        
        node = ActionClient()
        node.loop_call_server()

        rospy.spin()

    except rospy.ROSInterruptException: pass
