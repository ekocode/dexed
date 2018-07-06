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
#ifndef PRESETSLIBRARY_H_INCLUDED
#define PRESETSLIBRARY_H_INCLUDED

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginEditor.h"
#include "CartManager.h"
#include "PresetsListComponent.h"
//[/Headers]

#define PROGRAM_LENGTH 161

typedef enum
{
    TYPE,
    BANK,
    CHARACTERISTIC
} TagType;

class PresetsListComponent;

struct TagButton : public TextButton
{
public:
    TagButton(String name,int id,TagType type)
    {
        this->setButtonText(name);
        this->id = id;
        this->type = type;
    }
    //    void paint (Graphics& g) override
    //    {
    //
    //    }
        void resized() override
        {
            if (auto parent = getParentComponent())
                parent->resized();
        }
    //    void drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour,
    //                               bool isMouseOverButton, bool isButtonDown) override
    //    {
    //        //...
    //    }
    
    int id;
    TagType type;
    
};


struct TagsPanel : public Component
{
    
    FlexBox typeFlexBox;
    
    Array<TagButton*> TypeButtons;
	TagsPanel()
	{
        
	}
    
    void addTypeButton(TagButton* button)
    {
        TypeButtons.add(button);
    }

//    void paint(Graphics& g) override
//    {
//        g.fillAll(Colours::chocolate);
//    }
    
    void resized() override
    {
                                               // [1]
        typeFlexBox.flexWrap = FlexBox::Wrap::wrap;                   // [2]
        typeFlexBox.justifyContent = FlexBox::JustifyContent::center; // [3]
        typeFlexBox.alignContent = FlexBox::AlignContent::center;     // [4]
        for (TagButton* b : TypeButtons)
        {
            
            typeFlexBox.items.add (FlexItem (*b).withMinWidth (50.0f).withMinHeight (50.0f));
        }// [5]
        
        typeFlexBox.performLayout (getLocalBounds().toFloat());       // [6]
    }
	
};
struct PresetEditorPanel : public Component
{

	PresetEditorPanel()
	{

	}

	void paint(Graphics& g) override
	{
		g.fillAll(Colours::darkblue);
	}

};
struct LibraryPanel : public Component
{
public:
	//String statusText;
	LibraryPanel()
	{

	}

	void paint(Graphics& g) override
	{

		g.fillAll(Colours::darkgrey);
//        int x = 10, y = 50, width = getLocalBounds().getWidth() - 20, height = getLocalBounds().getHeight();
//        Colour fillColour = Colours::white;
//        g.setColour(fillColour);
//        g.setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
//        g.drawMultiLineText(statusText, x, y, 812 - 20);
	}

};

struct LibraryButtonsPanel : public Component
{

	LibraryButtonsPanel()
	{

	}

	void paint(Graphics& g) override
	{
		g.fillAll(Colours::brown);
	}

};

//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class PresetsLibrary  : public Component, public Button::Listener
{
    DexedAudioProcessorEditor *mainWindow;

    File cartDir;
	File libraryFile;
	const int librayVersionMajor=1;
	const int libraryVersionMinor=0;
	const String libraryFilename = "Dexed.presets.xml";

    ScopedPointer<TextButton> scanButton;
	ScopedPointer<TextButton> factoryResetButton;


	TagsPanel *tagsPanel;
	LibraryPanel *libraryPanel;
	PresetsListComponent *presetListBox;
	PresetEditorPanel *presetEditorPanel;
	LibraryButtonsPanel *libraryButtonPanel;
    
    #ifdef DEBUG
    DocumentWindow *statusWindow;
    TextEditor *statusText;
    #endif
    
	
    String statusMessage;
	
    
public:
    XmlElement* xmlPresetLibrary;
    //==============================================================================
    PresetsLibrary (DexedAudioProcessorEditor *editor);
    ~PresetsLibrary();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;

	void generateDefaultXml();
	XmlElement* makeXmlPreset(String name, uint8_t content[PROGRAM_LENGTH]
							, int typeTag=-1, int bankTag=-1, Array<int> characteristicTags = Array<int>()
							, String designer ="", String comment="", bool favorite=false, bool readOnly=false);
	XmlElement* makeXmlTag(String name, bool readOnly = false);
    void makeTagsButtons();


	int loadLibrary();
	int saveLibrary();
    void scan(File dir);
	int importCart(File file);
    
    void log(String message="");
    
    String getTagName(int id,TagType type=CHARACTERISTIC);
    



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetsLibrary)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif //PRESETSLIBRARY_H_INCLUDED
