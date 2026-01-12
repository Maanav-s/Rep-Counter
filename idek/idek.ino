#include <ICM20948_WE.h>
#define ICM20948_ADDR 0x69

ICM20948_WE myIMU = ICM20948_WE(ICM20948_ADDR);


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
  Serial.println("Position your ICM20948 flat and don't move it - calibrating...");
  delay(1000);
  myIMU.autoOffsets();
  Serial.println("Done!"); 
  
  myIMU.setAccRange(ICM20948_ACC_RANGE_2G);
  myIMU.setAccDLPF(ICM20948_DLPF_6);
  myIMU.setAccSampleRateDivider(10);

}

void loop() {
  myIMU.readSensor();
  
  xyzFloat gValue = myIMU.getGValues();
  xyzFloat angle = myIMU.getAngles();
  
/* For g-values the corrected raws are used */
  Serial.print("g-x      = ");
  Serial.print(gValue.x);
  Serial.print("  |  g-y      = ");
  Serial.print(gValue.y);
  Serial.print("  |  g-z      = ");
  Serial.println(gValue.z);

/* Angles are also based on the corrected raws. Angles are simply calculated by
   angle = arcsin(g Value) */
  Serial.print("Angle x  = ");
  Serial.print(angle.x);
  Serial.print("  |  Angle y  = ");
  Serial.print(angle.y);
  Serial.print("  |  Angle z  = ");
  Serial.println(angle.z);

  Serial.print("Orientation of the module: ");
  Serial.println(myIMU.getOrientationAsString());

  delay(1000);
}
