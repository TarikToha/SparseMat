#include <avr/io.h>
#include <util/delay.h>

#include "arduino.h"

//COPY ARDUINO FILE
 
#define HIGH_THRES 64
#define LOW_THRES 16
#define timeOut 200
#define samplingPeriod 10

int ul, ur, um,  ll, lm, lr;
int incoming, outgoing;

int lastSensed[3];
int sensorIndex;

 
void readAnalog() {
	ul = adc_read(0);
	um = adc_read(1);
	ur = adc_read(2);

	ll = adc_read(3);
	lm = adc_read(4);
	lr = adc_read(5);

	_delay_ms(samplingPeriod);
	
}

void loop() {

	incoming = outgoing = sensorIndex = 0;

	for (int i =0;i<timeOut;i++){
		readAnalog();
		while (ul > LOW_THRES || um > LOW_THRES || ur > LOW_THRES || ll > LOW_THRES || lm > LOW_THRES || lr > LOW_THRES) {
			i=0;
			readAnalog();
			if (ul > HIGH_THRES) {
				lastSensed[sensorIndex%3] = 0;
				sensorIndex++;
			}

			if (um > HIGH_THRES) {
				lastSensed[sensorIndex%3] = 0;
				sensorIndex++;
			}

			if (ur > HIGH_THRES) {
				lastSensed[sensorIndex%3] = 0;
				sensorIndex++;
			}

			if (ll > HIGH_THRES) {
				lastSensed[sensorIndex%3] = 1;
				sensorIndex++;
			}

			if (lm > HIGH_THRES) {
				lastSensed[sensorIndex%3] = 1;
				sensorIndex++;
			}

			if (lr > HIGH_THRES) {
				lastSensed[sensorIndex%3] = 1;
				sensorIndex++;
			}
		}
	}


	if (sensorIndex){

		for(int i=0; i < 3 ; i++) {
			if(!lastSensed[i])
			incoming++;
			else
			outgoing++;
		}


		if(incoming > outgoing)
			printOutput(0);
		else
			printOutput(1);
		
	} else {
		printOutput(-1);
	}

}


int main() {
    setup();
    while(1) {
        loop();
    }
}
