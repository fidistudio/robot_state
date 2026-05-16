#pragma once

#include "geometry_msgs/msg/pose2_d.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include "rclcpp/rclcpp.hpp"

namespace robot_state {

/**
 * @brief Converts Odometry messages into Pose2D (x, y, yaw).
 *
 * Subscribes to an odometry topic and republishes the 2D pose
 * (position + heading) derived from the full 6-DOF odometry.
 * Quaternion → yaw conversion is handled by tf2::getYaw,
 * which is numerically robust and avoids gimbal-lock issues.
 */
class StateNode : public rclcpp::Node {
public:
  explicit StateNode(
      const rclcpp::NodeOptions &options = rclcpp::NodeOptions{});

private:
  void onOdometry(const nav_msgs::msg::Odometry &msg);

  rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odom_sub_;
  rclcpp::Publisher<geometry_msgs::msg::Pose2D>::SharedPtr pose_pub_;
};

} // namespace robot_state
