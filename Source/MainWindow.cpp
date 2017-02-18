/*
====================================================================================
    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    Copyright (c) 2012 by SwingCoder
====================================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainWindow.h"
#include "BaseComp.h"

//==================================================================================
MainAppWindow::MainAppWindow()
    : DocumentWindow (JUCEApplication::getInstance()->getApplicationName(),
                      Colours::lightgrey,
                      DocumentWindow::allButtons)
{   
    // 内容组件.
    BaseComp* baseComp = new BaseComp();
    setContentOwned(baseComp, true);
    
    // 自身属性
    centreWithSize (baseComp->getWidth(), baseComp->getHeight());
    setResizable(true, false);
    setResizeLimits(840, 528, 4096, 4096);
	setUsingNativeTitleBar (true);
    setTitleBarButtonsRequired(7, true);
    setVisible (true);

    baseComp->grabKeyboardFocus();
}
//==================================================================================
MainAppWindow::~MainAppWindow()
{    
}
//==================================================================================
void MainAppWindow::closeButtonPressed()
{
    JUCEApplication::getInstance()->systemRequestedQuit();
}

