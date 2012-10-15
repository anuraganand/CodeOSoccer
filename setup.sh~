#!/bin/bash
echo "=================================================="
echo "Common setup"
echo "=================================================="
read -p "Continue [Y/n]? "
if [[ $REPLY = [yY] || $REPLY = "" ]] 
	then
		sudo apt-get install build-essential --fix-missing
		echo -e "Done\n\n"
fi
echo -e "\nDone\n\n"

echo "=================================================="
echo "Installing google protocol buffer"
echo "=================================================="
read -p "Continue [Y/n]? "
if [[ $REPLY = [yY] || $REPLY = "" ]] 
	then
		cd utils
		tar -xvjf protobuf-2.4.1.tar.bz2
		cd protobuf-2.4.1
		./configure --prefix=/usr CFLAGS=-O3 CPPFLAGS=-O3
		make && make check && sudo make install || echo -en "\007"
		cd ..
		sudo rm -rf protobuf-2.4.1
                cd ..
fi
echo -e "\nDone\n\n"

echo "=================================================="
echo "Installing sslrefereebox"
echo "=================================================="
read -p "Continue [Y/n]? "
if [[ $REPLY = [yY] || $REPLY = "" ]] 
	then
		sudo apt-get install libgtkmm-2.4-dev make g++ gtk2-engines-pixbuf --fix-missing
		cd sslrefbox
		make && sudo make install && make clean || echo -en "\007"
		cd ..
fi
echo -e "\nDone\n\n"

echo "=================================================="
echo "Installing grSim"
echo "=================================================="
read -p "Continue [Y/n]? "
if [[ $REPLY = [yY] || $REPLY = "" ]] 
	then
		sudo apt-get install libqt4-dev g++ build-essential libgl1-mesa-dev libglu1-mesa-dev --fix-missing
		cd grSim/proto/pb
		bash compile.sh
		cd ../..
		# Putting the executables into /usr/local/bin folder for easily starting the application
		qmake && make && sudo cp bin/grSim /usr/local/bin || echo -en "\007"
		sudo rm /usr/local/bin/settings.xml
		cd ..
fi 
echo -e "\nDone\n\n"

echo "=================================================="
echo "Installing Codelite"
echo "=================================================="
read -p "Continue [Y/n]? "
if [[ $REPLY = [yY] || $REPLY = "" ]] 
	then
		echo -e '\E[37;40m'"[1] Go to http://sourceforge.net/projects/codelite/files/Releases/codelite-3.5/"
		echo "[2] Select codelite_3.5.5375-ubuntu0_i386.deb from the list. This will initiate the download."
		echo "[3] Double click on the downloaded .deb file to start installation."; tput sgr0
fi
echo -e "\nDone\n\n"
sudo cp libs/libcodeosoccer.so /usr/lib/libcodeosoccer.so

