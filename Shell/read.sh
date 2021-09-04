#!/bin/bash
echo "Enter Your Name"
read name
echo "Welcome $name to ReadWorld"

echo -n "Type something and press enter: ";
read;
echo You typed ${REPLY}

echo -n "Type something and hit space: ";
read '-d ' result;
echo "";
echo "You typed ${result}"


read -p 'Please Enter Value: ' value;
echo "";
echo "You typed ${value}"

read -s -p 'Please Enter Secret Value: ' secret;
echo "";
echo "You typed ${secret}"

read -p "Multiple value: "  val1 val2 val3
echo "You typed val1=$val1 val2=$val2 val3=$val3"

