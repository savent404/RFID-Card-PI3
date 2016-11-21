#!/bin/bash

OUTPUT_PIN=27
GPIO_OUT=gpio27
INPUT_PIN=22
GPIO_IN=gpio22
function start {
	echo $OUTPUT_PIN > /sys/class/gpio/export
	echo $INPUT_PIN  > /sys/class/gpio/export
	echo out         > /sys/class/gpio/$GPIO_OUT/direction
	echo "Serve start ok."
}

function stop {
	echo $OUTPUT_PIN > /sys/class/gpio/unexport
	echo $INPUT_PIN  > /sys/class/gpio/unexport
	echo "Serve stopped"
}

function out1 {
	echo 1           > /sys/class/gpio/$GPIO_OUT/value
}

function out0 {
	echo 0           > /sys/class/gpio/$GPIO_OUT/value
}

function read {
	cat               /sys/class/gpio/$GPIO_IN/value
}

function open {
	out1
	sleep 1
	out0
}
function check {
	ans=$(cat /sys/class/gpio/$GPIO_IN/value)
	if [ $ans = 0 ];then
	echo Open OK!
	else
	echo Not Open!
	fi
}
$1
