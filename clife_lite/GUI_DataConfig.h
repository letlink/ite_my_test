/****************************************************************************************
**  版    权 :  深圳市和而泰智能控制股份有限公司所有（2020）
**  文件名称 :  GUI_DataConfig.c
**  功能描述 :  基于C-LIFE简化版协议的GUI数据配置
**  作    者 :  vincent
**  日    期 :  2020.07.01
**  版    本 :  V0.0.1
**  变更记录 :  V0.0.1/2020.07.01
                1 首次创建   
*****************************************************************************************/
#ifndef _GUI_DATA_CONFIG_H
#define _GUI_DATA_CONFIG_H
/*****************************************************************************************
								  Includes
*****************************************************************************************/
#include <stdbool.h>
#include <stdint.h>
/*****************************************************************************************
								Macro definitions
*****************************************************************************************/
#define         DATA_ENDIAN         0   //设备大小端，0，小端，1，大端（RAM芯片通常为小端，51芯片通常为大端）
/*****************************************************************************************
								Typedef definitions
*****************************************************************************************/
#pragma pack(1)

//协议数据
typedef struct
{
    uint8_t	 DisplayOnOff;			                            //显示开关设置
    uint32_t TimeStamp;                                         //设置系统时间，使用时间戳

    uint8_t	 AirConOnOff;			                            //空调模式设置
    uint8_t	 AirConMode;			                            //空调模式设置
    uint8_t	 AirConFan;			                                //空调风速设置
    uint8_t	 AirConSetTemp;			                            //空调设定温度
    uint8_t	 AirConCurrTemp;			                        //空调当前温度
    uint32_t AirConErrCode;			                            //空调故障代码

    uint8_t	 TestNumCnt;			                            //数字计数测试
    uint16_t TestMeterDegree;			                        //仪表盘测试
    uint16_t TestProgressBar;			                        //进度条测试
   
}TS_GUI_DATA;
#pragma pack()

//数据ID
typedef enum
{
    ID_ALL,

    ID_DISPLAY_ON_OFF,		//1	                                
    ID_TIME_STAMP,			                                   	        

    ID_AIR_CON_ON_OFF,		//3                                  	       
    ID_AIR_CON_MODE,		                                   	        
    ID_AIR_CON_FAN,	                                   	       
    ID_AIR_CON_SET_TEMP,	                                   	      
    ID_AIR_CON_CURR_TEMP,			                                   	     
    ID_AIR_CON_ERR_CODE,			                                   	      

    ID_TEST_NUM_CNT,	     //9                            	      
    ID_TEST_METER_DEGREE,			                                   	      
    ID_TEST_PROGRESS_BAR,			                                   	       
   
    ID_MAX
}TE_GUI_DATA_ID;

//数据长度
typedef enum
{
    LEN_ALL= 19,

    LEN_DISPLAY_ON_OFF = 1,
    LEN_TIME_STAMP = 4,

    LEN_AIR_CON_ON_OFF = 1,
    LEN_AIR_CON_MODE = 1,
    LEN_AIR_CON_FAN = 1,
    LEN_AIR_CON_SET_TEMP = 1,
    LEN_AIR_CON_CURR_TEMP = 1,
    LEN_AIR_CON_ERR_CODE = 4,

    LEN_TEST_NUM_CNT = 1,
    LEN_TEST_METER_DEGREE = 2,
    LEN_TEST_PROGRESS_BAR = 2,
}TE_GUI_DATA_LEN;

typedef enum
{
    WORK_OFF,
    WORK_ON,
}TE_GUI_WORK_STATUS;
/*
//数据单元
typedef struct
{
    uint8_t	 DataId;			                        //数据ID
    uint8_t  DataLen;                                   //数据长度
    uint8_t* pData;			                            //数据指针
}TS_GUI_DATA_UNIT;
*/

/*****************************************************************************************
								Global variables and functions
*****************************************************************************************/
extern TS_GUI_DATA g_GUI_Data;
//----------------------------------------------------------------------------------------
#endif
/***********************************END OF FILE*******************************************/
