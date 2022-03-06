#sudo apt-get install libusb-1.0-0-dev git
#sudo cp *.rules /etc/udev/rules.d
#sudo restart udev
export PATH=$PATH:/home/irfan/Desktop/arm/stlink/build/bin
st-flash write "build/DISC_TFT.bin" 0x8000000

