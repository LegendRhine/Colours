/*
====================================================================================
    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    Copyright (c) 2012 by SwingCoder
====================================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "AreaOfFavorColours.h"
#include "ColourComponent/FavorForCopyOrEdit.h"
#include "ColourComponent/EditCopyOrFavor.h"

//==================================================================================
AreaOfFavorColours::AreaOfFavorColours(EditCopyOrFavor* editObj, Viewport* viewport)  
    : nums(999), width(150), height(50), editCopyOrFavor(editObj), 
    isDrag(false), origIndex(0), dragY(0), parentViewport(viewport)
{
    jassert(viewport != nullptr);    // 本类必须置于Viewport中！

    // 加载上次退出时所收藏的颜色
    if (!loadColours())
    {
        LookAndFeel::getDefaultLookAndFeel().playAlertSound();
		AlertWindow::showMessageBox(AlertWindow::InfoIcon, L"消息",
            L"收藏文件尚未建立或已损坏，收藏夹初始化为空。", L"确 定");

        // 如果文件损坏，则无法确定本组件的大小。会出现定位错误。故在此设置一下大小。
        setSize(width + 35, height);
    }
}
//==================================================================================
AreaOfFavorColours::~AreaOfFavorColours()
{
}
//==================================================================================
void AreaOfFavorColours::paint(Graphics& g)
{
    // 拖拽时绘制视觉提示（深红色横线）
    if (isDrag)
    {
        g.setColour(Colours::darkred);
        g.fillRect(2.0f, dragY + 1.0f, getWidth() - 4.0f, 3.0f);        
    }
    
    // 绘制每个颜色的编号
    g.setColour(Colours::black);
    g.setFont(16.0f);

    int cNums = colours.size();

    for (int i = 0; i < cNums; ++i)
    {
        g.drawText(String(i + 1).paddedLeft ('0', 2), 
            0, i * (height + 5), 30, height, Justification::centred, false);
    }
}
//==================================================================================
void AreaOfFavorColours::resized()
{
    setSize(width + 35, colours.size() * (height + 5) + 5);
}
//==================================================================================
const bool AreaOfFavorColours::hasOne() const
{
    return colours.size() != 0;
}
//==================================================================================
/** 删除收藏夹中某个颜色。
            
        内部原理：删除某个颜色删除之前，该颜色已置为0x00透明黑，
        本函数查找数组中符合此条件的对象，删除之。*/
void AreaOfFavorColours::deleteFavorColour()
{
    int index = -1;

    int cNums = colours.size();

    for (int i = 0; i < cNums; ++i)
    {
        if (colours[i]->getColour() == Colour(0x00))
        {
            index = i;
            colours.remove(i, true);
            saveColours();
            break;
        }
    }

    // 受影响的颜色重新定位
    if (index >= 0)
    {
        for (int i = 0; i < cNums - 1; ++i)
            colours[i]->setTopLeftPosition(30, 5 + i * (height + 5));

        resized();
        sendChangeMessage();
    }
}
//==================================================================================
/** 清除所有的颜色块的颜色。*/
void AreaOfFavorColours::clearAllColours()
{
    if (AlertWindow::showOkCancelBox(
        AlertWindow::QuestionIcon, L"确定要清空所有收藏的颜色吗？", 
        L"此操作不可撤销，请务必三思！", L"确 定", L"取 消"))
    {
        colours.clear(true);
        repaint();
        resized();
        sendChangeMessage();
        saveColours();
    }
}
//==================================================================================
/** 添加一个颜色。*/
void AreaOfFavorColours::addFavorColour(const Colour& colour, int index)
{
    // 已收藏的颜色不再收藏
    int cNums = colours.size();

    for (int i = 0; i < cNums; ++i)
    {
        if (colours[i]->getColour() == colour)
        {
            // 滚屏后语泡提示
            parentViewport->setViewPositionProportionately(
                0.0, double(i + (i > 8 ? 1 : 0)) / colours.size());

            AttributedString s;
            s.append(ColourComponent::getStringOfColour(colour), colour);
            s.append(L"\n收藏夹中的" + String(i + 1) + L"号颜色与此完全一致，\n"
                L"没有必要再次收藏。");
            s.setFont(Font(L"微软雅黑", 18.0f, Font::plain));

            BubbleMessageComponent* bmc = new BubbleMessageComponent();        
            bmc->setAlwaysOnTop (true);
            bmc->addToDesktop (0);
            bmc->showAt (colours[i], s, 6000, true, true);

            return;
        }
    }
    // 完全透明的颜色不予追加（即系统默认的“无效颜色”）
    if (colour.getAlpha() == 0)
    {
        AttributedString s;        
        s.append(L"完全透明的颜色没有必要收藏。");
        s.setFont(Font(L"微软雅黑", 18.0f, Font::plain));

        BubbleMessageComponent* bmc = new BubbleMessageComponent();        
        bmc->setAlwaysOnTop (true);
        bmc->addToDesktop (0);
        bmc->showAt(editCopyOrFavor, s, 6000, true, true);

        return;
    }
    
    // 如果收藏夹已满，则提示后退出本函数
    if (cNums >= nums)
    {        
        LookAndFeel::getDefaultLookAndFeel().playAlertSound();
        AlertWindow::showMessageBox(AlertWindow::WarningIcon, L"收藏夹已满",
            L"请删除收藏区中不再需要的颜色，而后再收藏本颜色。", L"确 定");
        return;
    }

    // 否则添加
    FavorForCopyOrEdit* fce = new FavorForCopyOrEdit();
    fce->setColour(0, colour);

    fce->setMnemName(ColourComponent::getStringOfColour(colour).
        trimCharactersAtStart("Colour").removeCharacters("s:()"));
    fce->setEditComp(editCopyOrFavor);    
    fce->setSize(width, height);    
    addAndMakeVisible(fce);

    if (index < 0 || index >= colours.size())   // 索引越界则追加
    {
        index = colours.size();
        colours.add(fce);
    }
    else        // 否则插入
    {
        colours.insert(index, fce);
    }
    
    // 受影响的颜色重新定位
    for (int i = index; i < cNums + 1; ++i)
    {
        colours[i]->setTopLeftPosition(30, 5 + i * (height + 5));
    }

    resized();
    sendChangeMessage();
    saveColours();

    // 滚屏后语泡提示
    parentViewport->setViewPositionProportionately(
        0.0, double(index + 1) / colours.size());

    AttributedString s;
    s.append(ColourComponent::getStringOfColour(colour), colour);
    s.append(L"\n已收藏到" + String(index + 1) + L"号位置。");
    s.setFont(Font(L"微软雅黑", 18.0f, Font::plain));

    BubbleMessageComponent* bmc = new BubbleMessageComponent();        
    bmc->setAlwaysOnTop (true);
    bmc->addToDesktop (0);
    bmc->showAt (colours[index], s, 6000, true, true);
    LookAndFeel::getDefaultLookAndFeel().playAlertSound();
}
//==================================================================================
bool AreaOfFavorColours::saveColoursToFile() const
{
    // 创建文件选择对话框，使用操作系统的选择文件对话框
    FileChooser fc(L"保存当前收藏的颜色", 
        File::getCurrentWorkingDirectory().getChildFile("UserFavored.clr"), 
        "*.clr", true);

    // 弹出文件选择对话框，模式为保存文件。覆盖现有文件时不警告。
    // 不给予警告的原因是如果用户没有输入扩展名，则自动添加。此时警告功能失效，会导致混淆。
    // 添加扩展名后，再进行判断和覆盖警告。
    // 本语句置入if判断的原因是：如果用户点击了取消，则不执行if体内的语句
    if (fc.browseForFileToSave(false))
    {
        File file = fc.getResult()/*.getNonexistentSibling()*/;

        // 如果用户没有输入扩展名，则添加扩展名。这么做有利有弊。虽然方便，但定死了扩展名。
        if (!file.hasFileExtension(".clr"))
        {
            file = file.withFileExtension(".clr");
        }

        // 是否覆盖已有的文件。否的话，直接退出本函数。
        if (file.existsAsFile())
        {
            if (!AlertWindow::showOkCancelBox(AlertWindow::QuestionIcon, L"该文件已存在！",
                L"是否覆盖 " + file.getFileName() + " ?", L"确 定", L"取 消"))
            {
                return false;
            }
        }        
        saveColours(file);  // 写入文件
        return true;
    }
    return false;
}
//==================================================================================
bool AreaOfFavorColours::loadColoursFromFile()
{
    // 加载后将覆盖现有的数据，而且本程序没有使用撤销功能，因此先询问用户是否加载
    if (!AlertWindow::showOkCancelBox(AlertWindow::QuestionIcon, 
        L"加载后将重置当前收藏夹",
        L"以后每次启动本程序，默认即为要加载的收藏夹。\n"
        L"建议在加载之前先保存当前的收藏夹。\n\n确定要加载吗？", 
        L"确 定", L"取 消"))
    {        
        return false;
    }

    // 创建文件选择对话框，使用操作系统的选择文件对话框
    FileChooser fc(L"加载原先收藏的颜色", 
        File::getCurrentWorkingDirectory().getChildFile("*.clr"), 
        "*.clr", true);

    // 弹出文件选择对话框，模式为打开文件。
    // 本语句置入if判断的原因是：如果用户点击了取消，则不执行if体内的语句
    if (fc.browseForFileToOpen())
    {
        if (!loadColours(fc.getResult()))
        {
            LookAndFeel::getDefaultLookAndFeel().playAlertSound();
            AlertWindow::showMessageBox(AlertWindow::WarningIcon, L"无法加载",
                L"无法识别此文件。", L"确 定");
            return false;
        }
        return true;
    }
    return false;   
}
//==================================================================================
void AreaOfFavorColours::setCopyPrefixOrNo(const bool& copyOrno)
{
    int cNums = colours.size();

    if (cNums <= 0)
        return;       

    for (int i = 0; i < cNums; ++i)
    {
        colours[i]->setCopyPrefix(copyOrno);
    }
}
//==================================================================================
/** 内部使用。将当前所收藏的颜色保存到文件中。该文件位于本程序所在的目录。*/
bool AreaOfFavorColours::saveColours(const File& favorFile) const
{
    ScopedPointer<XmlElement> favor = new XmlElement ("favored");

    XmlElement* colour = favor->createNewChildElement("colour");
    XmlElement* name = favor->createNewChildElement("name");

    int cNums = colours.size();

    for (int i = 0; i < cNums; ++i)
    {
        colour->setAttribute("c" + String(i), colours[i]->getColour().toString());
        name->setAttribute("c" + String(i), colours[i]->getMnemName());
    }

    return favor->writeToFile(favorFile, String::empty);
}
//==================================================================================
/** 内部使用。创建本类对象时，将已经收藏的颜色添加到收藏区。*/
bool AreaOfFavorColours::loadColours(const File& favorFile)
{
    // 获取文档内容，该文件应与写入函数中的文件路径与名称一致
    ScopedPointer<XmlElement> favor = nullptr;
	
	if (favorFile.existsAsFile())
		favor = XmlDocument::parse(favorFile);

    // 检测文档是否有效，根节点是否对应所需。注意此处的Tag应与写入函数中的Tag名称相对应
	if (favor != nullptr && favor->hasTagName ("favored") && favor->getNumChildElements() >= 2)
    {        
        // 定义子节点，指向父节点的第一个子节点。稍后要指向下一个子节点
        XmlElement* colourNode = favor->getFirstChildElement();        

        // 如果这两个子节点有一个无效，则返回false并退出
        if (!(colourNode->hasTagName("colour") && 
            colourNode->getNextElement()->hasTagName("name")))
        {
            return false;
        }

        // 先清空，再添加，否则就成追加了
        colours.clear(true);

        // 创建FavorForCopyOrEdit对象，添加到数组中，基于子节点的所有属性值设置其颜色
        for (int i = 0; i < colourNode->getNumAttributes(); ++i)
        {
            colours.add(new FavorForCopyOrEdit());
            colours[i]->setEditComp(editCopyOrFavor);                
            colours[i]->setSize(width, height);
            colours[i]->setTopLeftPosition(30, 5 + i * (height + 5));
            // 读取子节点colourNode的每个属性，获取每个属性的属性值（颜色字符串代码），而后设置
            // FavorForCopyOrEdit对象的颜色
            colours[i]->setColour(0, Colour::fromString(
                colourNode->getStringAttribute("c" + String(i))));

            addAndMakeVisible(colours[i]);
        }

        // 指向第二个子节点并基于第二个子节点设置数组中每一个FavorForCopyOrEdit对象的助记名
        colourNode = colourNode->getNextElement();

        for (int i = 0; i < colourNode->getNumAttributes(); ++i)
            colours[i]->setMnemName(colourNode->getStringAttribute("c" + String(i)));
        
        resized();
        sendChangeMessage();
        saveColours();
        return true;
    } 

    return false;
}

//==================================================================================
/** 实现拖放目标类的纯虚函数，只接受拖放至此的 FavorForCopyOrEdit 对象。*/
bool AreaOfFavorColours::isInterestedInDragSource(const SourceDetails& sourceDetails)
{
    return sourceDetails.description.toString() == "favorColour";
}
//==================================================================================
/** 在本组件内拖拽 FavorForCopyOrEdit 对象时，自动调用此函数，记录当前所拖拽的对象的索引值。*/
void AreaOfFavorColours::itemDragEnter(const SourceDetails& sourceDetails)
{
    // 记录当前所拖拽的对象的索引值。
    origIndex = (sourceDetails.localPosition.getY() - 5) / (height + 5);
}
//==================================================================================
/** 拖拽 FavorForCopyOrEdit 对象并在本组件内移动时，自动调用此函数。*/
void AreaOfFavorColours::itemDragMove(const SourceDetails& sourceDetails)
{
    isDrag = true;

    // 实时更新鼠标的当前位置，乘除同一个表达式（height + 5）并非多此一举，而是为了自动“取整”。
    // 此位置即绘制横线的Y坐标
    dragY = (sourceDetails.localPosition.getY() - 5) / (height + 5) * (height + 5); 
        
    // 即使不移动鼠标也自动滚屏。即：连续发送鼠标拖拽的消息。参数为发送消息的间隔时间。
    beginDragAutoRepeat(100);

    // 本类的父级组件必须是Viewport对象，在此设置其自动滚屏。1参2参为当前位置，如果此位置距离
    // Viewport的某个边缘小于3参，则开始滚屏。否则不滚屏。滚屏速度为4参（每次移动几个像素）。
    parentViewport->autoScroll(
        0, dragY - parentViewport->getViewPositionY(), 80, 10);
   
    repaint();
}
//==================================================================================
/** 拖出本组件时。*/
void AreaOfFavorColours::itemDragExit(const SourceDetails&)
{
    isDrag = false;  
    repaint();
}
//==================================================================================
/** FavorForCopyOrEdit 对象拖放结束时，自动调用此函数。*/
void AreaOfFavorColours::itemDropped(const SourceDetails& /*sourceDetails*/)
{
    // 新的索引位置
    int newIndex = dragY / (height + 5);

    // 向下拖拽时，新索引要减1
    if (newIndex > origIndex)
        --newIndex;

    // 移动颜色对象
    colours.move(origIndex, newIndex);
    
    // 重新定位受影响的颜色对象
    for (int i = jmin(origIndex, newIndex); i <= jmax(origIndex, newIndex); ++i)
    {
        colours[i]->setTopLeftPosition(30, 5 + i * (height + 5));
    }

    isDrag = false;  
    repaint();
    saveColours();
}
