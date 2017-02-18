/*
====================================================================================
    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    Copyright (c) 2012 by SwingCoder
====================================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "AreaOfPresetColours.h"
#include "ColourComponent/PresetForSelect.h"

AreaOfPresetColours::AreaOfPresetColours(EditCopyOrFavor* _ecf) 
    : eachWidth(200), eachHeight(60), numsPreLine(1)
{
    addPresetColours(_ecf);
}
//==================================================================================

void AreaOfPresetColours::resized()
{
    numsPreLine = getWidth() / eachWidth;

    int x = 5;
    int y = 0;

    int cNums = colours.size();

    for (int i = 0; i < cNums; ++i)
    {
        colours[i]->setTopLeftPosition(x, y);        

        x += eachWidth + 5;

        if (x >= getWidth())
        {
            x = 5;
        }

        if ((i + 1) % numsPreLine == 0)
        {
            y += eachHeight + 5;
        }
    }
    setSize((eachWidth + 5) * numsPreLine + 5, 
        (eachHeight + 5) * (colours.size() / numsPreLine + 1));
}
//==================================================================================
/** 添加JUCE类库预置的枚举型颜色。此函数专供 PresetForSelect 所用。*/
void AreaOfPresetColours::addPresetColours(EditCopyOrFavor* ecf)
{
    for (int i = 0; i < 137; ++i)
    {
        PresetForSelect* pfs = new PresetForSelect();
        pfs->setEditComp(ecf);
        colours.add(pfs);
        addAndMakeVisible(colours[i]);
        colours[i]->setSize(eachWidth, eachHeight);
    }

    colours[0]->setColour(0, Colours::aliceblue);
    colours[1]->setColour(0, Colours::antiquewhite);
    colours[2]->setColour(0, Colours::aqua);
    colours[3]->setColour(0, Colours::aquamarine);
    colours[4]->setColour(0, Colours::azure);
    colours[5]->setColour(0, Colours::beige);
    colours[6]->setColour(0, Colours::bisque);
    colours[7]->setColour(0, Colours::black);
    colours[8]->setColour(0, Colours::blanchedalmond);
    colours[9]->setColour(0, Colours::blue);
    colours[10]->setColour(0, Colours::blueviolet);
    colours[11]->setColour(0, Colours::brown);
    colours[12]->setColour(0, Colours::burlywood);
    colours[13]->setColour(0, Colours::cadetblue);
    colours[14]->setColour(0, Colours::chartreuse);
    colours[15]->setColour(0, Colours::chocolate);
    colours[16]->setColour(0, Colours::coral);
    colours[17]->setColour(0, Colours::cornflowerblue);
    colours[18]->setColour(0, Colours::cornsilk);
    colours[19]->setColour(0, Colours::crimson);
    colours[20]->setColour(0, Colours::cyan);
    colours[21]->setColour(0, Colours::darkblue);
    colours[22]->setColour(0, Colours::darkcyan);
    colours[23]->setColour(0, Colours::darkgoldenrod);
    colours[24]->setColour(0, Colours::darkgrey);
    colours[25]->setColour(0, Colours::darkgreen);
    colours[26]->setColour(0, Colours::darkkhaki);
    colours[27]->setColour(0, Colours::darkmagenta);
    colours[28]->setColour(0, Colours::darkolivegreen);
    colours[29]->setColour(0, Colours::darkorange);
    colours[30]->setColour(0, Colours::darkorchid);
    colours[31]->setColour(0, Colours::darkred);
    colours[32]->setColour(0, Colours::darksalmon);
    colours[33]->setColour(0, Colours::darkseagreen);
    colours[34]->setColour(0, Colours::darkslateblue);
    colours[35]->setColour(0, Colours::darkslategrey);
    colours[36]->setColour(0, Colours::darkturquoise);
    colours[37]->setColour(0, Colours::darkviolet);
    colours[38]->setColour(0, Colours::deeppink);
    colours[39]->setColour(0, Colours::deepskyblue);
    colours[40]->setColour(0, Colours::dimgrey);
    colours[41]->setColour(0, Colours::dodgerblue);
    colours[42]->setColour(0, Colours::firebrick);
    colours[43]->setColour(0, Colours::floralwhite);
    colours[44]->setColour(0, Colours::forestgreen);
    colours[45]->setColour(0, Colours::fuchsia);
    colours[46]->setColour(0, Colours::gainsboro);
    colours[47]->setColour(0, Colours::gold);
    colours[48]->setColour(0, Colours::goldenrod);
    colours[49]->setColour(0, Colours::grey);
    colours[50]->setColour(0, Colours::green);
    colours[51]->setColour(0, Colours::greenyellow);
    colours[52]->setColour(0, Colours::honeydew);
    colours[53]->setColour(0, Colours::hotpink);
    colours[54]->setColour(0, Colours::indianred);
    colours[55]->setColour(0, Colours::indigo);
    colours[56]->setColour(0, Colours::ivory);
    colours[57]->setColour(0, Colours::khaki);
    colours[58]->setColour(0, Colours::lavender);
    colours[59]->setColour(0, Colours::lavenderblush);
    colours[60]->setColour(0, Colours::lemonchiffon);
    colours[61]->setColour(0, Colours::lightblue);
    colours[62]->setColour(0, Colours::lightcoral);
    colours[63]->setColour(0, Colours::lightcyan);
    colours[64]->setColour(0, Colours::lightgoldenrodyellow);
    colours[65]->setColour(0, Colours::lightgreen);
    colours[66]->setColour(0, Colours::lightgrey);
    colours[67]->setColour(0, Colours::lightpink);
    colours[68]->setColour(0, Colours::lightsalmon);
    colours[69]->setColour(0, Colours::lightseagreen);
    colours[70]->setColour(0, Colours::lightskyblue);
    colours[71]->setColour(0, Colours::lightslategrey);
    colours[72]->setColour(0, Colours::lightsteelblue);
    colours[73]->setColour(0, Colours::lightyellow);
    colours[74]->setColour(0, Colours::lime);
    colours[75]->setColour(0, Colours::limegreen);
    colours[76]->setColour(0, Colours::linen);
    colours[77]->setColour(0, Colours::magenta);
    colours[78]->setColour(0, Colours::maroon);
    colours[79]->setColour(0, Colours::mediumaquamarine);
    colours[80]->setColour(0, Colours::mediumblue);
    colours[81]->setColour(0, Colours::mediumorchid);
    colours[82]->setColour(0, Colours::mediumpurple);
    colours[83]->setColour(0, Colours::mediumseagreen);
    colours[84]->setColour(0, Colours::mediumslateblue);
    colours[85]->setColour(0, Colours::mediumspringgreen);
    colours[86]->setColour(0, Colours::mediumturquoise);
    colours[87]->setColour(0, Colours::mediumvioletred);
    colours[88]->setColour(0, Colours::midnightblue);
    colours[89]->setColour(0, Colours::mintcream);
    colours[90]->setColour(0, Colours::mistyrose);
    colours[91]->setColour(0, Colours::navajowhite);
    colours[92]->setColour(0, Colours::navy);
    colours[93]->setColour(0, Colours::oldlace);
    colours[94]->setColour(0, Colours::olive);
    colours[95]->setColour(0, Colours::olivedrab);
    colours[96]->setColour(0, Colours::orange);
    colours[97]->setColour(0, Colours::orangered);
    colours[98]->setColour(0, Colours::orchid);
    colours[99]->setColour(0, Colours::palegoldenrod);
    colours[100]->setColour(0, Colours::palegreen);
    colours[101]->setColour(0, Colours::paleturquoise);
    colours[102]->setColour(0, Colours::palevioletred);
    colours[103]->setColour(0, Colours::papayawhip);
    colours[104]->setColour(0, Colours::peachpuff);
    colours[105]->setColour(0, Colours::peru);
    colours[106]->setColour(0, Colours::pink);
    colours[107]->setColour(0, Colours::plum);
    colours[108]->setColour(0, Colours::powderblue);
    colours[109]->setColour(0, Colours::purple);
    colours[110]->setColour(0, Colours::red);
    colours[111]->setColour(0, Colours::rosybrown);
    colours[112]->setColour(0, Colours::royalblue);
    colours[113]->setColour(0, Colours::saddlebrown);
    colours[114]->setColour(0, Colours::salmon);
    colours[115]->setColour(0, Colours::sandybrown);
    colours[116]->setColour(0, Colours::seagreen);
    colours[117]->setColour(0, Colours::seashell);
    colours[118]->setColour(0, Colours::sienna);
    colours[119]->setColour(0, Colours::silver);
    colours[120]->setColour(0, Colours::skyblue);
    colours[121]->setColour(0, Colours::slateblue);
    colours[122]->setColour(0, Colours::slategrey);
    colours[123]->setColour(0, Colours::snow);
    colours[124]->setColour(0, Colours::springgreen);
    colours[125]->setColour(0, Colours::steelblue);
    colours[126]->setColour(0, Colours::tan);
    colours[127]->setColour(0, Colours::teal);
    colours[128]->setColour(0, Colours::thistle);
    colours[129]->setColour(0, Colours::tomato);
    colours[130]->setColour(0, Colours::turquoise);
    colours[131]->setColour(0, Colours::violet);
    colours[132]->setColour(0, Colours::wheat);
    colours[133]->setColour(0, Colours::white);
    colours[134]->setColour(0, Colours::whitesmoke);
    colours[135]->setColour(0, Colours::yellow);
    colours[136]->setColour(0, Colours::yellowgreen);
}

