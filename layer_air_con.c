#include <assert.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "SDL/SDL.h"
#include "scene.h"
#include "ctrlboard.h"
#include "clife_lite/GUI_ClifeProtocol.h"
#include "clife_lite/GUI_DataConfig.h"

/* widgets:
airConLayer
airConBackground
airConPageIndicatorSprite
airConPage2Icon
airConPage1Icon
airConCoverFlow
airConDataContainer
airConDataBackground
aicConCtrlContainer
airConSplitBackground
airConTempSetBackground
airConTempMinText
airConTempMaxText
airConSetTempTrackBar
airConSetTempButton
airConSetTempProgressBar
airConTempInfoBackground
airConSetTempTitleText
airConSetTempUnitText
airConSetTempValueText
airConCurrTempTitleText
airConCurrTempUnitText
airConCurrTempValueText
airConWindBackground
airConWindAutoAnimation
airConWindAutoLargeIcon
airConWindAutoIcon
airConWindFastAnimation
airConWindFastLargeIcon
airConWindFastIcon
airConWindNormalAnimation
airConWindNormalLargeIcon
airConWindNormalIcon
airConWindSlowAnimation
airConWindSlowLargeIcon
airConWindSlowIcon
airConWindAutoRadioBox
airConWindFastRadioBox
airConWindNormalRadioBox
airConWindSlowRadioBox
airConModeBackground
airConModeHeatText
airConModeHeatRadioBox
airConModeFanText
airConModeFanRadioBox
airConModeDryText
airConModeDryRadioBox
airConModeCoolText
airConModeCoolRadioBox
airConModeAutoText
airConModeAutoRadioBox
airConPowerBackground
airConPowerText
airConPowerCheckBox
airConGotoMenuButton
*/

static ITUCheckBox* airConPowerCheckBox;

static ITURadioBox* airConModeAutoRadioBox;
static ITURadioBox* airConModeCoolRadioBox;
static ITURadioBox* airConModeDryRadioBox;
static ITURadioBox* airConModeFanRadioBox;
static ITURadioBox* airConModeHeatRadioBox;

static ITUBackground* airConWindBackground;
static ITUBackground* airConModeBackground;

bool airConLayerOnEnter(ITUWidget* widget, char* param)
{
	airConPowerCheckBox = ituSceneFindWidget(&theScene, "airConPowerCheckBox");
	assert(airConPowerCheckBox);

	airConModeAutoRadioBox = ituSceneFindWidget(&theScene, "airConModeAutoRadioBox");
	assert(airConModeAutoRadioBox);
	airConModeCoolRadioBox = ituSceneFindWidget(&theScene, "airConModeCoolRadioBox");
	assert(airConModeCoolRadioBox);
	airConModeDryRadioBox = ituSceneFindWidget(&theScene, "airConModeDryRadioBox");
	assert(airConModeDryRadioBox);
	airConModeFanRadioBox = ituSceneFindWidget(&theScene, "airConModeFanRadioBox");
	assert(airConModeFanRadioBox);
	airConModeHeatRadioBox = ituSceneFindWidget(&theScene, "airConModeHeatRadioBox");
	assert(airConModeHeatRadioBox);

	airConWindBackground = ituSceneFindWidget(&theScene, "airConWindBackground");
	assert(airConWindBackground);
	airConModeBackground = ituSceneFindWidget(&theScene, "airConModeBackground");
	assert(airConModeBackground);

	ituCheckBoxSetChecked(airConPowerCheckBox, false);
	//总开关关闭时，模式全部设置为未选中状态
	ituRadioBoxSetChecked(airConModeAutoRadioBox, true);
	ituRadioBoxSetChecked(airConModeCoolRadioBox, false);
	ituRadioBoxSetChecked(airConModeDryRadioBox, false);
	ituRadioBoxSetChecked(airConModeFanRadioBox, false);
	ituRadioBoxSetChecked(airConModeHeatRadioBox, false);

	ituWidgetDisable(airConModeBackground);
	ituWidgetDisable(airConWindBackground);

	return true;
}

bool airConModeRadioBoxPress(ITUWidget* widget, char* param)
{
	return true;
}

bool AirConPowerCheckBoxChanged(ITUWidget* widget, char* param)
{
	if (ituCheckBoxIsChecked(airConPowerCheckBox))// 总开关开启
	{
        //协议数据更新
        g_GUI_Data.AirConOnOff = 1;
        
		ituWidgetEnable(airConModeBackground);
		ituWidgetEnable(airConWindBackground);

		//总开关关闭时，模式全部设置为未选中状态
		ituRadioBoxSetChecked(airConModeAutoRadioBox, true);
		ituRadioBoxSetChecked(airConModeCoolRadioBox, false);
		ituRadioBoxSetChecked(airConModeDryRadioBox, false);
		ituRadioBoxSetChecked(airConModeFanRadioBox, false);
		ituRadioBoxSetChecked(airConModeHeatRadioBox, false);
	}
	else //总开关关闭
	{
        //协议数据更新
        g_GUI_Data.AirConOnOff = 0;
        
		//总开关关闭时，模式全部设置为未选中状态
		ituRadioBoxSetChecked(airConModeAutoRadioBox, false);
		ituRadioBoxSetChecked(airConModeCoolRadioBox, false);
		ituRadioBoxSetChecked(airConModeDryRadioBox, false);
		ituRadioBoxSetChecked(airConModeFanRadioBox, false);
		ituRadioBoxSetChecked(airConModeHeatRadioBox, false);

		ituWidgetDisable(airConModeBackground);
		ituWidgetDisable(airConWindBackground);
	}
    //发送数据到串口
    HET_GUI_SendDataFrame(CMD_DOWNLOAD, ID_AIR_CON_ON_OFF, LEN_AIR_CON_ON_OFF, (uint8_t*)&g_GUI_Data.AirConOnOff);
	return true;
}

