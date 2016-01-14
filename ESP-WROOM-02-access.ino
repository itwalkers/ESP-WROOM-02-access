#include <ESP8266WiFi.h>

/**
 * constant
 */
const char* SSID            = "your_ssid";
const char* PASSWORD        = "your_p@$$w0rd";
const char* HOST            = "xxxxx.com";     // set host (xxxxx.com or IP address)
const char* CONNECTION      = "xxxxx";
const char* CACHE_CONTROL   = "xxxxx";
const char* ACCEPT          = "xxxxx";
const char* UP_INSECURE_REQ = "xxxxx";
const char* USER_AGENT      = "xxxxx";
const char* ACCEPT_ENCODING = "xxxxx";
const char* ACCEPT_LANGUAGE = "xxxxx";
const int HTTP_PORT         = 80;
const int ACCESS_INTERVAL   = 5000;            // サーバにアクセスする間隔（あまり短いとサーバに負荷がかかるので注意）

String url = "/set/?val=88";

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
  delay(ACCESS_INTERVAL);
  Serial.print("connecting to ");
  Serial.println(HOST);

  WiFiClient client;
  if (!client.connect(HOST, HTTP_PORT)) {
    Serial.println("connection failed");
    return;
  }

  Serial.print("Requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + HOST + "\r\n" +
               "Connection: " + CONNECTION + "\r\n" + 
               "Cache-Control: " + CACHE_CONTROL + "\r\n" + 
               "Accept: " + ACCEPT + "\r\n" + 
               "Upgrade-Insecure-Requests: " + UP_INSECURE_REQ + "\r\n" +
               "User-Agent: " + USER_AGENT + "\r\n" +
               "Accept-Encoding: " + ACCEPT_ENCODING + "\r\n" +
               "Accept-Language: " + ACCEPT_LANGUAGE + "\r\n" +
               "Connection: close\r\n\r\n");
  delay(2000);

  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
 
  Serial.println();
  Serial.println("closing connection"); 
}
