#include <assert.h>
#include "scene.h"
#include <sys/time.h>
/* widgets:
clockLayer
clockBackground
clockTimeSetConfirmBackground
clockTimeSetCancelButton
clockTimeSetConfirmButton
clockTimeSetBackground
Text4
Text3
Background11
Background10
clockSecWheel
clockMinWheel
clockHourWheel
clockDigitalClock
clockColon2Text
clockColon1Text
clockSecText
clockMinText
clockHourText
clockTimeSetButton
clockAnalogClock
clockSecIcon
clockMinIcon
clockHourIcon
gotoMainButton
*/
//---------------------------------------------------------------------------------------------------
static ITUAnalogClock* clockAnalogClock;
static ITUDigitalClock* clockDigitalClock;

static ITUWheel* clockHourWheel;
static ITUWheel* clockMinWheel;
static ITUWheel* clockSecWheel;

static ITUText* clockHourText;
static ITUText* clockMinText;
static ITUText* clockSecText;
//---------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------
bool ClockLayerOnEnter(ITUWidget* widget, char* param)
{
    //模拟时钟
    clockAnalogClock = ituSceneFindWidget(&theScene, "clockAnalogClock");
    assert(clockAnalogClock);

    //数字时钟
    clockDigitalClock = ituSceneFindWidget(&theScene, "clockDigitalClock");
    assert(clockDigitalClock);

    clockHourWheel = ituSceneFindWidget(&theScene, "clockHourWheel");
    assert(clockHourWheel);
    clockMinWheel = ituSceneFindWidget(&theScene, "clockMinWheel");
    assert(clockMinWheel);
    clockSecWheel = ituSceneFindWidget(&theScene, "clockSecWheel");
    assert(clockSecWheel);

    clockHourText = ituSceneFindWidget(&theScene, "clockHourText");
    assert(clockHourText);
    clockMinText = ituSceneFindWidget(&theScene, "clockMinText");
    assert(clockMinText);
    clockSecText = ituSceneFindWidget(&theScene, "clockSecText");
    assert(clockSecText);

    //进入界面时，先读取RTC时钟并更新显示
    return true;
}

bool ClockTimeSetConfirmButtonOnPress(ITUWidget* widget, char* param)
{
    //时间设置完成，用户点击确定按钮后，将设置时间更新到RTC
    struct timeval tv;
    struct tm *tm, mytime;
    char buf[8];

    gettimeofday(&tv, NULL);
    tm = localtime(&tv.tv_sec);

    memcpy(&mytime, tm, sizeof (struct tm));

    mytime.tm_hour = clockHourWheel->focusIndex;
    mytime.tm_min = clockMinWheel->focusIndex;
    mytime.tm_sec = clockSecWheel->focusIndex;

    tv.tv_sec = mktime(&mytime);
    tv.tv_usec = 0;

    settimeofday(&tv, NULL);

    return true;
}

bool ClockTimeSetButtonOnPress(ITUWidget* widget, char* param)
{
    //用户点击时间设置按钮，滚轮设置的初始化值加载为当前值
    ituWheelGoto(clockHourWheel, clockDigitalClock->hour);
    ituWheelGoto(clockMinWheel, clockDigitalClock->minute);
    ituWheelGoto(clockSecWheel, clockDigitalClock->second);
    return true;
}

