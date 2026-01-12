#include <ICM20948_WE.h>
#define ICM20948_ADDR 0x69

ICM20948_WE myIMU = ICM20948_WE(ICM20948_ADDR);
xyzFloat accRaw;
xyzFloat gyrRaw;
xyzFloat corrAccRaw;
xyzFloat corrGyrRaw;
xyzFloat accOffsets = xyzFloat(60.0, -120.0, 85.0);
xyzFloat gyrOffsets = xyzFloat(62.0, 57.0, 34.0);


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

  myIMU.setAccOffsets(accOffsets);
  myIMU.setGyrOffsets(gyrOffsets);
  myIMU.setAccRange(ICM20948_ACC_RANGE_4G);
  myIMU.setAccDLPF(ICM20948_DLPF_6);
  myIMU.setGyrRange(ICM20948_GYRO_RANGE_500);
  myIMU.setGyrDLPF(ICM20948_DLPF_6);
  myIMU.setTempDLPF(ICM20948_DLPF_6);
}

void loop() {
  // put your main code here, to run repeatedly:
  accRaw = myIMU.getAccRawValues();
  gyrRaw = myIMU.getGyrRawValues();
  corrAccRaw = myIMU.getCorrectedAccRawValues();
  corrGyrRaw = myIMU.getCorrectedGyrRawValues();

  Serial.println("Acceleration raw values with offset:");
  Serial.print(corrAccRaw.x);
  Serial.print("   ");
  Serial.print(corrAccRaw.y);
  Serial.print("   ");
  Serial.println(corrAccRaw.z);
  
  Serial.println("Gyroscope raw values with offset:");
  Serial.print(corrGyrRaw.x);
  Serial.print("   ");
  Serial.print(corrGyrRaw.y);
  Serial.print("   ");
  Serial.println(corrGyrRaw.z);


  Serial.println("********************************************");

  delay(2000);
}
