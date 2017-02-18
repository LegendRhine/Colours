/*
====================================================================================
    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    Copyright (c) 2012 by SwingCoder
====================================================================================
*/

#ifndef __FAVORFORCOPYOREDIT_H_
#define __FAVORFORCOPYOREDIT_H_

#include "ColourComponent.h"

class AreaOfFavorColours;

//==================================================================================

/** 本类为程序收藏区中的颜色块。左键单击，复制当前颜色的字符串代码。右键单击弹出菜单。
    
    创建本类对象后，必须调用继承自父类的 setEditComp()函数设置
    EditCopyOrFavor 编辑区对象！否则，本类的颜色无法置入编辑区。
    
    使用本类时可利用 ColourComponent::setCopyPrefix()确定是否复制颜色代码的前缀。
    
    @attention  本类的父级组件必须继承自 DragAnddropContainer 拖放容器类。否则，
                无法实现父级组件中拖拽本类对象来手工排序（收藏夹中更改本类对象的位置）。*/
class FavorForCopyOrEdit : public ColourComponent
{
public:
    //==============================================================================
    /** 构造函数。*/
    FavorForCopyOrEdit() : showMnem(true), mnemName(String::empty), isDrag(false) { }

    /** 析构函数。什么也不做。*/
    ~FavorForCopyOrEdit()     { }

    /** 绘制此组件的颜色和字符串，根据用户选择，显示此颜色的助记名或代码字符串。*/
    void paint(Graphics& g);

    /** 鼠标按下，准备拖拽本组件。*/
    void mouseDown(const MouseEvent& event);

    /** 拖拽本组件。*/
    void mouseDrag(const MouseEvent& event);

    /** 左键单击，复制当前颜色的字符串值。右键单击弹出菜单。
    
        弹出的菜单中可实现：编辑本类的当前颜色，将该颜色置入编辑区，编辑助记名，
        显示助记名/颜色代码，移除当前颜色（实质为设置成0x00透明黑），清空收藏区等。*/
    void mouseUp(const MouseEvent& mouseEvent);

    /** 设置此颜色的助记名。*/
    void setMnemName(const String& name) { mnemName = name; }

    /** 获取此颜色的助记名。*/
    const String& getMnemName() const { return mnemName; }

private:
    //==============================================================================
    /**  菜单项枚举值。*/
    enum MenuItemId
    {
        EDIT = 1,       /**< 编辑菜单。*/
        PUTINEDIT,      /**< 置入编辑区菜单。*/
        NAMED_MNEM,     /**< 助记符命名菜单。*/
        SHOW_MNEM,      /**< 显示收藏时给出的助记名称。*/
        SHOW_CODE,      /**< 显示该颜色的字符串代码。*/
        REMOVE,         /**< 移除菜单。*/
        CLEARALL        /**< 全部清除。*/
    };

    /** 点选菜单项后调用此函数。编辑、置入编辑区、编辑助记名、显示代码或助记名、移除、清空收藏区。

        本函数由 mouseUp()函数内部调用，因此，可将 MouseEvent 和 AreaOfFavorColours 传给本函数，
        而无需提前创建它们。
    
        @param itemId        所点选的菜单项的ID。
        @param mouseEvent    鼠标事件。
        @param areaOfFavor   此对象在本类的 mouseUp()中已通过获取父级组件并类型强转的方式得到，并转发至此。
                             由于本函数仅在 mouseUp()中内部调用一次，因此无需在本类中声明并持有此对象。*/
    bool selectOfMenuItem(const int itemId, 
        const MouseEvent& mouseEvent, 
        AreaOfFavorColours* areaOfFavor);

    /** 此布尔值为true则显示助记名称，值为false则显示颜色的代码字符串。*/
    bool showMnem;

    /** 此颜色的助记名。*/
    String mnemName;

    /** 是否拖拽的标志值。*/
    bool isDrag;

    //==============================================================================

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FavorForCopyOrEdit)
};

#endif  // __FAVORFORCOPYOREDIT_H_
