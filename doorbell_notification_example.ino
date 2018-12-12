/**
 * Door bell push notification send example
 *
 * You need to sign up for create your own node and field: https://iotguru.live/signup
 * 
 * The variables of the API call:
 *
 * {nodeKey} - the API key of your node
 * {message} - the message (URL encoded)
 *
 * http://api.iotguru.live/push/freeText/{nodeKey}/{message}
 *
 * See the example HTTP call below (don't forget to replace values!).
 *
 */
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

volatile int PIN_SWITCH = 2; // 10k pull-up, switch will be pull down the pin
volatile int pushed = 0;

void setup() {
    Serial.begin(115200);
    Serial.setTimeout(2000);

    WiFi.mode(WIFI_STA);
    WiFi.begin("your.wifi.ssid", "your.wifi.password");

    while (WiFi.status() != WL_CONNECTED) {
        delay(50);
        Serial.print(".");
    }

    pinMode(PIN_SWITCH, INPUT);
    attachInterrupt(PIN_SWITCH, handleSwitchPin, FALLING);

    Serial.println("Connected...");
}

void handleSwitchPin() {
    pushed = 1;
}

void loop()
{
    if (pushed == 1) {
        HTTPClient http;
        http.begin("http://api.iotguru.live/push/freeText/sTs5N5dlTmhbPT-ISHZApQ/Someone%20pushed%20the%door%20bell!");
        Serial.println("Result code: " + String(http.GET()));
        http.end();

        pushed = 0;
    }

    delay(50);
}
