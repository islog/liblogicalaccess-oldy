/**
 * \file a3mlgm5600ledbuzzerdisplay.cpp
 * \author Maxime C. <maxime-dev@islog.com>
 * \brief A3MLGM5600 LED/Buzzer Display.
 */

#include <logicalaccess/plugins/readers/a3mlgm5600/a3mlgm5600ledbuzzerdisplay.hpp>
#include <logicalaccess/plugins/readers/a3mlgm5600/readercardadapters/a3mlgm5600readercardadapter.hpp>

#include <iostream>
#include <iomanip>
#include <sstream>

namespace logicalaccess
{
A3MLGM5600LEDBuzzerDisplay::A3MLGM5600LEDBuzzerDisplay()
    : LEDBuzzerDisplay()
{
    d_red_led   = false;
    d_green_led = false;
    d_buzzer    = false;
}

void A3MLGM5600LEDBuzzerDisplay::setRedLed(const bool status)
{
    d_red_led = status;
    setLED();
}

void A3MLGM5600LEDBuzzerDisplay::setGreenLed(const bool status)
{
    d_green_led = status;
    setLED();
}

void A3MLGM5600LEDBuzzerDisplay::setBuzzer(const bool status)
{
    d_buzzer = status;

    ByteVector data;
    data.push_back(static_cast<unsigned char>(status ? 0 : 1));

    getA3MLGM5600ReaderCardAdapter()->sendCommand(0x26, data);
}

void A3MLGM5600LEDBuzzerDisplay::setLED() const
{
    ByteVector data;
    data.push_back(
        static_cast<unsigned char>((d_red_led ? 1 : 0) | (d_green_led ? 2 : 0)));

    getA3MLGM5600ReaderCardAdapter()->sendCommand(0x24, data);
}
}