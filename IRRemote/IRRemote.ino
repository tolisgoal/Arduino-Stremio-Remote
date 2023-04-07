#include <IRremote.h>

int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
unsigned long key_value=0;
unsigned long data=0;

int time=0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK);
}

/*REMOTE KEY CODES
 * 
 * CH- : BA45FF00
 * CH+ : B847FF00
 * CH  : B946FF00
 * >>| : BF40FF00
 * |<< : BB44FF00
 * Play/Pause: BC43FF00
 * -   : F807FF00
 * +   : EA15FF00
 * EQ  : F609FF00
 * 0   : E916FF00
 * 1   : F30CFF00
 * 2   : E718FF00
 * 3   : A15EFF00
 * 4   : F708FF00
 * 5   : E31CFF00
 * 6   : A55AFF00
 * 7   : BD42FF00
 * 8   : AD52FF00
 * 9   : B54AFF00
 * 100+: E619FF00
 * 200+: F20DFF00
 */
void loop() {
  // put your main code here, to run repeatedly:
  if(IrReceiver.decode()){
    data = IrReceiver.decodedIRData.decodedRawData;
    if(data == 0){
      data = key_value;
    }
    switch (data) { // compare the value to the following cases
      case 0xEA15FF00:
        Serial.println("+");
        delay(100);
        Serial.flush();
        break;
      case 0xF807FF00:
        Serial.println("-");
        delay(100);
        break;
      case 0xBF40FF00:
        Serial.println(">>|"); // No delay on skip cases, cuz we need speed
        break;
      case 0xBC43FF00:
        Serial.println("|> ||");
        delay(500);
        break;
      case 0xBB44FF00:
        Serial.println("|<<");
        break;
      case 0xF609FF00:
        Serial.println("EQ");
        delay(500);
        break;
      case 0xB946FF00:
        Serial.println("exit");
        delay(100);
        break;
    }
    key_value = data; // store the value as key_value
    IrReceiver.resume(); // Enable receiving of the next value
  }
    /* USE NEW 3.x FUNCTIONS
    IrReceiver.printIRResultShort(&Serial); // Print complete received data in one line
    IrReceiver.printIRSendUsage(&Serial); // Print the statement required to send this data
     */
}
