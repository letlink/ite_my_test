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
    //ģ��ʱ��
    clockAnalogClock = ituSceneFindWidget(&theScene, "clockAnalogClock");
    assert(clockAnalogClock);

    //����ʱ��
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

    //�������ʱ���ȶ�ȡRTCʱ�Ӳ�������ʾ
    return true;
}

bool ClockTimeSetConfirmButtonOnPress(ITUWidget* widget, char* param)
{
    //ʱ��������ɣ��û����ȷ����ť�󣬽�����ʱ����µ�RTC
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
    //�û����ʱ�����ð�ť���������õĳ�ʼ��ֵ����Ϊ��ǰֵ
    ituWheelGoto(clockHourWheel, clockDigitalClock->hour);
    ituWheelGoto(clockMinWheel, clockDigitalClock->minute);
    ituWheelGoto(clockSecWheel, clockDigitalClock->second);
    return true;
}

