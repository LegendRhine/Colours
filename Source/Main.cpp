/*
====================================================================================
    Author: SwingCoder
    Email: SwingCoder2@gmail.com
    Github: https://github.com/SwingCoder

    Copyright (c) 2012 by SwingCoder
====================================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainWindow.h"

//==================================================================================
class SwingColoursApplication  : public JUCEApplication
{
public:
    //==============================================================================
    SwingColoursApplication()
    {
    }

    ~SwingColoursApplication()
    {
    }

    //==============================================================================
    void initialise (const String& /*commandLine*/)
    {  
        LookAndFeel::getDefaultLookAndFeel().setDefaultSansSerifTypefaceName ("Microsoft YaHei");
        mainWindow = new MainAppWindow();
    }

    void shutdown()
    {
        mainWindow = 0;
    }

    //==============================================================================
    void systemRequestedQuit()
    {
        JUCEApplication::quit();
    }

    //==============================================================================
    const String getApplicationName()
    {
        return ProjectInfo::projectName;
    }

    const String getApplicationVersion()
    {
        return ProjectInfo::versionString;
    }

    bool moreThanOneInstanceAllowed()
    {
        return true;
    }

    void anotherInstanceStarted (const String& /*commandLine*/)
    {
        
    }

private:
    ScopedPointer <MainAppWindow> mainWindow;
};

//==============================================================================
START_JUCE_APPLICATION(SwingColoursApplication)
