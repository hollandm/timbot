

##
# logger
#
# Description: logs data and events from robotic operation so that human operators can determine why things exploded
#
class logger:

    def __init__(self):
        # TODO: Open a log file with the date and current time in the title
        return

    ##
    # logMessage
    #
    # Description: prints a message to the log
    #
    # Parameters:
    #   message: the message to log
    #
    def logMessage(self, message):
        # TODO: write a message to the log file
        return

    ##
    # logFile
    #
    # Description: dumps a large portion of data to a separate file to avoid cluttering the main log.
    #       places a message in the main log to indicate that this occurred and what were the file was saved
    #
    # Parameters:
    #   path - the path to the file
    #   data - the data that you want to save to the file
    #
    def logFile(self, path, data):
        # For dumping a bunch of data into a log without cluttering up the main log
        # TODO: save data into a new file
        # TODO: place a note and path to the new file in the main log
        return

    ##
    # logImage
    #
    # Description: dumps an image to a separate file. Places a message in the main log to indicate that
    #       this occurred and what were the file was saved
    #
    # Parameters:
    #   path - the path to the file
    #   data - the data that you want to save to the file
    #
    def logImage(self, path, img):
        # TODO: save an image (probably with openCV) to a new file
        # TODO: place a note and path to the new file in the main log
        return

    ##
    # closeLog
    #
    # Description: Closes the main log file
    #
    def closeLog(self):
        # TODO: close the log file
        return