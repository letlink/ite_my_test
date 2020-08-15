#include <assert.h>
#include "scene.h"
# include <stdio.h>
# include <stdlib.h>
/* widgets:
mainLayer
mainBackground
textBackground
titleText
downButton
upButton
*/

static ITUText* titleText;    //用于获取文本控件的句柄，后续可以通过该句柄来操作控件
uint32_t count_num = 0;  //用于记录数字增减的变量

//启动进入界面时会自动调用该函数，因此可以在该函数中执行一些初始化工作，如获取控件句柄、设置文本初始值等。
bool MainOnEnter(ITUWidget* widget, char* param)
{
	titleText = ituSceneFindWidget(&theScene, "titleText");
	assert(titleText);

	return true;
}

//Down按钮按下时会自动调用该函数，我们在其中实现数字减少的功能
bool DownButtonPress(ITUWidget* widget, char* param)
{
	char str[10];
	
	if (count_num > 0)
	{
		count_num--;
	}
	else
	{
		count_num = 20;
	}
	itoa(count_num, str, 10);
	ituTextSetString(titleText, str);
	return true;
}

//Up按钮按下时会自动调用该函数，我们在其中实现数字增加的功能
bool UpButtonPress(ITUWidget* widget, char* param)
{
	char str[10];
	if (++count_num > 20)
	{
		count_num = 0;
	}
	itoa(count_num, str, 10);
	ituTextSetString(titleText, str);
	return true;
}

