/*
====================================================================================
    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    Copyright (c) 2012 by SwingCoder
====================================================================================
*/

#ifndef __MAINWINDOW_H_B40ABDFA__
#define __MAINWINDOW_H_B40ABDFA__

//==================================================================================
/** 程序主窗口。*/
class MainAppWindow : public DocumentWindow
{
public:
    /** 创建程序主窗口，通过初始化基类来设置本窗口标题栏所显示的文本（程序名称）、颜色和标题栏按钮。
    
        构造函数中设置所容纳并管理的程序主界面，自身在屏幕上的位置和大小，是否可调整大小，标题栏高度，
        标题栏按钮的位置，窗口可调整的最大最小值等各种属性。*/
    MainAppWindow();

    /** 析构函数。什么也不做。*/
    ~MainAppWindow();

    /** 用户点击标题栏中的关闭按钮后，自动调用此函数。*/
    void closeButtonPressed();

private:
    /** 实时提示对象。*/
    TooltipWindow tooltip;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainAppWindow)
};

#endif  // __MAINWINDOW_H_B40ABDFA__
