# USB RFID reader
## how to use
    mkdir obj
    makefile
    sudo /home/pi/Documents/RFID-Card-PI3/obj/Login_System -config /home/pi/Documents/RFID-Card-PI3/cfg/config
## another func
* Balcklist
* Output info to /home/pi/Documents/out
* Show in cfg/config
## useful func
* search USB device

    
    cat /proc/bus/input/devices
* auto startup as Deamon

    
    add "sudo /home/pi/Documents/RFID-Card-PI3/obj/Login_System -config /home/pi/Documents/RFID-Card-PI3/cfg/config" to /etc/rc.loacl