from rovecomm_module.rovecomm import get_manifest
import sys
from enum import IntEnum
import neopixel
import board
import time
from PIL import Image

class State(IntEnum):
    TELEOP = 0
    AUTONOMY = 1
    REACHED_GOAL = 2
    NONE = 3

class LightingMode(IntEnum):
    NONE = 0
    STATE = 1
    PATTERN = 2
    RGB = 3

this = sys.modules[__name__]

# The PWM pin used to control the NeoPixels
this.pixel_pin = board.D18
 
# The number of NeoPixels
this.num_pixels = 256

# Set up our neopixel array
this.pixels = neopixel.NeoPixel(this.pixel_pin, this.num_pixels, brightness=0.05, auto_write=False)

# Delay for flashing reached marker
this.flash_delay = 0.5

# Our default lighting mode
this.lighting_mode = LightingMode.STATE

# Our default state display
this.state = State.TELEOP

# Our default RGB colors
this.rgb = (0,0,0)

this.image_id = None

this.manifest = get_manifest()

this.images = {
    0 : "/home/pi/Multimedia_Software/images/block.png",
    1 : "/home/pi/Multimedia_Software/images/belgium.png",
    2 : "/home/pi/Multimedia_Software/images/logo.png",
    3 : "/home/pi/Multimedia_Software/images/face.png",
    4 : "/home/pi/Multimedia_Software/images/circle_us.png"
}

def clear_lights():
    """
    Turns off all the LEDS
    """
    this.pixels.fill((0, 0, 0))
    this.pixels.show()

def handle_lighting_commands(packet):
    """
    Used to handle incoming lighting commands and set the appropriate mode
    """
    # Raise error if the packet has no data
    if packet == None:
        raise TypeError

    if packet.data_id == this.manifest["Multimedia"]["Commands"]["StateDisplay"]["dataId"]:
        this.state = packet.data[0]
        this.lighting_mode = LightingMode.STATE
    elif packet.data_id == this.manifest["Multimedia"]["Commands"]["LEDPatterns"]["dataId"]:
        this.image_id = packet.data[0]
        this.lighting_mode = LightingMode.PATTERN
    elif packet.data_id == this.manifest["Multimedia"]["Commands"]["LEDRGB"]["dataId"]:
        this.rgb = packet.data
        this.lighting_mode = LightingMode.RGB

def draw_image():
    im = Image.open(this.images[this.image_id])

    if im.size != (16,16):
        raise TypeError("Needs to be 16x16 image")

    im.load() # required for png.split()
    
    # Create a black image mask, and put non alpha pixels from image ontop
    # For neopixels, black is functionally "off"
    rgb_im = Image.new("RGB", im.size, (0, 0, 0))
    rgb_im.paste(im, mask=im.split()[3]) # 3 is the alpha channel

    for x in range(16):
        for y in range(16):
            # As the array operates in a snake pattern we have to 
            # switch directions every other row
            if x % 2 != 0:
                y_val = 15 - y
            else:
                y_val = y
            r, g, b = rgb_im.getpixel((x, y))
            this.pixels[x*16+y_val] = (r,g,b)
    this.pixels.show()
    
def display_rgb():
    """
    Fills the pixel matrix with the desired color
    """
    print("Displaying rgb")
    this.pixels.fill((this.rgb[0], this.rgb[1], this.rgb[2]))
    this.pixels.show()

def display_state():
    """
    Writes a color to the LED panel to indicate a rover state
    """
    if this.state == State.TELEOP:
        # Write BLUE to indicate teleop
        this.pixels.fill((0, 0, 255))
        this.pixels.show()
    elif this.state == State.AUTONOMY:
        # Write RED to indicate autonomy
        this.pixels.fill((255, 0, 0))
        this.pixels.show()
    elif this.state == State.REACHED_GOAL:
        # Flash Green to indicate reached goal
        this.pixels.fill((0, 255, 0))
        this.pixels.show()
        time.sleep(this.flash_delay)
        this.pixels.fill((0, 0, 0))
        this.pixels.show()
        time.sleep(this.flash_delay)
    else:
        # Default to showing no color
        this.pixels.fill((0, 0, 0))
        this.pixels.show()

def run_lighting():
    """
    Updates the lighting panel based on the current lighting mode and values
    """

    if this.lighting_mode == LightingMode.STATE:
        #print("State")
        display_state()
    elif this.lighting_mode == LightingMode.PATTERN:
        draw_image()
    elif this.lighting_mode == LightingMode.RGB:
        display_rgb()
    else:
        clear_lights()
    
