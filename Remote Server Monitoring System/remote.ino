#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Hash.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

const char* ssid ="FT-IOT-MON";
const char* password = "";

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

float t = 0.0;
float h = 0.0;

AsyncWebServer server(80);

unsigned long previousMillis = 0;
const long interval = 5000;
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html>
    <head>
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <link rel="stylesheet" 
        href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.2.0/css/all.min.css">
        <style>
            html
                {
                font-family: Arial;
                display: inline-block;
                margin-bottom: auto;
                text-align: center;
                background-color: #236AB9;
                color:#131313;
                font-family: 'Trebuchet MS', sans-serif;
                font-size: 4vw;
                }
            h2
                {
                font-size: 3.4vw;
                }
            p 
                {
                font-weight: bolder;
                }
            i
                {
                font-size: 5vw;
                }
            table 
                {
                text-align: justify;
                font-weight: bolder;
                border: 1px solid;
                width: 55%;
                margin-left: auto; 
                margin-right: auto;
                font-size: 3.5vw;
                }
            td
                {
                padding: 5px;
                height: 5px;
                }
        </style>
    </head>
    <body>
        <h1>Server Room Status</h1>
        <h2>Fourth Floor</h2>
        <table>
            <tbody>
                <tr>
                    <td>
                        <i class="fa fa-temperature-half" style="color:#9cce15;">
                        </i>    Temperature
                    </td>
                    <td>
                        <i class="fa-solid fa-circle-check" style="color:#9cce15"></i>
                        <span id="temperature">77</span>
                        <sup class="units">&deg;C</sup>
                    </td>
                </tr>
                <tr>
                    <td>
                        <i class="fa fa-droplet" style="color:#00eeff;">
                        </i>    Humidity
                    </td>
                    <td>
                        <i class='fa fa-check-circle'style="color:#99f323;"></i>
                        <span id="humidity">100</span>
                        <sup class="units">&percnt;</sup>
                    </td>
                </tr>
            </tbody>
        </table>
    </body>
    <script>
        setInterval(function ( )
            {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function()
            {
                if (this.readyState == 4 && this.status == 200)
                    {
                    document.getElementById("temperature").innerHTML = this.responseText;
                    }
                };
            xhttp.open("GET", "/temperature", true);
            xhttp.send();
            },
        10000 ) ;

        setInterval(function ( )
            {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function()
                {
                if (this.readyState == 4 && this.status == 200) 
                    {
                    document.getElementById("humidity").innerHTML = this.responseText;
                    }
                };
            xhttp.open("GET", "/humidity", true);
            xhttp.send();
            },
        10000 ) ;
    </script>
</html>
)rawliteral";

String processor(const String &var)
    {
    if (var == "TEMPERATURE")
        {
        return String(t);
        }
    else if (var == "HUMIDITY")
        {
        return String(h);
        }
    return String();
    }      

void setup()
    {
      
    Serial.begin(115200);

    dht.begin();
    
    WiFi.begin(ssid, password);
    Serial.println("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED)
        {
        delay(1000);
        Serial.println(".");
        }
    Serial.println(WiFi.localIP());
        Serial.println();
Serial.print("MAC: ");
Serial.println(WiFi.macAddress());

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
        {
        request->send_P(200, "text/html", index_html, processor);
        }   );

    server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request)
        {
        request->send_P(200, "text/plain", String(t).c_str());
        }   );
    server.on("/humidity", HTTP_GET,[](AsyncWebServerRequest *request)
        {
        request->send_P(200,"text/plain", String(h).c_str());
        }   );
    server.begin();
    }

void loop()
    {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval)
        {
        previousMillis = currentMillis;
        float newT = dht.readTemperature();
        if (isnan(newT))
            {
            Serial.println("Failed to read from DHT sensor!");
            }
        else
            {   
            t = newT;
            Serial.println(t);
            }
        float newH = dht.readHumidity();
        if (isnan(newH))
            {
            Serial.println("Failed to read from DHT sensor!");
            }   
        else
            {
            h = newH;
            Serial.println(h);
            }
        }
    }
