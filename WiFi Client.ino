#include <WiFi.h>  


const char* ssid = "***********"; // Your Network Name
const char* password =  "*********"; // Network password
 
const uint16_t port = 5000; 
const char * host = "***********"; // IP address


   WiFiClient client;


void setup()
{
    Serial.begin(115200);
    delay(10);

    WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("...");
  }
 Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());


 
    if (!client.connect(host, port)) {
 
        Serial.println("Connection to host failed");
 
        delay(1000);
        return;
    }
 
    Serial.println("Connected to server successful!");
 
}
void loop()
{
   
    // This will send a request to the server
    client.print("Hello From ESP32!");

    //read back one line from the server
    String line = client.readStringUntil('\r');
    Serial.println("Recieved Message From Server");
   
    Serial.println(line);
  Serial.println("Closing connection.");
   client.stop();

   Serial.println("Waiting 5 seconds before restarting...");
    delay(5000);
}

