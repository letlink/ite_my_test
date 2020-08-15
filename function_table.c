#include "ite/itu.h"

extern bool MainOnEnter(ITUWidget* widget, char* param);
extern bool UpButtonPress(ITUWidget* widget, char* param);
extern bool DownButtonPress(ITUWidget* widget, char* param);
extern bool ClockLayerOnEnter(ITUWidget* widget, char* param);
extern bool ClockTimeSetConfirmButtonOnPress(ITUWidget* widget, char* param);
extern bool ClockTimeSetButtonOnPress(ITUWidget* widget, char* param);
extern bool CircleCtrlOnEnter(ITUWidget* widget, char* param);
extern bool CircleCtrlOnTimer(ITUWidget* widget, char* param);
extern bool CircleCtrlFastButtonOnPress(ITUWidget* widget, char* param);
extern bool CircleCtrlSlowButtonOnPress(ITUWidget* widget, char* param);
extern bool onOffCheckBoxOnPress(ITUWidget* widget, char* param);
extern bool KbEnterButtonOnPress(ITUWidget* widget, char* param);
extern bool airConLayerOnEnter(ITUWidget* widget, char* param);
extern bool airConModeRadioBoxPress(ITUWidget* widget, char* param);
extern bool AirConPowerCheckBoxChanged(ITUWidget* widget, char* param);
extern bool MediaLayerOnEnter(ITUWidget* widget, char* param);
extern bool MediaLayerOnTimer(ITUWidget* widget, char* param);
extern bool MediaVideoScrollMediaFileListBoxOnSelection(ITUWidget* widget, char* param);
extern bool MediaMusicScrollMediaFileListBoxOnSelection(ITUWidget* widget, char* param);
extern bool MediaImageScrollMediaFileListBoxOnSelection(ITUWidget* widget, char* param);
extern bool MediaPlayerVolumeTrackBarOnChanged(ITUWidget* widget, char* param);
extern bool MediaModeCircleAllButtonOnPress(ITUWidget* widget, char* param);
extern bool MediaModeCircleOneButtonOnPress(ITUWidget* widget, char* param);
extern bool MediaModeCircleRandButtonOnPress(ITUWidget* widget, char* param);
extern bool MediaListCheckBoxOnPress(ITUWidget* widget, char* param);
extern bool MediaPlayCheckBoxOnPress(ITUWidget* widget, char* param);
extern bool MediaPlayNextButtonOnPress(ITUWidget* widget, char* param);
extern bool MediaPlayPrveButtonOnPress(ITUWidget* widget, char* param);
extern bool IOTestOnEnter(ITUWidget* widget, char* param);
extern bool IOTestOnTimer(ITUWidget* widget, char* param);
extern bool RcvdClearButtonOnPress(ITUWidget* widget, char* param);
extern bool IOReadButtonOnPress(ITUWidget* widget, char* param);
extern bool IOWriteButtonOnPress(ITUWidget* widget, char* param);
extern bool SPIWriteButtonOnPress(ITUWidget* widget, char* param);
extern bool IICWriteButtonOnPress(ITUWidget* widget, char* param);
extern bool IICReadButtonOnPress(ITUWidget* widget, char* param);
extern bool UartSendButtonOnPress(ITUWidget* widget, char* param);

ITUActionFunction actionFunctions[] =
{
    "MainOnEnter", MainOnEnter,
    "UpButtonPress", UpButtonPress,
    "DownButtonPress", DownButtonPress,
    "ClockLayerOnEnter", ClockLayerOnEnter,
    "ClockTimeSetConfirmButtonOnPress", ClockTimeSetConfirmButtonOnPress,
    "ClockTimeSetButtonOnPress", ClockTimeSetButtonOnPress,
    "CircleCtrlOnEnter", CircleCtrlOnEnter,
    "CircleCtrlOnTimer", CircleCtrlOnTimer,
    "CircleCtrlFastButtonOnPress", CircleCtrlFastButtonOnPress,
    "CircleCtrlSlowButtonOnPress", CircleCtrlSlowButtonOnPress,
    "onOffCheckBoxOnPress", onOffCheckBoxOnPress,
    "KbEnterButtonOnPress", KbEnterButtonOnPress,
    "airConLayerOnEnter", airConLayerOnEnter,
    "airConModeRadioBoxPress", airConModeRadioBoxPress,
    "AirConPowerCheckBoxChanged", AirConPowerCheckBoxChanged,
    "MediaLayerOnEnter", MediaLayerOnEnter,
    "MediaLayerOnTimer", MediaLayerOnTimer,
    "MediaVideoScrollMediaFileListBoxOnSelection", MediaVideoScrollMediaFileListBoxOnSelection,
    "MediaMusicScrollMediaFileListBoxOnSelection", MediaMusicScrollMediaFileListBoxOnSelection,
    "MediaImageScrollMediaFileListBoxOnSelection", MediaImageScrollMediaFileListBoxOnSelection,
    "MediaPlayerVolumeTrackBarOnChanged", MediaPlayerVolumeTrackBarOnChanged,
    "MediaModeCircleAllButtonOnPress", MediaModeCircleAllButtonOnPress,
    "MediaModeCircleOneButtonOnPress", MediaModeCircleOneButtonOnPress,
    "MediaModeCircleRandButtonOnPress", MediaModeCircleRandButtonOnPress,
    "MediaListCheckBoxOnPress", MediaListCheckBoxOnPress,
    "MediaPlayCheckBoxOnPress", MediaPlayCheckBoxOnPress,
    "MediaPlayNextButtonOnPress", MediaPlayNextButtonOnPress,
    "MediaPlayPrveButtonOnPress", MediaPlayPrveButtonOnPress,
    "IOTestOnEnter", IOTestOnEnter,
    "IOTestOnTimer", IOTestOnTimer,
    "RcvdClearButtonOnPress", RcvdClearButtonOnPress,
    "IOReadButtonOnPress", IOReadButtonOnPress,
    "IOWriteButtonOnPress", IOWriteButtonOnPress,
    "SPIWriteButtonOnPress", SPIWriteButtonOnPress,
    "IICWriteButtonOnPress", IICWriteButtonOnPress,
    "IICReadButtonOnPress", IICReadButtonOnPress,
    "UartSendButtonOnPress", UartSendButtonOnPress,
    NULL, NULL
};
