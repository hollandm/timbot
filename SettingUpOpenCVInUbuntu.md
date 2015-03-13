Last year I had to install this stuff way to many times. This year I'm going to document things.

**Step 1: Install OpenCV.**

I found a number of download scripts and such that did not work. The one that ended up working for me was at http://opencvstart.blogspot.com/2012/12/install-opencv-in-ubuntu-1204.html. This script installed all the prerequisites for compiling and installing OpenCV and then precoded to download the source, build it, and then install it. A copy is within the repository at http://code.google.com/p/timbot/source/browse/trunk/timbot/experiments/opencv-setup/opencv.sh.

**Step 2: Set up Compilation script**

Compiling a program that uses OpenCV requires a lot of extra fluff. I modified a script that I found to compile said programs quickly. The original script can be found here, https://help.ubuntu.com/community/OpenCV. My Version of the script is on the repository at http://code.google.com/p/timbot/source/browse/trunk/timbot/experiments/opencv-setup/compile_opencv.sh.

Usage for this script is:

./compile\_opencv.sh file\_name.c
or
./compile\_opencv.sh file\_name.cpp


**Step 3: Run a test program**

Next it would probably be wise to test the installation and make sure everything is working. Test cases for various languages can be found in our repository at http://code.google.com/p/timbot/source/browse/trunk/timbot/experiments/#experiments%2Fopencv-setup%2Flanguage_tests. However, users will have to change the path to the image file referenced.

**Step 4: Have fun**