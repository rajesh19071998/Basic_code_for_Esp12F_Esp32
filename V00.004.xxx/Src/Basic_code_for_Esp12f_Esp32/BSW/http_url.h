#ifndef _HTTP_URL_H
#define _HTTP_URL_H

// Replace with the URL you want to execute
//String url = "http://example.com/your-endpoint";

WiFiClient http_client;  // Create a WiFiClient object

String http_url(String url) {
    String Responce = "";
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Updated API: pass WiFiClient and URL
    http.begin(http_client, url);  

    int httpCode = http.GET(); // Make the GET request

    if (httpCode > 0) {
      String payload = http.getString();
      Responce = payload;

      Serial.println("Response:");
      Serial.println(payload);

    } else {
      Serial.printf("Error on HTTP request: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end(); // Close connection
  } else {
    Serial.println("WiFi not connected");
  }

  return Responce ;
}


#if 0

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

// Replace with your network credentials
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// Replace with your HTTPS endpoint
const char* url = "https://example.com/your-endpoint";

WiFiClientSecure client;  // Secure client for HTTPS

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi!");

  // For testing only: skip certificate validation
  client.setInsecure();  
  // ⚠️ Note: This disables SSL certificate checks. 
  // For production, you should use client.setFingerprint() or client.setTrustAnchors().
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Updated API: pass WiFiClientSecure and URL
    http.begin(client, url);  

    int httpCode = http.GET(); // Make the GET request

    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println("Response:");
      Serial.println(payload);
    } else {
      Serial.printf("Error on HTTP request: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end(); // Close connection
  } else {
    Serial.println("WiFi not connected");
  }

  delay(10000); // Wait 10 seconds before next request
}

#endif











#endif //_HTTP_URL_H