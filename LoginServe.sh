#!/bin/bash

OUTPUT_PIN=4
GPIO_OUT=gpio4
INPUT_PIN=5
GPIO_IN=gpio5
function start {
	echo $OUTPUT_PIN > /sys/class/gpio/export
	echo $INPUT_PIN  > /sys/class/gpio/export
	echo out         > /sys/class/gpio/$GPIO_OUT/direction
	echo 1           > /sys/class/gpio/$GPIO_OUT/value
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
	out0
	sleep 1
	out1
	ANS='/sys/class/gpio/gpio5/value'
	if [ $ANS ]
	then
	echo "Open OK!"
	else
	echo "Open bad!"
	fi
	date
}
$1