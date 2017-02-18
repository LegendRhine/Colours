/*
====================================================================================
    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    Copyright (c) 2012 by SwingCoder
====================================================================================
*/

#ifndef __AREAOFFAVORCOLOURS_H_
#define __AREAOFFAVORCOLOURS_H_

class FavorForCopyOrEdit;
class EditCopyOrFavor;

//==================================================================================
/** 本组件持有并显示当前所收藏的颜色，每个颜色由一个 FavorForCopyOrEdit 对象所表示。

    当前收藏的所有颜色由本类的数组对象所保存和管理。*/
class AreaOfFavorColours : 
    public Component, 
    public DragAndDropContainer,
    public DragAndDropTarget,
    public ChangeBroadcaster
{
friend class FavorForCopyOrEdit;

public:
    /** 创建对象，添加上次退出时所收藏的所有颜色。
    
        所添加的数据来自于本程序自动生成的Favored.clr文件。该文件位于本程序的目录下。
        
        @param editObj  编辑区对象。本类的颜色需传给该对象（所收藏的某个颜色置入编辑区），
                        为防止创建本类对象后忘记为本类设置此对象而导致崩溃，因此将其定为构造参数。
        @param viewport 本类对象必须置于该Viewport中。此参数用来指定所需的Viewport。*/
    AreaOfFavorColours(EditCopyOrFavor* editObj, Viewport* viewport);

    /** 销毁对象，将收藏夹中的颜色保存到文件Favored.clr中。该文件位于本程序的目录下。*/
    ~AreaOfFavorColours();

    /** 在当前所收藏的每个颜色块的左侧绘制一个数字编号。拖拽时绘制视觉提示。*/
    void paint(Graphics& g);

    /** 自动确定本组件的大小。追加或清空颜色后，重新调整大小。*/
    void resized();       
    //==============================================================================
    /** 如果当前至少收藏了一个颜色，则返回true。
    
        判断依据是本组件至少持有一个 FavorForCopyOrEdit 类的对象*/
    const bool hasOne() const;

    /** 获取收藏的数量。*/
    const int size() const { return colours.size(); }
    //==============================================================================
    /** 删除收藏夹中某个颜色。
            
        内部原理：删除某个颜色之前，该颜色已置为0x00透明黑，
        本函数查找数组中符合此条件的对象，删除之。*/
    void deleteFavorColour();

    /** 清除收藏夹中所有的颜色。
        
        即清空本类所持有的所有 FavorForCopyOrEdit 类的对象。*/
    void clearAllColours();

    /** 收藏某个颜色，将该颜色添加到收藏夹的末尾或空白位置处。
    
        给定的颜色追加到数组末尾。如果给出的颜色已有，或者完全透明，则不再收藏。        
        如果收藏夹已满，则给出提示。本类数据成员 nums 所设置的值为本程序最多可收藏的颜色数量。
        
        @param colour   将此颜色添加到收藏夹中。
        @param index    添加到该位置。值为-1或此值越界，则追加到当前收藏夹的末尾。*/
    void addFavorColour(const Colour& colour, int index = -1);
    //==============================================================================
    /** 将当前所收藏的颜色保存到磁盘文件中。文件扩展名为“*.clr”。*/
    bool saveColoursToFile() const;

    /** 从用户选择的文件中加载原先收藏的颜色。文件扩展名为“*.clr”。*/
    bool loadColoursFromFile();
    //==============================================================================
    /** 设置所持有的每个 FavorForCopyOrEdit 对象是否复制颜色代码的前缀。*/
    void setCopyPrefixOrNo(const bool& copyOrno);
    //==============================================================================
    /** 实现基类的纯虚函数，只接受拖放至此的 FavorForCopyOrEdit 对象。
    
        @param dragSourceDetails    来源描述信息。该信息的由子组件调用本类所继承的
                                    DragAndDropContainer 类的 startDragging()函数时所给出
                                    （第一个参数）。DragAndDropContainer类的所有子组件均具有
                                    可拖放属性，在该子组件的mouseDarg()函数中，获取其父级对象，
                                    并用父级对象调用startDragging()函数。该函数的1参即为此参数。
                                    不同的是，startDragging()的1参由本类自动接收后，本类自动
                                    增加鼠标当前位置，拖放来源组件等信息。这些信息，另外几个与拖放
                                    有关的函数会用到。这些函数，全部继承自 DragAndDropTarget
                                    拖放目标类，其参数均为SourceDetails类的对象。
        
        @note   本类双重继承了DragAndDropContainer拖放容器类和DragAndDropTarget拖放目标类，
                因此，即是所容纳的子组件的拖放容器，本身又是接收子组件拖放至此的目标。 startDragging()
                函数为拖放容器的成员函数，调用此函数的组件使用此函数来通知拖放目标：拖放开始了。
                并将必要的信息和自身（拖放来源）传递给拖放目标类。拖放目标接收到信息后进行判断处理，
                信息中增加来源组件。拖拽过程中自动增加和更新鼠标当前位置的信息。
                
        @see DragAndDropContainer, DragAndDropTarget, SourceDetails, DragAndDropTarget::SourceDetails
        */
    bool isInterestedInDragSource( const SourceDetails& dragSourceDetails );

    /** 在本组件内拖拽 FavorForCopyOrEdit 对象时，自动调用此函数，记录当前所拖拽的对象的索引值。
        
        @param dragSourceDetails    来源描述信息。该信息的由子组件调用本类所继承的
                                    DragAndDropContainer 类的 startDragging()函数时所给出
                                    （第一个参数）。DragAndDropContainer类的所有子组件均具有
                                    可拖放属性，在该子组件的mouseDarg()函数中，获取其父级对象，
                                    并用父级对象调用startDragging()函数。该函数的1参即为此参数。
                                    不同的是，startDragging()的1参由本类自动接收后，本类自动
                                    增加鼠标当前位置，拖放来源组件等信息。这些信息，另外几个与拖放
                                    有关的函数会用到。这些函数，全部继承自 DragAndDropTarget
                                    拖放目标类，其参数均为SourceDetails类的对象。

        @note   本类双重继承了DragAndDropContainer拖放容器类和DragAndDropTarget拖放目标类，
                因此，即是所容纳的子组件的拖放容器，本身又是接收子组件拖放至此的目标。 startDragging()
                函数为拖放容器的成员函数，调用此函数的组件使用此函数来通知拖放目标：拖放开始了。
                并将必要的信息和自身（拖放来源）传递给拖放目标类。拖放目标接收到信息后进行判断处理，
                信息中增加来源组件。拖拽过程中自动增加和更新鼠标当前位置的信息。

        @see DragAndDropContainer, DragAndDropTarget, SourceDetails, DragAndDropTarget::SourceDetails
        */
    void itemDragEnter( const SourceDetails& dragSourceDetails );

    /** 拖拽 FavorForCopyOrEdit 对象并在本组件内移动时，视为所拖放的对象改变排序位置。
    
        本函数记录并转换当前拖拽时的鼠标位置并触发重绘。
        
        @param dragSourceDetails    来源描述信息。该信息的由子组件调用本类所继承的
                                    DragAndDropContainer 类的 startDragging()函数时所给出
                                    （第一个参数）。DragAndDropContainer类的所有子组件均具有
                                    可拖放属性，在该子组件的mouseDarg()函数中，获取其父级对象，
                                    并用父级对象调用startDragging()函数。该函数的1参即为此参数。
                                    不同的是，startDragging()的1参由本类自动接收后，本类自动
                                    增加鼠标当前位置，拖放来源组件等信息。这些信息，另外几个与拖放
                                    有关的函数会用到。这些函数，全部继承自 DragAndDropTarget
                                    拖放目标类，其参数均为SourceDetails类的对象。

        @note   本类双重继承了DragAndDropContainer拖放容器类和DragAndDropTarget拖放目标类，
                因此，即是所容纳的子组件的拖放容器，本身又是接收子组件拖放至此的目标。 startDragging()
                函数为拖放容器的成员函数，调用此函数的组件使用此函数来通知拖放目标：拖放开始了。
                并将必要的信息和自身（拖放来源）传递给拖放目标类。拖放目标接收到信息后进行判断处理，
                信息中增加来源组件。拖拽过程中自动增加和更新鼠标当前位置的信息。

        @see DragAndDropContainer, DragAndDropTarget, SourceDetails, DragAndDropTarget::SourceDetails
        */
    void itemDragMove( const SourceDetails& dragSourceDetails );

    /** FavorForCopyOrEdit 对象拖出本组件时，视为该对象放弃排序。
    
        此函数亦触发重绘，防止拖拽到最上面并结束拖放时，最上面的视觉提示不消失。*/
    void itemDragExit(const SourceDetails&);

    /** FavorForCopyOrEdit 对象拖放结束时，自动调用此函数。

    @param dragSourceDetails    来源描述信息。该信息的由子组件调用本类所继承的
                                DragAndDropContainer 类的 startDragging()函数时所给出
                                （第一个参数）。DragAndDropContainer类的所有子组件均具有
                                可拖放属性，在该子组件的mouseDarg()函数中，获取其父级对象，
                                并用父级对象调用startDragging()函数。该函数的1参即为此参数。
                                不同的是，startDragging()的1参由本类自动接收后，本类自动
                                增加鼠标当前位置，拖放来源组件等信息。这些信息，另外几个与拖放
                                有关的函数会用到。这些函数，全部继承自 DragAndDropTarget
                                拖放目标类，其参数均为SourceDetails类的对象。

    @note   本类双重继承了DragAndDropContainer拖放容器类和DragAndDropTarget拖放目标类，
            因此，即是所容纳的子组件的拖放容器，本身又是接收子组件拖放至此的目标。 startDragging()
            函数为拖放容器的成员函数，调用此函数的组件使用此函数来通知拖放目标：拖放开始了。
            并将必要的信息和自身（拖放来源）传递给拖放目标类。拖放目标接收到信息后进行判断处理，
            信息中增加来源组件。拖拽过程中自动增加和更新鼠标当前位置的信息。

    @see DragAndDropContainer, DragAndDropTarget, SourceDetails, DragAndDropTarget::SourceDetails
    */
    void itemDropped( const SourceDetails& dragSourceDetails );

private:
    //==============================================================================
    /** 基于给出的文件加载所收藏的颜色。
    
        本函数由构造函数调用时，默认加载本程序自动生成的Favored.clr文件。该文件位于本程序的目录下。
        即本函数的默认参数。而由 loadColoursFromFile()函数调用时，参数为用户当前所选择的文件。*/
    bool loadColours(const File& favorFile = 
        File::getCurrentWorkingDirectory().getChildFile ("Favored.clr"));

    /** 将当前所收藏的颜色保存到给出的文件中。
    
        参数的默认值为位于本程序所在的目录下的颜色文件，此文件是本程序必不可少的。
        而本函数由 saveColoursToFile()调用时，则可以将当前收藏夹保存到用户指定的文件中。*/
    bool saveColours(const File& thisFile = 
        File::getCurrentWorkingDirectory().getChildFile ("Favored.clr")) const;
    //==============================================================================
    /** 用来保存当前所收藏的颜色，即持有若干 FavorForCopyOrEdit 对象的数组。*/
    OwnedArray<FavorForCopyOrEdit> colours;

    /** 本类所持有的 FavorForCopyOrEdit 对象需设置的 EditCopyOrFavor （编辑区）对象。
        
        即 FavorForCopyOrEdit 对象的颜色可用来设置 EditCopyOrFavor 对象。*/
    EditCopyOrFavor* editCopyOrFavor;

    /** 本程序最多可收藏的颜色数量。设定为999。*/
    const int nums;

     /** 本类所显示的每个颜色块的宽度。设定为150。*/
    const int width;
    
    /** 本类所显示的每个颜色块的高度。设定为50。*/
    const int height;

    /** 是否拖拽的标志值。如果无需在拖出本组件时触发重绘或实现其他目的，则可以不声明此值。
        
        而是用DragAndDropContainer拖放容器类的isDragAndDropActive()函数来替代。
        该函数返回值为布尔值，代表鼠标当前是否处于拖拽状态。由于本类继承了拖放容器类，
        因此可直接调用此函数。*/
    bool isDrag;

    /** 所拖拽的对象索引值。*/
    int origIndex;

    /** 当前拖拽的鼠标位置，y坐标。*/
    int dragY;

    /** 本类必须置入Viewport中，而且要实现自动滚屏，也必须依赖该类对象的Viewport::autoScroll()函数。*/
    Viewport* parentViewport;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AreaOfFavorColours)
};


#endif  // __AREAOFCOLOURS_H_
