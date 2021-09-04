#!/bin/bash
# else example
if [ $# -eq 1 ]
then
	nl $1
else
	nl /dev/stdin
fi
