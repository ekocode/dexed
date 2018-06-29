/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.3.2

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/
#ifndef SYSEXPRESETSLIBRARY_H_INCLUDED
#define SYSEXPRESETSLIBRARY_H_INCLUDED

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginEditor.h"
//[/Headers]

enum TagType
{
    MUSICSTYLE,
    INSTRUMENT,
    CARACTER
    
};

class Tag
{
    //name of the tag
    String name;
    //unique id of tag
    int uid;
    //Type of the tag (Style, instrument, Caracter)
    TagType type;
    
    
    Tag();
    ~Tag();
};

class Preset
{
    String Name;
    uint8_t unpackPgm[161];
    Array<int> tagsId;
    String Author;
    String Comment;
    bool favorite;
    
    Preset();
    ~Preset();
};

//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class SysexPresetsLibrary  : public Component, public Button::Listener
{
    DexedAudioProcessorEditor *mainWindow;
    File cartDir;
    ScopedPointer<TextButton> scanButton;
    DirectoryContentsList *libraryBrowserList;
    String statusText;
    Array<Preset> libraryDatas;
    
public:
    
    //==============================================================================
    SysexPresetsLibrary (DexedAudioProcessorEditor *editor, DirectoryContentsList *cartBrowserList);
    ~SysexPresetsLibrary();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    
    void scan(DirectoryContentsList *cartBrowserList);
    void addPreset();
    



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SysexPresetsLibrary)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif //SYSEXPRESETSLIBRARY_H_INCLUDED
