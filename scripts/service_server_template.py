#! /usr/bin/env python
#coding:utf-8

import rospy
from ros_template_programs.msg import Expression
from ros_template_programs.srv import Calculation, CalculationResponse

class ServiceServer():
    def __init__(self):
        self.service = rospy.Service('calculate_two_numbers', Calculation, self.calculate )
        rospy.loginfo('\n [ ' + rospy.get_name() + ' ] Ready to calculate_two_numbers.\n' )

    def calculate(self, req):
        res = CalculationResponse()
        ex = req.expression
        if ex.calculate == '+':
            res.result = ex.a + ex.b
        elif ex.calculate == '-':
            res.result = ex.a - ex.b
        elif ex.calculate == '*':
            res.result = ex.a * ex.b
        else:
            res.result = ex.a / ex.b
        rospy.loginfo('\n [ ' + rospy.get_name() + ' ] Received a call from a client\nRequest: %.2f %s %.2f = %.2f\n', ex.a, ex.calculate, ex.b, res.result )
        return res

if __name__ == '__main__':
    try:
        rospy.init_node('service_server_template')
        
        node = ServiceServer()

        rospy.spin()

    except rospy.ROSInterruptException: pass
