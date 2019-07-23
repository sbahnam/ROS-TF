#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <tf/transform_broadcaster.h>

void publishNEDandNWU(tf::StampedTransform transform){
    //Get states from ENU frame
    tf::Quaternion q = transform.getRotation();
    double x = transform.getOrigin().x();
    double y = transform.getOrigin().y();
    double z = transform.getOrigin().z();
    double roll;
    double pitch;
    double yaw;
    tf::Matrix3x3(q).getRPY(roll, pitch, yaw);

    static tf::TransformBroadcaster br_NED;
    tf::Transform transform_NED;
    static tf::TransformBroadcaster br_NWU;
    tf::Transform transform_NWU;

    // NED
    transform_NED.setOrigin( tf::Vector3(y, x, -z ));
    tf::Quaternion q_NED;
    q_NED.setRPY(pitch, roll, -yaw);
    transform_NED.setRotation(q_NED);
    br_NED.sendTransform(tf::StampedTransform(transform_NED, ros::Time::now(), "world", "tf_ned"));
    
    // NWU
    transform_NWU.setOrigin( tf::Vector3(y, -x, z ));
    tf::Quaternion q_NWU;
    q_NWU.setRPY(pitch, -roll, yaw);
    transform_NWU.setRotation(q_NWU);
    br_NWU.sendTransform(tf::StampedTransform(transform_NWU, ros::Time::now(), "world", "tf_nwu"));
}

int main(int argc, char** argv){
    ros::init(argc, argv, "my_tf_receiver");
  
    ros::NodeHandle node;
    ros::Rate rate(1.0);
    tf::TransformListener listener;
    while (node.ok()){
        tf::StampedTransform transform;
        try{
        ros::Time now = ros::Time(0);
        listener.waitForTransform("/world", "/base_tf_enu", now, ros::Duration(1.0));
        listener.lookupTransform("/world", "/base_tf_enu", now, transform);
        PublishNEDandNWU(transform); // publish NED and NWU when receiving (same rate)
        }
        catch (tf::TransformException ex) {
          ROS_ERROR("%s",ex.what());
          continue;
        }
    }
}


