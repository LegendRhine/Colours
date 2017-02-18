/*
====================================================================================
    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    Copyright (c) 2012 by SwingCoder
====================================================================================
*/

#ifndef __EDITCOPYORFAVOR_H_
#define __EDITCOPYORFAVOR_H_

#include "ColourComponent.h"

class AreaOfFavorColours;
//==================================================================================

/** 本组件为程序的编辑区，所显示的颜色可供编辑、复制或收藏。

    左键单击本组件，自动复制当前颜色的 Colours 名称或ARGB值。
    复制的结果为字符串，保存到系统剪贴板中。
    右键单击弹出菜单。菜单所执行的功能参见 MenuItemIndex 

    @attention   创建本类对象后，必须调用 setFavorComp()函数设置 AreaOfFavorColours 对象!
                 使用本类时可利用 ColourComponent::setCopyPrefix()确定是否复制颜色代码的前缀。
*/
class EditCopyOrFavor : public ColourComponent
{
public:
    // =============================================================================
    /** 创建对象，设置默认的颜色值和背景色，默认的颜色为：Colour(0xb267a6d0)*/
    EditCopyOrFavor();
    /** 析构函数。什么也不做。*/
    ~EditCopyOrFavor() {}
    
    // =============================================================================
    /** 左键单击复制颜色的文本值。右键单击弹出择色器。中键单击将当前颜色置入收藏区。*/
    void mouseUp(const MouseEvent& mouseEvent);

    /** 设置本类所需的 FavorForCopyOrEdit 对象，调用此函数之前，参数对象必须已经创建。
    
        @param areaOfFavor     收藏区对象。本类将颜色置入收藏区，实质为改变该对象的颜色属性。*/
    void setFavorComp(AreaOfFavorColours* areaOfFavor)  { areaOfFavorColours = areaOfFavor; }
    
private:
    // =============================================================================
    /** 本组件点击鼠标右键后，弹出菜单，此枚举为菜单项的索引值。*/
    enum MenuItemIndex
    {
        FAVOR_THIS = 1,                 /**< 收藏此颜色*/
        EDIT_THIS,                      /**< 编辑此颜色*/        
        BRIGHTNESS_ADD,                 /**< 增加亮度*/
        BRIGHTNESS_REDUCE,              /**< 减少亮度*/
        SATURATION_ADD,                 /**< 增加饱和度*/
        SATURATION_REDUCE,              /**< 减少饱和度*/
        ALPHA_REDUCE,                   /**< 增加透明度*/
        ALPHA_ADD,                      /**< 减少透明度*/
        HUE_ADD,                        /**< 增加HUE*/
        HUE_REDUCE,                     /**< 减少HUE*/
        ROTATE_HUE,                     /**< 翻转HUE*/
        RED_ADD,                        /**< 增加红色调*/
        RED_REDUCE,                     /**< 减少红色调*/
        GREEN_ADD,                      /**< 增加绿色调*/
        GREEN_REDUCE,                   /**< 减少绿色调*/
        BLUE_ADD,                       /**< 增加蓝色调*/
        BLUE_REDUCE,                    /**< 减少蓝色调*/
        CONTRASTING_THIS,               /**< 生成该颜色的补色*/
        GRAY_THIS,                      /**< 生成该颜色的灰度色*/
        ANOTHER_MIX_THIS,               /**< 生成与给定颜色的混合色*/
        ANOTHER_AND_THIS,               /**< 生成与给定颜色的中间色*/
        GENERATE_FROM_CODE,             /**< 生成给定的颜色*/
        GENERATE_RANDOM_BRIGHTNESS,     /**< 随机生成亮颜色*/
        GENERATE_RANDOM_DARK,           /**< 随机生成暗颜色*/
        GENERATE_RANDOM_GRAY            /**< 随机生成灰度色*/
    };

    /** 点选菜单项后调用此函数，即菜单项所执行的具体功能。*/
    void selectOfMenuItem (const int itemId, const MouseEvent &mouseEvent);

    /** 要求输入或粘贴颜色代码的对话框，根据文本框的内容返回对应的颜色。*/
    const Colour inputColourBox();

    /** 收藏区对象。本类将颜色添加到收藏区时，调用该对象的 AreaOfFavorColours::addFavorColour()函数。*/
    AreaOfFavorColours* areaOfFavorColours;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EditCopyOrFavor)
};


#endif  // __EDITCOPYORFAVOR_H_