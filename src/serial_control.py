#!/usr/bin/python
import rospy
import serial
import time
import struct
from std_msgs.msg import String
from nav_msgs.msg import Odometry
from geometry_msgs.msg import Twist

received_data = " "
received_data_save = " "
send_data = [1,2,3,4,5,6]
check = 0

cmd_x_str = 'V+000'
cmd_th_str = 'A+00'

send_data = 'V+000A+00'

def control_input(control_input):
    global cmd_x_str,cmd_th_str,send_data

    x = control_input.linear.x
    th = control_input.angular.z #deg

    x_sign = '+'
    th_sign = '+'
    if x < 0:
        x_sign = '-'
    if th < 0:
        th_sign = '-'
    cmd_x_str = 'V' + x_sign + str(int((abs(x) / 100)%10)) + str(int((abs(x) / 10)%10)) + str(int(abs(x) % 10))
    cmd_th_str = 'A' + th_sign + str(int((abs(th) / 10)%10)) + str(int((abs(th))%10))

    send_data = cmd_x_str + cmd_th_str + '\n'


def talker():
    pub = rospy.Publisher('chatter', String, queue_size=10)
    global send_data
    rospy.init_node('talker', anonymous=True)
    sub = rospy.Subscriber('cmd_vel', Twist, control_input)
    rate = rospy.Rate(20) # 10hz
    while not rospy.is_shutdown():

        try:
            ser = serial.Serial(port='/dev/ttyACM0',baudrate=9600,timeout=1,write_timeout=1)
            ser.write(send_data)

            ser.flushInput()
            ser.flushOutput()
            ser.close()

        except serial.SerialException:
            print("catch")
            continue

        rate.sleep()

if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyACM0')

    try:
        talker()
    except rospy.ROSInterruptException:
        pass

