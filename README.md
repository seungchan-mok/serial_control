# ros-simple-control-with-arduino
ros package for simple motor control for DC motor and Servo motor

## Installation
---
### dependency installation

```
pip install pyserial
```
See pyserial [website](https://pythonhosted.org/pyserial/pyserial.html#installation)

### Package Installation

```
cd <Your Work Space/src>
git clone https://github.com/msc9533/ros-simple-control-with-arduino.git
cd .. && catkin_make
```

### Arduino Upload

Open `arduino-uno.ino` by Arduino IDE, and Upload to Arduino

#### Motor Circuit



## Usage

### Control by `cmd_vel` Topic

`serial_control.py` node subscribe `cmd_vel` topic, and transfer data to Uno by serial.

```
rosrun serial_control serial_control.py
```

### Publish `cmd_vel` by using keyboard

```
rosrun serial_control teleop.py
```

        W
    A   S   D
        X

Control your DC motor and servo motor by keyboard  
W : vel + 10  
A, D : pos - 5, +5  
S : Stop  
X : vel - 10  