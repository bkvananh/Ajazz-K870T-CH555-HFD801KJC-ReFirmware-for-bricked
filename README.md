# Ajazz K870T Recovery Firmware (CH555 / HFD801KJC)

![Ajazz K870T](/image/B0D48CE3-C793-4D5A-9094-87E7643CCC86.jpeg)
Minimal open-source firmware for restoring and reviving the **Ajazz K870T** equipped with the **HFD801KJC** microcontroller (WCH CH555 compatible).

---

## Table of Contents

* Overview
* Hardware Variants
* Why This Project Exists
* Current Status
* Requirements
* Building
* Flashing
* Contributing
* Credits

---

# Overview

The Ajazz K870T exists in multiple hardware revisions that are **not firmware compatible**.

| MCU        | Architecture           | Status                    |
| ---------- | ---------------------- | ------------------------- |
| HFD2201KBA | Sonix compatible       | Supported by SonixQMK     |
| HFD801KJC  | WCH CH555 (8051) clone | Supported by this project |

Using firmware intended for the wrong MCU permanently disables normal USB operation, leaving the keyboard accessible only through the bootloader.

This project provides a lightweight firmware capable of restoring basic USB functionality for the **CH555/HFD801KJC** version.

---

# Hardware Variants

## HFD801KJC (CH555)
![HFD801KJC](/image/IMG_0594.jpeg)

Older production batches use the **HFD801KJC**, an MCU compatible with the WCH CH555 (8051 architecture).

---

## HFD2201KBA (Sonix)

Users with the Sonix version should use the excellent **[SonixQMK](https://github.com/SonixQMK)** project instead.

The HFD2201KBA variant is also firmware-compatible with the **RAKK Lam-Ang Pro (VS11K09A-1)**.

RAKK Lam-Ang Pro (Sonix)

The CH555 version of the RAKK keyboard uses different hardware.

RAKK Lam-Ang Pro (CH555)
<p align="center">
  <img src="/image/rakk@Xelus.jpg" width="45%">
  <img src="/image/rakk@Jikeneu.jpg" width="45%">
</p>

<p align="center">
  <em>RAKK Lam-Ang Pro (Sonix) &nbsp;&nbsp;&nbsp;&nbsp; RAKK Lam-Ang Pro (CH555)</em>
</p>

---

# Why This Project Exists

Official firmware for the CH555 version has become increasingly difficult to obtain, and many archived firmware packages available online target the wrong hardware revision.

Flashing Sonix firmware onto the CH555 model (or vice versa) results in a non-functional keyboard that only enters the bootloader.

This firmware was created to provide a simple recovery solution rather than a full QMK replacement.

Development started from the EVT examples in **[HorrorTroll/WCH_CH555](https://github.com/HorrorTroll/WCH_CH555)** and was gradually adapted for the K870T hardware.

---

# Current Status

## Implemented

* USB keyboard functionality
* Basic key matrix scanning
* RGB backlight (4 modes/change or turn of by Original Bluetooth button)
* Keyboard recovery from bootloader


## Not Yet Implemented

* Function layers (Fn)
* Bluetooth mode
* VIA / Vial support
* QMK compatibility
* NKRO

## Known Issues

* RGB animations may occasionally flicker.
* LED timing still requires refinement.

---

# Requirements

| Tool          | Purpose        |
| ------------- | -------------- |
| **[Keil µVision5](https://www.keil.com/)** | Build firmware |
| **[WCHISPStudio](http://www.wch-ic.com/downloads/WCHISPTool_Setup_exe.html)**  | Flash firmware |

> **Note**
>
> The free Keil C51 edition is limited to **2 KB** of generated code.
> This project currently exceeds that size, so a valid license is required for building modified firmware.
>
> Silicon Labs provides free PK51 licenses for eligible users:
> https://www.silabs.com/software-and-tools/keil-pk51
>
> A precompiled `K870T.hex` is already included if you only need to recover your keyboard.

---

# Building

Open the project with **Keil µVision5**.

```
Project
└── Open Project...
```

Select:

```
K870T.uvproj
```

Build using **F7**.

The generated firmware will be located at:

```
K870T_CH555_ReFirmware/Objects/K870T.hex
```

---

# Flashing

## Enter Bootloader

Locate the **BOOT** pads on the PCB.

<p align="center">
  <img src="/image/IMG_0593.jpeg" width="48%">
  <img src="/image/IMG_0594.jpeg" width="48%">
</p>

They are positioned to the **left of the Spacebar switch**.

Short the pads while connecting the USB cable.

---

## Program the Firmware

Open **WCHISPStudio**.

1. Verify the device is detected as **CH555**.
2. Load `K870T.hex`.
3. Disable:

```
Enable P7.1 as manual reset input pin
```

4. Click **Download / Program**.

After programming completes, the USB device reconnects automatically and the RGB lighting should turn on.

---

# PCB

---

# Contributing

Contributions are welcome.

Areas that would benefit the most include:

* Fn layer implementation
* GPIO cleanup
* RGB improvements
* USB optimization
* VIA/Vial compatibility
* Documentation

Pull requests, issue reports, and hardware information are appreciated.

---

## Credits

This project is based on the CH555 EVT examples from **[HorrorTroll/WCH_CH555](https://github.com/HorrorTroll/WCH_CH555)**.

It is intended solely for educational purposes and for recovering otherwise unusable keyboards.

Commercial use is not intended.
