# x1_carbon_gen10

![x1_carbon_gen10](imgur.com image replace me!)

*A short description of the keyboard/project*

* Keyboard Maintainer: [C. Scott Ananian](https://github.com/cscott)
* Hardware Supported: *The PCBs, controllers supported*
* Hardware Availability: *Links to where you can find this hardware*

Make example for this keyboard (after setting up your build environment):

    make x1_carbon_gen10:default

Flashing example for this keyboard:

    make x1_carbon_gen10:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the Fn key and plug in the keyboard.
* **Physical reset button**: short the pad labeled BOOT to ground
  when powering up the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
  (Currently: Fn-F12.)
