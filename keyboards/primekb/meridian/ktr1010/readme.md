# Meridian KTR1010 Variant

This is the KTR1010 LED variant of the Meridian keyboard.

## Key Features

- **RGB LEDs:** 3 programmable RGB indicator LEDs on the top right
- **LED Driver:** KTR1010 LEDs (WS2812 protocol with custom timing)
- **Default Configuration:** Lock key indicators (Caps/Num/Scroll Lock)

## Documentation

- **[LED Configuration Guide](LED_CONFIGURATION.md)** - Complete guide to configuring the three RGB LEDs
- **[LED Quick Reference](LED_QUICK_REF.md)** - Quick reference for common LED operations
- **[Example Keymap](../keymaps/led_example/)** - Working example with custom LED configuration

## Building Firmware

Compile for this variant:
```bash
make primekb/meridian/ktr1010:default
```

Compile and flash:
```bash
make primekb/meridian/ktr1010:default:flash
```

With custom keymap:
```bash
make primekb/meridian/ktr1010:your_keymap_name:flash
```

## LED Configuration at a Glance

The three LEDs (top to bottom) are controlled by index:
- **LED 0** (top): Default = Caps Lock (green)
- **LED 1** (middle): Default = Num Lock (blue)
- **LED 2** (bottom): Default = Scroll Lock (red)

You can customize these in your keymap! See the documentation above for examples.

## More Information

See the [main Meridian README](../readme.md) for general keyboard information.
