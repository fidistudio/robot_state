import rclpy
from rclpy.node import Node
from nav_msgs.msg import Odometry
from geometry_msgs.msg import Pose2D
from scipy.spatial.transform import Rotation as R


class StateNode(Node):

    def __init__(self):
        super().__init__("state_node")

        self.declare_parameter("odom_topic", "/odom1")
        self.declare_parameter("pose_topic", "/robot_pose")

        odom_topic = self.get_parameter("odom_topic").value
        pose_topic = self.get_parameter("pose_topic").value

        self.pose_pub = self.create_publisher(Pose2D, pose_topic, 10)
        self.create_subscription(Odometry, odom_topic, self.odom_callback, 10)

    def odom_callback(self, msg: Odometry) -> None:
        pose = Pose2D()
        pose.x = msg.pose.pose.position.x
        pose.y = msg.pose.pose.position.y

        q = msg.pose.pose.orientation
        yaw = R.from_quat([q.x, q.y, q.z, q.w]).as_euler("xyz")[2]
        pose.theta = yaw

        self.pose_pub.publish(pose)


def main():
    rclpy.init()
    node = StateNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()
