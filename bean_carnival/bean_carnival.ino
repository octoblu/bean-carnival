uint32_t MAX_BEAN_SLEEP = 4294967295;
int TIMEOUT = 2000;

int lastClick = 0;
int maxAccel = 0;

void wakeup(){
  lastClick = millis();
  maxAccel = 0;
}

void setup() {
  Serial.begin(57600);
  pinMode(4,INPUT);
  Bean.attachChangeInterrupt(4, wakeup);
  Bean.setAccelerationRange(16);
}

void loop() {
  if(millis() - lastClick > TIMEOUT){
    Bean.sleep(MAX_BEAN_SLEEP);
    return;
  }

  AccelerationReading accel = Bean.getAcceleration();

  int16_t localMaxAccel = abs(accel.xAxis);

  if(abs(accel.yAxis) > localMaxAccel){
    localMaxAccel = abs(accel.yAxis);
  }

  if(abs(accel.zAxis) > localMaxAccel){
    localMaxAccel = abs(accel.zAxis);
  }

  if(localMaxAccel > maxAccel){
    maxAccel = localMaxAccel;
    Bean.setScratchNumber(1, maxAccel);
  }
}
