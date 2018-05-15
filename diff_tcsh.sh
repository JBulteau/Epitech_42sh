#!/bin/bash

if [ "$1" = "env" ]
then
        env="env -i"
        shift
else
        $env = ""
fi

echo "--------------"
echo "-----42sh-----"
echo "--------------"
echo $1 | $env ./42sh; echo $?
echo
echo "--------------"
echo "-----tcsh-----"
echo "--------------"
echo $1 | $env tcsh; echo $?
echo
