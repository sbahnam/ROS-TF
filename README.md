# ROS-TF

To enable ros commands:
`source catkin_ws/devel/setup.bash` 

build the files:
`catkin_make` in the catkin_ws directory

open three other terminals (tabs) and source them.
First run `roscore`
Second run `rosrun ros_transframes tf_publsiher_base` and input 6 floats/ints.
Third run `rosrun ros_transframes tf_receiver_translator` (Ignore the first error).
Fourth check the different frames with: `rosrun tf tf_echo /world /base_tf_enu`, `rosrun tf tf_echo /world /tf_ned` and `rosrun tf tf_echo /world /base_tf_nwu`
