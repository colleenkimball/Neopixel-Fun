# CircuitPython demo - NeoPixel RGBW

import time
import board
import neopixel

pixel_pin = board.A1
num_pixels = 16

pixels = neopixel.NeoPixel(pixel_pin, num_pixels, brightness=0.3, auto_write=False)


def wheel(pos):
    # Input a value 0 to 255 to get a color value.
    # The colours are a transition r - g - b - back to r.
    if pos < 0 or pos > 255:
        return (0, 0, 0)
    if pos < 85:
        return (255 - pos * 3, pos * 3, 0)
    if pos < 170:
        pos -= 85
        return (0, 255 - pos * 3, pos * 3)
    pos -= 170
    return (pos * 3, 0, 255 - pos * 3)

def color_chase(color, wait):
    for i in range(num_pixels):
        pixels[i] = color
        time.sleep(wait)
        pixels.show()
    time.sleep(0.5)


def colorWipe(color):
    for i in range(0, num_pixels):
        lightUp(i, color)


def rainbowFunc(wait):
    for i in range(0, 256):
        for j in range(0, num_pixels):
            idx = i+j
            pixels[j] = wheel(idx & 255)

    pixels.show()
    time.sleep(wait)


def rainbow_cycle(wait):
    for j in range(255):
        for i in range(num_pixels):
            rc_index = (i * 256 // num_pixels) + j
            pixels[i] = wheel(rc_index & 255)
        pixels.show()
        time.sleep(wait)


def everyOther(color1, color2):
    sleep = 0.5
    for i in range(num_pixels, -1, -2):
        lightUp(i, color1)
        time.sleep(sleep)
        lightUp(i+1, color2)
        time.sleep(sleep)


def openCloseLights(color1, color2):
    for j in range(0, num_pixels):
        lightUp(j, color1)
        time.sleep(0.5)

    for j in range(num_pixels, -1, -1):
        lightUp(j, color2)
        time.sleep(0.5)


def blinkLights():
    for i in range(0, 7):
        color = rainbow[i]

        sleep = 0.5
        for j in range(0, num_pixels):
            pixels.clear()
            time.sleep(sleep)
            lightUp(j, color)

    for i in range(0, 49):
        color = rainbow[i % 7]
        pixels.clear()
        pixels.show()
        time.sleep(sleep)
        for j in range(0, num_pixels):
            lightUp(j, color)

    time.sleep(sleep)


def rainbowLights():
    for i in range(0, num_pixels + 7, 7):
        lightUp(i, RED)
        lightUp(i+1, ORANGE)
        lightUp(i+2, YELLOW)
        lightUp(i+3, GREEN)
        lightUp(i+4, BLUE)
        lightUp(i+5, INDIGO)
        lightUp(i+6, VIOLET)


def lightUp(charIndex, color):
    pixels[charIndex]=color
    pixels.show()
    time.sleep(0.1)

RED=(255, 0, 0)
ORANGE=(255, 127, 0)
YELLOW=(255, 255, 0)
GREEN=(0, 255, 0)
BLUE=(0, 0, 255)
INDIGO=(75, 0, 130)
VIOLET=(148, 0, 211)
MAGENTA=(255, 0, 255)
WHITE=(0, 0, 0)

rainbow=[RED, ORANGE, YELLOW, GREEN, BLUE, INDIGO, VIOLET]

while True:
    pixels.fill(RED)
    pixels.show()
    for i in range(0, num_pixels):
        lightUp(i, INDIGO)

    everyOther(RED, BLUE)

    everyOther(YELLOW, GREEN)

    everyOther(GREEN, BLUE)

    everyOther(BLUE, YELLOW)
    
    everyOther(INDIGO, RED)

    everyOther(VIOLET, GREEN)

    openCloseLights(RED, BLUE)

    openCloseLights(YELLOW, GREEN)

    openCloseLights(INDIGO, RED)

    openCloseLights(GREEN, BLUE)

    openCloseLights(RED, YELLOW)

    openCloseLights(BLUE, YELLOW)

    openCloseLights(VIOLET, GREEN)

    blinkLights()

    colorWipe(RED) # Red
    colorWipe(GREEN) # Green
    colorWipe(BLUE) # Blue

    rainbowFunc(0.5)
    rainbowCycle(0.5)