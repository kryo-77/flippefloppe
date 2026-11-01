// WIP (i only tested with 4 servos)
// uses xiao s3 instead of c3 supermini
// add Adafruit_PWMServoDriver.h library

//used a bit of ai, specially for combining html & .ino together but mostly written by me (following tutorials)


//to-do:  Add RTC module for binary clock 

#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

const char* ssid = "example"; //change to wifi name
const char* password = "example"; //change to wifi pass

// Servo driver I2C address 0x40)
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Servo positions (pulse length out of 4096)
int GREEN_POS = 150;   // like 0 degrees
int RED_POS   = 450;   // like 90 degrees

WebServer server(80);

// html
const char webpage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>Mechanical Display</title>
  <style>
    body {
      background: #2d3340;
      color: white;
      font-family: sans-serif;
      text-align: center;
    }

    #grid {
      display: grid;
      grid-template-columns: repeat(4, 100px);
      gap: 10px;
      justify-content: center;
      margin-top: 30px;
    }

    .pixel {
      width: 100px;
      height: 100px;
      background: green;
      border: 3px solid black;
      cursor: pointer;
      color: white;
      font-size: 14px;
    }
  </style>
</head>
<body>

  <h1>Mechanical Display</h1>
  <p>Click a pixel to flip it between green and red</p>

  <div id="grid">
    <button class="pixel" onclick="flip(this)">r1c1</button>
    <button class="pixel" onclick="flip(this)">r1c2</button>
    <button class="pixel" onclick="flip(this)">r1c3</button>
    <button class="pixel" onclick="flip(this)">r1c4</button>

    <button class="pixel" onclick="flip(this)">r2c1</button>
    <button class="pixel" onclick="flip(this)">r2c2</button>
    <button class="pixel" onclick="flip(this)">r2c3</button>
    <button class="pixel" onclick="flip(this)">r2c4</button>

    <button class="pixel" onclick="flip(this)">r3c1</button>
    <button class="pixel" onclick="flip(this)">r3c2</button>
    <button class="pixel" onclick="flip(this)">r3c3</button>
    <button class="pixel" onclick="flip(this)">r3c4</button>

    <button class="pixel" onclick="flip(this)">r4c1</button>
    <button class="pixel" onclick="flip(this)">r4c2</button>
    <button class="pixel" onclick="flip(this)">r4c3</button>
    <button class="pixel" onclick="flip(this)">r4c4</button>
  </div>

  <script>
    function flip(button) {
      if (button.style.background == "red") {
        button.style.background = "green";
      } else {
        button.style.background = "red";
      }
    }
  </script>

 

  <script>
    const originalFlip = flip;
    flip = function(button) {
      originalFlip(button);
      const all = document.querySelectorAll(".pixel");
      const channel = Array.from(all).indexOf(button);   // 0 to 15
      const isRed = (button.style.background == "red") ? 1 : 0;
      fetch("/servo?ch=" + channel + "&red=" + isRed);
    };
  </script>

</body>
</html>
)rawliteral";


void handleRoot() {
  server.send(200, "text/html", webpage);
}

// Move a servo
void handleServo() {
  int channel = server.arg("ch").toInt();
  int isRed = server.arg("red").toInt();

  if (isRed == 1) {
    pwm.setPWM(channel, 0, RED_POS);
  } else {
    pwm.setPWM(channel, 0, GREEN_POS);
  }

  server.send(200, "text/plain", "OK");
}

void setup() {
  Serial.begin(115200);

  // I2c
  Wire.begin();

  // Start PCA servo driver
  pwm.begin();
  pwm.setPWMFreq(50); 

  // Starts with first color on all 16 servos
  for (int i = 0; i < 16; i++) {
    pwm.setPWM(i, 0, GREEN_POS);
  }

  // Connect  wifi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Open this in your browser: http://");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/servo", handleServo);
  server.begin();
}

void loop() {
  server.handleClient();
}