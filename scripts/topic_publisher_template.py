#! /usr/bin/env python
#coding:utf-8

import rospy
from std_msgs.msg import String

class TopicPublisher():
    def __init__(self):
        self.pub_msg = rospy.Publisher('pub_msg', String, queue_size=1)
        self.msg = rospy.get_param( rospy.get_name() + '/message', 'Hello, World!')

    def loop_publish(self):
        loop_rate = rospy.Rate(1)
        while not rospy.is_shutdown():
            self.pub_msg.publish(self.msg)
            rospy.loginfo('\n [ ' + rospy.get_name()  + ' ] Message Published\n%s\n', self.msg )
            loop_rate.sleep()
        return

if __name__ == '__main__':
    try:
        rospy.init_node('topic_publisher_template')
        
        node = TopicPublisher()
        node.loop_publish()

        rospy.spin()

    except rospy.ROSInterruptException: pass
