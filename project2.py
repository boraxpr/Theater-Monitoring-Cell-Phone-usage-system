import pyfiglet
from termcolor import cprint
import serial
//Establish serial connection
ser = serial.Serial('/dev/ttyUSB1', 115200, timeout=1)
//Flush junk out
ser.flush()
print("Serial connection success")
//Keep latest_lighted_seats in memory
lastest_lighted_seats = 0
//Test figlet text
cprint(pyfiglet.figlet_format("Best Experience"), "blue")

while True:
// If there is some message in serial
    if ser.in_waiting > 0:
// readline from serial
// decode to get rid of tags like /n (newline)
// rstrip() to get rid of spaces
        line = ser.readline().decode('unicode_escape').rstrip()
// print message received from serial and its type 
        print("Line: "+str(line)+" "+str(type(line)))
// since it will be only "0" or "1" that is important message (Other than WiFi connecting message or other debug code)
// in future implementation, improve can be done with if( line in range(MAX_SEAT_IN_THEATER) ) for more LDR sensors
        if (line == "0" or line == "1"):
            print("int string detected")
// cast to int
            lighted_seats = int(line)
// if the number of seat is changed
            if (lastest_lighted_seats != lighted_seats):
// if the number of seat is changed then forget the old one and replace with the current (Make it ready for the next iteration)
                latest_lighted_seats = lighted_seats
// For futher implementation if (lighted_seats in range(1, MAX_SEAT_IN_THEATER, 1)
                if (lighted_seats > 0):
                    cprint(pyfiglet.figlet_format(str(lighted_seats)), "red")
                else: #no seat is playing mobile phone in the theater
                    cprint(pyfiglet.figlet_format("Best Experience"), "blue")
