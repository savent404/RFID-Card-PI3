#!/bin/bash

OUTPUT_PIN=4
GPIO_OUT=gpio4
INPUT_PIN=5
GPIO_IN=gpio5

start () {
	echo $OUTPUT_PIN > /sys/class/gpio/export
	echo $INPUT_PIN  > /sys/class/gpio/export
	echo out        > /sys/class/gpio/$GPIO_OUT/direction
	echo 1          > /sys/class/gpio/$GPIO_OUT/value
	return 0
}

stop () {
	echo $OUTPUT_PIN > /sys/class/gpio/unexport
	echo $INPUT_PIN  > /sys/class/gpio/unexport
	return 0
}

out1 () {
	echo 1          > /sys/class/gpio/$GPIO_OUT/value
	return 0
}

out0 () {
	echo 0          > /sys/class/gpio/$GPIO_OUT/value
}

read () {
	echo /sys/class/gpio/$GPIO_IN/value
	return /sys/class/gpio/$GPIO_IN/value
}

open () {
	out0
	sleep 1
	out1
	return 0
}