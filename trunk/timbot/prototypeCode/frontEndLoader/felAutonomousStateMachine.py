
##
# felAutonomousStateMachine
#
# Description: State machine to hold autonomous behavior of the robot
#
# TODO: Decide on a method to enable the state machine to access sensors and control motors
# TODO: Should this be it's own thread
#
class felAutonomousStateMachine:

    IDLE_STATE = 0

    def __init__(self):
        self.state = 0

    ##
    # step
    #
    # Description: upon every iteration of the main program loop this will be called and preform some function
    #       Each function should be quick to execute (or utilize threads) so as not to block the main program loop
    #
    def step(self):

        if self.state == self.IDLE_STATE:
            return
        else:
            return

    ##
    # getState
    #
    # Description: returns the current state of the state machine in numeric form
    #
    def getState(self):
        return self.state