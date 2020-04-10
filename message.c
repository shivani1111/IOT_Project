//Git initial commit 
//git commit
//git commit on branch

//Connect the Tx pin of the GSM modem to D3
//Connect the Rx pin of the GSM modem to D4
//SMS Trigger Key/Input connected to D7 (Active LOW)
//CALL Trigger Key connected to D8 (Active LOW)
//END Key Connected to D9 (Active LOW)
#include <SoftwareSerial.h>
SoftwareSerial mySerial(3, 4); // RX and TX pins to communicate with GSM module
//#define msg_key 7
#define call_key 8
#define end_key 9
#define sensor_pin A0
#define relaypin 13
int a=0;
int b=0;
String number = "9146581390"; // Add the 10-Digit Mobile Number to which message / call is to be made,by replacing the 0's
void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(sensor_pin, INPUT);
  pinMode(relaypin,OUTPUT);
// digitalWrite(msg_key, HIGH);



}
void loop()
{
  int output_value = analogRead(sensor_pin);
  output_value = map(output_value, 1023, 0, 0, 100);

  Serial.print("Mositure : ");
  Serial.print(output_value);
  Serial.println("%");
  delay(1000);

  //Sends an sms everytime msg_key is pressed
  if (output_value >= 25) // Check if the sms key is being pressed
  {
    digitalWrite(relaypin,LOW);
    delay(5000);
  }
  if (output_value>=25&&a==0) // motor on message
  {
         b=0;
         a=a+1;
         mySerial.println("AT+CMGF=1"); // Set the Mode as Text Mode
         delay(150);
         mySerial.println("AT+CMGS=\"+91" + number + "\""); // Specify the Destination number in international format by replacing the 0's
         delay(150);
         mySerial.print("Motor is ON!"); // Enter the message
         delay(150);
         mySerial.write((byte)0x1A); // End of message character 0x1A : Equivalent to Ctrl+z
         delay(50);
         mySerial.println();

  }
  if(output_value<25&&b==0)// motor on message
  {
         a=0;
         b=b+1;
         mySerial.println("AT+CMGF=1"); // Set the Mode as Text Mode
         delay(150);
         mySerial.println("AT+CMGS=\"+91" + number + "\""); // Specify the Destination number in international format by replacing the 0's
         delay(1500);
         mySerial.print("Motor is OFF!"); // Enter the message
         delay(1500);
         mySerial.write((byte)0x1A); // End of message character 0x1A : Equivalent to Ctrl+z
         delay(500);
         mySerial.println();


  }

 digitalWrite(relaypin,HIGH);

}
