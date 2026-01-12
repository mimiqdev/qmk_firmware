# LED Example Keymap

This keymap demonstrates how to customize the three RGB indicator LEDs on the Meridian keyboard.

## LED Configuration

This example shows:

1. **Top LED (index 0)**: Caps Lock indicator with **Magenta** color
2. **Middle LED (index 1)**: Num Lock indicator with **Yellow** color  
3. **Bottom LED (index 2)**: Layer indicator
   - Off on base layer (layer 0)
   - **Red** on function layer (layer 1)
   - **Purple** on any other layer

## Startup Effect

When the keyboard powers on, all three LEDs briefly flash white before turning off.

## Building This Keymap

To compile and flash this example:

```bash
make primekb/meridian/ktr1010:led_example:flash
```

Or to just compile:

```bash
make primekb/meridian/ktr1010:led_example
```

## Customizing Further

You can modify `keymap.c` to change:
- LED colors (RGB values 0-255)
- Which LED shows which indicator
- Add more layers with different colors
- Change the startup animation

See the [LED Configuration Guide](../../ktr1010/LED_CONFIGURATION.md) for more customization examples.
