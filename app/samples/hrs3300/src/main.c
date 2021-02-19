/*
 * Copyright (c) 2021, najnesnaj 
 *
 * SPDX-License-Identifier: Apache-2.0


This sample was an attempt to read external led pulses with the HR-sensor.
This way, one should be able read out an external sensor.

With the Desay D6 smart watch, I managed to get it up and running.
With the Pinetime, however I cannot switch of the internal LED and still read out the sensor....

Using the RTT console, you still can experiment with reading out the sensor
 rtt:~$ sensor get HRS3300 18 (ir -- this switches off the sensor)
 rtt:~$ sensor get HRS3300 19 (red -- this switches on the sensor)
 rtt:~$ sensor get HRS3300 20 (green -- get a value)




 */

#include <zephyr.h>
#include <drivers/sensor.h>
#include <stdio.h>
#include <string.h>



void main(void)
{
	typedef unsigned long long  u64_t;
	u64_t pulse_ms_start, pulse_ms_end, lengte;
	int start=0, positie=0, con, teller=0;
	int message_count=0;
	char message_str[64];
	char message_start[17]="SSLLLLLLSSLLLLLL\0";
	char message_search[17]="XXXXXXXXXXXXXXXX\0";

	//struct sensor_value green;
	struct sensor_value val;
	//const struct device *dev = device_get_binding(DT_LABEL(DT_INST(0, hx_hrs3300)));
	//const struct device *dev = device_get_binding("HRS3300NEW");
	const struct device *dev = device_get_binding("HRS3300");

	if (dev == NULL) {
		printf("Could not get hrs3300 device\n");
		return;
	}

	sensor_channel_get(dev, SENSOR_CHAN_IR, &val); //switches blinking LED OFF
	while (1) {
		sensor_sample_fetch(dev);
		sensor_channel_get(dev, SENSOR_CHAN_GREEN, &val);

		/* Print green LED data*/
		//printf("hrs=%d\n", green.val1);
		//printf("als=%d\n", green.val2);
		printf("als=%d\n", val.val1); //ambient light sensor
		lengte=0;
		if ((val.val1 > 100) && (start==0)){ //external LED is on
			//pulse_ms_start = k_uptime_get_32();
			pulse_ms_start = k_cycle_get_32();
			start=1;
		}
		if ((val.val1 < 100) && (start==1)){ //external LED is off
			//pulse_ms_end = k_uptime_get_32();
			pulse_ms_end = k_cycle_get_32();
			start=0;
			lengte=pulse_ms_end-pulse_ms_start;
		}
		if (lengte>1500) { //long pulse
			//printk("L");
			message_str[message_count]='L';
		}
		if ((lengte<1500) && (lengte>0)) { //short pulse
			//printk("S");
			message_str[message_count]='S';
		}
		if (lengte>0) {
			//printk("\n");
			message_count++;
			if (message_count > 64) { //once we get 64 LED pulses, analysis starts
				//printk("%s\n",message_str);
				message_count=0;
				for (int searching=0; searching<48; searching++) //locate the start-sequence
				{
					strncpy(message_search,message_str+searching,16);
					//              printk("message_search %s\n",message_search);
					if (strcmp(message_start,message_search)==0){
						printk("eureka!\n");
						positie=searching;
						break;
					}
				}
				printk("locate string %d\n",positie);
				for (con=positie+16;con<positie+24;con++) //get the sensor ID
				{
					//              printk("%c",message_str[con]);
					if (message_str[con]=='S'){
						teller |= 1<<(con-positie-16);

					}
				}
				printk("sensor number : %d\n",teller);
				teller=0;
				for (con=positie+24;con<positie+32;con++) //get the Value
				{
					//               printk("%c",message_str[con]);
					if (message_str[con]=='S'){
						teller |= 1<<(con-positie-24);
					}
				}

				printk("external sensor value : %d\n",teller); //lightpulses converted into integer value
				teller=0;
			}
		}

		k_sleep(K_MSEC(20));
	}
}
