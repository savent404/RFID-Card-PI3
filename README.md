# USB RFID reader
## how to use
    mkdir obj
    makefile
    sudo /home/pi/Documents/RFID-Card-PI3/obj/Login_System -config /home/pi/Documents/RFID-Card-PI3/cfg/config
## another para
* Balcklist
* Output info to /home/pi/Documents/out
* Show in cfg/config
## useful func

search USB device

    cat /proc/bus/input/devices


auto startup as Deamon

    add "sudo /home/pi/Documents/RFID-Card-PI3/obj/Login_System -config /home/pi/Documents/RFID-Card-PI3/cfg/config" to /etc/rc.loacl

## Hook函数说明
 为实现功能的快速补充 主要操作以hook形式的例程给出

    type hook(arg) {
        //example hook
        return (static) example_hook(arg);

        //usr define hook
        return (extern) usr_hook(arg);
    }
在hook.c文件中用户可根据Example函数的具体实现方法对功能进行补充和更改

* usr_login_hook(int fd_out);

 当程序以守护函数形式运行初，可向文档输出登陆时间以及用户自定义的信息
arg fd_out 文档的文件符号

* usr_config_hook(int argc, char* argv[]);

 例程usr_config中根据变量'-config ConfigFilePath'配置信息到（struct config) config_info
用户可在struct config 结构体中添加更多的配置信息并在usr_config_hook中实现

* usr_permision_hook(char* pt);

 检查用户ID的登陆权限,例程中是查询黑名单文件，若不在黑名单中则认为可以开门

 * usr_IO_open_hook(int fd_out);

 调用GPIO内核实现开门，输出信息到文件：fd_out