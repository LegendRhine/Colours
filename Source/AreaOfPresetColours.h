/*
====================================================================================
    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    Copyright (c) 2012 by SwingCoder
====================================================================================
*/

#ifndef __AREAOFPRESETCOLOURS_H_
#define __AREAOFPRESETCOLOURS_H_

class PresetForSelect;
class EditCopyOrFavor;
//==================================================================================
/** 本组件用来显示 Colours 类中定义的所有颜色，每个颜色由一个 PresetForSelect 类的对象所表示。*/
class AreaOfPresetColours : public Component
{
public:
    /** 创建对象。调用 addPresetColours() 函数，添加所有的 Colours 颜色。
    
        @param editCopyOrFavor  编辑区对象。本类所持有的 PresetForSelect 对象需要此参数。
               点击PresetForSelect对象后，可将其所代表的颜色置入编辑区。
               此参数对象仅在本类的构造函数调用 addPresetColours()函数时作为参数传递给该函数。
               addPresetColours()函数中创建并添加 PresetForSelect 对象后，随即使用该对象调用
               PresetForSelect::setEditComp()函数，将此参数传过去。
               由于此参数对象只在这一处使用，因此本类无需持有，也无需在类中声明之。*/
    AreaOfPresetColours(EditCopyOrFavor* editCopyOrFavor);
    
    /** 析构函数。什么也不做。*/
    ~AreaOfPresetColours() {}

    /** 本类的大小改变后，对所有的颜色块进行重新定位，并重新设置自身的大小。*/
    void resized();

private:
    /** 添加 Colours 类中定义的所有颜色。

        本函数创建一批 PresetForSelect 类的对象，每个对象设置一个 Colours 颜色。
        由于每个PresetForSelect对象在创建后需调用 PresetForSelect::setEditComp()设置编辑区对象，
        因此，本函数的参数将传递给该对象。               
        
        由于本类的构造参数即为 EditCopyOrFavor 指针型对象，而本函数仅由构造函数内部调用一次，
        因此无需在此创建该对象或为其赋值，仅接受构造函数转入的构造参数即可。
        本类也无需声明并持有该类的对象。*/
    void addPresetColours(EditCopyOrFavor* editCopyOrFavor);

    /** 用来保存所有的 Colours 颜色，即持有137个 PresetForSelect 对象的数组。*/
    OwnedArray<PresetForSelect> colours;

    /** 每个颜色块的宽度。*/
    const int eachWidth;
    
    /** 每个颜色块的高度。*/
    const int eachHeight;
    
    /** 用来确定每行显示的颜色块数量。
    
        本类大小改变后，需重新布局所持有的颜色块，并设置自身的大小。    
        此时，需要确定每行所能显示的颜色块数量。并依据此值确定自身的高度。*/
    int numsPreLine;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AreaOfPresetColours)
};

#endif  // __AREAOFPRESETCOLOURS_H_
