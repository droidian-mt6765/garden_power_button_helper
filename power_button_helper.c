#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

// Convert seconds to micros
#define SLEEP_PERIOD 0.5*1000000

// For debug uncomment
//#define DEBUG

int main(int argc,char* argv[]){
	int backlight_stat_fd;
	long backlight_stat = 0;
	int brightness_control;
	char readchar;
	int last_stat;
	char before_lock[4];
	int read_bytes;

	backlight_stat_fd = open("/sys/android_brightness/brightness_light",O_RDONLY);
	read(backlight_stat_fd,&readchar,1);
	close(backlight_stat_fd);
	last_stat = readchar - '0';

	while(true){

		backlight_stat_fd = open("/sys/android_brightness/brightness_light",O_RDONLY);

		read(backlight_stat_fd,&readchar,1);

		close(backlight_stat_fd);

		#ifdef DEBUG
			printf("Read char : %c\n",readchar);
		#endif

		backlight_stat = readchar - '0';

		#ifdef DEBUG
			printf("last_stat : %d, backlight_stat : %d\n",last_stat,backlight_stat);
		#endif

		if(backlight_stat == 5 && last_stat == 0){
			//Screen Turned On

			#ifdef DEBUG
			puts("Changing Screen");
			#endif

			// Read the Brightness and save it
			brightness_control = open("/sys/class/leds/lcd-backlight/brightness",O_RDONLY);
			read_bytes = read(brightness_control,before_lock,4);
			close(brightness_control);

			#ifdef DEBUG
			printf("Brightness before : %s\n",before_lock);
			#endif

			// Setting to zero since the values must differ to turn on the screen
			brightness_control = open("/sys/class/leds/lcd-backlight/brightness",O_WRONLY);
			write(brightness_control,"0",1);
			close(brightness_control);
			// Setting the Brightness saved before
			brightness_control = open("/sys/class/leds/lcd-backlight/brightness",O_WRONLY);
			write(brightness_control,before_lock,read_bytes);
                        close(brightness_control);
		}

		last_stat = backlight_stat;
		usleep(SLEEP_PERIOD);
	}
}
