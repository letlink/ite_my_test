#include <assert.h>
#include "scene.h"
#include "audio_mgr.h"
#include "castor3player.h"

/* widgets:
mediaLayer
mediaBackground
mediaListBackground
mediaSourceBackground
mediaVideoScrollMediaFileListBox
mediaMusicScrollMediaFileListBox
mediaImageScrollMediaFileListBox
mediaVideoRadioBox
mediaMusicRadioBox
mediaImageRadioBox
mediaVideoContainer
mediaPlayerVideo
mediaMusicContainer
mediaMusicMeter
mediaMusicGuagePointerIcon
mediaMusicCoverBgIcon
mediaMusicCoverAnimation
mediaMusicCover3Icon
mediaMusicCover2Icon
mediaMusicCover1Icon
mediaImageContainer
mediaImagePlayerIcon
mediaPlayProgressBackground
mediaPlayEndTimeText
mediaPlayCurrTimeText
mediaPlayTrackBar
mediaSliderButton
mediaPlayCtrlBackground
mediaVolumeBackground
mediaVolumeTrackBar
mediaVolumeButton
mediaVolumeSprite
mediaVolumeOnIcon
mediaVolumeOffIcon
mediaPlayModeBackground
mediaModeCircleAllButton
mediaModeCircleOneButton
mediaModeCircleRandButton
mediaListCheckBox
mediaPlayCheckBox
mediaPlayNextButton
mediaPlayPrveButton
gotoMainButton
*/

//---------------------------------------------------------------------------------------------------
//ý���ļ��б�
static ITUBackground* mediaListBackground;

static ITURadioBox* mediaImageRadioBox;
static ITURadioBox* mediaMusicRadioBox;
static ITURadioBox* mediaVideoRadioBox;

static ITUScrollMediaFileListBox* mediaImageScrollMediaFileListBox;
static ITUScrollMediaFileListBox* mediaMusicScrollMediaFileListBox;
static ITUScrollMediaFileListBox* mediaVideoScrollMediaFileListBox;

//ý�岥�ſ���
static ITUBackground* mediaPlayModeBackground;
static ITUButton* mediaModeCircleAllButton;
static ITUButton* mediaModeCircleOneButton;
static ITUButton* mediaModeCircleRandButton;

static ITUButton* mediaPlayPrveButton;
static ITUButton* mediaPlayNextButton;
static ITUCheckBox* mediaPlayCheckBox;
static ITUCheckBox* mediaListCheckBox;

static ITUText* mediaPlayCurrTimeText;

static ITUBackground* mediaVolumeBackground;
static ITUTrackBar* mediaVolumeTrackBar;
static ITUSprite* mediaVolumeSprite;

//����������
static ITUContainer* mediaImageContainer;
static ITUIcon* mediaImagePlayerIcon;

static ITUContainer* mediaMusicContainer;
static ITUMeter* mediaMusicMeter;
static ITUAnimation* mediaMusicCoverAnimation;

static ITUContainer* mediaVideoContainer;
static ITUVideo* mediaPlayerVideo;
//---------------------------------------------------------------------------------------------------
//ͼƬ���ű���
char imagePlayerPath[PATH_MAX];
bool imagePlayerLoading, imagePlayerLoaded, imageBackFromPlayer;
static uint8_t* imagePlayerData;
static int imagePlayerDataSize;
int imagePlayerPageIndex, imagePlayerFocusIndex;

//���ֲ��ű���
static bool audioPlayerPlaying;
static int audioPlayerPageIndex;
static int audioPlayerFocusIndex;
static bool audioPlayerPlayingFinish;
static bool audioMuteSign = false;

static uint32_t mediaVolumeLastTick;

//��Ƶ���ű���
static int x, y, width, height = 0;
static MTAL_SPEC mtal_spec = { 0 };
int LastMediaPlayerVoice = 0;
bool videoPlayerIsFileEOF = false;
bool videoPlayerIsPlaying = false;
int videoPlayerPercentage = 0;
int videoPlayerPageIndex, videoPlayerFocusIndex;
//---------------------------------------------------------------------------------------------------
//ͼƬ���Żص�
static void imagePlayerLoadCallback(uint8_t* data, int size)
{
    if (data && size > 0)
    {
        if (imagePlayerDataSize > 0)
        {
            free(imagePlayerData);
            imagePlayerData = NULL;
            imagePlayerDataSize = 0;
        }
        imagePlayerData = data;
        imagePlayerDataSize = size;
        imagePlayerLoaded = true;
    }
}

//���ֲ��Żص�
static int AudioPlayerPlayCallback(int state)
{
    switch (state)
    {
    case AUDIOMGR_STATE_CALLBACK_PLAYING_FINISH:
        audioPlayerPlayingFinish = true;
        break;
    }
    return 0;
}

static void EventHandler(PLAYER_EVENT nEventID, void *arg)
{
    switch (nEventID)
    {
    case PLAYER_EVENT_EOF:
        printf("File EOF\n");
        videoPlayerIsFileEOF = true;
        break;
    case PLAYER_EVENT_OPEN_FILE_FAIL:
        printf("Open file fail\n");
        videoPlayerIsFileEOF = true;
        break;
    case PLAYER_EVENT_UNSUPPORT_FILE:
        printf("File not support\n");
        videoPlayerIsFileEOF = true;
        break;
    default:
        break;
    }
}


void MusicPlayerPlayButtonHandle(ITUCheckBox* checkbox)
{
    if (checkbox == NULL) return false;
    if (ituCheckBoxIsChecked(checkbox)) //����״̬
    {
        ITUScrollText* item = ituMediaFileListPlay((ITUMediaFileListBox*)mediaMusicScrollMediaFileListBox);
        if (item)
        {
            //��ȡ�û���ý���б���ѡ����ļ���·��
            char* filepath = (char*)ituWidgetGetCustomData(item);
            ITUListBox* listbox = (ITUListBox*)mediaMusicScrollMediaFileListBox;

            if (videoPlayerIsPlaying)
            {
#ifdef CFG_VIDEO_ENABLE        
                mtal_pb_stop();
#endif
                videoPlayerIsPlaying = false;
                videoPlayerPercentage = 0;
                //ituVideoStop(mediaPlayerVideo);
            }

            AudioPauseKeySound();
            AudioPlayMusic(filepath, AudioPlayerPlayCallback);
            audioPlayerPlaying = true;
            audioPlayerPageIndex = listbox->pageIndex;
            audioPlayerFocusIndex = listbox->focusIndex;

            // ���ֲ��Ŷ���Ч��
            ituMeterSetValue(mediaMusicMeter, 100);

            ituWidgetEnable(mediaMusicCoverAnimation);
            ituAnimationSetDelay(mediaMusicCoverAnimation, 500);
            mediaMusicCoverAnimation->animationFlags |= ITU_ANIM_ROTATE;
            ituAnimationPlay(mediaMusicCoverAnimation, 1);
            //mediaMusicCoverAnimation->playing = true;
        }
        else //ý���ļ��б��ȡʧ��
        {
            ituCheckBoxSetChecked(checkbox, false);
        }
    }
    else // ֹͣ״̬
    {
        if (audioPlayerPlaying)
        {
            AudioStop();
            AudioResumeKeySound();
            audioPlayerPlaying = false;

            // ���ֲ��Ŷ���Ч��
            ituMeterSetValue(mediaMusicMeter, 0);

            mediaMusicCoverAnimation->animationFlags &= ~ITU_ANIM_ROTATE;
            mediaMusicCoverAnimation->playing = false;
            ituAnimationGotoFrame(mediaMusicCoverAnimation, 2);
            ituWidgetDisable(mediaMusicCoverAnimation);
        }
    }
    ituTextSetString(mediaPlayCurrTimeText, NULL);
    return true;
}

bool VideoPlayerPlayButtonHandle(ITUCheckBox* checkbox)
{
    if (checkbox == NULL) return false;
    if (ituCheckBoxIsChecked(checkbox)) //����״̬
    {
        ITUScrollText* item = ituMediaFileListPlay((ITUMediaFileListBox*)mediaVideoScrollMediaFileListBox);
        if (item)
        {
            char* filepath = (char*)ituWidgetGetCustomData(item);

            //AudioPauseKeySound();

            // TODO: IMPLEMENT
            strcpy(mtal_spec.srcname, filepath);
            mtal_spec.vol_level = LastMediaPlayerVoice;

            AudioStop();
#ifdef CFG_VIDEO_ENABLE            
            mtal_pb_stop();
            mtal_pb_select_file(&mtal_spec);
            mtal_pb_play();
#endif            

            videoPlayerIsPlaying = true;
            videoPlayerPercentage = 0;
            ituVideoPlay(mediaPlayerVideo, -1);
        }
        else
        {
            ituCheckBoxSetChecked(checkbox, false);
        }
    }
    else // ֹͣ״̬
    {
#ifdef CFG_VIDEO_ENABLE        
        mtal_pb_stop();
#endif

        videoPlayerIsPlaying = false;
        videoPlayerPercentage = 0;
        //ituVideoStop(mediaPlayerVideo);
    }
    ituTextSetString(mediaPlayCurrTimeText, NULL);
    return true;
}

bool MediaLayerOnEnter(ITUWidget* widget, char* param)
{
    //ý���ļ��б�
    mediaListBackground = ituSceneFindWidget(&theScene, "mediaListBackground");
    assert(mediaListBackground);

    mediaImageRadioBox = ituSceneFindWidget(&theScene, "mediaImageRadioBox");
    assert(mediaImageRadioBox);
    mediaMusicRadioBox = ituSceneFindWidget(&theScene, "mediaMusicRadioBox");
    assert(mediaMusicRadioBox);
    mediaVideoRadioBox = ituSceneFindWidget(&theScene, "mediaVideoRadioBox");
    assert(mediaVideoRadioBox);

    mediaImageScrollMediaFileListBox = ituSceneFindWidget(&theScene, "mediaImageScrollMediaFileListBox");
    assert(mediaImageScrollMediaFileListBox);
    mediaMusicScrollMediaFileListBox = ituSceneFindWidget(&theScene, "mediaMusicScrollMediaFileListBox");
    assert(mediaMusicScrollMediaFileListBox);
    mediaVideoScrollMediaFileListBox = ituSceneFindWidget(&theScene, "mediaVideoScrollMediaFileListBox");
    assert(mediaVideoScrollMediaFileListBox);

    //ý�岥�ſ���
    mediaPlayModeBackground = ituSceneFindWidget(&theScene, "mediaPlayModeBackground");
    assert(mediaPlayModeBackground);
    mediaModeCircleAllButton = ituSceneFindWidget(&theScene, "mediaModeCircleAllButton");
    assert(mediaModeCircleAllButton);
    mediaModeCircleOneButton = ituSceneFindWidget(&theScene, "mediaModeCircleOneButton");
    assert(mediaModeCircleOneButton);
    mediaModeCircleRandButton = ituSceneFindWidget(&theScene, "mediaModeCircleRandButton");
    assert(mediaModeCircleRandButton);

    mediaPlayPrveButton = ituSceneFindWidget(&theScene, "mediaPlayPrveButton");
    assert(mediaPlayPrveButton);
    mediaPlayNextButton = ituSceneFindWidget(&theScene, "mediaPlayNextButton");
    assert(mediaPlayNextButton);
    mediaPlayCheckBox = ituSceneFindWidget(&theScene, "mediaPlayCheckBox");
    assert(mediaPlayCheckBox);
    mediaListCheckBox = ituSceneFindWidget(&theScene, "mediaListCheckBox");
    assert(mediaListCheckBox);

    mediaPlayCurrTimeText = ituSceneFindWidget(&theScene, "mediaPlayCurrTimeText");
    assert(mediaPlayCurrTimeText);

    mediaVolumeBackground = ituSceneFindWidget(&theScene, "mediaVolumeBackground");
    assert(mediaVolumeBackground);
    mediaVolumeTrackBar = ituSceneFindWidget(&theScene, "mediaVolumeTrackBar");
    assert(mediaVolumeTrackBar);
    mediaVolumeSprite = ituSceneFindWidget(&theScene, "mediaVolumeSprite");
    assert(mediaVolumeSprite);
    //������
    mediaImageContainer = ituSceneFindWidget(&theScene, "mediaImageContainer");
    assert(mediaImageContainer);
    mediaImagePlayerIcon = ituSceneFindWidget(&theScene, "mediaImagePlayerIcon");
    assert(mediaImagePlayerIcon);

    mediaMusicContainer = ituSceneFindWidget(&theScene, "mediaMusicContainer");
    assert(mediaMusicContainer);
    mediaMusicMeter = ituSceneFindWidget(&theScene, "mediaMusicMeter");
    assert(mediaMusicMeter);
    mediaMusicCoverAnimation = ituSceneFindWidget(&theScene, "mediaMusicCoverAnimation");
    assert(mediaMusicCoverAnimation);

    mediaVideoContainer = ituSceneFindWidget(&theScene, "mediaVideoContainer");
    assert(mediaVideoContainer);
    mediaPlayerVideo = ituSceneFindWidget(&theScene, "mediaPlayerVideo");
    assert(mediaPlayerVideo);

    ituWidgetDisable(mediaImageScrollMediaFileListBox);
    ituWidgetDisable(mediaMusicScrollMediaFileListBox);
    ituWidgetDisable(mediaVideoScrollMediaFileListBox);

    ituSpriteGoto(mediaVolumeSprite, 1);
    AudioSetVolume(mediaVolumeTrackBar->value);
    return true;
}

//���Ŷ�ʱɨ������
bool MediaLayerOnTimer(ITUWidget* widget, char* param)
{
    if (ituRadioBoxIsChecked(mediaImageRadioBox))
    {
        ITUListBox *listbox = (ITUListBox*)mediaImageScrollMediaFileListBox;
        ITUSurface *surf;
        if (listbox->pageIndex == imagePlayerPageIndex && listbox->focusIndex == -1)
            ituListBoxSelect(listbox, imagePlayerFocusIndex);

        if (imagePlayerLoading && !imagePlayerLoaded)
        {
            int ret = PhotoLoad(imagePlayerPath, imagePlayerLoadCallback);
            if (ret == 0)
                imagePlayerLoading = false;
        }
        else if (imagePlayerLoaded)
        {
            ituIconLoadJpegData(mediaImagePlayerIcon, imagePlayerData, imagePlayerDataSize);
            ituWidgetSetVisible(mediaImagePlayerIcon, true);
            free(imagePlayerData);
            imagePlayerData = NULL;
            imagePlayerDataSize = 0;
            imagePlayerLoaded = false;
        }
    }
    else if (ituRadioBoxIsChecked(mediaMusicRadioBox))
    {

    }
    else
    {
        ITUListBox *listbox = (ITUListBox*)mediaVideoScrollMediaFileListBox;

        if (listbox->pageIndex == videoPlayerPageIndex && listbox->focusIndex == -1)
            ituListBoxSelect(listbox, videoPlayerFocusIndex);
        // TODO: IMPLEMENT
        if (videoPlayerIsFileEOF)
        {
            ITUScrollText* item;
            if (listbox->focusIndex == -1)
            {
                ituListBoxGoto(listbox, videoPlayerPageIndex);
                ituListBoxSelect(listbox, videoPlayerFocusIndex);
            }
            item = ituMediaFileListNext((ITUMediaFileListBox*)mediaVideoScrollMediaFileListBox);
            videoPlayerIsFileEOF = false;
#ifdef CFG_VIDEO_ENABLE        
            mtal_pb_stop();
#endif
            if (item)
            {
                char* filepath = (char*)ituWidgetGetCustomData(item);
                strcpy(mtal_spec.srcname, filepath);
                mtal_spec.vol_level = LastMediaPlayerVoice;
#ifdef CFG_VIDEO_ENABLE            
                mtal_pb_select_file(&mtal_spec);
                mtal_pb_play();
#endif            
            }
            else
            {
                videoPlayerPercentage = 0;
                videoPlayerIsPlaying = false;
            }
            videoPlayerPageIndex = listbox->pageIndex;
            videoPlayerFocusIndex = listbox->focusIndex;
        }

        if (videoPlayerIsPlaying)
        {
            ScreenSaverRefresh();
#ifdef CFG_VIDEO_ENABLE        
            //videoPlayerPercentage = CalVideoPlayerProgressBarPercentage();
#endif
            //if (videoPlayerPercentage >= 0)
            //ituProgressBarSetValue(videoPlayerProgressBar, videoPlayerPercentage);
        }

        if (videoPlayerIsPlaying)
        {
            int h, m, s = 0;
            char buf[32];

#ifdef CFG_VIDEO_ENABLE        
            if (mtal_pb_get_current_time(&s) == 0)

#endif        
            {
                m = s / 60;
                s %= 60;
                h = m / 60;
                m %= 60;

                if (h > 0)
                    sprintf(buf, "%02d:%02d:%02d", h, m, s);
                else
                    sprintf(buf, "%02d:%02d", m, s);

                //ituTextSetString(videoPlayerTimeText, buf);
            }
        }
        return true;
    }

    return true;
}

//��Ƶ�б�ѡ���¼�
bool MediaVideoScrollMediaFileListBoxOnSelection(ITUWidget* widget, char* param)
{
    ITUListBox *listbox = (ITUListBox*)mediaVideoScrollMediaFileListBox;

    videoPlayerPageIndex = listbox->pageIndex;
    videoPlayerFocusIndex = listbox->focusIndex;

    //��ʾ��ǰ����
    ituWidgetSetVisible(mediaPlayModeBackground, true);
    ituWidgetEnable(mediaPlayModeBackground);
    ituWidgetSetVisible(mediaPlayCheckBox, true);
    ituWidgetEnable(mediaPlayCheckBox);
    ituWidgetSetVisible(mediaVolumeBackground, true);
    ituWidgetEnable(mediaVolumeBackground);

    ituWidgetSetVisible(mediaImageContainer, false);
    ituWidgetDisable(mediaImageContainer);

    ituWidgetSetVisible(mediaMusicContainer, false);
    ituWidgetDisable(mediaMusicContainer);

    ituWidgetEnable(mediaVideoContainer);
    ituWidgetSetVisible(mediaVideoContainer, true);
    ituWidgetEnable(mediaPlayerVideo);
    ituWidgetSetVisible(mediaPlayerVideo, true);


    return true;
}

bool MediaMusicScrollMediaFileListBoxOnSelection(ITUWidget* widget, char* param)
{
    ITUListBox* listbox = (ITUListBox*)mediaMusicScrollMediaFileListBox;

    audioPlayerPageIndex = listbox->pageIndex;
    audioPlayerFocusIndex = listbox->focusIndex;

    //��ʾ��ǰ����
    ituWidgetSetVisible(mediaPlayModeBackground, true);
    ituWidgetEnable(mediaPlayModeBackground);
    ituWidgetSetVisible(mediaPlayCheckBox, true);
    ituWidgetEnable(mediaPlayCheckBox);
    ituWidgetSetVisible(mediaVolumeBackground, true);
    ituWidgetEnable(mediaVolumeBackground);

    ituWidgetSetVisible(mediaImageContainer, false);
    ituWidgetDisable(mediaImageContainer);

    ituWidgetSetVisible(mediaVideoContainer, false);
    ituWidgetDisable(mediaVideoContainer);

    ituWidgetEnable(mediaMusicContainer);
    ituWidgetSetVisible(mediaMusicContainer, true);

    return true;
}

bool MediaImageScrollMediaFileListBoxOnSelection(ITUWidget* widget, char* param)
{
    if (((ITUListBox*)mediaImageScrollMediaFileListBox)->focusIndex >= 0
        && !imagePlayerLoaded  &&  !imagePlayerDataSize && !imagePlayerLoading)
    {
        ITUScrollText* item = ituMediaFileListPlay((ITUMediaFileListBox*)mediaImageScrollMediaFileListBox);
        if (item)
        {
            char* filepath = (char*)ituWidgetGetCustomData(item);
            ITUListBox *listbox = (ITUListBox*)mediaImageScrollMediaFileListBox;

            printf("Try to load %s\n", filepath);

            strncpy(imagePlayerPath, filepath, PATH_MAX);

            imagePlayerLoading = true;

            imagePlayerPageIndex = listbox->pageIndex;
            imagePlayerFocusIndex = listbox->focusIndex;
            ituCheckBoxSetChecked(mediaPlayCheckBox, false);
        }
    }

    //���֮ǰ�ڲ������ֻ�����Ƶ������ֹͣ
    if (audioPlayerPlaying)
    {
        AudioStop();
        AudioResumeKeySound();
        audioPlayerPlaying = false;
    }

    if (videoPlayerIsPlaying)
    {
#ifdef CFG_VIDEO_ENABLE        
        mtal_pb_stop();
#endif
        videoPlayerIsPlaying = false;
        videoPlayerPercentage = 0;
        //ituVideoStop(mediaPlayerVideo);
    }

    //��ʾ��ǰ����
    //ͼƬ�������£�����ģʽ��ť�����Ű�ť���������ڲ��ɼ�
    ituWidgetSetVisible(mediaPlayModeBackground, false);
    ituWidgetDisable(mediaPlayModeBackground);
    ituWidgetSetVisible(mediaPlayCheckBox, false);
    ituWidgetDisable(mediaPlayCheckBox);
    ituWidgetSetVisible(mediaVolumeBackground, false);
    ituWidgetDisable(mediaVolumeBackground);


    ituWidgetSetVisible(mediaVideoContainer, false);
    ituWidgetDisable(mediaVideoContainer);

    ituWidgetSetVisible(mediaMusicContainer, false);
    ituWidgetDisable(mediaMusicContainer);

    ituWidgetEnable(mediaImageContainer);
    ituWidgetSetVisible(mediaImageContainer, true);

    return true;
}

bool MediaPlayerVolumeTrackBarOnChanged(ITUWidget* widget, char* param)
{
    int vol;

    if (!mediaVolumeSprite)
        return false;

    mediaVolumeLastTick = itpGetTickCount();

    vol = atoi(param);
    LastMediaPlayerVoice = vol;

    if (vol > 0)
    {
        ituSpriteGoto(mediaVolumeSprite, 1);
    }
    else
    {
        ituSpriteGoto(mediaVolumeSprite, 0);
    }

    AudioSetVolume(vol);
    return true;
}
bool MediaModeCircleAllButtonOnPress(ITUWidget* widget, char* param)
{
    return true;
}

bool MediaModeCircleOneButtonOnPress(ITUWidget* widget, char* param)
{
    return true;
}

bool MediaModeCircleRandButtonOnPress(ITUWidget* widget, char* param)
{
    return true;
}

bool MediaListCheckBoxOnPress(ITUWidget* widget, char* param)
{
    if (ituCheckBoxIsChecked(mediaListCheckBox))
    {
        ituWidgetEnable(mediaListBackground);
        ituWidgetSetVisible(mediaListBackground, true);

        ituRadioBoxSetChecked(mediaImageRadioBox, true);

        ituWidgetEnable(mediaImageScrollMediaFileListBox);
        ituWidgetDisable(mediaMusicScrollMediaFileListBox);
        ituWidgetDisable(mediaVideoScrollMediaFileListBox);
        ituWidgetSetVisible(mediaImageScrollMediaFileListBox, true);
        ituWidgetSetVisible(mediaMusicScrollMediaFileListBox, false);
        ituWidgetSetVisible(mediaVideoScrollMediaFileListBox, false);

    }
    else
    {
        ituWidgetSetVisible(mediaListBackground, false);
        ituWidgetDisable(mediaListBackground);
    }
    return true;
}

//���Ű�ť
bool MediaPlayCheckBoxOnPress(ITUWidget* widget, char* param)
{
    if (ituRadioBoxIsChecked(mediaImageRadioBox))
    {
        return true;
    }
    else if (ituRadioBoxIsChecked(mediaMusicRadioBox)) //���ֲ�����
    {
        MusicPlayerPlayButtonHandle(mediaPlayCheckBox);
    }
    else //��Ƶ����
    {
        VideoPlayerPlayButtonHandle(mediaPlayCheckBox);
    }
    return true;
}

bool MediaPlayNextButtonOnPress(ITUWidget* widget, char* param)
{
    if (ituRadioBoxIsChecked(mediaImageRadioBox))
    {
        ITUListBox* listbox = (ITUListBox*)mediaImageScrollMediaFileListBox;
        ITUScrollText* item;

        if (listbox->focusIndex == -1)
        {
            ituListBoxGoto(listbox, imagePlayerPageIndex);
            ituListBoxSelect(listbox, imagePlayerFocusIndex);
        }

        item = ituMediaFileListNext((ITUMediaFileListBox*)mediaImageScrollMediaFileListBox);
        imagePlayerPageIndex = listbox->pageIndex;
        imagePlayerFocusIndex = listbox->focusIndex;

        if (item)
        {
            char* filepath = (char*)ituWidgetGetCustomData(item);

            printf("Try to load %s\n", filepath);

            strncpy(imagePlayerPath, filepath, PATH_MAX);

            imagePlayerLoading = true;
        }
    }
    else if (ituRadioBoxIsChecked(mediaMusicRadioBox))
    {
        ITUListBox* listbox = (ITUListBox*)mediaMusicScrollMediaFileListBox;
        ITUScrollText* item;

        if (listbox->focusIndex == -1)
        {
            ituListBoxGoto(listbox, audioPlayerPageIndex);
            ituListBoxSelect(listbox, audioPlayerFocusIndex);
        }

        item = ituMediaFileListNext((ITUMediaFileListBox*)mediaMusicScrollMediaFileListBox);
        audioPlayerPageIndex = listbox->pageIndex;
        audioPlayerFocusIndex = listbox->focusIndex;
        if (item && audioPlayerPlaying)
        {
            char* filepath = (char*)ituWidgetGetCustomData(item);

            AudioPauseKeySound();
            AudioPlayMusic(filepath, AudioPlayerPlayCallback);
            ituTextSetString(mediaPlayCurrTimeText, NULL);
            /*audioPlayerPageIndex = listbox->pageIndex;
            audioPlayerFocusIndex = listbox->focusIndex;*/
        }
    }
    else
    {
        ITUListBox *listbox = (ITUListBox*)mediaVideoScrollMediaFileListBox;
        ITUScrollText* item;

        if (listbox->focusIndex == -1)
        {
            ituListBoxGoto(listbox, videoPlayerPageIndex);
            ituListBoxSelect(listbox, videoPlayerFocusIndex);
        }

        item = ituMediaFileListNext((ITUMediaFileListBox*)mediaVideoScrollMediaFileListBox);

        if (item && videoPlayerIsPlaying)
        {
            char* filepath = (char*)ituWidgetGetCustomData(item);

            //AudioPauseKeySound();

            strcpy(mtal_spec.srcname, filepath);
            mtal_spec.vol_level = LastMediaPlayerVoice;

            AudioStop();
#ifdef CFG_VIDEO_ENABLE        
            mtal_pb_stop();
            mtal_pb_select_file(&mtal_spec);
            mtal_pb_play();
#endif
            //ituWidgetSetVisible(videoPlayerViewBackground, true);
            //ituWidgetSetVisible(videoPlayerViewButton, true);
            ituTextSetString(mediaPlayCurrTimeText, NULL);

            videoPlayerPercentage = 0;
            //ituWidgetSetVisible(videoPlayerProgressBar, true);
        }
        videoPlayerPageIndex = listbox->pageIndex;
        videoPlayerFocusIndex = listbox->focusIndex;
        return true;
    }
    return true;
}

bool MediaPlayPrveButtonOnPress(ITUWidget* widget, char* param)
{
    if (ituRadioBoxIsChecked(mediaImageRadioBox))   //��ǰΪͼƬ����
    {
        ITUListBox* listbox = (ITUListBox*)mediaImageScrollMediaFileListBox;
        ITUScrollText* item;

        if (listbox->focusIndex == -1)
        {
            ituListBoxGoto(listbox, imagePlayerPageIndex);
            ituListBoxSelect(listbox, imagePlayerFocusIndex);
        }

        item = ituMediaFileListPrev((ITUMediaFileListBox*)mediaImageScrollMediaFileListBox);
        imagePlayerPageIndex = listbox->pageIndex;
        imagePlayerFocusIndex = listbox->focusIndex;

        if (item)
        {
            char* filepath = (char*)ituWidgetGetCustomData(item);

            printf("Try to load %s\n", filepath);

            strncpy(imagePlayerPath, filepath, PATH_MAX);

            imagePlayerLoading = true;
        }
    }
    else if (ituRadioBoxIsChecked(mediaMusicRadioBox))  //��ǰΪ���ֲ���
    {
        ITUListBox* listbox = (ITUListBox*)mediaMusicScrollMediaFileListBox;
        ITUScrollText* item;

        if (listbox->focusIndex == -1)
        {
            ituListBoxGoto(listbox, audioPlayerPageIndex);
            ituListBoxSelect(listbox, audioPlayerFocusIndex);
        }

        item = ituMediaFileListPrev((ITUMediaFileListBox*)mediaMusicScrollMediaFileListBox);
        audioPlayerPageIndex = listbox->pageIndex;
        audioPlayerFocusIndex = listbox->focusIndex;
        if (item && audioPlayerPlaying)
        {
            char* filepath = (char*)ituWidgetGetCustomData(item);

            AudioPauseKeySound();
            AudioPlayMusic(filepath, AudioPlayerPlayCallback);
            ituTextSetString(mediaPlayCurrTimeText, NULL);
            /*audioPlayerPageIndex = listbox->pageIndex;
            audioPlayerFocusIndex = listbox->focusIndex;*/
        }
    }
    else    //��ǰΪ��Ƶ����
    {
        ITUListBox *listbox = (ITUListBox*)mediaVideoScrollMediaFileListBox;
        ITUScrollText* item;

        if (listbox->focusIndex == -1)
        {
            ituListBoxGoto(listbox, videoPlayerPageIndex);
            ituListBoxSelect(listbox, videoPlayerFocusIndex);
        }

        item = ituMediaFileListPrev((ITUMediaFileListBox*)mediaVideoScrollMediaFileListBox);

        if (item && videoPlayerIsPlaying)
        {
            char* filepath = (char*)ituWidgetGetCustomData(item);

            //AudioPauseKeySound();

            strcpy(mtal_spec.srcname, filepath);
            mtal_spec.vol_level = LastMediaPlayerVoice;

            AudioStop();
#ifdef CFG_VIDEO_ENABLE        
            mtal_pb_stop();
            mtal_pb_select_file(&mtal_spec);
            mtal_pb_play();
#endif    
            // ituWidgetSetVisible(videoPlayerViewBackground, true);
            // ituWidgetSetVisible(videoPlayerViewButton, true);
            ituTextSetString(mediaPlayCurrTimeText, NULL);

            videoPlayerPercentage = 0;
            // ituWidgetSetVisible(videoPlayerProgressBar, true);
        }
        videoPlayerPageIndex = listbox->pageIndex;
        videoPlayerFocusIndex = listbox->focusIndex;
    }

    return true;
}


