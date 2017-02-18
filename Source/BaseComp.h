/*
================================================================================
    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    Copyright (c) 2012 by SwingCoder
================================================================================
*/

#ifndef __BASECOMP_H_
#define __BASECOMP_H_

class EditCopyOrFavor;

//==============================================================================
/** 本程序的主界面。*/
class BaseComp : 
    public Component, 
    public Button::Listener,
    public ChangeListener
{
public:
    /** 创建本程序的主界面。*/
    BaseComp ();

    /** 销毁主界面。*/
    ~BaseComp();

    /** 绘制主界面的背景和各个操作区的分界线。*/
    void paint(Graphics& g);

    /** 确定主界面中所有控件和元素的布局定位。*/
    void resized();

    /** 点击按钮后，自动执行此函数。*/
    void buttonClicked(Button* button);

    /** ChangeBroadcaster对象绑定本类并产生消息后，此回调用于更新收藏夹标题。*/
    void changeListenerCallback (ChangeBroadcaster *source);

    /** 设置收藏夹标题，显示当前的收藏数量。*/
    void setFavorLabelText(int favoredNums);
    
private:
    /** 保存或加载收藏夹。
    
        @param isSave   如果为true，则为保存当前的收藏夹。
                        如果为false，则为加载已有的收藏夹。*/
    void saveOrLoad(bool isSave);

    /** 此标签用于显示预置区标题。*/
    Label* presetTitle;

    /** 此标签用于显示显示收藏区标题。*/
    Label* favorTitle;

    /** 编辑区对象。*/
    EditCopyOrFavor* editCopyOrFavor;

    /** 预置区的Viewport。*/
    Viewport* presetViewport;

    /** 收藏区的Viewport。*/
    Viewport* favorViewport;

    /** 文本按钮数组所用的枚举值。*/
    enum TextButtonsEnum
    {
        COPY_PREFIX,    /**< 是否复制代码前缀*/
        SAVE,           /**< 保存按钮的枚举值*/
        LOAD,           /**< 加载按钮的枚举值*/
        HELP,           /**< 帮助按钮的枚举值*/
        ABOUT,          /**< 关于按钮的枚举值*/
        TEXTBT_NUMS     
    };

    /** 文本按钮。*/
    OwnedArray<TextButton> buttons;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BaseComp)
};

#endif  // __BASECOMP_H_
