
#Give permision for the computer to use the animatics smart motors via usb
sudo chmod 777 /dev/ttyUSB0
#Give permision for the computer to use the arduino via usb
sudo chmod 777 /dev/ttyACM0

#run the E-Week Demo
python ~/svn/timbot/trunk/timbot/Demos/E-Week/Robot/main.py

