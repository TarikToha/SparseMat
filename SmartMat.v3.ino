#define HIGH_THRES 64
#define LOW_THRES 16

#define timeOut 200
#define samplingPeriod 10


int ul, um, ur, ll, lm, lr;
int incoming, outgoing;

bool isSensed[6];
int lastSensed[3];
int sensorIndex;


void setup() {
  Serial.begin(115200);
}


void readAnalog() {
  ul = analogRead(0);
  um = analogRead(1);
  ur = analogRead(2);

  ll = analogRead(3);
  lm = analogRead(4);
  lr = analogRead(5);

  delay(samplingPeriod);
}


void loop() {

  lastSensed[0] = lastSensed[1] = lastSensed[2] = -1;
  //isSensed[0] = isSensed[1] = isSensed[2] = isSensed[3] = isSensed[4] = isSensed[5] = false;
  
  
  incoming = outgoing = sensorIndex = 0;

  for (int i = 0; i < timeOut; i++) {
    readAnalog();
    while (ul > LOW_THRES || um > LOW_THRES || ur > LOW_THRES || ll > LOW_THRES || lm > LOW_THRES || lr > LOW_THRES ) {
      i = 0;
      readAnalog();
      if (ul > HIGH_THRES) {
        lastSensed[sensorIndex % 3] = 0;
        sensorIndex++;
        isSensed[0] = true;
        //Serial.println("ul\n");
      }

      if (um > HIGH_THRES) {
        lastSensed[sensorIndex % 3] = 0;
        sensorIndex++;
        isSensed[1] = true;

        //Serial.println("um\n");
      }

      if (ur > HIGH_THRES) {
        lastSensed[sensorIndex % 3] = 0;
        sensorIndex++;
        isSensed[2] = true;
        //Serial.println("ur\n");

      }

      if (ll > HIGH_THRES) {
        lastSensed[sensorIndex % 3] = 1;
        sensorIndex++;
        isSensed[3] = true;
        //Serial.println("ll\n");

      }

      if (lm > HIGH_THRES) {
        lastSensed[sensorIndex % 3] = 1;
        sensorIndex++;
        isSensed[4] = true;
        //Serial.println("lm\n");

      }

      if (lr > HIGH_THRES) {
        lastSensed[sensorIndex % 3] = 1;
        sensorIndex++;
        isSensed[5] = true;
        //Serial.println("lr\n");

      }
    }
  }



  if (sensorIndex)  {


    for (int i = 0; i < 3 ; i++) {
      if (lastSensed[i]==0)
        incoming++;
      else if(lastSensed[i]==1) 
        outgoing++;
    }


    if (incoming > outgoing)
      Serial.println("Incoming");
    else
      Serial.println("Outgoing");

  }

}

