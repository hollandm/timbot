# The device class stores information about the robot and references to important components

class device:

    #############
    ## Constants
    ##

    # In the standbye mode the device will ignore all manual or autonomous movement commands.
    MODE_STANDBYE = 0

    # While under manual control, the device receives movement commands via a network connection
    MODE_MANUAL_CONTROL = 1

    # While in autonomous mode the device will make decisions about what movements it should make
    MODE_AUTONOMOUS = 2

    # device id constants
    DEVICE_ID_ALL = 0        # Data is meant for all robots (Not the console)
    DEVICE_ID_CONSOLE = 1    # Data is meant for the command console
    DEVICE_ID_FEL = 2       # Data is meant for the Front End Loader (old robot)

    DEVICE_NAMES = []
    DEVICE_NAMES.insert(DEVICE_ID_ALL, "Robots")
    DEVICE_NAMES.insert(DEVICE_ID_FEL, "FEL")


    def __init__(self, deviceId):
        # Initialize the robot in standbye mode
        self.deviceMode = self.MODE_STANDBYE

        self.deviceId = deviceId


        self.netManager = None


        return

