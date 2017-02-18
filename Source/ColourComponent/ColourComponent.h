/*
====================================================================================
    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    Copyright (c) 2012 by SwingCoder
====================================================================================
*/

#ifndef __COLOURCOMPONENT_H_
#define __COLOURCOMPONENT_H_

class EditCopyOrFavor;

//==================================================================================
/** 由某一颜色填充背景的组件。

    左键单击，将当前颜色的字符串值复制到系统剪贴板中。
    右键单击弹出择色器，获取所选择的颜色并实时改变本组件的背景。*/
class ColourComponent : public Component, public ChangeListener
{
public:
    /** 创建对象，设置鼠标位于本组件时的形状（小手）。*/
    ColourComponent();
    
    /** 析构函数。什么也不做。*/
    virtual ~ColourComponent(){}

    /** 填充背景颜色，显示该颜色的Colours文本值或ARGB值。
    
        并且当鼠标位于本组件时，显示一个视觉效果以提醒用户。*/
    virtual void paint(Graphics& g);
    //==============================================================================
    /** 获取所传入的颜色及其文本代码，并以此颜色填充本组件的背景。
    
        @param colourId     此参数未使用，仅仅是继承自父类
        @param colour       所传入的颜色*/
    virtual void setColour(const int colourId, const Colour& colour);

    /** 获取当前的背景颜色。*/
    virtual const Colour getColour() const      { return colour; }
    //==============================================================================
    /** 鼠标指向本组件时，触发重绘，给予视觉效果提示。*/
    virtual void mouseEnter(const MouseEvent& mouseEvent);

    /** 鼠标离开本组件时，触发重绘，取消视觉效果提示。*/
    virtual void mouseExit(const MouseEvent& mouseEvent);

    /** 鼠标点击本组件后，执行相应的操作。左键复制颜色代码，右键弹出择色器。*/
    virtual void mouseUp(const MouseEvent& mouseEvent);
    //==============================================================================
    /** 设置EditCopyOrFavor对象，专供派生类使用。
    
        @attention  调用此函数之前，参数对象必须已创建！*/
    virtual void setEditComp(EditCopyOrFavor* editObj) { editCopyOrFavor = editObj; }

    /** 是否复制颜色代码前缀。*/
    virtual void setCopyPrefix(const bool& copyOrNo) { copyPrefix = copyOrNo; }
    //==============================================================================
    /** 捕获到 ChangeBroadcaster 对象的消息后，此函数自动进行判断处理。
    
        如果本函数的参数对象继承自ChangeBroadcaster，且已经绑定了本类进行可变捕获，
        则参数对象发生变化或产生的消息由此函数判断处理。
        
        @param source   继承自ChangeBroadcaster类的对象。*/
    virtual void changeListenerCallback(ChangeBroadcaster *source);
    //==============================================================================
    /** 获取给定颜色的代码。如果匹配 Colours 类所定义的颜色名称，则返回该名称，否则返回ARGB值。

        @param colour   返回该颜色的代码字符串。
    
        @note   Colours类中定义的颜色共有137种。*/
    static const String getStringOfColour(const Colour& colour);

protected:
    /** 本组件的颜色对象。*/
    Colour colour;
    /** 颜色对象的代码字符串*/
    String colourString;
    /** 编辑区对象。该对象的类由本类所派生。*/
    EditCopyOrFavor* editCopyOrFavor;  
    /** 是否复制颜色代码前缀的标志值。*/
    bool copyPrefix;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ColourComponent)
};


#endif  // __COLOURCOMPONENT_H_
