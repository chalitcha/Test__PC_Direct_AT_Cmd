/**********
 * for Send AT Command from PC(Serial Monitor) to BC95-True IoT
 * 
 ********/
#include "True_NB_bc95.h"
#include <AltSoftSerial.h>  

AltSoftSerial Serial2;     

True_NB_bc95 modem;
String end_line = "\r\n";

void setup()
{

  Serial.begin(9600);   // Connect PC
  Serial2.begin(9600);  // connect BC95

  delay(3000);
  Serial.println("Starting-AT Command Tester!!");
  Serial.println("initial modem interface...");
  modem.init(Serial2);
  //modem.initModem();

  Serial.println("initial success\r\n");
  Serial.println("#[Please enter AT Command]:");
}

void loop()
{
  String pc_at_cmd = "";
  char bc95_resp[MODEM_RESP];
  int bc95_resp_len;

  if (Serial.available() > 0)
  {
    // clear buffer
    bc95_resp[0] = '\0';
    bc95_resp_len = 0;
    pc_at_cmd = "";

    // read PC command
    pc_at_cmd = Serial.readString();
    Serial.print("#send: ");
    Serial.print(pc_at_cmd);

    // send modem
    Serial.println("\r\nwait response...");
    pc_at_cmd = pc_at_cmd + end_line;
    bc95_resp_len = modem.send_AT_cmd(pc_at_cmd, &bc95_resp[0]);

    Serial.println("response: [" + String(bc95_resp_len) + "]");
    Serial.print(bc95_resp);
    Serial.println("#[Please enter AT Command]:");

  }

}


