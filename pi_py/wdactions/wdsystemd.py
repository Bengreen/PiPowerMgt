from time import sleep
from signal import signal, SIGINT
from .watchdog import PiWatchDog


def watchdogd(watchdogAddress: int, id: int, on: int, off: int, sleepinterval: int):

    if off > on:
        raise RuntimeError("OFF_THRESHOLD must be less than ON_THRESHOLD")

    watchdog = PiWatchDog(watchdogAddress)

    running = True

    onThreshold = on * 1000
    offThreshold = off * 1000

    def signal_handler(sig, frame):
        nonlocal running
        print(f"Got interrupt signal: {sig}, Quitting on next iteration")
        running = False

    signal(SIGINT, signal_handler)

    def get_temp():
        """Get the core temperature.
        Read file from /sys to get CPU temp in temp in C *1000
        Returns:
            int: The core temperature in thousanths of degrees Celsius.
        """
        with open("/sys/class/thermal/thermal_zone0/temp") as f:
            temp_data = f.read()

        return int(temp_data)

    watchdog.fanOn(id)
    fanState = True

    temp = get_temp()
    print(f"Initial temperature is {temp/1000}")

    while running:

        watchdog.powerOff(id)
        sleep(2)

        temp = get_temp()

        if temp > onThreshold and fanState:
            print(f"Turning on fan (temp={temp/1000})")
            watchdog.fanOn(id)
            fanState = True
        elif fanState and temp < offThreshold:
            print(f"Turning off fan (temp={temp/1000})")
            watchdog.fanOff(id)
            fanState = False

        if fanState:
            print(f"Temp high (temp={temp/1000})")

        watchdog.kickDog(id)
        print(f"Kicked dog")

        sleep(sleepinterval)

    print(f"Exiting")
