#!/bin/bash
# Simple script to greet the user

echo "Enter your name:"
read -r name
echo "Hello, $name!"

# Using additional bash features
echo "Enter two numbers:"
read -r num1 num2
sum=$((num1 + num2))
echo "The sum is: $sum"
