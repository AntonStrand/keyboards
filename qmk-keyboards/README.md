# QMK Keyboards

I wanted an easy way to keep track of my keyboards and keymaps in one place but still be able to easily compile and flash them.

This repo is inspired by this [blog post](https://medium.com/@patrick.elmquist/separate-keymap-repo-for-qmk-136ff5a419bd) by Patrick Elmquist.

## Usage

`<keyboard>` is a place holder for the name of the folder that contains the keyboard that should be compiled. You can also use `all` to compile all the keyboards in series.

Run `make <keyboard>` to compile the keymap and store the build in `./build`.

Run `make flash-<keyboard>` to compile and flash the keyboard.

Run `make lint-<keyboard>` to lint the keymap

## To do

- [ ] Make `crkbd` compile again.
- [ ] Add my missing keyboard.

## Key code mapping

The modifier keys are mapped differently for a swedish Mac. For future reference I chose to list them here.

| Key       | Result                   |
| --------- | ------------------------ |
| `KC_LALT` | `shift`                  |
| `KC_LCTL` | `N/A`                    |
| `KC_LGUI` | `shift` + `ctrl`         |
| `KC_LSFT` | `ctrl`                   |
| `KC_RALT` | `shift` + `alt`          |
| `KC_RCTL` | `alt`                    |
| `KC_RGUI` | `shift` + `ctrl` + `alt` |
| `KC_RSFT` | `ctrl` + `alt`           |
| `KC_HYPR` | `N/A`                    |
| `KC_MEH`  | `N/A`                    |
