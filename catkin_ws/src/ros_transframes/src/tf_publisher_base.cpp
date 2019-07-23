#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
//#include <math.h.>


//ros::init(argc, argv, "tf_publsiher_base", ros::init_options::AnonymousName);

void publishENU(double states[6]){
    double x = states[0];
    double y = states[1];
    double z = states[2];
    double roll = states[3]*M_PI/180;
    double pitch = states[4]*M_PI/180; //angles to radian
    double yaw = states[5]*M_PI/180;
    
    static tf::TransformBroadcaster br;
    tf::Transform transform;
    transform.setOrigin( tf::Vector3(x, y, z) );
    tf::Quaternion q;
    q.setRPY(roll, pitch, yaw);
    transform.setRotation(q);
    br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", "base_tf_enu"));
}


int main(int argc, char** argv){
    ros::init(argc, argv, "my_tf_broadcaster");
    ros::NodeHandle node;
    ros::Rate rate(1.0);
    
    double states[6] = {}; // angles in degree
    char inputchar[30];
    
    std::cout << "Give input (x, y, z, roll, pitch, yaw)"<<std::endl;
    std::cin.getline(inputchar, sizeof(inputchar));
    std::string inputstr(inputchar);
    std::string delimiter = ",";
    
    //convert string to double array
    for(int i=0; i<=5; i++){
        std::string valuestr = inputstr.substr(0, inputstr.find(delimiter));
        inputstr.erase(0, inputstr.find(delimiter) + delimiter.length());
        states[i] =atof(valuestr.c_str());
    }

    while(node.ok())
    {
        publishENU(states);
        rate.sleep();
    }
    return 0;
};
