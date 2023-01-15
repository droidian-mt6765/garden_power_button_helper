# Garden Power Button Helper
A workaround for the broken power button on garden devices.

# Compile and Install
1. You must have gcc installed e.g.`sudo apt install gcc`
2. compile (without debug) : `gcc power_button_helper.c -o power_button_helper -O3 -static` (if you want with debug run this instead : `gcc -DDEBUG power_button_helper.c -o power_button_helper -O3 -static`)
3. Install executable : `sudo cp power_button_helper /usr/local/bin/power_button_helper`
4. Install service : `cp power_button_helper.service /etc/systemd/system/power_button_helper.service`
5. execute : `sudo systemctl enable power_button_helper` and reboot

# Don't Compile and Install
1. Do steps 3-5 but download the power_button_helper from release

# How it does it
1. First it checks if 5 is in the /sys/android_brightness/brightness_light
2. Then stores the contents of /sys/class/leds/lcd-backlight/brightness 
3. After that it copys 0 to /sys/class/leds/lcd-backlight/brightness
4. Now it restores the content of step 2
5. This is repeated every half second
