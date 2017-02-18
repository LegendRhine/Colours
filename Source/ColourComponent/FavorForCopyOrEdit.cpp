/*
====================================================================================
    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    Copyright (c) 2012 by SwingCoder
====================================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "FavorForCopyOrEdit.h"
#include "EditCopyOrFavor.h"
#include "../AreaOfFavorColours.h"

//==================================================================================
/** 绘制此组件的颜色和名称。根据用户选择，显示此颜色的助记名或代码字符串。*/
void FavorForCopyOrEdit::paint(Graphics& g)
{
    // 绘制“棋盘”
    g.fillCheckerBoard(Rectangle<int>(0, 0, getWidth(), getHeight()),
        getHeight() / 3, getHeight() / 3, Colours::white, Colours::lightgrey);

    // 填充背景颜色
    g.fillAll(colour);

    // 当前颜色完全透明时，不绘制颜色的代码文本
    if (colour.getAlpha() != 0)
    {
        g.setFont(getHeight() / 3.0f);
        g.setColour(colour.contrasting());

        g.drawText(showMnem ? mnemName : colourString, 
            0, 0, getWidth(), getHeight(), Justification::centred, true);
    }   
}
//==================================================================================
void FavorForCopyOrEdit::mouseDown(const MouseEvent& /*e*/)
{
    isDrag = false;
}
//==================================================================================
/** 拖拽本组件。*/
void FavorForCopyOrEdit::mouseDrag(const MouseEvent& /*e*/)
{
    isDrag = true;

    // 本类的父级组件继承自DragAndDropContainer，在此强转一下
    // startDragging()用于发送鼠标拖拽方面的消息，该消息由DragAndDropTarget类自动接收并判断处理
    DragAndDropContainer* dc = dynamic_cast<DragAndDropContainer*>(getParentComponent());

    if (dc != nullptr)
        dc->startDragging(var("favorColour"), this);
}
//==================================================================================
void FavorForCopyOrEdit::mouseUp( const MouseEvent& e )
{
    // 左键单击调用父类的同名方法（复制当前颜色）
    if (!isDrag && e.mods.isLeftButtonDown())
    {
        ColourComponent::mouseUp(e);
        return;
    }
    // 右键单击弹出菜单
    if (!isDrag && e.mods.isPopupMenu())
    {
        const bool isValid = (colour.getAlpha() != 0);
        
        AreaOfFavorColours* aoc = 
            dynamic_cast<AreaOfFavorColours*>(getParentComponent());

        jassert(aoc != nullptr);  // 本类的对象必须是AreaOfFavorColours类所addAndMakeVisible()的！
            
        bool hasColour = aoc->hasOne();

        PopupMenu m;

        m.addItem(EDIT, L"编辑此颜色");
        m.addItem(PUTINEDIT, L"置入编辑区", isValid);
        m.addSeparator();
        m.addItem(NAMED_MNEM, L"编辑助记名称");
        m.addItem(SHOW_MNEM, L"显示助记名称", isValid && !showMnem);
        m.addItem(SHOW_CODE, L"显示颜色代码", isValid && showMnem);
        m.addSeparator();
        m.addItem(REMOVE, L"移除此颜色");
        m.addItem(CLEARALL, L"清空收藏区", hasColour);

        selectOfMenuItem(m.show(), e, aoc);        
    }
}
//==================================================================================
bool FavorForCopyOrEdit::selectOfMenuItem(int itemId, 
    const MouseEvent& me, AreaOfFavorColours* afc)
{
    /** 提前定义弹出窗口。此窗口用于输入或编辑此颜色的助记名。*/
    AlertWindow inputNameWindow(L"编辑助记名称", 
        L"当前颜色的代码为：" + getStringOfColour(colour) +
        L"\n\n所输入的名称只是为了助记，并不会复制到剪贴板中。", 
        AlertWindow::InfoIcon);

    inputNameWindow.addTextEditor("editName", mnemName);
    inputNameWindow.addButton(L"确 定", 1, KeyPress(KeyPress::returnKey));
    inputNameWindow.addButton(L"取 消", 0, KeyPress(KeyPress::escapeKey));

    switch (itemId)
    {
    case EDIT:         //============ 编辑当前颜色的代码
        ColourComponent::mouseUp(me);
        afc->saveColours();
        return true;

    case PUTINEDIT:         //=========== 当前颜色置入编辑区
        // 创建本类后必须调用setEditComp()设置EditCopyOrFavor对象!
        jassert (editCopyOrFavor != nullptr);  

        if (nullptr != editCopyOrFavor)
            editCopyOrFavor->setColour(0, colour);

        return true;

    case NAMED_MNEM:     //========== 输入新的助记名字符串
        if (1 == inputNameWindow.runModalLoop())
        {
            mnemName = inputNameWindow.getTextEditorContents("editName");
            showMnem = true;
            repaint();
            afc->saveColours();
            return true;
        }
        else
        {
            return false;
        }

    case SHOW_MNEM:     //========== 显示助记名字符串
        showMnem = true;
        repaint();
        return true;

    case SHOW_CODE:     //=========== 显示颜色代码
        showMnem = false;
        repaint();
        return true;

    case REMOVE:         //=========== 移除当前颜色（实质为设置成0x00透明黑）
        if (AlertWindow::showOkCancelBox(
            AlertWindow::QuestionIcon, L"确认要移除此颜色吗？", 
            L"要移除的颜色代码为：" + getStringOfColour(colour) +
            L"\n注意：此操作不可撤销。", L"确 定", L"取 消"))
        {
            colour = Colour(0x00);

            if (nullptr != afc)
                afc->deleteFavorColour();

            return true;
        }
        return false;

    case CLEARALL:         //============= 清空收藏夹，即调用
        
        if (nullptr != afc)
            afc->clearAllColours();

        return true;

    default:
        return false;
    }
}
