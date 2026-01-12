#include <Wire.h>
#include <mpu9250.h>

float ix, iy, iz, ax, ay, az, im, force;
float cx, cy, cz = 0;

const int CALIBRATION_CYCLES = 20;

/* Mpu9250 object */
bfs::Mpu9250 imu;

void setup() {
  /* Serial to display data */
  Serial.begin(9600);
  Serial.println("balls");
  while(!Serial) {}
  /* Start the I2C bus */
  Wire.begin();
  Wire.setClock(400000);
  /* I2C bus,  0x68 address */
  imu.Config(&Wire, bfs::Mpu9250::I2C_ADDR_PRIM);
  /* Initialize and configure IMU */
  if (!imu.Begin()) {
    Serial.println("Error initializing communication with IMU");
    while(1) {}
  }
  /* Set the sample rate divider */
  if (!imu.ConfigSrd(20)) {
    Serial.println("Error configured SRD");
    while(1) {}
  }

  if (!imu.ConfigAccelRange(bfs::Mpu9250::ACCEL_RANGE_16G)) {
    Serial.println("Error configuring Acceleration Range");
    while(1) {}
  }
  
  if (!imu.ConfigDlpfBandwidth(bfs::Mpu9250::DLPF_BANDWIDTH_20HZ)) {
    Serial.println("Error configuring Acceleration Range");
    while(1) {}
  }

  for (int i = 0; i < CALIBRATION_CYCLES; i++) {
    delay(50);
    imu.Read();
    cx += imu.accel_x_mps2();
    cy += imu.accel_y_mps2();
    cz += imu.accel_z_mps2();
  }

  ix = cx/CALIBRATION_CYCLES;
  iy = cy/CALIBRATION_CYCLES;
  iz = cz/CALIBRATION_CYCLES;

    Serial.println(ix);
    Serial.println(iy);
    Serial.println(iz);
  
  im = sqrt((ix*ix) + (iy*iy) + (iz*iz));

}

void loop() {
  // put your main code here, to run repeatedly:
  if (imu.Read()) {
    ax = imu.accel_x_mps2() - ix;
    ay = imu.accel_y_mps2() - iy;
    az = imu.accel_z_mps2() - iz;

    /*
    Serial.print("x:");
    Serial.println(ax);
    Serial.print("y:");
    Serial.println(ay);
    Serial.print("z:");
    Serial.println(az);
    */

    force = (((ax*ix) + (ay*iy) + (az*iz))/im);
  } else {
    Serial.println("Error reading accel data");
    force = 0;
  }

  Serial.print("up:");
  Serial.println(force);
  
  delay(50);
}

