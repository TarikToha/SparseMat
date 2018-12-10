#define HIGH_THRES 40
#define LOW_THRES 16

#define timeOut 100
#define samplingPeriod 10


int ul, ur, ml, mr, ll, lr;
int incoming, outgoing;

int incomingA, incomingB, incomingC, outgoingA, outgoingB, outgoingC;




int lastSensedUpper[3], lastSensedMiddle[3], lastSensedLower[3];
int upperSensorIndex, middleSensorIndex, lowerSensorIndex;

int last_l, last_m, last_u, cnt, cnt2; /*Ahnaf*/



void setup() {
    Serial.begin(115200);
}


void readAnalog() {
    ul = analogRead(0);
    ur = analogRead(1);

    ml = analogRead(2);
    mr = analogRead(3);

    ll = analogRead(4);
    lr = analogRead(5);

    delay(samplingPeriod);
}

void loop() {

    incoming = outgoing = upperSensorIndex = middleSensorIndex = lowerSensorIndex = 0;

    cnt2 = cnt = last_l = last_m = last_u = 0; /*Ahnaf*/

    for (int i =0; i<timeOut; i++) {
        readAnalog();
        while (ul > LOW_THRES || ur > LOW_THRES || ml > LOW_THRES || mr > LOW_THRES || ll > LOW_THRES || lr > LOW_THRES ) {
            i=0;
            readAnalog();
            if (ul > HIGH_THRES) {
                lastSensedUpper[upperSensorIndex%3] = 0;
                upperSensorIndex++;
                lastSensedMiddle[middleSensorIndex%3] = 0;
                middleSensorIndex++;
            }

            if (ur > HIGH_THRES) {
                lastSensedUpper[upperSensorIndex%3] = 0;
                upperSensorIndex++;
                lastSensedMiddle[middleSensorIndex%3] = 0;
                middleSensorIndex++;
            }

            if ((ur > HIGH_THRES || ul > HIGH_THRES) && !last_u) { /*Ahnaf*/
                last_u = ++cnt;
                cnt2++;
                //Serial.println("this");
            }

            if (ml > HIGH_THRES) {
                lastSensedMiddle[middleSensorIndex%3] = 1;
                middleSensorIndex++;
                lastSensedLower[lowerSensorIndex%3] = 1;
                lowerSensorIndex++;
            }

            if (mr > HIGH_THRES) {
                lastSensedMiddle[middleSensorIndex%3] = 1;
                middleSensorIndex++;
                lastSensedLower[lowerSensorIndex%3] = 1;
                lowerSensorIndex++;
            }

            if ((mr > HIGH_THRES || ml > HIGH_THRES) && !last_m) { /*Ahnaf*/
                last_m = ++cnt;
                cnt2++;
                //Serial.println("this2");
            }

            if (ll > HIGH_THRES) {
                lastSensedLower[lowerSensorIndex%3] = 2;
                lowerSensorIndex++;
                lastSensedUpper[upperSensorIndex%3] = 2;
                upperSensorIndex++;
            }

            if (lr > HIGH_THRES) {
                lastSensedLower[lowerSensorIndex%3] = 2;
                lowerSensorIndex++;
                lastSensedUpper[upperSensorIndex%3] = 2;
                upperSensorIndex++;
            }

            if ((lr > HIGH_THRES || ll > HIGH_THRES) && !last_l){ /*Ahnaf*/
                last_l = ++cnt;
                cnt2++;
                //Serial.println("this3");
            }
            
        }
    }


    /*if (upperSensorIndex && middleSensorIndex && lowerSensorIndex) {


        for(int i=0; i < 3 ; i++) {
            if(lastSensedUpper[i] == 0)
                incoming++;
            else
                outgoing++;

            if(lastSensedMiddle[i] == 0)
                incoming++;
            else
                outgoing++;
                
            if(lastSensedLower[i] == 1)
                incoming++;
            else
                outgoing++;
        }*/

      if (cnt && cnt2 > 1) {
        if ((last_l > last_u) || (last_l > last_m))
              Serial.println("Incoming");
        /*else if (last_u && (last_m > last_u)) 
              Serial.println("Incoming");*/
        else if ((last_u > last_l) || (last_u > last_m))
              Serial.println("Outgoing");
        /*else if (last_l && (last_m > last_l))
              Serial.println("Outgoing");*/
        cnt = cnt2 = 0;
      }
      /*if(incoming > outgoing)
            //Serial.println("Incoming");
      else if(outgoing > incoming) 
           // Serial.println("Outgoing");*/
    //}

}

