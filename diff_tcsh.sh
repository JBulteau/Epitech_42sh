#!/bin/bash

echo "--------------"
echo "-----42sh-----"
echo "--------------"
echo $1 | ./42sh; echo $?
echo
echo "--------------"
echo "-----tcsh-----"
echo "--------------"
echo $1 | tcsh; echo $?
echo
