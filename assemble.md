# 🔧 KIMO Desktop Pet — Assembly Guide 

---

## 📦 Overview

This document explains **how to physically assemble KIMO**, including mounting the ESP32-S3-CAM, connecting components, and preparing the robot for programming.

Follow the steps in order.

---

## 🧰 Required Components

* ESP32-S3-CAM board
* USB cable (data + power)
* Micro servo motor(s)
* Touch sensor or tactile switch
* Small speaker or buzzer
* Jumper wires
* Base frame or enclosure
* Screws / glue / mounting tape

---

## 📐 Step 1: Prepare the Base

1. Place the base on a flat surface
2. Ensure the base is stable and does not wobble
3. Identify mounting positions for:

   * ESP32-S3-CAM
   * Servo motor(s)
   * Speaker

---

## 🧠 Step 2: Mount the ESP32-S3-CAM

1. Place the ESP32-S3-CAM securely on the base
2. Ensure:

   * USB port is accessible
   * GPIO pins are not shorted
   * Board is firmly fixed
3. Use screws or non-conductive adhesive

---

## 🦾 Step 3: Install the Servo Motor

1. Attach the servo motor to the frame
2. Ensure the servo horn can move freely
3. Do not block the servo range of motion

---

## 🫳 Step 4: Install the Touch Sensor

1. Mount the touch sensor on an outer surface
2. Position it where users naturally touch
3. Secure it firmly to avoid false triggers

---

## 🔊 Step 5: Mount the Speaker / Buzzer

1. Place the speaker facing outward
2. Do not cover the sound opening
3. Secure using tape or enclosure slots

---

## 🔌 Step 6: Wiring

### Common Rules

* Always connect **GND** to a common ground
* Double-check polarity before powering

### Typical Connections

* Touch Sensor → ESP32-S3 GPIO + GND
* Servo Signal → ESP32-S3 GPIO
* Servo Power → Regulated 5V
* Speaker Signal → ESP32-S3 GPIO

(Exact pin numbers depend on firmware configuration.)

---

## ⚡ Step 7: Power Check

1. Power the ESP32-S3-CAM via USB
2. Ensure:

   * Board powers on
   * No component heats up
   * No loose connections

---

## 🧪 Step 8: Initial Movement Test

1. Upload basic servo test firmware
2. Confirm servo moves smoothly
3. Test touch input response
4. Test sound output

---

## 🧷 Step 9: Cable Management

* Keep wires short
* Secure loose cables
* Avoid tension on GPIO pins

---

## ✅ Assembly Complete

Once assembled:

* The robot should sit firmly on the desk
* All components should be secured
* USB connection should remain accessible

At this point, KIMO is ready for **full firmware flashing and behavior tuning**.
