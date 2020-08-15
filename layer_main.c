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

static ITUText* titleText;    //���ڻ�ȡ�ı��ؼ��ľ������������ͨ���þ���������ؼ�
uint32_t count_num = 0;  //���ڼ�¼���������ı���

//�����������ʱ���Զ����øú�������˿����ڸú�����ִ��һЩ��ʼ�����������ȡ�ؼ�����������ı���ʼֵ�ȡ�
bool MainOnEnter(ITUWidget* widget, char* param)
{
	titleText = ituSceneFindWidget(&theScene, "titleText");
	assert(titleText);

	return true;
}

//Down��ť����ʱ���Զ����øú���������������ʵ�����ּ��ٵĹ���
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

//Up��ť����ʱ���Զ����øú���������������ʵ���������ӵĹ���
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

