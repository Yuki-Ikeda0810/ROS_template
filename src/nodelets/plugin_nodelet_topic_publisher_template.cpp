#include <ros/ros.h>
#include <nodelet/nodelet.h>
#include <pluginlib/class_list_macros.h>
#include <std_msgs/String.h>

namespace ros_template_programs {
    class PluginNodeletTopicPublisher : public nodelet::Nodelet {
        private:
            ros::NodeHandle nh_;
            ros::NodeHandle pnh_;
            ros::Publisher pub_;
            ros::Timer timer_;
            std_msgs::String msg_;

        public:
            virtual void onInit();
            void timer_callback(const ros::TimerEvent&);
    };
}

void ros_template_programs::PluginNodeletTopicPublisher::onInit() {
    NODELET_INFO("Talker Init");
    nh_ = getNodeHandle();
    pnh_ = getPrivateNodeHandle();

    msg_.data = pnh_.param<std::string>("message", "Hello, World!");
    pub_ = nh_.advertise<std_msgs::String>("pub_msg", 10);
    double sleep_time = 1.0 / ( pnh_.param<double>("hz", 1.0 ) != 0.0  ? pnh_.param<double>("hz", 1.0 ) : 1.0);
    timer_ = nh_.createTimer(ros::Duration(sleep_time), &PluginNodeletTopicPublisher::timer_callback, this);
    // タイマーを生成
    // 1つ目の引数は実行間隔です。つまり10Hzで動作させたいならros::Duration(0.1)と入れます。
    // 2つ目がtimerが起動したときに起動するコールバック関数です。またデフォルトだとタイマーは繰り返しになります。つまり無限に0.1秒ごとにコールバック関数が呼ばれます。
}

void ros_template_programs::PluginNodeletTopicPublisher::timer_callback(const ros::TimerEvent&) {
    pub_.publish(msg_);
    NODELET_INFO("send: %s", msg_.data.c_str());
}

PLUGINLIB_EXPORT_CLASS(ros_template_programs::PluginNodeletTopicPublisher, nodelet::Nodelet);