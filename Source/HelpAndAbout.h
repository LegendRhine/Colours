/*
====================================================================================
    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    Copyright (c) 2012 by SwingCoder
====================================================================================
*/

#ifndef __HELPANDABOUT_H_
#define __HELPANDABOUT_H_

#include "../JuceLibraryCode/JuceHeader.h"

//==================================================================================
/** 提供程序中其它类或函数所需的帮助文本和“关于”文本，两个静态函数的返回值均为const String。*/
class HelpAndAbout
{
public:
    /** 返回本程序的帮助文本。*/
	static const String getHelpString()
    {
        String s;

        s << L"操作界面分为四个区域：" << newLine << newLine <<
            L"左上最大的区域为预置区，列举了 Colours 类的所有静态颜色值。鼠标左键" << newLine <<
            L"点击某个颜色，可将其置入下方的编辑区，供编辑、复制或收藏。" << newLine
            << newLine <<
            L"右上为收藏区，列举当前收藏的所有颜色。本程序最多可收藏999种不同的颜" << newLine <<
            L"色。鼠标左键点击将该颜色的文本代码复制到系统剪贴板中，右键点击弹出菜" << newLine <<
            L"单，可进一步编辑此颜色，设置助记名，或将其置入编辑区。还可以移除之，" << newLine <<
            L"或者清空整个收藏区。鼠标拖拽，可对当前所收藏某个颜色进行手工排序。" << newLine 
            << newLine <<
            L"为便于使用，每个收藏的颜色建议定义助记名，可随时编辑该名称。通过菜单    " << newLine <<
            L"可切换显示该颜色的助记名或颜色代码。程序默认显示助记名。" << newLine 
            << newLine <<
            L"左下为编辑区，显示当前所选择的颜色。左键点击复制该颜色的代码；中键点" << newLine <<
            L"击将其添加到收藏夹的末尾或第一个空白处；右键点击弹出菜单，供编辑此颜" << newLine <<
            L"色或生成新的颜色。可弹出择色器进行可视化编辑。" << newLine
            << newLine <<
            L"右下为按钮区，最上面的按钮为开关式，可设置是否复制颜色代码的前缀，" << newLine <<
            L"其余按钮用于保存和加载收藏夹文件，查看操作指南和版权信息等。" << newLine
            << newLine <<
            L"可保存当前的收藏夹，文件扩展名为：*.clr。还可以从已经保存的文件中" << newLine <<
            L"加载。注意：加载后将重置当前收藏夹。以后每次启动，默认即为上次退出" << newLine <<
            L"时的收藏夹。因此，为保险起见，加载之前最好先保存当前的收藏夹。" << newLine 
            << newLine <<
            L"关于复制的结果：如果该颜色对应Colours中定义的名称，则复制该名称。" << newLine <<
            L"否则复制ARGB值（0xAARRGGBB ）。注意：完全透明的颜色不予复制。";

        return s;
    }
    //==============================================================================
    /** 返回本程序的“关于”文本。*/
    static const String getAboutString()
    {
        String s;

        s << L"SwingColours是程序员在选择颜色和书写颜色代码时的好帮手。" << newLine <<
            L"可将某个颜色的代码复制到系统剪贴板，以便粘贴到源代码中。" << newLine 
            << newLine <<
            L"支持生成、收藏、编辑和助记任何颜色，收藏夹可保存和加载。" << newLine <<
            newLine <<            
            L"作者：SwingCoder  " << L"  邮箱: miti-net@126.com" << newLine <<
            "https://github.com/SwingCoder" << newLine << newLine <<
            L"SwingColours V1.0    (C) 2012版权所有";

        return s;
    }

private:
    HelpAndAbout();
    ~HelpAndAbout();
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(HelpAndAbout)
};

#endif  // __HELPANDABOUT_H_

