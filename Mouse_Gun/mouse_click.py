import win32api
import time
import serial

state_left = win32api.GetKeyState(0x01)  # Left button down
state_right = win32api.GetKeyState(0x02)  # Right button down
ser = serial.Serial('COM4', 9600, timeout=.1)

while True:
    a = win32api.GetKeyState(0x01)
    #b = win32api.GetKeyState(0x02)

    if a != state_left:  # Button state changed
        state_left = a
        while a < 0:
            print('Left Button Pressed')
            a = win32api.GetKeyState(0x01)
            ser.write(bytes("1", 'utf-8'))
            time.sleep(0.1)
    #else:
    #    ser.write(bytes("2", 'utf-8'))
    #    time.sleep(0.01)
            

            
