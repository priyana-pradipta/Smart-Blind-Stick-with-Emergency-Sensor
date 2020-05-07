//THIS CODE WAS CREATED ON 1/12/2017 THE CODE MAY BE OUTDATED BY THE TIME YOU USE IT, BUT YOU ARE WELCOME TO TRY
//CODE DEVELOPED BY FUNGUYPRO
//BLYNK IS REQUIRED
//USES BLE
//VISIT https:www.funguypro.net for more infomation

//#define BLYNK_DEBUG
#define BLYNK_PRINT Serial

//#define BLYNK_USE_DIRECT_CONNECT

#include <BlynkSimpleCurieBLE.h>
#include <CurieBLE.h>
#include "CurieIMU.h"


// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "YourAuthToken"; //Currently this is NOT required but if it doent work then make sure to change this!

BLEPeripheral  blePeripheral;

void setup() {
  Serial.begin(9600);
  delay(1000);

  CurieIMU.begin();
  //CurieIMU.attachInterrupt(eventCallback);
  CurieIMU.setDetectionThreshold(CURIE_IMU_SHOCK, 1500); // 1.5g = 1500 mg //EDIT THIS FOR SENSITIVITY
  CurieIMU.setDetectionDuration(CURIE_IMU_SHOCK, 50);   // 50ms //EDIT THIS FOR SENSITIVITY
  CurieIMU.interrupts(CURIE_IMU_SHOCK);

  blePeripheral.setLocalName("Funguy");
  blePeripheral.setDeviceName("Funguy");
  blePeripheral.setAppearance(384);

  Blynk.begin(blePeripheral, auth);

  blePeripheral.begin();

  Serial.println("Waiting for connections...");
}

void loop() {
  Blynk.run();
  blePeripheral.poll();
  if (CurieIMU.getInterruptStatus(CURIE_IMU_SHOCK)){
    Blynk.virtualWrite(V0, "t");
    Blynk.virtualWrite(V1, HIGH);
    Serial.println("GOT");
  }
}

