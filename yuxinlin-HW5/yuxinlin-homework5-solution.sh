#!/bin/bash
#SBATCH -J yuxinlin-homework5               #Job name
#SBATCH -n 1                                #Number of tasks
#SBATCH -e error.%j                         #Error File
#SBATCH -o output.%j                        #Output File
#SBATCH -t 00:50:00                         #Maximim execution time

#Gather the hostname
hostname

#Gather uptime information
uptime

#Gather disk space usage
df -h

#Gather the number of entries in /etc directory
etc_entries=$(ls /etc | wc -l)
echo "The number of entries in /etc directory: $etc_entries"

#Gather the number of entries in /usr/bin directory
usr_bin_entries=$(ls /usr/bin |wc -l)
echo "The number of entries in /usr/bin directory :$usr_bin_entries"

#Add a sleep for a few minitutes
sleep 500

