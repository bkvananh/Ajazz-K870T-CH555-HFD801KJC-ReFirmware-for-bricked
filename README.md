## Ajazz K870T Custom/Restoration Firmware (CH555 / HFD801KJC)

> A minimal, custom open-source firmware designed to unbrick and restore basic functionality for the **Ajazz K870T** mechanical keyboard featuring the **HFD801KJC** MCU.

---

## 📖 Background & The "Brick" Story

The **Ajazz K870T** mechanical keyboard was manufactured with at least two distinct MCU revisions:
1. **HFD2201KBA** (Sonix clone)
2. **HFD801KJC** (Older batch, clone of WCH CH555 / 8051 architecture)

Due to conflicting firmware revisions distributed online, many users accidentally flashed firmware intended for the Sonix variant onto the CH555 variant (or vice versa), completely bricking their keyboards. 

Attempting to recover the keyboard using official channels proved difficult—Ajazz appears to have removed the legacy firmware files from their official website due to high return/brick rates. 

* **For HFD2201KBA (Sonix) Users:** You are in luck! Check out the [SonixQMK](https://github.com/SonixQMK) project. Furthermore, HFD2201KBA shares firmware compatibility with the *Rakk Lam-ang Pro* (which uses the VS11K09A-1 chip).
* **For HFD801KJC (CH555) Users:** Standard QMK for 8051 ports are overly complex, requiring extensive GPIO remapping and low-level adjustments. 

### How This Firmware Was Created
Using base EVT examples provided in [HorrorTroll/WCH_CH555](https://github.com/HorrorTroll/WCH_CH555), a lightweight recovery firmware was developed with the assistance of LLMs (Gemini / Claude). It is compiled using **Keil µVision5** and flashed via **WCHISPStudio**. (Pardon the experimental "vibe code", but it successfully revives dead boards!)

---

## ⚡ Features & Current Status

### Working Features
* ✅ **Core Restoration:** Unbricks the keyboard and restores basic typing capabilities via USB connection.
* ✅ **RGB Backlighting:** Basic rainbow dynamic lighting effect.
* ✅ **Fn Key Handling:** Disabled/turned off the LED on the original Fn key slot.

### Known Limitations & Bugs
* ⚠️ **Non-functional Keys:** `PgUp` and `PgDn` keys are currently non-responsive (PRs/contributions welcomed!).
* ⚠️ Single lighting mode (no dynamic effect switching yet).
* ⚠️ LED effects can occasionally jitter or misbehave.
* ⚠️ No FN key / Layer support.
* ⚠️ No Bluetooth support (USB Wired only).
* ⚠️ No QMK / VIA support.

---

## 🛠️ Requirements & Tools

* **IDE / Compiler:** [Keil µVision5](https://www.keil.com/) (MDK-ARM or C51 depending on setup; free evaluation mode works under 2KB limit).
* **Flashing Utility:** [WCHISPStudio](http://www.wch-ic.com/downloads/WCHISPTool_Setup_exe.html) (WCH In-System Programming Tool).

---

## 🚀 How to Build & Flash

### 1. Download / Clone
Clone or download this repository to your local computer.

### 2. Compile (Optional)
*Note: A pre-compiled binary (`K870T.hex`) is already provided inside `K870T_CH555_ReFirmware/Objects/`. You only need to compile if you plan to modify keymaps or add features.*

1. Open **Keil µVision5**.
2. Go to `Project` > `Open Project...` and select `K870T.uvproj` in the root folder.
3. Press `F7` to build the project.
4. The output binary will be generated at:
K870T_CH555_ReFirmware/Objects/K870T.hex


### 3. Flashing Process
1. Launch **WCHISPStudio**.
2. **Enter Bootloader Mode:**
- Locate the `BOOT` jumper/test pads on the K870T PCB (located to the **left of the Spacebar switch**).
- Short the `BOOT` pads (using tweezers or a conductive jumper cable) **while plugging in the USB cable** to your PC.
3. Verify that **WCHISPStudio** detects the device as a **CH555** chip.
4. In the software:
- Under **Object File 1**, click the `...` button and navigate to `K870T.hex`.
- ⚠️ **Crucial Step:** **UNCHECK** the option `Enable P7.1 as manual reset input pin`. *(This prevents accidental triggers/resets during key presses).*
5. Click **Download / Program**.
6. Upon successful completion, you will hear the USB disconnect sound, followed by the RGB lights powering up. Your keyboard is now restored!

---

## 🤝 Contributing & Help Wanted

If you have experience with 8051 assembly/C or GPIO pin mapping for the CH555/HFD801KJC controller, feel free to open a Pull Request! Specifically, help is needed to:
* Fix the `PgUp` and `PgDn` key matrix mapping.
* Implement proper Fn layers and secondary key functions.
* Add selectable RGB backlight modes.

---

## 📜 Acknowledgments & License

* Base EVT code courtesy of [HorrorTroll/WCH_CH555](https://github.com/HorrorTroll/WCH_CH555).
* Created solely for educational, recovery, and **non-commercial** purposes.
"""

with open("README.md", "w", encoding="utf-8") as f:
 f.write(readme_content)

print("README.md created successfully.")
'''

# Execute python code to produce file
from google:ds_python_interpreter import execute_python
execute_python(code=code)
```Wait while I generate the file...Your Markdown file is ready
[file-tag: code-generated-file-a521ce3323]

---

Dưới đây là toàn bộ nội dung của file **`README.md`** được viết bằng tiếng Anh chuẩn chuẩn phong cách GitHub (dùng Markdown đẹp mắt, cấu trúc rõ ràng, chuyên nghiệp nhưng vẫn giữ đúng tinh thần và các chi tiết kỹ thuật bạn đưa ra):

```markdown
# Ajazz K870T Custom/Restoration Firmware (CH555 / HFD801KJC)

> A minimal, custom open-source firmware designed to unbrick and restore basic functionality for the **Ajazz K870T** mechanical keyboard featuring the **HFD801KJC** MCU.

---

## 📖 Background & The "Brick" Story

The **Ajazz K870T** mechanical keyboard was manufactured with at least two distinct MCU revisions:
1. **HFD2201KBA** (Sonix clone)
2. **HFD801KJC** (Older batch, clone of WCH CH555 / 8051 architecture)

Due to conflicting firmware revisions distributed online, many users accidentally flashed firmware intended for the Sonix variant onto the CH555 variant (or vice versa), completely bricking their keyboards. 

Attempting to recover the keyboard using official channels proved difficult—Ajazz appears to have removed the legacy firmware files from their official website due to high return/brick rates. 

* **For HFD2201KBA (Sonix) Users:** You are in luck! Check out the [SonixQMK](https://github.com/SonixQMK) project. Furthermore, HFD2201KBA shares firmware compatibility with the *Rakk Lam-ang Pro* (which uses the VS11K09A-1 chip).
* **For HFD801KJC (CH555) Users:** Standard QMK 8051 ports are overly complex, requiring extensive GPIO remapping and low-level adjustments. 

### How This Firmware Was Created
Using base EVT examples provided in [HorrorTroll/WCH_CH555](https://github.com/HorrorTroll/WCH_CH555), a lightweight recovery firmware was developed with the assistance of LLMs (Gemini / Claude). It is compiled using **Keil µVision5** and flashed via **WCHISPStudio**. (Pardon the experimental "vibe code", but it successfully revives dead boards!)

---

## ⚡ Features & Current Status

### Working Features
* ✅ **Core Restoration:** Unbricks the keyboard and restores basic typing capabilities via USB connection.
* ✅ **RGB Backlighting:** Basic rainbow dynamic lighting effect.
* ✅ **Fn Key Handling:** Disabled/turned off the LED on the original Fn key slot.

### Known Limitations & Bugs
* ⚠️ **Non-functional Keys:** `PgUp` and `PgDn` keys are currently non-responsive (PRs/contributions welcomed!).
* ⚠️ Single lighting mode (no dynamic effect switching yet).
* ⚠️ LED effects can occasionally jitter or misbehave.
* ⚠️ No FN key / Layer support.
* ⚠️ No Bluetooth support (USB Wired only).
* ⚠️ No QMK / VIA support.

---

## 🛠️ Requirements & Tools

* **IDE / Compiler:** [Keil µVision5](https://www.keil.com/) (MDK-ARM or C51 depending on setup; free evaluation mode works under 2KB limit).
* **Flashing Utility:** [WCHISPStudio](http://www.wch-ic.com/downloads/WCHISPTool_Setup_exe.html) (WCH In-System Programming Tool).

---

## 🚀 How to Build & Flash

### 1. Download / Clone
Clone or download this repository to your local computer.

### 2. Compile (Optional)
*Note: A pre-compiled binary (`K870T.hex`) is already provided inside `K870T_CH555_ReFirmware/Objects/`. You only need to compile if you plan to modify keymaps or add features.*

1. Open **Keil µVision5**.
2. Go to `Project` > `Open Project...` and select `K870T.uvproj` in the root folder.
3. Press `F7` to build the project.
4. The output binary will be generated at:
K870T_CH555_ReFirmware/Objects/K870T.hex


### 3. Flashing Process
1. Launch **WCHISPStudio**.
2. **Enter Bootloader Mode:**
- Locate the `BOOT` jumper/test pads on the K870T PCB (located to the **left of the Spacebar switch**).
- Short the `BOOT` pads (using tweezers or a conductive jumper cable) **while plugging in the USB cable** to your PC.
3. Verify that **WCHISPStudio** detects the device as a **CH555** chip.
4. In the software:
- Under **Object File 1**, click the `...` button and navigate to `K870T.hex`.
- ⚠️ **Crucial Step:** **UNCHECK** the option `Enable P7.1 as manual reset input pin`. *(This prevents accidental triggers/resets during key presses).*
5. Click **Download / Program**.
6. Upon successful completion, you will hear the USB disconnect sound, followed by the RGB lights powering up. Your keyboard is now restored!

---

## 🤝 Contributing & Help Wanted

If you have experience with 8051 assembly/C or GPIO pin mapping for the CH555/HFD801KJC controller, feel free to open a Pull Request! Specifically, help is needed to:
* Fix the `PgUp` and `PgDn` key matrix mapping.
* Implement proper Fn layers and secondary key functions.
* Add selectable RGB backlight modes.

---

## 📜 Acknowledgments & License

* Base EVT code courtesy of [HorrorTroll/WCH_CH555](https://github.com/HorrorTroll/WCH_CH555).
* Created solely for educational, recovery, and **non-commercial** purposes.
