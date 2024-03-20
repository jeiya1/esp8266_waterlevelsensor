#!/usr/bin/env python

import gi
from app import app
import subprocess,webbrowser

gi.require_version("Gtk", "3.0")
from gi.repository import Gtk

from pathlib import Path

# Check if shell exists and specify the shell
def shell_exists(shell):
    if Path(f"/bin/{shell}").is_file():
        return f"{shell} exists."
    else:
        return f"{shell} is not found."
print(shell_exists('bash'))

# Main Window
class MyWindow(Gtk.Window):
    def __init__(self):
        super().__init__(title="Esp8266 Water Level Sensor")

        self.set_border_width(10)
        self.set_default_size(240, 100)
        self.set_position(Gtk.WindowPosition.CENTER)
        self.set_resizable(False)

        hbox = Gtk.Box(spacing=6)
        self.add(hbox)
        vbox = Gtk.Box(orientation=Gtk.Orientation.VERTICAL, spacing=6)
        self.add(vbox)

        button = Gtk.Button(label="Start Server")
        button.connect("clicked", self.start_server)
        hbox.pack_start(button, True, True, 0)

        button = Gtk.Button(label="Stop Server")
        button.connect("clicked", self.stop_server)
        hbox.pack_start(button, True, True, 0)

        self.server_process = None

    def start_server(self, widget):
        if self.server_process and self.server_process.poll() is None:
            print("Server is ONLINE")
        else:
            self.server_process = subprocess.Popen(["python3", "app.py"])
            webbrowser.open("http://192.168.1.100:5000/webpage")
    def stop_server(self, widget):
        if self.server_process and self.server_process.poll() is None:
            self.server_process.terminate()
        else:
            print("Server is not online")

win = MyWindow()
win.connect("destroy", Gtk.main_quit)
win.show_all()
Gtk.main()
