#include <chrono>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/header.hpp"
#include "sensor_msgs/msg/image.hpp"

#include <cv_bridge/cv_bridge.h>                    // Converts between OpenCV image representations and ROS 2 image messages
#include <image_transport/image_transport.hpp>      // Allows us to publish and subscribe to compressed image streams in ROS 2
#include <opencv2/opencv.hpp>

using namespace std::chrono_literals;

class MinimalImagePublisher :   public rclcpp::Node
{
    public:

        MinimalImagePublisher() :   Node("minimal_image_publisher"), count_(0)    
        {
            publisher_ = this->create_publisher<sensor_msgs::msg::Image>("random_image", 10);
            timer_ = this->create_wall_timer(500ms, std::bind(&MinimalImagePublisher::timer_callback, this));
        }

    private:

        void timer_callback() 
        {
            // Create a new 640x480 image

            cv::Mat image(cv::Size(640, 480), CV_8UC3);

            // Generate an image where each pixel is a random color

            cv::randu(image, cv::Scalar(0, 0, 0), cv::Scalar(255, 255, 25));

            // Write message to be sent. Member function toImageMsg() converts a CvImage into ROS image message

            msg_ = cv_bridge::CvImage(std_msgs::msg::Header(), "bgr8", image).toImageMsg();

            // Publish the image to the topic defined in the publisher

            publisher_->publish(*msg_.get());
            RCLCPP_INFO(this->get_logger(), "Image %ld published", count_);
            count_++;        
        }

        rclcpp::TimerBase::SharedPtr timer_;
        sensor_msgs::msg::Image::SharedPtr msg_;
        rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher_;
        size_t count_;
};



int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);

    // Create a ROS 2 node

    auto node = std::make_shared<MinimalImagePublisher>();

    // Process ROS 2 callbacks until receiveing a SIGINT (ctrl-c)

    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}