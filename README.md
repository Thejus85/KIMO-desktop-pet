# 🤖 KIMO — Desktop Pet Robot (ESP32-S3-CAM)

---

## 📌 Project Overview

**KIMO** is a compact **desktop pet robot** powered by an **ESP32-S3-CAM**. It lives beside a laptop or workspace and behaves like a small, expressive robotic companion. KIMO reacts to touch, produces cute sounds, performs friendly movements, and creates the feeling of a tiny living system on your desk.

This document explains the **project design, behavior, hardware, and software concepts** only.

> 📎 **Assembly instructions are provided separately in [`assemble.md`]** for step-by-step build guidance.

---

## 🧠 Concept

KIMO is built around the idea that even simple embedded systems can feel expressive.

The design focuses on:

* Physical interaction
* Motion-based expression
* Simple sound feedback
* Predictable, friendly behavior

---

## ✨ Core Features

### 🫳 Touch Interaction

* Touch detected using a sensor or tactile input
* Immediate response when touched
* Reactions scale with interaction frequency

### 🔊 Sound Responses

* Short, playful sound effects
* Simple greeting-style audio
* Sound synchronized with motion

### 🦾 Motion & Gestures

* Servo-driven movement
* Friendly gestures such as nodding and tilting
* Smooth motion suitable for a desk environment

### 💤 Idle Behavior

* Subtle idle animations
* Occasional autonomous movement
* Prevents inactive or static behavior

---

## 🧩 System Architecture

KIMO uses a **state-based embedded architecture** running entirely on the ESP32-S3-CAM.

### Main Loop Flow

1. Read touch input
2. Determine current state
3. Trigger motion and/or sound
4. Return to idle state

This loop repeats continuously.

---

## 🛠 Hardware Platform

### Primary Controller

* **ESP32-S3-CAM**

  * Dual-core MCU
  * Sufficient GPIO for sensors and servos
  * Compact form factor
  * USB programming and power

### Additional Components

* Touch sensor or tactile switch
* Micro servo motor(s)
* Small speaker or buzzer
* Power source (USB / regulated battery)
* Frame or enclosure

---

## 🔌 Electrical Design

* Low-voltage operation
* Shared ground across components
* Servo powered through regulated supply
* Clean pin assignment for reliability

The wiring is designed to stay minimal and easy to troubleshoot.

---

## 🧠 Software Design

### Firmware Structure

* Board initialization (ESP32-S3-CAM)
* Pin configuration
* Sensor polling logic
* Motion control functions
* Sound playback functions
* State machine logic

The firmware is modular so behaviors can be expanded easily.

---

## 🎭 Personality Design

KIMO’s personality is defined by:

* Calm idle behavior
* Friendly reaction sounds
* Smooth, non-aggressive motion
* Fast response to touch

The goal is expression without distraction.

---

## 📐 Mechanical Design

* Desk-sized footprint
* Stable base
* Lightweight structure
* Simple mounting for ESP32-S3-CAM

---

## 🧪 Interaction Examples

* Touch → sound + motion
* Multiple touches → excited reaction
* No interaction → idle animation

---

## 📘 What This Project Demonstrates

* ESP32-S3 embedded programming
* Sensor-to-actuator control loops
* Real-time interaction handling
* Hardware–software integration
* Expressive robotics design

---

## 🧭 Design Scope

* Runs completely on-device
* No external control required
* Focused on touch, sound, and motion
* Intended for safe desktop use

---

## 📂 Build Guide

For **step-by-step physical assembly, wiring, and mounting**, see:

➡️ **`assemble.md`**

---

## ✅ Summary

KIMO is a desktop pet robot built using an ESP32-S3-CAM that transforms simple hardware into an expressive, interactive companion through motion, sound, and touch-based behavior.
