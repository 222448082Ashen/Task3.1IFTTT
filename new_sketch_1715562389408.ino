#include <WiFiNINA.h>

//please enter your sensitive data in the Secret tab
char ssid[] = "RHD32";
char pass[] = "12345678";

WiFiClient client;

char   HOST_NAME[] = "maker.ifttt.com";
String PATH_NAME   = "/trigger/Sunlight is available Now/with/key/cgx1jHAzHix9Qothjlor_y"; // for the event sunlight available
String PATH_NAME1  = "/trigger/Sunlight not available/with/key/cgx1jHAzHix9Qothjlor_y"; // for the event sunlight not available

//initial no sunlight before placing in the garden
int sunlightstate = 0;

void setup() {
  // initialize WiFi connection
  WiFi.begin(ssid, pass);

  Serial.begin(9600);
  while (!Serial);

  

}

void loop() {

  Serial.println("Welcome");
  Serial.println(sunlightstate);
  int lightlevel = analogRead(A7);
  Serial.println(lightlevel);

  //if sunlight not available before and now avilable do this
  if (sunlightstate < 1 && lightlevel > 400) {
    // connect to web server on port 80:
    if (client.connect(HOST_NAME, 80)) {
        // if connected:
      Serial.println("Connected to server");
    }
    else {// if not connected:
      Serial.println("connection failed");
    }
    //trigerring the sunlight available email
    // make a HTTP request:
    // send HTTP header
    client.println("GET " + PATH_NAME + " HTTP/1.1");
    client.println("Host: " + String(HOST_NAME));
    client.println("Connection: close");
    client.println(); // end HTTP header
    //remebering that sunlight is available now
    sunlightstate = 1;

    while (client.connected()) {
      if (client.available()) {
        // read an incoming byte from the server and print it to serial monitor:
        char c = client.read();
        Serial.print(c);
      }
    }

    // the server's disconnected, stop the client:
    client.stop();
    Serial.println();
    Serial.println("disconnected");
    delay(30000);
  }else if (sunlightstate > 0 && lightlevel < 400) {

    // connect to web server on port 80:
    if (client.connect(HOST_NAME, 80)) {
        // if connected:
      Serial.println("Connected to server");
    }
    else {// if not connected:
      Serial.println("connection failed");
    }
    //trigerring the sunlight available email
    // make a HTTP request:
    // send HTTP header
    client.println("GET " + PATH_NAME1 + " HTTP/1.1");
    client.println("Host: " + String(HOST_NAME));
    client.println("Connection: close");
    client.println(); // end HTTP header
    //remebering that sunlight is available now
    sunlightstate = 0;

    while (client.connected()) {
      if (client.available()) {
        // read an incoming byte from the server and print it to serial monitor:
        char c = client.read();
        Serial.print(c);
      }
    }

    // the server's disconnected, stop the client:
    client.stop();
    Serial.println();
    Serial.println("disconnected");
    delay(30000);
  }else {
    Serial.println("The sunlightstate is unchanged ");
    delay(30000);
  }

}
