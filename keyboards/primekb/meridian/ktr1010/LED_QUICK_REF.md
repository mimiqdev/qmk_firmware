# KTR1010 LED Quick Reference

## Three RGB LEDs on Top Right

### Default Behavior (Out of Box)
| LED | Function | Color | Trigger |
|-----|----------|-------|---------|
| Top (0) | Caps Lock | Green | Caps Lock key |
| Middle (1) | Num Lock | Blue | Num Lock key |
| Bottom (2) | Scroll Lock | Red | Scroll Lock key |

### LED Control Function
```c
rgblight_setrgb_at(red, green, blue, index);
```
- `red`, `green`, `blue`: 0-255
- `index`: 0 (top), 1 (middle), 2 (bottom)

### Quick Color Reference
```c
// Common colors (R, G, B)
Red:     (255, 0, 0)
Green:   (0, 255, 0)
Blue:    (0, 0, 255)
Yellow:  (255, 255, 0)
Cyan:    (0, 255, 255)
Magenta: (255, 0, 255)
White:   (255, 255, 255)
Orange:  (255, 128, 0)
Purple:  (128, 0, 255)
Off:     (0, 0, 0)
```

### Example: Layer Indicator on Bottom LED
```c
layer_state_t layer_state_set_user(layer_state_t state) {
    if (get_highest_layer(state) == 1) {
        rgblight_setrgb_at(255, 0, 0, 2);  // Red
    } else {
        rgblight_setrgb_at(0, 0, 0, 2);    // Off
    }
    return state;
}
```

## Full Documentation
See [LED_CONFIGURATION.md](LED_CONFIGURATION.md) for complete guide with examples.

## Example Keymap
See `keymaps/led_example/` for a working example with custom LED configuration.
