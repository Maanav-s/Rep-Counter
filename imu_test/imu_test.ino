#include <Wire.h>
#include <mpu9250.h>
#include <SensorFusion.h>

SF fusion;

float gx, gy, gz, ax, ay, az, mx, my, mz, temp;
float pitch, roll, yaw;
float deltat;


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
  if (!imu.ConfigSrd(19)) {
    Serial.println("Error configured SRD");
    while(1) {}
  }

  if (!imu.ConfigAccelRange(bfs::Mpu9250::ACCEL_RANGE_8G)) {
    Serial.println("Error configuring Acceleration Range");
    while(1) {}
  }
  
  if (!imu.ConfigDlpfBandwidth(bfs::Mpu9250::DLPF_BANDWIDTH_20HZ)) {
    Serial.println("Error configuring Acceleration Range");
    while(1) {}
  }
}

void loop() {
  /* Check if data read */
  if (imu.Read()) {
    /*Serial.print(imu.new_imu_data());
    Serial.print("\t");
    Serial.print(imu.new_mag_data());
    Serial.print("\t");
    Serial.print(imu.accel_x_mps2());
    Serial.print("\t");
    Serial.print(imu.accel_y_mps2());
    Serial.print("\t");
    Serial.print(imu.accel_z_mps2());
    Serial.print("\t");
    Serial.print(imu.gyro_x_radps());
    Serial.print("\t");
    Serial.print(imu.gyro_y_radps());
    Serial.print("\t");
    Serial.print(imu.gyro_z_radps());
    Serial.print("\t");
    Serial.print(imu.mag_x_ut());
    Serial.print("\t");
    Serial.print(imu.mag_y_ut());
    Serial.print("\t");
    Serial.print(imu.mag_z_ut());
    Serial.print("\t");
    Serial.print(imu.die_temp_c());
    Serial.print("\n");*/

    ax = imu.accel_x_mps2();
    ay = imu.accel_y_mps2();
    az = imu.accel_z_mps2();
    gx = imu.gyro_x_radps();
    gy = imu.gyro_y_radps();
    gz = imu.gyro_z_radps();
    mx = imu.mag_x_ut();
    my = imu.mag_y_ut();
    mz = imu.mag_z_ut();

    deltat = fusion.deltatUpdate();
    fusion.MahonyUpdate(gx, gy, gz, ax, ay, az, mx, my, mz, deltat);

    roll = fusion.getRoll();
    pitch = fusion.getPitch();
    yaw = fusion.getYaw();

    Serial.print("Variable_1:");
    Serial.println(ax);
  }
    //Serial.print("problemo");
}