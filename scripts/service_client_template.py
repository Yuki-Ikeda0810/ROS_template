#! /usr/bin/env python
#coding:utf-8

import rospy
from ros_template_programs.msg import Expression
from ros_template_programs.srv import Calculation

class ServiceClient():
    def __init__(self):
        rospy.wait_for_service('calculate_two_numbers')
        self.client = rospy.ServiceProxy('calculate_two_numbers', Calculation)
        
    def loop_call_server(self):
        loop_rate = rospy.Rate(1)
        count = 0
        ex = Expression()
        ex.a = rospy.get_param( rospy.get_name() + '/a', 1.0)
        ex.b = rospy.get_param( rospy.get_name() + '/b', 1.0)
        while not rospy.is_shutdown():
            if count%4 == 0:
                ex.calculate = '+'
            elif count%4 == 1:
                ex.calculate = '-'
            elif count%4 == 2:
                ex.calculate = '*'
            else:
                ex.calculate = '/'
            try:
                res = self.client(ex)
                rospy.loginfo('\n [ ' + rospy.get_name()  + ' ] Result: %.2f\n', res.result )

            except rospy.ServiceException, e:
                print "Failed to call service calculate_two_numbers : %s"%e
            count += 1
            loop_rate.sleep()
        return

if __name__ == '__main__':
    try:
        rospy.init_node('service_client_template')
        
        node = ServiceClient()
        node.loop_call_server()

        rospy.spin()

    except rospy.ROSInterruptException: pass
