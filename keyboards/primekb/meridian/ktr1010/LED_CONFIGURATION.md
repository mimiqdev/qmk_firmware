# Meridian KTR1010 LED Configuration Guide

## Overview

The Meridian keyboard with KTR1010 LEDs features **three RGB indicator LEDs** located on the top right of the keyboard. These LEDs can be configured to show various keyboard states, layer information, or custom effects.

## Default LED Behavior

By default, the three LEDs are configured as lock key indicators:

| LED Position | Index | Default Function | Color | Triggered By |
|--------------|-------|------------------|-------|--------------|
| **Top** | 0 | Caps Lock Indicator | Green | Caps Lock key |
| **Middle** | 1 | Num Lock Indicator | Blue | Num Lock key |
| **Bottom** | 2 | Scroll Lock Indicator | Red | Scroll Lock key |

When a lock key is inactive, its corresponding LED turns off completely.

## LED Configuration

### Understanding LED Control

The three LEDs are controlled using QMK's `rgblight` API. Each LED can display any RGB color (0-255 for each channel).

**LED Indices:**
- `0` = Top LED
- `1` = Middle LED  
- `2` = Bottom LED

**Setting LED Colors:**
```c
rgblight_setrgb_at(red, green, blue, index);
```

Where:
- `red`, `green`, `blue` are values from 0-255
- `index` is the LED number (0, 1, or 2)

### Common Color Values

| Color | R | G | B |
|-------|---|---|---|
| Red | 255 | 0 | 0 |
| Green | 0 | 255 | 0 |
| Blue | 0 | 0 | 255 |
| Yellow | 255 | 255 | 0 |
| Cyan | 0 | 255 | 255 |
| Magenta | 255 | 0 | 255 |
| White | 255 | 255 | 255 |
| Orange | 255 | 128 | 0 |
| Purple | 128 | 0 | 255 |
| Off | 0 | 0 | 0 |

## Customization Examples

### Example 1: Change Lock Indicator Colors

To change the default lock indicator colors, edit `meridian.c`:

```c
bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        if (led_state.caps_lock) {
            rgblight_setrgb_at(255, 0, 255, 0); // Magenta instead of green
        } else {
            rgblight_setrgb_at(0, 0, 0, 0);
        }
        if (led_state.num_lock) {
            rgblight_setrgb_at(255, 255, 0, 1); // Yellow instead of blue
        } else {
            rgblight_setrgb_at(0, 0, 0, 1);
        }
        if (led_state.scroll_lock) {
            rgblight_setrgb_at(0, 255, 255, 2); // Cyan instead of red
        } else {
            rgblight_setrgb_at(0, 0, 0, 2);
        }
    }
    return res;
}
```

### Example 2: Layer Indicators

To use LEDs for layer indication instead of lock keys, add this to your `keymap.c`:

```c
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case 0:  // Base layer
            rgblight_setrgb_at(0, 0, 0, 2);     // Bottom LED off
            break;
        case 1:  // Function layer
            rgblight_setrgb_at(255, 0, 0, 2);   // Bottom LED red
            break;
        case 2:  // Second function layer
            rgblight_setrgb_at(0, 0, 255, 2);   // Bottom LED blue
            break;
        case 3:  // Third layer
            rgblight_setrgb_at(0, 255, 0, 2);   // Bottom LED green
            break;
    }
    return state;
}
```

### Example 3: Multiple LED Layer Indicators

Use all three LEDs to show different layer states:

```c
layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t layer = get_highest_layer(state);
    
    // Top LED shows if on layer 1+
    if (layer >= 1) {
        rgblight_setrgb_at(255, 0, 0, 0);  // Red
    } else {
        rgblight_setrgb_at(0, 0, 0, 0);    // Off
    }
    
    // Middle LED shows if on layer 2+
    if (layer >= 2) {
        rgblight_setrgb_at(255, 255, 0, 1);  // Yellow
    } else {
        rgblight_setrgb_at(0, 0, 0, 1);      // Off
    }
    
    // Bottom LED shows if on layer 3+
    if (layer >= 3) {
        rgblight_setrgb_at(0, 255, 0, 2);  // Green
    } else {
        rgblight_setrgb_at(0, 0, 0, 2);    // Off
    }
    
    return state;
}
```

### Example 4: Combining Lock Keys and Layer Indicators

You can use different LEDs for different purposes:

```c
// In keymap.c - Use bottom LED for layers
layer_state_t layer_state_set_user(layer_state_t state) {
    if (get_highest_layer(state) == 1) {
        rgblight_setrgb_at(255, 0, 0, 2);   // Bottom LED red on layer 1
    } else {
        rgblight_setrgb_at(0, 0, 0, 2);     // Off on base layer
    }
    return state;
}

// Keep top and middle LEDs for Caps/Num Lock (default behavior)
```

### Example 5: Custom Startup Animation

Initialize LEDs with a specific pattern at startup:

```c
void keyboard_post_init_user(void) {
    // Flash all LEDs white briefly
    rgblight_setrgb_at(255, 255, 255, 0);
    rgblight_setrgb_at(255, 255, 255, 1);
    rgblight_setrgb_at(255, 255, 255, 2);
    wait_ms(200);
    
    // Turn all off
    rgblight_setrgb_at(0, 0, 0, 0);
    rgblight_setrgb_at(0, 0, 0, 1);
    rgblight_setrgb_at(0, 0, 0, 2);
}
```

## Creating a Custom Keymap

To create your own LED configuration:

1. **Copy the default keymap:**
   ```bash
   cd keyboards/primekb/meridian/keymaps
   cp -r default my_config
   ```

2. **Edit the keymap.c file:**
   ```bash
   nano my_config/keymap.c
   ```

3. **Add your LED functions** (examples above) to the file

4. **Compile and flash:**
   ```bash
   make primekb/meridian/ktr1010:my_config:flash
   ```

## Disabling Lock Key Indicators

If you want to disable the default lock key indicators to use LEDs for other purposes, you need to modify `meridian.c` or override `led_update_user()` in your keymap:

```c
// In your keymap.c
bool led_update_user(led_t led_state) {
    // Return false to prevent default LED behavior
    return false;
}
```

## Technical Details

### LED Hardware
- **LED Type:** KTR1010 RGB LEDs
- **Count:** 3 LEDs
- **Data Pin:** B15
- **Driver:** WS2812 protocol (with custom timing)

### Special Timing
The KTR1010 LEDs use custom WS2812 timing parameters (defined in `config.h`):
- `WS2812_TIMING`: 1325
- `WS2812_T0H`: 350
- `WS2812_T1H`: 975
- `WS2812_T0L`: 975
- `WS2812_T1L`: 350

These settings ensure proper communication with the KTR1010 LEDs.

## Troubleshooting

### LEDs Not Working
1. Verify you compiled for the correct variant: `ktr1010` (not `ws2812`)
2. Check that rgblight is enabled in your keymap's `rules.mk` (enabled by default)

### LEDs Show Wrong Colors
- Make sure you're using the correct LED index (0, 1, or 2)
- Verify RGB values are in range 0-255

### LEDs Flicker
- This may indicate timing issues; the default config should work for KTR1010 LEDs

## Additional Resources

- [QMK RGB Lighting Documentation](https://docs.qmk.fm/#/feature_rgblight)
- [QMK Layer Documentation](https://docs.qmk.fm/#/feature_layers)
- [Meridian Main README](../readme.md)

## Questions?

For more help with customization, check the [QMK Discord](https://discord.gg/qmk) or [QMK Reddit](https://reddit.com/r/olkb).
