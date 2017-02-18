/*
====================================================================================
    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    Copyright (c) 2012 by SwingCoder
====================================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "ColourComponent.h"

ColourComponent::ColourComponent() 
    : colour(0x00), 
    colourString(colour.toString()), 
    editCopyOrFavor(nullptr), 
    copyPrefix(false)
{
    setMouseCursor (MouseCursor::PointingHandCursor);
}
//==================================================================================

void ColourComponent::paint( Graphics& g )
{
    // 绘制“棋盘”
    g.fillCheckerBoard(Rectangle<int>(0, 0, getWidth(), getHeight()),
        getHeight() / 3, getHeight() / 3, Colours::white, Colours::lightgrey);

    // 填充背景颜色
    g.fillAll(colour);

    // 当前颜色完全透明时，不绘制颜色的文本值
    if (colour.getAlpha() != 0)
    {
        g.setFont(getHeight() / 3.2f);
        g.setColour(colour.contrasting());
        g.drawText(colourString, 0, 0, getWidth(), getHeight(), 
            Justification::centred, true);
    }    

    // 如果鼠标指向本组件，则绘制边框以起到视觉提示的效果
    if (isMouseOver(true) && colour.getAlpha() != 0)
    {
        g.setColour(Colour(0xffededed));
        g.drawRect(0, 0, getWidth(), getHeight(), 3);
    }
}
//==================================================================================

void ColourComponent::setColour(const int /*colourId*/, const Colour& clr)
{
    colour = clr;
    colourString = getStringOfColour(clr);
    repaint();
}
//==================================================================================
void ColourComponent::mouseEnter(const MouseEvent& /*e*/)
{
    repaint();
}

void ColourComponent::mouseExit(const MouseEvent& /*e*/)
{
    repaint();
}
//==================================================================================
void ColourComponent::mouseUp(const MouseEvent& e)
{
    // 左键单击，将当前颜色的字符串值复制到系统剪贴板中
    if (e.mods.isLeftButtonDown())
    {
        // 不复制完全透明的颜色
        if (colour.getAlpha() == 0)
        {
            AttributedString s;        
            s.append(L"完全透明的颜色没有必要复制。");
            s.setFont(Font(L"微软雅黑", 18.0f, Font::plain));

            BubbleMessageComponent* bmc = new BubbleMessageComponent();        
            bmc->setAlwaysOnTop (true);
            bmc->addToDesktop (0);
            bmc->showAt(this, s, 6000, true, true);

            return;
        }

        String sc = getStringOfColour(colour);

        if (!copyPrefix)  // 不复制前缀
        {
            if (sc.contains("Colours::"))
                sc = sc.fromFirstOccurrenceOf("Colours::", false, false);
            else
                sc = sc.trimCharactersAtStart("Colour(").removeCharacters(")");
        }

        SystemClipboard::copyTextToClipboard(sc);

        // 语泡提示
        AttributedString s;
        s.append(sc, colour);
        s.append(L"\n已复制到系统剪贴板。");
        s.setFont(Font(L"微软雅黑", 18.0f, Font::plain));

        BubbleMessageComponent* bmc = new BubbleMessageComponent();        
        bmc->setAlwaysOnTop (true);
        bmc->addToDesktop (0);
        bmc->showAt (this, s, 6000, true, true);
        LookAndFeel::getDefaultLookAndFeel().playAlertSound();

        return;
    }
    // 右键单击，弹出择色器，位于标注窗口中
    if (e.mods.isRightButtonDown())  
    {
        ColourSelector colourSelector;

        // 绑定可变捕获器
        colourSelector.addChangeListener (this);
        colourSelector.setColour (ColourSelector::backgroundColourId, Colour(0xffededed));
        colourSelector.setSize (460, 500);
        colourSelector.setCurrentColour(colour);

        // 创建并弹出标注窗口，模态运行
        CallOutBox callOut (colourSelector, getBounds(), nullptr);
        callOut.runModalLoop();
    }
}
//==================================================================================
void ColourComponent::changeListenerCallback(ChangeBroadcaster *source)
{
    // 定义一个颜色选择器指针型对象，参数对象强转为同类型的指针对象后赋值
    ColourSelector* cs = dynamic_cast <ColourSelector*> (source);
    setColour(0, cs->getCurrentColour());
}
//==================================================================================
const String ColourComponent::getStringOfColour(const Colour& c)
{
    if (c == Colours::aliceblue)            return "Colours::aliceblue";
    if (c == Colours::antiquewhite)         return "Colours::antiquewhite";
    if (c == Colours::aqua)                 return "Colours::aqua";
    if (c == Colours::aquamarine)           return "Colours::aquamarine";
    if (c == Colours::azure)                return "Colours::azure";
    if (c == Colours::beige)                return "Colours::beige";
    if (c == Colours::bisque)               return "Colours::bisque";
    if (c == Colours::black)                return "Colours::black";
    if (c == Colours::blanchedalmond)       return "Colours::blanchedalmond";
    if (c == Colours::blue)                 return "Colours::blue";
    if (c == Colours::blueviolet)           return "Colours::blueviolet";
    if (c == Colours::brown)                return "Colours::brown";
    if (c == Colours::burlywood)            return "Colours::burlywood";
    if (c == Colours::cadetblue)            return "Colours::cadetblue";
    if (c == Colours::chartreuse)           return "Colours::chartreuse";
    if (c == Colours::chocolate)            return "Colours::chocolate";
    if (c == Colours::coral)                return "Colours::coral";
    if (c == Colours::cornflowerblue)       return "Colours::cornflowerblue";
    if (c == Colours::cornsilk)             return "Colours::cornsilk";
    if (c == Colours::crimson)              return "Colours::crimson";
    if (c == Colours::cyan)                 return "Colours::cyan";
    if (c == Colours::darkblue)             return "Colours::darkblue";
    if (c == Colours::darkcyan)             return "Colours::darkcyan";
    if (c == Colours::darkgoldenrod)        return "Colours::darkgoldenrod";
    if (c == Colours::darkgrey)             return "Colours::darkgrey";
    if (c == Colours::darkgreen)            return "Colours::darkgreen";
    if (c == Colours::darkkhaki)            return "Colours::darkkhaki";
    if (c == Colours::darkmagenta)          return "Colours::darkmagenta";
    if (c == Colours::darkolivegreen)       return "Colours::darkolivegreen";
    if (c == Colours::darkorange)           return "Colours::darkorange";
    if (c == Colours::darkorchid)           return "Colours::darkorchid";
    if (c == Colours::darkred)              return "Colours::darkred";
    if (c == Colours::darksalmon)           return "Colours::darksalmon";
    if (c == Colours::darkseagreen)         return "Colours::darkseagreen";
    if (c == Colours::darkslateblue)        return "Colours::darkslateblue";
    if (c == Colours::darkslategrey)        return "Colours::darkslategrey";
    if (c == Colours::darkturquoise)        return "Colours::darkturquoise";
    if (c == Colours::darkviolet)           return "Colours::darkviolet";
    if (c == Colours::deeppink)             return "Colours::deeppink";
    if (c == Colours::deepskyblue)          return "Colours::deepskyblue";
    if (c == Colours::dimgrey)              return "Colours::dimgrey";
    if (c == Colours::dodgerblue)           return "Colours::dodgerblue";
    if (c == Colours::firebrick)            return "Colours::firebrick";
    if (c == Colours::floralwhite)          return "Colours::floralwhite";
    if (c == Colours::forestgreen)          return "Colours::forestgreen";
    if (c == Colours::fuchsia)              return "Colours::fuchsia";
    if (c == Colours::gainsboro)            return "Colours::gainsboro";
    if (c == Colours::gold)                 return "Colours::gold";
    if (c == Colours::goldenrod)            return "Colours::goldenrod";
    if (c == Colours::grey)                 return "Colours::grey";
    if (c == Colours::green)                return "Colours::green";
    if (c == Colours::greenyellow)          return "Colours::greenyellow";
    if (c == Colours::honeydew)             return "Colours::honeydew";
    if (c == Colours::hotpink)              return "Colours::hotpink";
    if (c == Colours::indianred)            return "Colours::indianred";
    if (c == Colours::indigo)               return "Colours::indigo";
    if (c == Colours::ivory)                return "Colours::ivory";
    if (c == Colours::khaki)                return "Colours::khaki";
    if (c == Colours::lavender)             return "Colours::lavender";
    if (c == Colours::lavenderblush)        return "Colours::lavenderblush";
    if (c == Colours::lemonchiffon)         return "Colours::lemonchiffon";
    if (c == Colours::lightblue)            return "Colours::lightblue";
    if (c == Colours::lightcoral)           return "Colours::lightcoral";
    if (c == Colours::lightcyan)            return "Colours::lightcyan";
    if (c == Colours::lightgoldenrodyellow) return "Colours::lightgoldenrodyellow";
    if (c == Colours::lightgreen)           return "Colours::lightgreen";
    if (c == Colours::lightgrey)            return "Colours::lightgrey";
    if (c == Colours::lightpink)            return "Colours::lightpink";
    if (c == Colours::lightsalmon)          return "Colours::lightsalmon";
    if (c == Colours::lightseagreen)        return "Colours::lightseagreen";
    if (c == Colours::lightskyblue)         return "Colours::lightskyblue";
    if (c == Colours::lightslategrey)       return "Colours::lightslategrey";
    if (c == Colours::lightsteelblue)       return "Colours::lightsteelblue";
    if (c == Colours::lightyellow)          return "Colours::lightyellow";
    if (c == Colours::lime)                 return "Colours::lime";
    if (c == Colours::limegreen)            return "Colours::limegreen";
    if (c == Colours::linen)                return "Colours::linen";
    if (c == Colours::magenta)              return "Colours::magenta";
    if (c == Colours::maroon)               return "Colours::maroon";
    if (c == Colours::mediumaquamarine)     return "Colours::mediumaquamarine";
    if (c == Colours::mediumblue)           return "Colours::mediumblue";
    if (c == Colours::mediumorchid)         return "Colours::mediumorchid";
    if (c == Colours::mediumpurple)         return "Colours::mediumpurple";
    if (c == Colours::mediumseagreen)       return "Colours::mediumseagreen";
    if (c == Colours::mediumslateblue)      return "Colours::mediumslateblue";
    if (c == Colours::mediumspringgreen)    return "Colours::mediumspringgreen";
    if (c == Colours::mediumturquoise)      return "Colours::mediumturquoise";
    if (c == Colours::mediumvioletred)      return "Colours::mediumvioletred";
    if (c == Colours::midnightblue)         return "Colours::midnightblue";
    if (c == Colours::mintcream)            return "Colours::mintcream";
    if (c == Colours::mistyrose)            return "Colours::mistyrose";
    if (c == Colours::navajowhite)          return "Colours::navajowhite";
    if (c == Colours::navy)                 return "Colours::navy";
    if (c == Colours::oldlace)              return "Colours::oldlace";
    if (c == Colours::olive)                return "Colours::olive";
    if (c == Colours::olivedrab)            return "Colours::olivedrab";
    if (c == Colours::orange)               return "Colours::orange";
    if (c == Colours::orangered)            return "Colours::orangered";
    if (c == Colours::orchid)               return "Colours::orchid";
    if (c == Colours::palegoldenrod)        return "Colours::palegoldenrod";
    if (c == Colours::palegreen)            return "Colours::palegreen";
    if (c == Colours::paleturquoise)        return "Colours::paleturquoise";
    if (c == Colours::palevioletred)        return "Colours::palevioletred";
    if (c == Colours::papayawhip)           return "Colours::papayawhip";
    if (c == Colours::peachpuff)            return "Colours::peachpuff";
    if (c == Colours::peru)                 return "Colours::peru";
    if (c == Colours::pink)                 return "Colours::pink";
    if (c == Colours::plum)                 return "Colours::plum";
    if (c == Colours::powderblue)           return "Colours::powderblue";
    if (c == Colours::purple)               return "Colours::purple";
    if (c == Colours::red)                  return "Colours::red";
    if (c == Colours::rosybrown)            return "Colours::rosybrown";
    if (c == Colours::royalblue)            return "Colours::royalblue";
    if (c == Colours::saddlebrown)          return "Colours::saddlebrown";
    if (c == Colours::salmon)               return "Colours::salmon";
    if (c == Colours::sandybrown)           return "Colours::sandybrown";
    if (c == Colours::seagreen)             return "Colours::seagreen";
    if (c == Colours::seashell)             return "Colours::seashell";
    if (c == Colours::sienna)               return "Colours::sienna";
    if (c == Colours::silver)               return "Colours::silver";
    if (c == Colours::skyblue)              return "Colours::skyblue";
    if (c == Colours::slateblue)            return "Colours::slateblue";
    if (c == Colours::slategrey)            return "Colours::slategrey";
    if (c == Colours::snow)                 return "Colours::snow";
    if (c == Colours::springgreen)          return "Colours::springgreen";
    if (c == Colours::steelblue)            return "Colours::steelblue";
    if (c == Colours::tan)                  return "Colours::tan";
    if (c == Colours::teal)                 return "Colours::teal";
    if (c == Colours::thistle)              return "Colours::thistle";
    if (c == Colours::tomato)               return "Colours::tomato";
    if (c == Colours::turquoise)            return "Colours::turquoise";
    if (c == Colours::violet)               return "Colours::violet";
    if (c == Colours::wheat)                return "Colours::wheat";
    if (c == Colours::white)                return "Colours::white";
    if (c == Colours::whitesmoke)           return "Colours::whitesmoke";
    if (c == Colours::yellow)               return "Colours::yellow";
    if (c == Colours::yellowgreen)          return "Colours::yellowgreen";

    return ("Colour(0x" + c.toString() + ")");
}
//==================================================================================