#include <SPI.h>
#include <Ethernet.h>  // Ethernet Library
#include <NewPing.h>   // JSN-SR04T Library

/* JSN-SR04T Setting
 * Arduino Pins: 9 = Echo, 8 = Trigger
 * Maximum measured distance = 200 cm
 */
#define TRIGGER_PIN    9
#define ECHO_PIN       8
#define MAX_DISTANCE   200

/* Ethernet Setting
 * MAC address must be unique on your network
 * IP Address = 192.168.1.20
 * Server = 192.168.1.1
 * Gateway = 192.168.1.1 
 * Subnet = 255.255.255
 * DNS = 8.8.8.8 (DNS Google)
 */
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char server[] = "192.168.1.1";

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 1, 20);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress myDns(8, 8, 8, 8);

/* Initialize the Ethernet server library
 * with the IP address and port you want to use
 * (port 80 is default for HTTP)
 */
EthernetClient client;              
                     
// Initialize JSN-SR04T sensor
NewPing ultrasonic(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 
                                 
//long previousMillis = 0;
//unsigned long currentMillis = 0;
// Interval between data
int interval = 5000;   
int distance = 0;
                         
void setup() {
  // Open serial communications and wait for port to open
  Serial.begin(9600);

  // Wait for serial port to connect. Needed for Leonardo only
  while (!Serial) {
    
  }
  
  /* Initialize Ethernet Device
   */
  Ethernet.begin(mac, ip, myDns, gateway, subnet);

  // Give the Ethernet shield a second to initialize:
  delay(5000);
  Serial.println("Connecting...");
  Serial.println("************************************");
  Serial.println("     Distance Monitoring System     ");
  Serial.println("************************************");
  Serial.print("IP Address          : ");
  Serial.println(Ethernet.localIP());
  Serial.print("Subnet Mask         : ");
  Serial.println(Ethernet.subnetMask());
  Serial.print("Default Gateway IP  : ");
  Serial.println(Ethernet.gatewayIP());
  Serial.print("DNS Server IP       : ");
  Serial.println(Ethernet.dnsServerIP());
  Serial.println("************************************");
  delay(5000);
}

void loop() {
  /*
  currentMillis = millis();
  // Read sensor once per interval
  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;
    distance = ultrasonic.ping_cm();
  }
  */
  
  distance = ultrasonic.ping_cm();
    
  if (client.connect(server, 80)) {
    // Make a HTTP request
    client.print("GET /add_data.php?");
    client.print("distance=");
    client.print(distance);
    Serial.print("Distance = ");
    Serial.print(distance);
    if (distance < 50) {
      client.print("&led_status=ON");
      client.print("&relay_status=ON");
      Serial.print(" LED Status = ON");
      Serial.println(" Relay Status = ON");
    }
    else {
      client.print("&led_status=OFF");
      client.print("&relay_status=OFF");
      Serial.print(" LED Status = OFF");
      Serial.println(" Relay Status = OFF");
    }
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(server);
    client.println("Connection: close");
    client.println();
  }
  else {
    Serial.println("Connection cannot be established");
  }  

  // Disconnect from server
  if (client.connected()){
    client.stop();  
  }

  delay(interval);
} 






