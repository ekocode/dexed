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
#include "PresetsLibraryPanel.h"
#include "PresetsTagsPanel.h"
#include "PresetEditorPanel.h"
#include "DXLookNFeel.h"

#define PROGRAM_LENGTH 161

#define XML_TAG_LIBRARY "DEXEDLIBRARY"
#define XML_TAG_TAGS "TAGS"
#define XML_TAG_TAG "TAG"
#define XML_TAG_TYPES "TYPES"
#define XML_TAG_BANKS "BANKS"
#define XML_TAG_CHARACTERISTICS "CHARACTERISTICS"
#define XML_TAG_PRESETS "PRESETS"
#define XML_TAG_PRESET "PRESET"

#define LIBRARY_VERSION_MAJOR 1
#define LIBRARY_VERSION_MINOR 0
#define LIBRARY_FILENAME "Dexed.presets.xml"
#define LIBRARY_DEFAULT_CART "Dexed_01.syx"


typedef enum
{
    TYPE,
    BANK,
    CHARACTERISTIC
} TagType;

class PresetsListComponent;
class PresetsTagsPanel;
class PresetsLibraryPanel;
class PresetEditorPanel;


struct TagButton : public ToggleButton
{
public:
    TagButton(String name, int id, TagType type)
    {
        this->setButtonText(name);
        this->id = id;
        this->type = type;
    }
    void paint(Graphics& g) override
    {
        if (getToggleState())
        {
            g.setColour(DXLookNFeel::librarySelectedBackground);
            g.fillRect(getLocalBounds());
            g.setColour(DXLookNFeel::libraryText);
            g.drawText(getButtonText(), getLocalBounds().toFloat(), Justification::centred);
        }
        else
        {
            g.setColour(DXLookNFeel::roundBackground);
            g.fillRect(getLocalBounds());
            g.setColour(DXLookNFeel::libraryDarkText);
            g.drawText(getButtonText(), getLocalBounds().toFloat(), Justification::centred);
        }
    }
    
    int getId() { return id; }
    TagType getTagType() { return type; }
    int id;
    TagType type;
};


struct LibraryButtonsPanel : public Component
{
    
    LibraryButtonsPanel()
    {
        
    }
    
    void paint(Graphics& g) override
    {
        g.fillAll(DXLookNFeel::roundBackground);
    }
    
};

//[/Headers]


//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class PresetsLibrary  : public Component, public Button::Listener
{
    
    
public:
    

    //==============================================================================
    PresetsLibrary (DexedAudioProcessorEditor *editor);
    ~PresetsLibrary();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    XmlElement* xmlPresetLibrary;
    PresetsTagsPanel *tagsPanel;
    PresetsLibraryPanel *libraryPanel;
    PresetEditorPanel *presetEditorPanel;

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;

	void generateDefaultXml();
	XmlElement* makeXmlPreset(String name, uint8_t content[PROGRAM_LENGTH]
							, int typeTag=-1, int bankTag=-1, Array<int> characteristicTags = Array<int>()
							, String designer ="", String comment="", bool favorite=false, bool readOnly=false);
	XmlElement* makeXmlTag(String name, bool readOnly = false);
    static String arrayToXml(Array<int> array);
    static Array<int> xmlToArray(String xmlArray);
    
    void makeTagsButtons();
    String getTagName(int id,TagType type=CHARACTERISTIC);
    void tagFilter();

	int loadLibrary();
	int saveLibrary();
    void scan(File dir);
	int importCart(File file);
    
   
    
    
	void selectPreset(XmlElement* preset);
    /**
     should be with other sysex functions #TODO
     */
	static void changeSysexProgramName(uint8* program,String newName);
	//void savePreset(XmlElement* preset);
	static void getDataFromPreset(uint8_t* destData, XmlElement* sourcePreset);
	static void setDataToPreset(uint8_t* sourceData, XmlElement* destPreset);
	static void setPresetName(XmlElement* preset, String newName);

	
    void setCurrentProgram(uint8_t* data);
    static String dataToString(const uint8_t* data);

    void log(String message="");
    //[/UserMethods]
private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    DexedAudioProcessorEditor *mainWindow;
    File cartDir;
    File libraryFile;
    ScopedPointer<TextButton> scanButton;
	ScopedPointer<TextButton> saveLibraryButton;
    ScopedPointer<TextButton> factoryResetButton;
	ScopedPointer<TextButton> unselectAllTagsButton;
    PresetsListComponent *presetListBox;
    LibraryButtonsPanel *libraryButtonPanel;
    String statusMessage;
    
#ifdef DEBUG
    DocumentWindow *statusWindow;
    TextEditor *statusText;
#endif
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetsLibrary)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif //PRESETSLIBRARY_H_INCLUDED
