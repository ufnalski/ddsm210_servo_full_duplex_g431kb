# Direct drive servo motor DDSM210 from Waveshare (STM32G431KB)
An STM32 HAL example of communicating with DDSM210 - an in-wheel outer-rotor (AKA hub) PMSM drive with a full-duplex UART communication interface. It's a barebone example to be developed (hopefully by my trainees) into a fully-fledged library.

![Waveshare DDSM210 in action](/Assets/Images/ddsm210_in_action.jpg)

> [!WARNING]
> Be careful with colors: [/Assets/Images/](/Assets/Images/).

# Missing files?
Don't worry :slightly_smiling_face: Just hit Alt-K to generate /Drivers/CMCIS/ and /Drivers/STM32G4xx_HAL_Driver/ based on the .ioc file. After a couple of seconds your project will be ready for building.

# Hardware
* [DDSM210 Direct Drive Servo Motor, Low Speed & High Torque, Low Noise, Hub Motor](https://www.waveshare.com/ddsm210.htm) (Waveshare)

# Terminal
* [Tabby - a terminal for the modern age](https://tabby.sh/)

# Display (optional fun activities)
* [2inch LCD Module](https://www.waveshare.com/wiki/2inch_LCD_Module) (Waveshare)
* [ST7789-STM32](https://github.com/Floyd-Fish/ST7789-STM32) (Floydfish)
* [lcd-image-converter](https://sourceforge.net/projects/lcd-image-converter/) (riuson)
* [Bitmap Converter for emWin](https://www.segger.com/products/user-interface/emwin/tools/tools-overview/) (SEGGER)
* [Grand Theft Auto Font](https://fontmeme.com/grand-theft-auto-font/) (Font Meme)

# In-wheel drives (for electromobility aficionados)
Hub motors are prevalent in bicycles, scooters and skateboards. They are also more and more often regarded as viable alternatives for cars. A sip of history: 1900 Lohner-Porsche "Chaise" and "Mixte"[^1].
* [Protean Electric](https://www.proteanelectric.com/)
* [Elaphe](https://in-wheel.com/en/)
* [DeepDrive](https://www.deepdrive.tech/)
* [BMW Startup Chronicles: Testing a revolutionary e-drive with DeepDrive](https://www.youtube.com/watch?v=2YI1L5HJ2Xs) (BMW Startup Garage)

[^1]: [Lohner-Porsche](https://en.wikipedia.org/wiki/Lohner%E2%80%93Porsche) (Wikipedia)

# DDSM210 is marked as discontinued - what next? Go LIN bus[^2]!
* [DDSM400 Direct Drive Servo Motor, Wide Speed Range Adjustable, Hub Motor](https://www.waveshare.com/wiki/DDSM400) (Waveshare)

[^2]: [LIN bus demo using VW Golf VII / Audi A3 8V wiper actuator](https://github.com/ufnalski/lin_bus_golf7_wiper_actuator_g474re) - an example of LIN bus in automotive.

# Call for action
Create your own [home laboratory/workshop/garage](http://ufnalski.edu.pl/control_engineering_for_hobbyists/2024_dzien_otwarty_we/Dzien_Otwarty_WE_2024_Control_Engineering_for_Hobbyists.pdf)! Get inspired by [ControllersTech](https://www.youtube.com/@ControllersTech), [DroneBot Workshop](https://www.youtube.com/@Dronebotworkshop), [Andreas Spiess](https://www.youtube.com/@AndreasSpiess), [GreatScott!](https://www.youtube.com/@greatscottlab), [ElectroBOOM](https://www.youtube.com/@ElectroBOOM), [Phil's Lab](https://www.youtube.com/@PhilsLab), [atomic14](https://www.youtube.com/@atomic14), [That Project](https://www.youtube.com/@ThatProject), [Paul McWhorter](https://www.youtube.com/@paulmcwhorter), [RS Elektronika](https://www.youtube.com/@RSElektronika), and many other professional hobbyists sharing their awesome projects and tutorials! Shout-out/kudos to all of them!

> [!WARNING]
> Control in power electronics and drives - do try this at home :exclamation:

190+ challenges to start from: [Control Engineering for Hobbyists at the Warsaw University of Technology](http://ufnalski.edu.pl/control_engineering_for_hobbyists/Control_Engineering_for_Hobbyists_list_of_challenges.pdf).

Initial commit date: :three::one:.:one::two:.:two::zero::two::four:.

Let's make :two::zero::two::five: a year of sharing, collaboration, and innovation:grey_exclamation: Happy New Year:grey_exclamation:
