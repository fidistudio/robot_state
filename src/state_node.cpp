#include "robot_state/state_node.hpp"

#include "tf2/utils.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.hpp"

namespace robot_state {

StateNode::StateNode(const rclcpp::NodeOptions &options)
    : Node("state_node", options) {
  declare_parameter("odom_topic", "/odom1");
  declare_parameter("pose_topic", "/robot_pose");

  const auto odom_topic = get_parameter("odom_topic").as_string();
  const auto pose_topic = get_parameter("pose_topic").as_string();

  odom_sub_ = create_subscription<nav_msgs::msg::Odometry>(
      odom_topic, 10,
      [this](const nav_msgs::msg::Odometry &msg) { onOdometry(msg); });

  pose_pub_ = create_publisher<geometry_msgs::msg::Pose2D>(pose_topic, 10);

  RCLCPP_INFO(get_logger(), "StateNode ready | %s → %s", odom_topic.c_str(),
              pose_topic.c_str());
}

void StateNode::onOdometry(const nav_msgs::msg::Odometry &msg) {
  geometry_msgs::msg::Pose2D pose;
  pose.x = msg.pose.pose.position.x;
  pose.y = msg.pose.pose.position.y;
  pose.theta = tf2::getYaw(msg.pose.pose.orientation);

  pose_pub_->publish(pose);
}

} // namespace robot_state
