# Rover Space Makers

<p align="center">
  <img src="https://github.com/fectec/RoverSpaceMakers/assets/127822858/fbe39ed3-3b11-4ee0-9bde-d4fdea8a9cb7" alt = "Space Makers Logo" width = "300" height = "300"/>
</p>

*ROS 2* navigation system for **autonomous rover**. The exploration vehicle is in development for *CIRC* (Canadian International Rover Challenge) *2024*, as part of the activities of the student group *Space Makers*. The competition's objective is to design, build, and operate a rover that can navigate and complete tasks on a simulated Martian surface alongside human settlement. 

## Aruco markers & GPS localization

In the first task, a crashed lander has scattered crates of supplies nearby, and the rover must survey the area and identify the crates that can be salvaged. Some of the crates have working GPS transponders that indicate their locations. They will also be marked with an *Aruco* marker.

Thus, a system was created to correctly identify the marker using *OpenCV*. The Aruco scanning and detection software is running in the background and automatically displays the correct result when the Aruco marker comes within range and frame of the camera. 

In addition, a program was developed that obtains the current coordinates of the rover and, based on the coordinates of the crates, plans the movement of the vehicle so that it can obtain them. 
