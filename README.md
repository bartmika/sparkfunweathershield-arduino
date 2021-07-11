![SparkFun Weather Shield](https://github.com/bartmika/sparkfunweathershield-arduino/blob/master/media/red_mulberries_germination_with_sparkfun_weather_shield.jpg?raw=true)
*SparkFun Weather Shield monitoring dutifully a red mulberry seedling, the code is powered by this code repository*

# SparkFun Weather Shield (Arduino)

Arduino code which will communicate with the [SparkFun Weather Shield (DEV-13956)](https://github.com/sparkfun/Weather_Shield) to provide polling service to return time-series data in a `JSON` format.

# Hardware

* You are running either Linux or a Mac
* You have purchased 1x - [SparkFun Weather Shield (DEV-13956)](https://www.sparkfun.com/products/13956) device.
* You have purchased 1x - [Arduino Uno](https://store.arduino.cc/usa/arduino-uno-rev3) device.
* You have successfully assembled the Shield with the Arduino device and connected it through USB to your computer.

## Installation

First step after having assembled the shield is you will need to **download** the [Arduino IDE](https://www.arduino.cc/en/software) to your **computer**, please do so now. Afterwards open the **IDE**. You should see something as follows:

![](https://github.com/bartmika/sparkfunweathershield-arduino/blob/master/media/1.png)

Then highlight all the code in the **terminal** and delete it. Afterwards please go to our [sparkfunweathershield-adruino.ino](https://raw.githubusercontent.com/bartmika/sparkfunweathershield-arduino/master/src/sparkfunweathershield-adruino/sparkfunweathershield-adruino.ino) to copy and paste the code in there into your *Arduino IDE*.

Click save and save the file somewhere, afterwords click the **Verify** button and you should see a success message as follows:

![](https://github.com/bartmika/sparkfunweathershield-arduino/blob/master/media/2.png)

If you have received the above message, please continue by clicking the **Upload** button. The **IDE** will compile and then upload to the device. Once uploaded the Arduino device is running with the code we've written! Let's test out our code, please click the **Serial Monitor** icon now:

![](https://github.com/bartmika/sparkfunweathershield-arduino/blob/master/media/3.png)

Once you click it you should see the **Serial Monitor** as follows:

![](https://github.com/bartmika/sparkfunweathershield-arduino/blob/master/media/4.png)

In the **textfield**, type in letter one (ex: **1**) and hit **Send**. If everything works, you should see something like this:

![](https://github.com/bartmika/sparkfunweathershield-arduino/blob/master/media/5.png)

Hurray! You have successfully connected and polled your first data from the [SparkFun Weather Shield (DEV-13956)](https://www.sparkfun.com/products/13956) device. We're not finished yet, close the **Serial Monitor**, go to the **menu** and click **port**. When you open the **menu** please write down the URL path of the [Arduino Uno](https://store.arduino.cc/usa/arduino-uno-rev3) device.

![](https://github.com/bartmika/sparkfunweathershield-arduino/blob/master/media/6.png)

For example, on my screen the value is ``/dev/cu.usbmodem14401``.

**Please save your value as you will need it!** More specifically, you'll need it in the [serialreader-server](https://github.com/bartmika/serialreader-server) code repository.

## License

This application is licensed under the **BSD 3-Clause License**. See [LICENSE](LICENSE) for more information.
