#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
//#include "MPU6050.h" // not necessary if using MotionApps include file

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

MPU6050 mpu;
int val;

#define EARTH_GRAVITY_MS2 9.80665  // m/s2
#define DEG_TO_RAD        0.017453292519943295769236907684886
#define RAD_TO_DEG        57.295779513082320876798154814105

// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 gg;         // [x, y, z]            gyro sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorInt16 ggWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector


TaskHandle_t Task1;
TaskHandle_t Task2;

// LED pins
const int led1 = 2;
const int led2 = 4;

void setup() {
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
        Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

    Serial.begin(115200);

    mpu.initialize();
    devStatus = mpu.dmpInitialize();

    // supply your own gyro offsets here, scaled for min sensitivity
    mpu.setXAccelOffset(-102);
  mpu.setYAccelOffset(-3228);
  mpu.setZAccelOffset(1073);
  mpu.setXGyroOffset(408);
  mpu.setYGyroOffset(5);
  mpu.setZGyroOffset(-6);// 1688 factory default for my test chip
  Serial.println(xPortGetCoreID());

    // make sure it worked (returns 0 if so)
    if (devStatus == 0) {

        mpu.CalibrateAccel(6);
        mpu.CalibrateGyro(6);
        mpu.PrintActiveOffsets();
        mpu.setDMPEnabled(true);

        mpuIntStatus = mpu.getIntStatus();

        dmpReady = true;
        packetSize = mpu.dmpGetFIFOPacketSize();
    }

  //create a task that will be executed in the Task1code() function, with priority 1 and executed on core 0
  xTaskCreatePinnedToCore(
                    Task1code,   /* Task function. */
                    "Task1",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task1,      /* Task handle to keep track of created task */
                    0);          /* pin task to core 0 */                  
  delay(500); 

  //create a task that will be executed in the Task2code() function, with priority 1 and executed on core 1
  xTaskCreatePinnedToCore(
                    Task2code,   /* Task function. */
                    "Task2",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task2,      /* Task handle to keep track of created task */
                    1);          /* pin task to core 1 */
    delay(500); 
}

//Task1code: blinks an LED every 1000 ms
void Task1code( void * pvParameters ){
  Serial.print("Task1 running on core ");
  Serial.println(xPortGetCoreID());

  for(;;){
    val = analogRead(4);
    delay(1);
  } 
}

void Task2code( void * pvParameters ){
  Serial.print("Task2 running on core ");
  Serial.println(xPortGetCoreID());

  for(;;){
    long start_time = millis();
    if (!dmpReady) return;
    // Serial.println(xPortGetCoreID());
    if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) { // Get the Latest packet 

        // display quaternion values in easy matrix form: w x y z
        mpu.dmpGetQuaternion(&q, fifoBuffer);
        // Serial.print("quat\t");
        // Serial.print(q.w);
        // Serial.print("\t");
        // Serial.print(q.x);
        // Serial.print("\t");
        // Serial.print(q.y);
        // Serial.print("\t");
        // Serial.println(q.z);

        mpu.dmpGetGravity(&gravity, &q);

        // // display initial world-frame acceleration, adjusted to remove gravity
        // // and rotated based on known orientation from quaternion
        // mpu.dmpGetAccel(&aa, fifoBuffer);
        // mpu.dmpConvertToWorldFrame(&aaWorld, &aa, &q);
        // Serial.print("aworld\t");
        // Serial.print(aaWorld.x * mpu.get_acce_resolution() * EARTH_GRAVITY_MS2);
        // Serial.print("\t");
        // Serial.print(aaWorld.y * mpu.get_acce_resolution() * EARTH_GRAVITY_MS2);
        // Serial.print("\t");
        // Serial.println(aaWorld.z * mpu.get_acce_resolution() * EARTH_GRAVITY_MS2);

        // // display initial world-frame acceleration, adjusted to remove gravity
        // // and rotated based on known orientation from quaternion
        // mpu.dmpGetGyro(&gg, fifoBuffer);
        // mpu.dmpConvertToWorldFrame(&ggWorld, &gg, &q);
        // Serial.print("ggWorld\t");
        // Serial.print(ggWorld.x * mpu.get_gyro_resolution() * DEG_TO_RAD);
        // Serial.print("\t");
        // Serial.print(ggWorld.y * mpu.get_gyro_resolution() * DEG_TO_RAD);
        // Serial.print("\t");
        // Serial.println(ggWorld.z * mpu.get_gyro_resolution() * DEG_TO_RAD);

        mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
        // Serial.print("ypr\t");
        // Serial.print(ypr[0] );
        // Serial.print(",");
        // Serial.print(ypr[1] );
        // Serial.print("roll:    ");
        Serial.print(ypr[2] * RAD_TO_DEG);
        Serial.print(",");
        // delay(1);
    Serial.print(val);
// Serial.print(",");
// Serial.println(millis()-start_time);
        // Serial.print(",");

  }
}
}

void loop() {
  
}

