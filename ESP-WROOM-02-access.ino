#include <ESP8266WiFi.h>

// set wifi
const char* SSID     = "your_ssid";
const char* PASSWORD = "your_p@$$w0rd";

// set host (xxxxx.com or IP address)
const char* HOST = "xxxxx.com";

void setup()
{
  delay(10);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(SSID);

  // connect WiFi
  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  delay(100);
  Serial.begin(115200);
  Serial.println("Starting up");
}

void loop()
{
  delay(5000);
  Serial.print("connecting to ");
  Serial.println(HOST);

  WiFiClient client;
  const int HTTP_PORT = 80;
  if (!client.connect(HOST, HTTP_PORT)) {
    Serial.println("connection failed");
    return;
  }

  String url = "/set/?val=88";
  Serial.print("Requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + HOST + "\r\n" +
               "Connection: xxxxx\r\n" + 
               "Cache-Control: xxxxx\r\n" + 
               "Accept: xxxxx\r\n" + 
               "Upgrade-Insecure-Requests: xxxxx\r\n" +
               "User-Agent: xxxxx\r\n" +
               "Accept-Encoding: xxxxx\r\n" +
               "Accept-Language: xxxxx\r\n" +
               "Connection: close\r\n\r\n");
  delay(2000);

  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
 
  Serial.println();
  Serial.println("closing connection"); 
}
