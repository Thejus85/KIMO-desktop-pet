/****************************************************
   KIMO S3 - FULL CUTE ROBOT CODE
   Board: ESP32-S3 Dev Module (OPI PSRAM enabled)

   Features:
   - DRV8833 motors
   - TTP223 touch sensor
   - SSD1306 OLED (eyes)
   - MAX98357A I2S speaker
   - Cute "HELLO~" voice on touch
****************************************************/

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "driver/i2s.h"
#include <math.h>

/* ================= PIN DEFINITIONS ================= */

// ---- MOTORS (DRV8833) ----
#define LEFT_M1   4
#define LEFT_M2   5
#define RIGHT_M1  6
#define RIGHT_M2  7

// ---- TOUCH SENSOR ----
#define TOUCH_PIN 14   // TTP223 (ACTIVE HIGH)

// ---- OLED I2C ----
#define OLED_SDA  8
#define OLED_SCL  9

// ---- I2S AUDIO (MAX98357A) ----
#define I2S_BCLK  10
#define I2S_LRC   11
#define I2S_DOUT  13

/* ================= OLED SETUP ================= */

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

/* ================= EYES ================= */

void drawEyes(uint8_t mood) {
  display.clearDisplay();

  if (mood == 0) {             // NORMAL
    display.fillCircle(40, 32, 8, SSD1306_WHITE);
    display.fillCircle(88, 32, 8, SSD1306_WHITE);
  }
  else if (mood == 1) {        // HAPPY
    display.drawArc(28, 32, 14, 14, 200, 340, SSD1306_WHITE);
    display.drawArc(72, 32, 14, 14, 200, 340, SSD1306_WHITE);
  }
  else if (mood == 2) {        // SLEEP
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

/* ================= I2S AUDIO SETUP ================= */

void setupI2S() {
  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
    .sample_rate = 16000,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_I2S,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 8,
    .dma_buf_len = 256,
    .use_apll = false,
    .tx_desc_auto_clear = true,
    .fixed_mclk = 0
  };

  i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_BCLK,
    .ws_io_num = I2S_LRC,
    .data_out_num = I2S_DOUT,
    .data_in_num = -1
  };

  i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_NUM_0, &pin_config);
}

/* ================= CUTE HELLO VOICE ================= */

void playCuteHello() {
  const int sampleRate = 16000;
  const int samples = 320;
  int16_t buffer[samples];
  size_t written;

  // ----- "Hee~" -----
  for (int i = 0; i < samples; i++) {
    float freq = 500 + i * 1.3;
    buffer[i] = 2500 * sin(2 * PI * freq * i / sampleRate);
  }
  i2s_write(I2S_NUM_0, buffer, sizeof(buffer), &written, portMAX_DELAY);

  delay(80);

  // ----- "Loo~" -----
  for (int i = 0; i < samples; i++) {
    float freq = 420 - i * 0.6;
    buffer[i] = 2300 * sin(2 * PI * freq * i / sampleRate);
  }
  i2s_write(I2S_NUM_0, buffer, sizeof(buffer), &written, portMAX_DELAY);
}

/* ================= SETUP ================= */

void setup() {

  // Motor pins
  pinMode(LEFT_M1, OUTPUT);
  pinMode(LEFT_M2, OUTPUT);
  pinMode(RIGHT_M1, OUTPUT);
  pinMode(RIGHT_M2, OUTPUT);

  // Touch pin
  pinMode(TOUCH_PIN, INPUT);

  // OLED
  Wire.begin(OLED_SDA, OLED_SCL);
  display.begin(SSD1306_SWITCHCAPVCC, 0x_
