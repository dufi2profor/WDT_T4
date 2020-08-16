# WDT_T4
Watchdog for Teensy 4, WDOG1,2,3, EWM

Modified by adding pause() and resume() functions which will properly disable the WDT3 and enable.
Aim was to be able to pause the WDT3 timer before calling Snooze.deepSleep(config_teensy40); from Snooze library that can be found here: https://github.com/duff2013/Snooze.
After waking up, resume() should be called and then serviced within the window.

Without pausing the WDT3, Teensy resets after exiting Snooze.deepSleep(config_teensy40);
