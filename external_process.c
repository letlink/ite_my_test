/******************************************************************************\
**  版    权 :  深圳市和而泰智能控制股份有限公司所有（2020）
**  文件名称 :  external_process.c
**  功能描述 :  任务消息处理
**  作    者 :  vincent
**  日    期 :  2020.06.29
**  版    本 :  V0.0.1
**  变更记录 :  V0.0.1/2020.06.29
1 首次创建
\******************************************************************************/
/******************************************************************************\
Includes
\******************************************************************************/
#include <assert.h>
#include <stdlib.h>
#include <sys/time.h>

#include "SDL/SDL.h"
#include "ctrlboard.h"
#include "scene.h"
#include "ite/itp.h"
#include "clife_lite/GUI_ClifeProtocol.h"
#include "clife_lite/GUI_DataConfig.h"
/******************************************************************************\
                             Variables definitions
\******************************************************************************/

/*
* 函数名称 : ExternalProcessUartUploadRx
* 功能描述 : 收到串口任务发来的消息，根据串口发来的消息更新控件
* 参    数 : ev -- 消息指针
* 返回值   : 无
* 示    例 : 无
*/
/******************************************************************************/
static void ExternalProcessUartUploadRx(ExternalEvent* ev)
/******************************************************************************/
{
    char str[20];
    TS_GUI_DATA* pThis = (TS_GUI_DATA*)ev->arg1;

    //更新当前温度显示
    memset(str, 0, sizeof(str));
    itoa(pThis->AirConCurrTemp, str, 10);
    ITUText *pThisText = ituSceneFindWidget(&theScene, "airConCurrTempValueText");
    ituTextSetString(pThisText, str);
    
    return;
}

/*
* 函数名称 : ExternalProcessUartTx
* 功能描述 : 收到UI任务发来的消息，根据UI发来的消息通过串口发送数据出去
* 参    数 : ev -- 消息指针
* 返回值   : 无
* 示    例 : 无
*/
/******************************************************************************/
static void ExternalProcessUartTx(ExternalEvent* ev)
/******************************************************************************/
{
    ;
}

/*
* 函数名称 : ExternalInQueueProcessEvent
* 功能描述 : UI任务接收到消息并进行处理
* 参    数 : ev -- 消息指针
* 返回值   : 无
* 示    例 : 无
*/
/******************************************************************************/
void ExternalInQueueProcessEvent(ExternalEvent* ev)
/******************************************************************************/
{
    //char buf[64];
    assert(ev);

    switch (ev->type)
    {
    case EXTERNAL_SHOW_MSG:
        printf("EXTERNAL_SHOW_MSG\n");
        
        break;

    case EXTERNAL_UART_UPLOAD_RX: //收到串口任务发过来的消息，对UI控件进行更新
        printf("EXTERNAL_UART_UPLOAD_RX\n");
        ExternalProcessUartUploadRx(ev);
        
        break;

    case EXTERNAL_UART_DEV_INFO_RX: //收到串口任务发过来的消息，对UI控件进行更新
        printf("EXTERNAL_UART_DEVINFO_RX\n");
        
        
        break;

    case EXTERNAL_UART_SYNC_DATA_RX: //收到串口任务发过来的消息，对UI控件进行更新
        printf("EXTERNAL_UART_SYNC_DATA_RX\n");
        
        
        break;

    case EXTERNAL_UART_FACTORY_TEST_RX: //收到串口任务发过来的消息，对UI控件进行更新
        printf("EXTERNAL_UART_FACTORY_TEST_RX\n");
        
        
        break;

    case EXTERNAL_UART_RESET_RX: //收到串口任务发过来的消息，对UI控件进行更新
        printf("EXTERNAL_UART_RESET_RX\n");
        
        
        break;
        
	case EXTERNAL_BEEP:
		printf("EXTERNAL_BEEP\n");
		break;
    
	case EXTERNAL_VOLUME:
		printf("EXTERNAL_VOLUME\n");
		theConfig.keylevel = ev->arg1*14;
		AudioSetVolume(theConfig.keylevel);
		break;
        
	case EXTERNAL_BRIGHTNESS:
		printf("EXTERNAL_BRIGHTNESS\n"); 
		theConfig.brightness = ev->arg1;
		ScreenSetBrightness(theConfig.brightness);
		break;
    }
}

/*
* 函数名称 : ExternalOutQueueProcessEvent
* 功能描述 : 收到UI任务发给外部任务的消息，执行对应操作
* 参    数 : ev -- 消息指针
* 返回值   : 无
* 示    例 : 无
*/
/******************************************************************************/
void ExternalOutQueueProcessEvent(ExternalEvent* ev)
/******************************************************************************/
{
//    char buf[64];
    assert(ev);

    switch (ev->type)
    {
        case EXTERNAL_UART_TX: //按空调界面的电源按钮时，串口发送对应的数据
            printf("EXTERNAL_UART_TX\n");
            ExternalProcessUartTx(ev);
            break;
            
    	default:break;
    }
}

/*
* 函数名称 : ExternalProcessInit
* 功能描述 : 外部任务初始化
* 参    数 : 无
* 返回值   : 无
* 示    例 : 无
*/
/******************************************************************************/
void ExternalProcessInit(void)
/******************************************************************************/
{
    ;
}
