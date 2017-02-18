/*
====================================================================================
    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    Copyright (c) 2012 by SwingCoder
====================================================================================
*/

#ifndef __PRESETFORSELECT_H_
#define __PRESETFORSELECT_H_

#include "ColourComponent.h"

//==================================================================================

/** 本类为预置区中的某个颜色块，用于显示Colours类中定义的某一个颜色。

    左键单击，用当前所显示的颜色设置 EditCopyOrFavor 对象（编辑区）的颜色，
    即将此颜色赋值给编辑区对象（置入编辑区），供复制、编辑或收藏。
    
    @attention  创建本类对象后，必须调用 setEditComp()函数设置 EditCopyOrFavor 对象。
                否则，本类的颜色无法通过鼠标左键单击的方式置入该对象。*/
class PresetForSelect : public ColourComponent
{
public:
    /** 构造函数，什么也不做。*/
    PresetForSelect()         { }
    /** 析构函数，什么也不做。*/
    ~PresetForSelect()        { }

    /** 左键单击设置 EditCopyOrFavor 对象（即编辑区）的背景。*/
    void mouseUp(const MouseEvent& mouseEvent);

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PresetForSelect)
};

#endif  // __PRESETFORSELECT_H_
