#include <assert.h>
#include "scene.h"
#include "ite/itp.h"
/* widgets:
ioTestLayer
ioTestBackground
TextBox29
rcvdClearButton
ioValueText
ioReadTitleText
ioWriteLButton
ioWriteHButton
spiWriteButton
spiReadButton
iicWriteButton
iicReadButton
uartSendButton
sendTitleText
rcvdTitleText
sendTextBox
gotoMainButton
rcvdTextBox
*/
static ITUTextBox* sendTextBox;
static ITUTextBox* rcvdTextBox;
char* pstr = 0;
char SendStr[256];
char GetStr[256];

bool IOTestOnEnter(ITUWidget* widget, char* param)
{

    sendTextBox = ituSceneFindWidget(&theScene, "sendTextBox");
    assert(sendTextBox);
    rcvdTextBox = ituSceneFindWidget(&theScene, "rcvdTextBox");
    assert(rcvdTextBox);

    rcvdTextBox->maxLen = 256;

    return true;
}

bool IOTestOnTimer(ITUWidget* widget, char* param)
{
    int len = 0;
    static int index = 0;
    char StrTemp[256];

    len = read(ITP_DEVICE_UART1, GetStr, 256);

     if (len > 0)
    {
        //strcpy(rcvdTextBox->text.stringSet->strings[0], pstr);
         sprintf(StrTemp, "%s", GetStr);
        ituTextBoxInput(rcvdTextBox, StrTemp);
        //index++;
    }
    return true;
}

bool RcvdClearButtonOnPress(ITUWidget* widget, char* param)
{
    ituTextBoxSetString(rcvdTextBox, NULL);
    return true;
}

bool IOReadButtonOnPress(ITUWidget* widget, char* param)
{
    return true;
}

bool IOWriteButtonOnPress(ITUWidget* widget, char* param)
{
    return true;
}

bool SPIWriteButtonOnPress(ITUWidget* widget, char* param)
{
    return true;
}

bool IICWriteButtonOnPress(ITUWidget* widget, char* param)
{
    return true;
}

bool IICReadButtonOnPress(ITUWidget* widget, char* param)
{
    return true;
}

bool UartSendButtonOnPress(ITUWidget* widget, char* param)
{
    
    //pstr = ituTextBoxGetString(sendTextBox);
    pstr = sendTextBox->text.stringSet->strings[0];
    sprintf(SendStr, "%s", pstr);
    write(ITP_DEVICE_UART1, SendStr, strlen(SendStr));

    //ituTextBoxInput(rcvdTextBox, "1234");
    return true;
}

