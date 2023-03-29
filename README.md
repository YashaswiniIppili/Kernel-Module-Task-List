# Kernel-Module-Task-List
This is a Linux kernel module that lists all current tasks in the system starting from the init task. </br>
The output is displayed in a tree structure that includes the name of the task, its state, and process ID. </br>

## Building & Installing : 
To build and install the module, run the following commands : </br>
make </br>
sudo insmod tasklist.ko </br>

## Running the module : 
sudo insmod task_module.ko  </br>
lsmod | grep task_module  </br>
sudo dmesg  </br>

## Uninstalling the module : 
sudo rmmod tasklist

