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
//[/Headers]

#define PROGRAM_LENGTH 161


struct TagsPanel : public Component
{
	
	TagsPanel()
	{
		
	}

	void paint(Graphics& g) override
	{
		g.fillAll(Colours::chocolate);
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
	PresetEditorPanel *presetEditorPanel;
	LibraryButtonsPanel *libraryButtonPanel;
    
    #ifdef DEBUG
    DocumentWindow *statusWindow;
    TextEditor *statusText;
    #endif
    
	XmlElement* xmlPresetLibrary;
    String statusMessage;
	
    
public:
    
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


	int loadLibrary();
	int saveLibrary();
    
    void scan(File dir);
	
	int importCart(File file);
    
    void log(String message="");
    



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
