/*Door lock system code
 * https://srituhobby.com
 */
 
#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
String UID = "35 F0 A8 01";

Servo servo;
MFRC522 rfid(SS_PIN, RST_PIN);


void setup() {
  Serial.begin(9600);
  servo.write(0);
  servo.attach(3);
  SPI.begin();
  // rfid.PCD_Init();
  Serial.println("\nWelcome!");
  Serial.println("Put your card:");
}

void loop() {
  if ( ! rfid.PICC_IsNewCardPresent())
    return;
  if ( ! rfid.PICC_ReadCardSerial())
    return;

  Serial.print("NUID tag is :");
  String ID = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    ID.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
    ID.concat(String(rfid.uid.uidByte[i], HEX));
    delay(300);
  }
  ID.toUpperCase();

  if (ID.substring(1) == UID) {
    Serial.println(ID);
    Serial.println("Correct Card");
    servo.write(180);
    delay(1500);
    servo.write(0);

  } else {
    Serial.println(ID);
    Serial.println("Wrong card");
  }
}