#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "SDL/SDL.h"
#include "scene.h"
#include "ctrlboard.h"

#define UNIT_MS     33
#define MIN_SPEED   1
#define MAX_SPEED   10


static ITUCircleProgressBar* circleCtrlCircleProgressBar;
static ITUText *circleCtrlPercentText;
ITUCheckBox* onOffCheckBox;

static bool circleCtrlPlaying;
static int circleCtrlSpeed;
static int circleCtrlStep;

/* widgets:
circleCtrlLayer
circleCtrlBackground
circleCtrlFastButton
circleCtrlSlowButton
onOffCheckBox
circleCtrlCircleProgressBar
circleCtrlPercentText
circleCtrlProgressIcon
gotoMainButton
*/

bool CircleCtrlOnEnter(ITUWidget* widget, char* param)
{
	circleCtrlCircleProgressBar = ituSceneFindWidget(&theScene, "circleCtrlCircleProgressBar");
	assert(circleCtrlCircleProgressBar);

	circleCtrlPercentText = ituSceneFindWidget(&theScene, "circleCtrlPercentText");
	assert(circleCtrlPercentText);

	onOffCheckBox = ituSceneFindWidget(&theScene, "onOffCheckBox");
	assert(onOffCheckBox);

	ituCircleProgressBarSetValue(circleCtrlCircleProgressBar, 0);
	ituTextSetString(circleCtrlPercentText, "0%");

	circleCtrlPlaying = false;
	circleCtrlSpeed = MIN_SPEED;
	circleCtrlStep = 0;

	return true;
}

bool CircleCtrlOnTimer(ITUWidget* widget, char* param)
{
	bool updated = false;
	if (circleCtrlPlaying)
	{
		static uint32_t lastTick = 0;
		uint32_t tick = SDL_GetTicks();
		char c_value[8];

		if (tick - lastTick >= UNIT_MS)
		{
			circleCtrlStep++;
			lastTick = tick;
		}

		if (circleCtrlStep >= MAX_SPEED)
		{
			int value = circleCtrlCircleProgressBar->value >= 100 ? 0 : circleCtrlCircleProgressBar->value + 1;
			ituCircleProgressBarSetValue(circleCtrlCircleProgressBar, value);

			circleCtrlStep = circleCtrlSpeed;
			sprintf(c_value, "%d%%", value);
			ituTextSetString(circleCtrlPercentText, c_value);

			updated = true;
		}
	}
	return updated;
}

bool CircleCtrlFastButtonOnPress(ITUWidget* widget, char* param)
{
	if (circleCtrlSpeed < MAX_SPEED)
		circleCtrlSpeed++;

	return true;
}

bool CircleCtrlSlowButtonOnPress(ITUWidget* widget, char* param)
{
	if (circleCtrlSpeed > MIN_SPEED)
		circleCtrlSpeed--;

	return true;
}

bool onOffCheckBoxOnPress(ITUWidget* widget, char* param)
{
	if (ituCheckBoxIsChecked(onOffCheckBox))
	{
		circleCtrlPlaying = true;
	}
	else
	{
		circleCtrlPlaying = false;
	}

	return true;
}

