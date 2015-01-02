#!/bin/bash

#Checks whether the OS is OS X (Darwin) or Linux
OS=$(uname -a | cut -d' ' -f1)
#Gets location of the script
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

#versionnumber without patch-number, eg 3.4, not 3.4.2
ver_no=$(python3 --version | cut -d' ' -f2 | cut -d. -f1,2)

#path to python bin
bin_dir=$(which python3)
#removes the bin subdirectory from path
rm_this=/bin/python3
pyth_dir=${bin_dir/$rm_this}  

#saves include directory and library path.
incl_dir="$pyth_dir"/include/python"$ver_no"m 		#Path to include directory
lib_path="$pyth_dir"/lib/libpython"$ver_no"m.dylib	#Path to library file


#Checks if include directory exists
if [ ! -d "$incl_dir" ]
	then
		printf "\nERROR: The include directory couldn't be found in the standard"
		printf "directory ($incl_dir). \n Please enter the path manually: "
		read incl_dir
		
		#checks if directory entered by user exists
		while [ ! -d "$incl_dir" ]; do
			printf "\n\n\nThe directory $incl_dir does not exist. Please check for typos"
			printf " and try again: "
			read incl_dir
		done
fi

#Checks if library file exists AND is not a directory
if [ ! -e "$lib_path" ]&&[ ! -d "$lib_path" ]
	then
		printf "\nERROR: The library path couldn't be found in the standard"
		printf "directory ($lib_path). \nPlease enter the path manually.\n"
		printf "Note: The file MUST be named like this: libpythonX.Xm.dylib while X.X"
		printf " is the python version.\n"
		read lib_path
		
		#checks if library file entered by user exists AND is not a directory
		while [ ! -e "$lib_path" ]&&[ ! -d "$lib_path" ]; do
			printf "\n\n\nThe file $lib_path does not exist. Please check for typos"
			printf " and if the path is really a file and try again: "
			read lib_path
		done
fi

#Writes the CMakeLists.txt
cat <<EOT >> CMakeLists.txt


#########################################################
##################IMPORTANT##############################
#Write the content of CMakeLists.txt here, use $incl_dir#
#and $lib_path for the Python 3 paths.###################
#########################################################
####################WARNING##############################
#Remove this comment block, as comments with # _WILL_ be#
#written into the file!!#################################
#########################################################


EOT
###END OF CMakeLists.txt###

#If OS is Darwin, ask the user to generate the makefile with the CMake-GUI.
if [ "$os"="Darwin" ] #OS X is installed
	then
		printf "\n\n\nYou are using OS X, the cmake command line tool is probably not "
		printf "installed. Please download the CMake GUI from "
		printf "http://www.cmake.org/download/. Use the following paths: \n"
		printf "Where is the source code: $DIR \n"
		printf "Where to build the binaries: "$DIR"/build/ .\n"
		printf "After you generated the make file, press any key to continue."
		read -n 1 -s #Waits for user input
		cd build
		make
		cd ..
		
		printf "\n\n Script finished. If it did'n return any errors, well, "
		printf "congratulations, it seems the project was built successfully! :) \n\n"
	
	else #We assume that Linux is running, if the kernel is not Darwin.
		cd build
		cmake ..
		make
		cd ..
		printf "\n\n Script finished. If it did'n return any errors, well, "
		printf "congratulations, it seems the project was built successfully! :) \n\n"
fi
exit 0