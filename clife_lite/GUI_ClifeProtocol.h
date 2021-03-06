/******************************************************************************\
**  版    权 :  深圳市和而泰智能控制股份有限公司所有（2020）
**  文件名称 :  GUI_ClifeProtocol.h
**  功能描述 :  产品组件头文件
**  作    者 :  vincent
**  日    期 :  2020.07.01
**  版    本 :  V0.0.1
**  变更记录 :  V0.0.1/2020.07.01
                1 首次创建 
\******************************************************************************/

#ifndef _GUI_CLIFE_PROTOCOL_H_
#define _GUI_CLIFE_PROTOCOL_H_

/******************************************************************************\
                             Includes
\******************************************************************************/	
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "HET_ClifeProtocol.h"
#include "GUI_DataConfig.h"
/******************************************************************************\
                          Macro definitions
\******************************************************************************/
//#define	WIFI_RESET_RCC_CLK_ENABLE()		__HAL_RCC_GPIOB_CLK_ENABLE()	//复位脚时钟
//#define WIFI_RESET_PORT			        GPIOB                           //复位脚端口
//#define WIFI_RESET_PIN                  GPIO_PIN_0                      //复位脚序
//#define WIFI_RESET_POLARITY             GPIO_PIN_RESET                  //复位有效电平
//#define WIFI_RESET_N_POLARITY           GPIO_PIN_SET                    //复位反有效电平
//#define WIFI_USART_ID                   USART3                          //串口ID
//#define WIFI_USART_TX_PIN               GPIO_PIN_10                     //串口TX PIN
//#define WIFI_USART_TX_PORT              GPIOB                           //串口TX端口
//#define WIFI_USART_RX_PIN               GPIO_PIN_11                     //串口RX PIN
//#define WIFI_USART_RX_PORT              GPIOB                           //串口RX端口
//#define WIFI_USART_MODE                 HET_WIFI_USART_DMA              //串口工作模式
//#define WIFI_BAUDRATE                   9600                            //串口波特率
//
//#define htons(A)    ((((uint16_t)(A) & 0xff00) >> 8 ) | \
//                    (((uint16_t)(A) & 0x00ff) << 8 ))
//#define htonl(A)    ((((uint32_t)(A) & 0xff000000) >> 24) | \
//                    (((uint32_t)(A)& 0x00ff0000) >> 8) | \
//                    (((uint32_t)(A)& 0x0000ff00) << 8) | \
//                    (((uint32_t)(A)& 0x000000ff) << 24))
//#define ntohs     htons
//#define ntohl     htonl

#ifndef MY_WIN32_COM
#define MY_WIN32_COM           2
#endif

/******************************************************************************\
                         Typedef definitions
\******************************************************************************/  
//时间数据结构体
typedef struct
{
	uint8_t Type;					//时间格式(0:格林威治时间,1:北京时间)
	uint8_t	Year;					//年
	uint8_t	Month;					//月
	uint8_t	Day;					//日
	uint8_t	Hour;					//时
	uint8_t	Min;					//分
	uint8_t	Sec;					//秒
	uint8_t	Week;					//星期
}TS_HET_DATE;
/******************************************************************************\
                    Global variables and functions
\******************************************************************************/
/*
* 函数名称 : HET_GUI_UartRecvCallback
* 功能描述 : 串口接收回调
* 参    数 : pBuf:数据指针
             Len:数据长度
* 返回值   : 无
* 示    例 : 无
*/
/******************************************************************************/
extern void HET_GUI_UartRecvCallback(uint8_t *pBuf, uint16_t Len);
/******************************************************************************/

/*
* 函数名称 : HET_GUI_SendDataFrame
* 功能描述 : 协议数据发送
* 参    数 : Cmd      - 功能码
             DataId   - 数据ID
             DataLen  - 数据长度
             pDataBuf - 数据指针
* 返回值   : 无
* 示    例 : 无
*/
/******************************************************************************/
extern uint8_t HET_GUI_SendDataFrame(TE_HET_CP_CMD Cmd, uint8_t DataId, uint8_t DataLen, uint8_t* pDataBuf);
/******************************************************************************/

/*
* 函数名称 : HET_GUI_GetDataHandle
* 功能描述 : 获取协议数据指针
* 参    数 : 无
* 返回值   : 无
* 示    例 : 无
*/
/******************************************************************************/
extern TS_GUI_DATA* HET_GUI_GetDataHandle(void);
/******************************************************************************/

/*
* 函数名称 : HET_GUI_Init
* 功能描述 : 通信协议组件初始化
* 参    数 : 无
* 返回值   : 无
* 示    例 : 无
*/
/******************************************************************************/
extern void HET_GUI_Init(void);
/******************************************************************************/

/*
* 函数名称 : HET_GUI_Task
* 功能描述 : GUI任务，需放置到10ms循环中
* 参    数 : 无
* 返回值   : 无
* 示    例 : 无
*/
/******************************************************************************/
extern void HET_GUI_Task(void);
/******************************************************************************/

#endif
/******************************* End of File (H) ******************************/
