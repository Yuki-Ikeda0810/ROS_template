#! /usr/bin/env python
#coding:utf-8

import rospy
from std_msgs.msg import String

class TopicSubscriber():
    def __init__(self):
        self.sub_msg = rospy.Subscriber('pub_msg', String, self.callback_message )

    def callback_message(self, msg):
        rospy.loginfo('\n [ ' + rospy.get_name() + ' ] Message Subscribed\n%s\n', msg )
        return

if __name__ == '__main__':
    try:
        rospy.init_node('topic_subscriber_template')
        
        node = TopicSubscriber()

        rospy.spin()

    except rospy.ROSInterruptException: pass
