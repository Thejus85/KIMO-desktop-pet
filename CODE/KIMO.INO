/*****************************************************
   KIMO S3 – FULL ROBOT CODE
   Board : ESP32-S3 Dev Module (OPI PSRAM)
*****************************************************/

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "esp_camera.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "driver/i2s.h"
#include <math.h>

/* ================= PIN DEFINITIONS ================= */

// ---- DRV8833 MOTOR DRIVER ----
#define LEFT_M1   4
#define LEFT_M2   5
#define RIGHT_M1  6
#define RIGHT_M2  7

// ---- TOUCH SENSOR ----
#define TOUCH_PIN 14   // TTP223 (HIGH when touched)

// ---- OLED I2C ----
#define OLED_SDA  8
#define OLED_SCL  9

// ---- I2S AUDIO ----
#define I2S_BCLK  10
#define I2S_LRC   11
#define I2S_DOUT  13   // Speaker (MAX98357A)
#define I2S_DIN   12   // Mic (INMP441)

// ---- CAMERA (OV2640) ----
#define PWDN_GPIO_NUM    -1
#define RESET_GPIO_NUM   -1
#define XCLK_GPIO_NUM    15
#define SIOD_GPIO_NUM    16
#define SIOC_GPIO_NUM    17
#define Y9_GPIO_NUM      18
#define Y8_GPIO_NUM      19
#define Y7_GPIO_NUM      20
#define Y6_GPIO_NUM      21
#define Y5_GPIO_NUM      47
#define Y4_GPIO_NUM      48
#define Y3_GPIO_NUM      45
#define Y2_GPIO_NUM      46
#define VSYNC_GPIO_NUM   38
#define HREF_GPIO_NUM    39
#define PCLK_GPIO_NUM    40

/* ================= WIFI ================= */

const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASSWORD";
AsyncWebServer server(80);

/* ================= OLED ================= */

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

/* ================= EYES ================= */

void drawEyes(int mood) {
  display.clearDisplay();

  if (mood == 0) { // NORMAL
    display.fillCircle(40, 32, 8, SSD1306_WHITE);
    display.fillCircle(88, 32, 8, SSD1306_WHITE);
  }
  else if (mood == 1) { // HAPPY
    display.drawArc(30, 32, 12, 12, 200, 340, SSD1306_WHITE);
    display.drawArc(70, 32, 12, 12, 200, 340, SSD1306_WHITE);
  }
  else if (mood == 2) { // SLEEP
    display.drawLine(30, 32, 50, 32, SSD1306_WHITE);
    display.drawLine(78, 32, 98, 32, SSD1306_WHITE);
  }

  display.display();
}

/* ================= MOTOR CONTROL ================= */

void stopMotors() {
  digitalWrite(LEFT_M1, LOW);
  digitalWrite(LEFT_M2, LOW);
  digitalWrite(RIGHT_M1, LOW);
  digitalWrite(RIGHT_M2, LOW);
}

void moveForward() {
  digitalWrite(LEFT_M1, HIGH);
  digitalWrite(LEFT_M2, LOW);
  digitalWrite(RIGHT_M1, HIGH);
  digitalWrite(RIGHT_M2, LOW);
}

void moveLeft() {
  digitalWrite(LEFT_M1, LOW);
  digitalWrite(LEFT_M2, HIGH);
  digitalWrite(RIGHT_M1, HIGH);
  digitalWrite(RIGHT_M2, LOW);
}

/* ================= I2S AUDIO ================= */

void setupI2S() {
  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
    .sample_rate = 16000,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_I2S,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 8,
    .dma_buf_len = 256
  };

  i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_BCLK,
    .ws_io_num = I2S_LRC,
    .data_out_num = I2S_DOUT,
    .data_in_num = I2S_DIN
  };

  i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_NUM_0, &pin_config);
}

/* ================= PURR SOUND ================= */

void playPurr() {
  const int samples = 800;
  int16_t buffer[samples];

  for (int i = 0; i < samples; i++) {
    buffer[i] = 2500 * sin(2 * PI * 120 * i / 16000);
  }

  size_t bytes_written;
  i2s_write(I2S_NUM_0, buffer, sizeof(buffer), &bytes_written, portMAX_DELAY);
}

/* ================= CAMERA TASK (CORE 0) ================= */

void cameraTask(void *pv) {

  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  config.frame_size = FRAMESIZE_QVGA;
  config.jpeg_quality = 12;
  config.fb_count = 2;

  esp_camera_init(&config);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *req){
    req->send(200, "text/plain", "KIMO S3 Camera Running");
  });

  server.begin();
  vTaskDelete(NULL);
}

/* ================= CONTROL TASK (CORE 1) ================= */

void controlTask(void *pv) {
  while (true) {
    if (digitalRead(TOUCH_PIN)) {
      stopMotors();
      drawEyes(1);
      playPurr();
      delay(1000);
      drawEyes(0);
    }
    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}

/* ================= SETUP ================= */

void setup() {

  pinMode(LEFT_M1, OUTPUT);
  pinMode(LEFT_M2, OUTPUT);
  pinMode(RIGHT_M1, OUTPUT);
  pinMode(RIGHT_M2, OUTPUT);
  pinMode(TOUCH_PIN, INPUT);

  Wire.begin(OLED_SDA, OLED_SCL);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  drawEyes(0);

  setupI2S();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);

  xTaskCreatePinnedToCore(cameraTask, "Camera", 12000, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(controlTask, "Control", 6000, NULL, 1, NULL, 1);
}

void loop() {
  delay(1000);
}
