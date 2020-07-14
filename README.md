# memory_usage_monitor
# 1 Function
The tool is for sampling a task memory usage, and converting the usage to a .svg diagram. The tool consists of two part, one is for sampling memory usage on the target board, and the sampling data will be saved on a file, and the other one is to convert the sampling log to a .svg diagram on host machine.  

And the sampling log format is as following  
```
PROC_COMM
Sample Begin time stamp:1568267862
Sample interval time:5 Sec

VmPeak:	 2498864 kB
VmSize:	 2383636 kB
VmLck:	      32 kB
VmPin:	       0 kB
VmHWM:	  381652 kB
VmRSS:	  237224 kB
VmData:	 1439372 kB
VmStk:	     136 kB
VmExe:	   93900 kB
VmLib:	   62896 kB
VmPTE:	    2448 kB
VmSwap:	   23620 kB
VmPeak:	 2498864 kB
VmSize:	 2383636 kB
VmLck:	      32 kB
VmPin:	       0 kB
VmHWM:	  381652 kB
VmRSS:	  237224 kB
VmData:	 1439372 kB
VmStk:	     136 kB  
VmExe:	   93900 kB  
VmLib:	   62896 kB  
VmPTE:	    2448 kB  
VmSwap:	   23620 kB
```

# 2 How to use memory_usage_monitor  
on host  
```
$ cd memory_usage_monitor  
$ make clean;make CC=your_toolchain
```
On board  

``` $ ./memusage -p PID -c COUNT -i INTERVAL ```  
The PID is the pid of a task which need to be monitored  
The COUNT is total sampling times  
The INTERVAL is the sampling interval time  
After the command, there is a "status.log" in the current directory.  

On Host  
Please copy that "status.log" to host.  
```$ ./memusage.py status.log  ```  
After the command, a "memory_usage.svg" will be created, please
open the file with a browser, such as Chrome, Firefox.  

# 3 Note
Because the memusage.py depends on pygal module, so please install the module first.  
# 4 How to install pygal on Ubuntu14.04
$ sudo apt-get install python-pip  
$ sudo pip install pygal_maps_world  
