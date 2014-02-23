import pygame
from pygame.locals import *

import socket
import time

class control:

    # if the joystick value is +/- this value from 50 then ignore the value
    JOYSTICK_PERCENT_IGNORE = 5

    JOYSTICK_DISPLAY_HEIGHT = 250
    JOYSTICK_DISPLAY_WIDTH = 120

    BUTTON_DISPLAY_WIDTH = 60
    BUTTON_DISPLAY_HEIGHT = 20

    COLOR_OUTLINE = (190, 190, 190)
    COLOR_DISPLAY = (200, 0, 200)
    COLOR_DISPLAY_TEXT = (255, 255, 255)
    COLOR_BACKGROUND_TEXT = (0, 0, 0)

    UDP_IP = "224.0.0.1"
    #Use this one for testing on the normal wireless network
    #UDP_IP = "127.0.0.1"
    UDP_PORT = 6000

    ## __init__
    #
    # Description: Initialize the application, set up the screen, joysticks, and network
    #
    def __init__(self):
        pygame.init()

        pygame.display.set_caption("Robotics Control")

        self.left_joystick = None
        self.right_joystick = None
        self.dualJoysticks = False
        self.initJoysticks()


        self.screen = pygame.display.set_mode((500, 300))
        self.font = pygame.font.SysFont("Comic Sans MS", 15)

        print "UDP target IP:", self.UDP_IP
        print "UDP target port:", self.UDP_PORT

        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)    # UDP

        self.joyData = bytearray(7)

    def initJoysticks(self):
        pygame.joystick.init()

        numSticks = pygame.joystick.get_count()

        if numSticks == 2:
            self.dualJoysticks = True
            print "Using Dual Joysticks"


            self.left_joystick = pygame.joystick.Joystick(0)
            self.right_joystick = pygame.joystick.Joystick(1)

            self.left_joystick.init()
            self.right_joystick.init()

        elif numSticks == 1:
            print "Using 360 Gamepad"

            self.left_joystick = pygame.joystick.Joystick(0)
            self.left_joystick.init()

        else:
            print "This program requires either two Logitech Attack 3 Joysticks or a single Xbox 360 controller"
            print "Neither of these where found. Program will terminate.\n"

            print "Number of devices found: " + str(numSticks)
            for i in range(0, numSticks):
                print "\tDevice " + str(i) + pygame.joystick.Joystick(i).get_name()

            pygame.joystick.quit()
            exit()

    def run(self):
        while True:
            self.g_keys = pygame.event.get()

            self.screen.fill(0)
            for event in self.g_keys:
                if event.type == KEYDOWN and event.key == K_ESCAPE:
                    self.quit()
                    return

                elif event.type == QUIT:
                    self.quit()
                    return


            self.loadJoystickData()
            self.drawGUI()

            self.sendData()


    def quit(self):
        pygame.display.quit()
        self.left_joystick.quit()
        if self.dualJoysticks:
            self.right_joystick.quit()
        pygame.joystick.quit()


    def sendData(self):
        #shouldSend = True
        #if self.joyData[0] > 50 + self.JOYSTICK_PERCENT_IGNORE or self.joyData[0] < 50 - self.JOYSTICK_PERCENT_IGNORE:
        #    shouldSend = True
        #if self.joyData[1] > 50 + self.JOYSTICK_PERCENT_IGNORE or self.joyData[1] < 50 - self.JOYSTICK_PERCENT_IGNORE:
        #    shouldSend = True
        #if self.joyData[2] > 50 + self.JOYSTICK_PERCENT_IGNORE or self.joyData[2] < 50 - self.JOYSTICK_PERCENT_IGNORE:
        #    shouldSend = True
        #if self.joyData[3] > 50 + self.JOYSTICK_PERCENT_IGNORE or self.joyData[3] < 50 - self.JOYSTICK_PERCENT_IGNORE:
        #    shouldSend = True



        #if shouldSend:
        self.sock.sendto(self.joyData, (self.UDP_IP, self.UDP_PORT))
        time.sleep(0.01)


    def loadJoystickData(self):

        def joyFormat(unformated):
            formated = int(unformated*50)
            if abs(formated) < self.JOYSTICK_PERCENT_IGNORE:
                return 50
            else:
                return formated+50

        if self.dualJoysticks:
            # it is annoying to have to physically swap around the joysticks
            # lets just have a button on each joystick which we press to make that joystick the right
            if self.left_joystick.get_button(4) == 1:
                print "Swapped Joysticks"
                temp = self.right_joystick
                self.right_joystick = self.left_joystick
                self.left_joystick = temp

            #speedMod = self.left_joystick.get_axis(3)/2 + 0.5
            #print speedMod

            #digMode = self.joyData[4] * self.joyData[5] == 255

            self.joyData[0] = joyFormat(self.left_joystick.get_axis(1))
            self.joyData[1] = joyFormat(self.left_joystick.get_axis(0))
            self.joyData[2] = joyFormat(self.right_joystick.get_axis(1))
            self.joyData[3] = joyFormat(self.right_joystick.get_axis(0))

            # Triggers
            self.joyData[4] = self.left_joystick.get_button(0)*255
            self.joyData[5] = self.right_joystick.get_button(0)*255

            # Reset
            self.joyData[6] = max(self.left_joystick.get_button(3), self.right_joystick.get_button(3))*255
            if self.joyData[6] > 0:
                print "Reseting Motors"


        else:
            # 360 Controller

            self.joyData[0] = joyFormat(self.left_joystick.get_axis(1))
            self.joyData[1] = joyFormat(self.left_joystick.get_axis(0))
            self.joyData[2] = joyFormat(self.left_joystick.get_axis(3))
            self.joyData[3] = joyFormat(self.left_joystick.get_axis(2))
            self.joyData[4] = self.left_joystick.get_button(4)*255
            self.joyData[5] = self.left_joystick.get_button(5)*255
            self.joyData[6] = self.left_joystick.get_button(0)*255


    def drawGUI(self):

        #Fill background
        background = pygame.Surface(self.screen.get_size())
        background = background.convert()
        background.fill((255, 255, 255))

        self.drawJoystick(background, (10, 10), self.joyData[0])
        self.drawJoystick(background, (370, 10), self.joyData[2])


        # Left Trigger
        label = self.font.render("Left Trigger", 1, self.COLOR_BACKGROUND_TEXT)
        background.blit(label, (10, 25+self.JOYSTICK_DISPLAY_HEIGHT))
        self.drawButton(background, (70, 20+self.JOYSTICK_DISPLAY_HEIGHT), self.joyData[4] == 255)

        # Right Trigger
        label = self.font.render("Right Trigger", 1, self.COLOR_BACKGROUND_TEXT)
        background.blit(label, (365, 25+self.JOYSTICK_DISPLAY_HEIGHT))
        self.drawButton(background, (430, 20+self.JOYSTICK_DISPLAY_HEIGHT), self.joyData[5] == 255)

        # That handy button which sends the ZS command to the motors so that they reset after an over voltage
        label = self.font.render("Reset Motors", 1, self.COLOR_BACKGROUND_TEXT)
        background.blit(label, (170, 25))
        self.drawButton(background, (240, 20), self.joyData[6] == 255)


        # Blit everything to the screen
        self.screen.blit(background, (0, 0))
        pygame.display.flip()

        return


    def drawJoystick(self, background, origin, joyValue):

        value = joyValue-50

        outline = pygame.Surface((self.JOYSTICK_DISPLAY_WIDTH, self.JOYSTICK_DISPLAY_HEIGHT))
        outline = outline.convert()
        outline.fill(self.COLOR_OUTLINE)

        displayBarWidth = self.JOYSTICK_DISPLAY_WIDTH - 10

        displayCenter = self.JOYSTICK_DISPLAY_HEIGHT/2

        displayBarTop = displayCenter - 7
        displayBarBottom = displayCenter + 7

        if value > 0:
            displayBarBottom = round(displayCenter + self.JOYSTICK_DISPLAY_HEIGHT * value / 105)
            #print displayBarBottom

        elif value < 0:
            displayBarTop = round(displayCenter + self.JOYSTICK_DISPLAY_HEIGHT * value / 105)
            #print displayBarTop

        displayBarHeight = displayBarBottom - displayBarTop

        displayBar = pygame.Surface((displayBarWidth, displayBarHeight))
        displayBar = displayBar.convert()
        displayBar.fill(self.COLOR_DISPLAY)

        label = self.font.render(str(int(joyValue)), 1, self.COLOR_DISPLAY_TEXT)

        if value > 0:
            displayBar.blit(label, (2, displayBarHeight - 14))
        else:
            displayBar.blit(label, (2, 2))


        outline.blit(displayBar, (5, displayBarTop))
        background.blit(outline, origin)

    def drawButton(self, background, origin, pressed):

        radius = self.BUTTON_DISPLAY_HEIGHT/2

        outline = pygame.Surface((self.BUTTON_DISPLAY_WIDTH-2*radius, self.BUTTON_DISPLAY_HEIGHT))
        outline = outline.convert()
        outline.fill(self.COLOR_OUTLINE)

        background.blit(outline, (origin[0]+radius, origin[1]))

        pygame.draw.circle(background, self.COLOR_OUTLINE, (origin[0]+radius, origin[1]+radius), radius, 0)
        pygame.draw.circle(background, self.COLOR_OUTLINE, (origin[0] + self.BUTTON_DISPLAY_WIDTH-radius,
                                                            origin[1]+radius), radius, 0)
        if pressed:
            radiusMod = 3
            radius = radius - radiusMod

            display = pygame.Surface((self.BUTTON_DISPLAY_WIDTH-2*radius-radiusMod*2,
                                      self.BUTTON_DISPLAY_HEIGHT - radiusMod*2))
            display = display.convert()
            display.fill(self.COLOR_DISPLAY)

            background.blit(display, (origin[0]+radius+radiusMod, origin[1]+radiusMod))

            pygame.draw.circle(background, self.COLOR_DISPLAY, (origin[0]+radius+2*radiusMod - radiusMod,
                                                                origin[1]+radius + radiusMod), radius, 0)

            pygame.draw.circle(background, self.COLOR_DISPLAY, (origin[0] + self.BUTTON_DISPLAY_WIDTH-radius - radiusMod,
                                                                origin[1]+radius + radiusMod), radius, 0)


a = control()
a.run()