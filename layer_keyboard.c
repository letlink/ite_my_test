#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "SDL/SDL.h"
#include "scene.h"
#include "ctrlboard.h"
/* widgets:
keyboardLayer
keyboardBackground
numberKeyboard
kbEnterButton
kbDelButton
kbNmuber0Button
kbNmuber9Button
kbNmuber8Button
kbNmuber7Button
kbNmuber6Button
kbNmuber5Button
kbNmuber4Button
kbNmuber3Button
kbNmuber2Button
kbNmuber1Button
inputTextBox
gotoMainButton
split2Background
split1Background
*/

bool KbEnterButtonOnPress(ITUWidget* widget, char* param)
{
    return true;
}

