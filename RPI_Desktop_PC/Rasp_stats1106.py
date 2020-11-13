from luma.core.interface.serial import i2c, spi, pcf8574
from luma.core.interface.parallel import bitbang_6800
from luma.core.render import canvas
from luma.oled.device import ssd1306, ssd1309, ssd1325, ssd1331, sh1106, ws0010

import os
import sys
import time
from pathlib import Path
from datetime import datetime
import subprocess

if os.name != 'posix':
     sys.exit('{} platform not supported'.format(os.name))

from demo_opts import get_device
from luma.core.render import canvas
from PIL import Image
from PIL import ImageDraw
from PIL import ImageFont

try:
    import psutil
except ImportError:
    print("The psutil library was not found. Run 'sudo -H pip install psutil' to install it.")
    sys.exit()


# TODO: custom font bitmaps for up/down arrows
# TODO: Load histogram


# rev.1 users set port=0
# substitute spi(device=0, port=0) below if using that interface
# substitute bitbang_6800(RS=7, E=8, PINS=[25,24,23,27]) below if using that interface
serial = i2c(port=1, address=0x3C)

# substitute ssd1331(...) or sh1106(...) below if using that device
device = sh1106(serial)

# with canvas(device) as draw:
#     draw.rectangle(device.bounding_box, outline="white", fill="black")
#     draw.text((30, 40), "Hello World", fill="white")
    
    
#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Copyright (c) 2014-2020 Richard Hull and contributors
# See LICENSE.rst for details.
# PYTHON_ARGCOMPLETE_OK

"""
Display basic system information.

Needs psutil (+ dependencies) installed::

  $ sudo apt-get install python-dev
  $ sudo -H pip install psutil
"""

width = 128
height = 64
# image = Image.new('1', (width, height))

# Get drawing object to draw on image.
# draw = ImageDraw.Draw(image)

# Draw a black filled box to clear the image.
# draw.rectangle((0,0,width,height), outline=0, fill=0)

# Draw some shapes.
# First define some constants to allow easy resizing of shapes.
padding = -2
top = padding
bottom = height-padding
# Move left to right keeping track of the current x position for drawing shapes.
x = 0
font = ImageFont.load_default()
# font = ImageFont.truetype("arial.ttf", 15)
# font = ImageFont.truetype('Roboto-Bold.ttf', size=10)

while True:

    with canvas(device) as draw:
        # Draw a black filled box to clear the image.
#         draw.rectangle((0,0,width,height), outline=0, fill=0)

        # Shell scripts for system monitoring from here : https://unix.stackexchange.com/questions/119126/command-to-display-memory-usage-disk-usage-and-cpu-load
        cmd = "hostname -I | cut -d\' \' -f1"
        IP = subprocess.check_output(cmd, shell = True )
        cmd = "top -bn1 | grep load | awk '{printf \"CPU Load: %.2f\", $(NF-2)}'"
        CPU = subprocess.check_output(cmd, shell = True )
        cmd = "free -m | awk 'NR==2{printf \"Mem:%s/%sMB %.2f%%\", $3,$2,$3*100/$2 }'"
        MemUsage = subprocess.check_output(cmd, shell = True )
        cmd = "df -h | awk '$NF==\"/\"{printf \"Disk: %d/%dGB %s\", $3,$2,$5}'"
        Disk = subprocess.check_output(cmd, shell = True )
        cmd = "vcgencmd measure_temp |cut -f 2 -d '='"
        temp = subprocess.check_output(cmd, shell = True )
    
        draw.text((0, top), "IP: " + str(IP,'utf-8'), font=font, fill=255)
        draw.text((0, top+16), str(CPU,'utf-8') + " " + str(temp,'utf-8') , font=font, fill=255)
        draw.text((0, top+32), str(MemUsage,'utf-8'), font=font, fill=255)
        draw.text((0, top+48), str(Disk,'utf-8'), font=font, fill=255)

        # Display image.
        time.sleep(.1)
