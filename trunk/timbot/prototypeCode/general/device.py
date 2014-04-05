# The device class stores information about the robot and references to important components


class device:

    #############
    ## Constants
    ##

    # In the standby mode the device will ignore all manual or autonomous movement commands.
    MODE_STANDBY = 0

    # While under manual control, the device receives movement commands via a network connection
    MODE_MANUAL = 1

    # While in autonomous mode the device will make decisions about what movements it should make
    MODE_AUTONOMOUS = 2

    # device id constants
    DEVICE_ID_ALL = 0        # Data is meant for all robots (Not the console)
    DEVICE_ID_CONSOLE = 1    # Data is meant for the command console
    DEVICE_ID_FEL = 2       # Data is meant for the Front End Loader (old robot)

    # Human readable names for each of the robots
    DEVICE_NAMES = []
    DEVICE_NAMES.insert(DEVICE_ID_ALL, "Robots")
    DEVICE_NAMES.insert(DEVICE_ID_FEL, "FEL")



    def __init__(self, deviceId):
        # List of sensor components opened by this program
        self._sensors = {}

        # List of actuators opened by this program
        self._actuators = {}

        # Initialize the robot in standby mode
        self.deviceMode = self.MODE_STANDBY

        self.deviceId = deviceId

        self.netManager = None

        return

    ##
    # getSensor
    #
    # Description: gets a sensor from list of opened sensors, has the ability to provide a "fake" simulation sensor
    #       instead of the real thing if we tell it to
    #
    # Parameters:
    #   sensorId - unique identifier of the sensor
    #
    # Return: the sensor object that we will be getting data from
    #
    def getSensor(self, sensorId):

        # TODO: determine how to id sensors, add constants for each sensor
        # TODO: determine how to indicate if a sensor or a "fake" should be returned

        return self._sensors[sensorId]

    ##
    # getActuator
    #
    # Description: gets an actuator from list of opened actuators, has the ability to provide a "fake" simulation
    #       actuators instead of the real thing if we tell it to
    #
    # Parameters:
    #   actuatorId - unique identifier of the actuators
    #
    # Return: the actuator object that we will be getting data from
    #
    def getActuator(self, actuatorId):

        # TODO: determine how to id actuators, add constants for each actuator
        # TODO: determine how to indicate if a actuator or a "fake" should be returned

        return self._sensors[actuatorId]

    ##
    # addSensor
    #
    # Description: adds a sensor to the list of opened sensors
    #
    # Parameters:
    #   sensorId - unique identifier of the actuators
    #   obj - the actuator controller object to add
    #
    def addSensor(self, sensorId, obj):
        self._sensors[sensorId] = obj

    ##
    # addActuator
    #
    # Description: adds an actuator to the list of opened actuators
    #
    # Parameters:
    #   actuatorId - unique identifier of the actuators
    #   obj - the actuator controller object to add
    #
    def addActuator(self, actuatorId, obj):
        self._actuators[actuatorId] = obj


# test = {}
# test["motors"] = 1
