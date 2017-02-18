/*
====================================================================================
    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    Copyright (c) 2012 by SwingCoder
====================================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "EditCopyOrFavor.h"
#include "../AreaOfFavorColours.h"

//==================================================================================
EditCopyOrFavor::EditCopyOrFavor() : areaOfFavorColours(nullptr)
{    
    setColour(0, Colour(0xb267a6d0));
}
//==================================================================================
void EditCopyOrFavor::mouseUp(const MouseEvent& e)
{
    // 中键单击，收藏颜色，而后退出本函数
    if (e.mods.isMiddleButtonDown())
    {       
        // 创建本类对象后，必须调用 setFavorComp()函数设置 AreaOfFavorColours 对象!
        jassert (areaOfFavorColours != nullptr); 
            
        if (nullptr != areaOfFavorColours)
        {
            areaOfFavorColours->addFavorColour(getColour());
            return;
        }
    }

    // 左键单击，调用父类的同名函数，复制颜色
    else if (e.mods.isLeftButtonDown())
    {
        ColourComponent::mouseUp(e);
    }
    // 右键单击，弹出菜单
    else if (e.mods.isRightButtonDown())
    {
        PopupMenu m;
        m.addItem(FAVOR_THIS,    L"收藏此颜色", colour.getAlpha() != 0);
        m.addItem (EDIT_THIS,    L"编辑此颜色");
        m.addSeparator();

        PopupMenu mb;
        mb.addItem (BRIGHTNESS_ADD,    L"增加亮度", colour.getBrightness() != 1.0f);
        mb.addItem (BRIGHTNESS_REDUCE, L"减少亮度", colour.getBrightness() != 0.0f);
        m.addSubMenu(L"增减亮度", mb);

        PopupMenu ms;
        ms.addItem (SATURATION_ADD,    L"增加饱和度", colour.getSaturation() != 1.0f);
        ms.addItem (SATURATION_REDUCE, L"减少饱和度", colour.getSaturation() != 0.0f);
        m.addSubMenu(L"增减饱和度", ms);

        PopupMenu ma;
        ma.addItem (ALPHA_REDUCE,      L"增加透明度", colour.getAlpha() != 0);
        ma.addItem (ALPHA_ADD,         L"减少透明度", colour.getAlpha() != 0xff);
        m.addSubMenu(L"增减透明度", ma);

        PopupMenu mh;
        mh.addItem (HUE_ADD,           L"增加HUE", colour.getHue() != 1.0f);
        mh.addItem (HUE_REDUCE,        L"减少HUE", colour.getHue() != 0.0f);
        mh.addItem (ROTATE_HUE,        L"翻转HUE");
        m.addSubMenu(L"增减和翻转HUE", mh);

        PopupMenu mRgb;
        mRgb.addItem (RED_ADD,         L"增加红色调", colour.getRed() != 0xff);
        mRgb.addItem (RED_REDUCE,      L"减少红色调", colour.getRed() != 0);
        mRgb.addSeparator();
        mRgb.addItem (GREEN_ADD,       L"增加绿色调", colour.getGreen() != 0xff);
        mRgb.addItem (GREEN_REDUCE,    L"减少绿色调", colour.getGreen() != 0);
        mRgb.addSeparator();
        mRgb.addItem (BLUE_ADD,        L"增加蓝色调", colour.getBlue() != 0xff);
        mRgb.addItem (BLUE_REDUCE,     L"减少蓝色调", colour.getBlue() != 0);
        m.addSubMenu(L"增减红绿蓝色调", mRgb);
        m.addSeparator();

        PopupMenu mr;
        mr.addItem (GENERATE_RANDOM_BRIGHTNESS,   L"随机生成亮颜色");
        mr.addItem (GENERATE_RANDOM_DARK,         L"随机生成暗颜色");
        mr.addItem (GENERATE_RANDOM_GRAY,         L"随机生成灰度色");
        m.addSubMenu(L"随机生成新颜色", mr);

        PopupMenu mg;
        mg.addItem (CONTRASTING_THIS,     L"生成该颜色的补色");
        mg.addItem (GRAY_THIS,            L"生成该颜色的灰度色");
        mg.addSeparator();
        mg.addItem (ANOTHER_MIX_THIS,     L"生成与给定颜色的混合色");
        mg.addItem (ANOTHER_AND_THIS,     L"生成与给定颜色的中间色");
        m.addSubMenu(L"基于该颜色生成新的颜色", mg);
        m.addSeparator();

        m.addItem (GENERATE_FROM_CODE,  L"生成给定的颜色");

        const int slt = m.show();
        selectOfMenuItem(slt, e);
    }
}
//==================================================================================
void EditCopyOrFavor::selectOfMenuItem (const int itemId, 
    const MouseEvent &mouseEvent)
{
    uint8 value = jmax(colour.getRed(), colour.getGreen(), colour.getBlue());
    float f = colour.getAlpha() / 255.0f;
    uint8 r = colour.getRed();
    uint8 g = colour.getGreen();
    uint8 b = colour.getBlue();
    uint8 a = colour.getAlpha();

    switch (itemId)
    {
    case FAVOR_THIS:    // 收藏
        // 创建本类对象后，必须调用 setFavorComp()函数设置 AreaOfFavorColours 对象!
        jassert (areaOfFavorColours != nullptr);

        if (nullptr != areaOfFavorColours)
        {
            areaOfFavorColours->addFavorColour(getColour());
            return;
        }
        break;

    case EDIT_THIS:     // 弹出择色器编辑此颜色
        ColourComponent::mouseUp(mouseEvent);
        break;

    case BRIGHTNESS_ADD:    // 增加亮度 
        colour = colour.withBrightness(colour.getBrightness() + 0.1f);
        break;

    case BRIGHTNESS_REDUCE:       // 减少亮度
        colour = colour.withBrightness(colour.getBrightness() - 0.1f);
        break;

    case SATURATION_ADD:    // 增减饱和度
        colour = colour.withSaturation(colour.getSaturation() + 0.1f);
        break;

    case SATURATION_REDUCE:       
        colour = colour.withSaturation(colour.getSaturation() - 0.1f);
        break;

    case ALPHA_REDUCE:    // 增减透明度
        f -= 0.1f;

        if (f <= 0)
        {
            f = 0;
        }

        colour = colour.withAlpha(f);
        break;

    case ALPHA_ADD:    // 增减透明度
        f += 0.1f;

        if (f >= 1.0f)
        {
            f = 1.0f;
        }

        colour = colour.withAlpha(f);
        break;

    case HUE_ADD:   // 增减和翻转hue
        colour = colour.withHue(colour.getHue() + 0.1f);
        break;

    case HUE_REDUCE:      
        colour = colour.withHue(colour.getHue() - 0.1f);
        break;

    case ROTATE_HUE:      
        colour = colour.withRotatedHue(0.50f);
        break;

    case RED_ADD:   // 增减红绿蓝
        r = (r >= 230) ? 255 : r + 25;
        colour = Colour(r, g, b, a);
        break;

    case RED_REDUCE: 
        r = (r <= 25) ? 0 : r - 25;
        colour = Colour(r, g, b, a);
        break;

    case GREEN_ADD: 
        g = (g >= 230) ? 255 : g + 25;
        colour = Colour(r, g, b, a);
        break;

    case GREEN_REDUCE: 
        g = (g <= 25) ? 0 : g - 25;
        colour = Colour(r, g, b, a);
        break;

    case BLUE_ADD:  
        b = (b >= 230) ? 255 : b + 25;
        colour = Colour(r, g, b, a);
        break;

    case BLUE_REDUCE:  
        b = (b <= 25) ? 0 : b - 25;
        colour = Colour(r, g, b, a);
        break;

    case CONTRASTING_THIS:  // 补色
        colour = colour.contrasting(0.9f);
        break;

    case GRAY_THIS:       // 灰度色
        colour = Colour(value, value, value, a);
        break;

    case ANOTHER_MIX_THIS:        // 混合给出的颜色
        colour = colour.overlaidWith(inputColourBox().withAlpha(0.5f));
        break;

    case ANOTHER_AND_THIS:        // 中间色
        colour = colour.interpolatedWith(inputColourBox(), 0.5f);
        break;

    case GENERATE_FROM_CODE:      // 生成给出代码所表示的颜色
        colour = inputColourBox();
        break;

    case GENERATE_RANDOM_BRIGHTNESS:    // 随机生成亮颜色
        colour = Colour (Random::getSystemRandom().nextFloat(), 0.2f, 0.9f, 1.0f);
        break;

    case GENERATE_RANDOM_DARK:      // 随机生成暗颜色
        colour = Colour (Random::getSystemRandom().nextFloat(), 0.8f, 0.3f, 1.0f);
        break;

    case GENERATE_RANDOM_GRAY:      // 随机生成灰度色
        colour = Colour::greyLevel(Random::getSystemRandom().nextFloat());
        break;
    
    default: break;
    }

    colourString = getStringOfColour(colour);
    repaint();
}
//==================================================================================
const Colour EditCopyOrFavor::inputColourBox()
{
    AlertWindow giveColour(L"请给出所需的颜色", 
        L"文本框中默认为系统剪贴板中的内容。给出的颜色带不带前缀均可。\n\n" 
        L"Colours名称和ARGB值均可识别。无法识别的内容自动转为纯白色。",
        AlertWindow::QuestionIcon);

    // 防止剪贴板中的内容有回车换行符
    String s(SystemClipboard::getTextFromClipboard());
    s = s.removeCharacters("\r\n");
    giveColour.addTextEditor("inputColour", s);
    
    giveColour.addButton(L"确 定", 1, KeyPress(KeyPress::returnKey));
    giveColour.addButton(L"取 消", 0, KeyPress(KeyPress::escapeKey));
    
    if(giveColour.runModalLoop() == 0)
        return colour;

    String colourCode(giveColour.getTextEditorContents("inputColour"));

    // 如果字符串中有前缀Colour(...)、Colours::...则去除之
    if (colourCode.contains("Colour("))
        colourCode = colourCode.trimCharactersAtStart("Colour(").removeCharacters(")");

    else if (colourCode.contains("Colours::"))
        colourCode = colourCode.fromFirstOccurrenceOf("Colours::", false, false);

    // 如果不是0x开头（即Colours名称，而非ARGB值），则直接返回其颜色
    if (!colourCode.startsWithIgnoreCase("0x"))
        return Colours::findColourForName(colourCode, Colour(0xffffffff));

    return Colour::fromString(colourCode);
}
