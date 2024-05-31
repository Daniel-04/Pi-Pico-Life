# Conway's Game of Life in the Pi Pico
A small .ino sketch that outputs life to an I2C oled display.

## Setup
This uses the Adafruit SSD1306 library.

The pi pico and the oled are connected as shown:
```
┌╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶┐            
╎                          ╎            
╎ ┌╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶╶┐ ╎            
╎ ╎ ┌───────────┐        ╎ ╎            
╎ └╶│VBUS       │        ╎ ╎            
╎   │        GP4│╶╶╶╶╶╶╶╶┼╶┼╶╶╶┐        
└╶╶╶│GND     GP5│╶╶╶╶╶╶╶╶┼╶┼╶┐ ╎        
    │           │        ╎ ╎ ╎ ╎        
    │     P     │        ╎ ╎ ╎ ╎        
    │     i     │        ╎ ╎ ╎ ╎        
    │           │        V G S S        
    │     P     │   ┌────C─N─C─D─────┐  
    │     i     │   │    C D L A     │  
    │     c     │   │                │  
    │     o     │   │    I2C oled    │  
    │           │   │                │  
    │           │   │                │  
    │           │   └────────────────┘  
    └───────────┘                       
```
