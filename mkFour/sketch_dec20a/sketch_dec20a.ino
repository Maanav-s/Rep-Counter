#include <ICM20948_WE.h>
#define ICM20948_ADDR 0x69

ICM20948_WE myIMU = ICM20948_WE(ICM20948_ADDR);
xyzFloat accRaw;
xyzFloat gyrRaw;
xyzFloat corrAccRaw;
xyzFloat corrGyrRaw;
xyzFloat gVal;


void setup() {
  // put your setup code here, to run once:
  delay(3000);
  Wire.begin();
  Serial.begin(9600);
  while(!Serial) {}
  
  if(!myIMU.init()){
    Serial.println("ICM20948 does not respond");
  } else {
    Serial.println("ICM20948 is responding");
  }

  myIMU.setAccOffsets(-16330.0, 16450.0, -16600.0, 16180.0, -16520.0, 16690.0);
  myIMU.setGyrOffsets(62.0, 57.0, 34.0);
  myIMU.setAccRange(ICM20948_ACC_RANGE_4G);
  myIMU.setAccDLPF(ICM20948_DLPF_6);
  myIMU.setGyrRange(ICM20948_GYRO_RANGE_500);
  myIMU.setGyrDLPF(ICM20948_DLPF_6);
  myIMU.setTempDLPF(ICM20948_DLPF_6);

  xyzFloat off = myIMU.getAccOffsets();
  
  Serial.println("Acceleration raw values without offset:");
  Serial.print(off.x);
  Serial.print("   ");
  Serial.print(off.y);
  Serial.print("   ");
  Serial.println(off.z);
}

void loop() {
  // put your main code here, to run repeatedly:
  myIMU.readSensor();

  accRaw = myIMU.getAccRawValues();
  gyrRaw = myIMU.getGyrRawValues();
  corrAccRaw = myIMU.getCorrectedAccRawValues();
  corrGyrRaw = myIMU.getCorrectedGyrRawValues();
  xyzFloat gVal = myIMU.getGValues();
  
  Serial.println("Acceleration raw values without offset:");
  Serial.print(accRaw.x);
  Serial.print("   ");
  Serial.print(accRaw.y);
  Serial.print("   ");
  Serial.println(accRaw.z);

  Serial.println("Gyroscope raw values without offset:");
  Serial.print(gyrRaw.x);
  Serial.print("   ");
  Serial.print(gyrRaw.y);
  Serial.print("   ");
  Serial.println(gyrRaw.z);

  Serial.println("g-values, based on corrected raws (x,y,z):");
  Serial.print(gVal.x);
  Serial.print("   ");
  Serial.print(gVal.y);
  Serial.print("   ");
  Serial.println(gVal.z);

  Serial.println("Gyroscope raw values with offset:");
  Serial.print(corrGyrRaw.x);
  Serial.print("   ");
  Serial.print(corrGyrRaw.y);
  Serial.print("   ");
  Serial.println(corrGyrRaw.z);


  Serial.println("********************************************");

  delay(2000);
}
