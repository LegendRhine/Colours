/*
====================================================================================
    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    Copyright (c) 2012 by SwingCoder
====================================================================================
*/

/** 内容组件. */

#include "../JuceLibraryCode/JuceHeader.h"
#include "BaseComp.h"
#include "ColourComponent/EditCopyOrFavor.h"
#include "ColourComponent/FavorForCopyOrEdit.h"
#include "ColourComponent/PresetForSelect.h"
#include "AreaOfFavorColours.h"
#include "AreaOfPresetColours.h"
#include "HelpAndAbout.h"

//==================================================================================

BaseComp::BaseComp ()     
{
    // 预置颜色区标签
    presetTitle = new Label(String::empty, L"预置颜色 (137)");
    addAndMakeVisible(presetTitle);
    presetTitle->setJustificationType(Justification::centred);
    presetTitle->setFont(16.0f);

    // 收藏夹标签
    favorTitle = new Label();
    addAndMakeVisible(favorTitle);
    favorTitle->setJustificationType(Justification::centred);
    favorTitle->setFont(16.0f);

    // 颜色显示和选择组件
    editCopyOrFavor = new EditCopyOrFavor();
    addAndMakeVisible(editCopyOrFavor);

    // 预置区
    presetViewport = new Viewport();
    addAndMakeVisible(presetViewport);
    presetViewport->setViewedComponent(
        new AreaOfPresetColours(editCopyOrFavor), true);
 
    // 收藏区    
    favorViewport = new Viewport();
    addAndMakeVisible(favorViewport);
    AreaOfFavorColours* afc = new AreaOfFavorColours(editCopyOrFavor, favorViewport);
    afc->addChangeListener(this);
    favorViewport->setViewedComponent(afc);

    // 编辑区对象设置收藏区对象，否则无法将自己的颜色传给收藏区。此处必须使用类型强转
    editCopyOrFavor->setFavorComp(afc); 
        
    // 获取收藏的颜色数量，设置收藏夹标题
	favorTitle->setText(L"收藏夹 (" + String(afc->size()) + ")", dontSendNotification);

    // 文本按钮
    for (int i = 0; i < TEXTBT_NUMS; ++i)
    {
        buttons.add(new TextButton());
        buttons[i]->addListener(this);
        buttons[i]->setSize(110, 25);
        addAndMakeVisible(buttons[i]);
    }

    buttons[COPY_PREFIX]->setButtonText(L"复制前缀(关)");
    buttons[COPY_PREFIX]->setClickingTogglesState(true);
	buttons[COPY_PREFIX]->setColour (TextButton::buttonOnColourId, Colours::lightgreen);
	buttons[COPY_PREFIX]->setToggleState(false, dontSendNotification);

    buttons[SAVE]->setButtonText(L"保存收藏夹");
    buttons[LOAD]->setButtonText(L"加载收藏夹");
    buttons[HELP]->setButtonText(L"操作指南...");
    buttons[ABOUT]->setButtonText(L"关于本软件...");

    // 本类属性
    setSize(1040, 730);
    setVisible(true);    
}
//==================================================================================
BaseComp::~BaseComp()
{
    deleteAndZero(presetTitle);
    deleteAndZero(favorTitle);
    deleteAndZero(editCopyOrFavor);
    deleteAndZero(presetViewport);
    deleteAndZero(favorViewport);
}
//==================================================================================
void BaseComp::paint( Graphics& g )
{
	g.fillAll(Colours::lightgrey); // 背景色    
    
    // 绘制各个操作区的分界线
	g.setColour(Colours::whitesmoke.withAlpha(0.6f));

    g.drawHorizontalLine(23, 1.0f, getWidth() - 1.0f);
    g.drawHorizontalLine(getHeight() - 150, 1.0f, getWidth() - 1.0f);
    g.drawVerticalLine(getWidth() - 198, 24.0f, getHeight() - 150.0f);
}

//==================================================================================
void BaseComp::resized()
{   
    // 当前颜色显示和复制区的高度
    int showAndSelectHeight = 150;

    // 预置颜色区的标签
    presetTitle->setBounds(0, 0, getWidth() - 173, 20);

    // 预置颜色区
    presetViewport->setBounds(0, 25, 
        getWidth() - (favorViewport->getViewedComponent()->getWidth() + 13), 
        getHeight() - showAndSelectHeight - 25);
    // 设置所包含的预置颜色显示区的大小
    presetViewport->getViewedComponent()->setSize(presetViewport->getWidth() - 13,
        presetViewport->getHeight());

    // 收藏区标签
    favorTitle->setBounds(presetViewport->getRight(), 0,
        favorViewport->getViewedComponent()->getWidth() + 13, 20);

    // 收藏区
    favorViewport->setBounds(presetViewport->getRight(), 25,
        favorViewport->getViewedComponent()->getWidth() + 13,         
        getHeight() - showAndSelectHeight - 25);

    // 编辑区
    editCopyOrFavor->setBounds(0, presetViewport->getBottom(), 
        getWidth() - 198, showAndSelectHeight);

    // 文本按钮
    for (int i = 0; i < TEXTBT_NUMS; ++i)
    {
        buttons[i]->setTopLeftPosition(getWidth() - 150, 
            presetViewport->getBottom() + 5 + i * 29);
    }
}
//==================================================================================
void BaseComp::buttonClicked(Button* button)
{
    if (buttons[COPY_PREFIX] == button)     // 是否复制前缀按钮
    {
        const bool copyPre = buttons[COPY_PREFIX]->getToggleState();

        buttons[COPY_PREFIX]->setButtonText(
            copyPre ? L"复制前缀(开)" : L"复制前缀(关)");

        // 编辑区设置是否复制颜色代码的前缀
        editCopyOrFavor->setCopyPrefix(copyPre);

        // 收藏区设置是否复制颜色代码的前缀
        AreaOfFavorColours* afc = 
            dynamic_cast<AreaOfFavorColours*>(favorViewport->getViewedComponent());

        if (afc != nullptr)
        {
            afc->setCopyPrefixOrNo(copyPre);
        }

    }
    else if (buttons[HELP] == button)       // 操作指南按钮
    {
        AlertWindow::showMessageBox(AlertWindow::QuestionIcon, L"操作指南",
            HelpAndAbout::getHelpString(), L"确 定");
    }
    else if (buttons[ABOUT] == button)      // 关于按钮
    {
        AlertWindow::showMessageBox(AlertWindow::InfoIcon, L"关于本软件",
            HelpAndAbout::getAboutString(), L"确 定");     
    }
    else if (buttons[SAVE] == button)       // 保存文件按钮
    {
        saveOrLoad(true);
    }
    else if (buttons[LOAD] == button)       // 加载文件按钮
    {
        saveOrLoad(false);
    }
}
//==================================================================================
/** 此回调用于更新收藏夹标题。*/
void BaseComp::changeListenerCallback (ChangeBroadcaster *source)
{
    AreaOfFavorColours* afc = dynamic_cast<AreaOfFavorColours*>(source);
	favorTitle->setText(L"收藏夹 (" + String(afc->size()) + ")", dontSendNotification);
}
//==================================================================================
void BaseComp::saveOrLoad( bool isSave )
{
    AreaOfFavorColours* afc = dynamic_cast<AreaOfFavorColours*>(
        favorViewport->getViewedComponent());

    if (afc != nullptr && isSave)
    {
        afc->saveColoursToFile();
    }
    else if (afc != nullptr && !isSave)
    {
        afc->loadColoursFromFile();
    }
}
