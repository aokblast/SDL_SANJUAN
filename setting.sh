#!/bin/bash
echo -ne "Checking dependencies...\n";
for name in cmake libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev
do
        if [ $(dpkg-query -W -f='${Status}' $name 2>/dev/null | grep -c "ok installed") -eq 0 ]; then
        echo "$name isn't installed. Starting install...";
        sudo apt-get install -y $name;
  else
        echo "Package $name has been installed.";
  fi
done
echo "Finishing check dependencies...";
