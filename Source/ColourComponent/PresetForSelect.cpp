/*
====================================================================================
    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    Copyright (c) 2012 by SwingCoder
====================================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "PresetForSelect.h"
#include "EditCopyOrFavor.h"

//==================================================================================
void PresetForSelect::mouseUp( const MouseEvent& e )
{
    // 左键单击，设置EditCopyOrFavor对象的背景色
    if (e.mods.isLeftButtonDown())
    {
        // 创建本类对象后，必须调用 setEditComp()函数设置 EditCopyOrFavor 对象！
        jassert (editCopyOrFavor != nullptr); 

        if (nullptr != editCopyOrFavor)
            editCopyOrFavor->setColour(0, colour);

        // 语泡提示
        AttributedString s;
        s.append(getStringOfColour(colour), colour);
        s.append(L"\n已置入下方的编辑区。");
        s.setFont(Font("Microsoft YaHei", 18.0f, Font::plain));

        BubbleMessageComponent* bmc = new BubbleMessageComponent();        
        bmc->setAlwaysOnTop (true);
        bmc->addToDesktop (0);
        bmc->showAt (this, s, 6000, true, true);
    }
}

