from pydbus import SessionBus
from gi.repository import GLib
import sys

if len(sys.argv) != 2:
	print("Usage : {} <brightness>")
	exit(1)
level = int(sys.argv[1])
bus = SessionBus()
obj = bus.get("org.gnome.SettingsDaemon.Power", "/org/gnome/SettingsDaemon/Power")
obj.Set("org.gnome.SettingsDaemon.Power.Screen", "Brightness", GLib.Variant.new_int32(level-1))
obj.Set("org.gnome.SettingsDaemon.Power.Screen", "Brightness", GLib.Variant.new_int32(level))
