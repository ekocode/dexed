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

struct TagButton : public ToggleButton
{
public:
    TagButton(String name,int id,TagType type)
    {
        this->setButtonText(name);
        this->id = id;
        this->type = type;
    }
        void paint (Graphics& g) override
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
				g.setColour(DXLookNFeel::libraryDarkBackground);
				g.drawText(getButtonText(), getLocalBounds().toFloat(), Justification::centred);
			}

			
        }
		
		int getId() { return id; }
		TagType getTagType() { return type; }
    int id;
    TagType type;
    
};


struct TagsPanel : public Component
{    
    FlexBox typeFlexBox;
	FlexBox characteristicFlexBox;
	FlexBox bankFlexBox;    
	OwnedArray<TagButton> typeButtons;
	OwnedArray<TagButton> characteristicButtons;
	OwnedArray<TagButton> bankButtons;

	TagsPanel()
	{
		typeFlexBox.alignContent = FlexBox::AlignContent::flexStart;
		typeFlexBox.flexDirection = FlexBox::Direction::row;
		typeFlexBox.justifyContent = FlexBox::JustifyContent::flexStart;
		typeFlexBox.alignItems = FlexBox::AlignItems::flexStart;
		typeFlexBox.flexWrap = FlexBox::Wrap::wrap;

		characteristicFlexBox.alignContent = FlexBox::AlignContent::flexStart;
		characteristicFlexBox.flexDirection = FlexBox::Direction::row;
		characteristicFlexBox.justifyContent = FlexBox::JustifyContent::flexStart;
		characteristicFlexBox.alignItems = FlexBox::AlignItems::flexStart;
		characteristicFlexBox.flexWrap = FlexBox::Wrap::wrap;

		bankFlexBox.alignContent = FlexBox::AlignContent::flexStart;
		bankFlexBox.flexDirection = FlexBox::Direction::row;
		bankFlexBox.justifyContent = FlexBox::JustifyContent::flexStart;
		bankFlexBox.alignItems = FlexBox::AlignItems::flexStart;
		bankFlexBox.flexWrap = FlexBox::Wrap::wrap;
	}
    
    void addButton(TagButton* button)
    {   
		FlexBox* destFlexBox;
		OwnedArray<TagButton>* destOwnedArray;

		switch (button->getTagType())
		{
		case TagType::TYPE:
			destFlexBox = &typeFlexBox;
			destOwnedArray = &typeButtons;
			break;
		case TagType::CHARACTERISTIC:
			destFlexBox = &characteristicFlexBox;
			destOwnedArray = &characteristicButtons;
			break;
		case TagType::BANK:
			destFlexBox = &bankFlexBox;
			destOwnedArray = &bankButtons;
			break;
		}		

		destFlexBox->items.add(FlexItem((getWidth() / 3) - 2, 20).withMargin(1));
		auto &flexItem = destFlexBox->items.getReference(destFlexBox->items.size() - 1);
		destOwnedArray->add(button);
		flexItem.associatedComponent = button;
		addAndMakeVisible(button);
    }
    
    void resized() override
    {
		performLayout();
    }

	void performLayout()
	{
		//Rectangle<int> bounds = this->getLocalBounds();
		int width = getWidth();

		typeFlexBox.performLayout(Rectangle<int> (0,0,width,200));
		characteristicFlexBox.performLayout(Rectangle<int>(0,22*5, width, 200));
		bankFlexBox.performLayout(Rectangle<int>(0, 22*12, width, 200));
	}
	
};
struct PresetEditorPanel : public Component
{

	PresetEditorPanel(XmlElement * xmlPresetLibrary)
	{
		currentPreset = nullptr;
		this->xmlPresetLibrary = xmlPresetLibrary;

		name.setReadOnly(true);
		designer.setReadOnly(true);
		//type.setEnabled(false);
		characteristic.setEnabled(false);
		//bank.setEnabled(false);

		addAndMakeVisible(name);
		name.setBounds(0, 0, 100, 20);
		addAndMakeVisible(designer);
		designer.setBounds(0, 22, 100, 20);
		makeComboBoxes();

		addAndMakeVisible(type);
		type.setBounds(0, 44, 100, 20);
		//addAndMakeVisible(characteristic);
		//characteristic.setBounds(0, 66, 100, 20);
		addAndMakeVisible(bank);
		bank.setBounds(0, 88, 100, 20);
	}

	void makeComboBoxes()
	{
		if (xmlPresetLibrary == nullptr)
			return;
		type.clear();
		//characteristic.clear();
		bank.clear();
		
		XmlElement* typeElements = (xmlPresetLibrary->getChildByName(XML_TAG_TAGS))->getChildByName(XML_TAG_TYPES);
		XmlElement* bankElements = (xmlPresetLibrary->getChildByName(XML_TAG_TAGS))->getChildByName(XML_TAG_BANKS);
		//XmlElement* characteristicElements = (xmlPresetLibrary->getChildByName(XML_TAG_TAGS))->getChildByName(XML_TAG_CHARACTERISTICS);
		
		int i;
		i = 1;
		forEachXmlChildElement(*typeElements, child)
		{
			
			type.addItem(child->getStringAttribute("name"), i);
			i++;
		}
		/*i = 0;

		forEachXmlChildElement(*characteristicElements, child)
		{
			characteristic.addItem(child->getStringAttribute("designer"), i);
			i++;
		}*/
		i = 1;
		forEachXmlChildElement(*bankElements, child)
		{
			bank.addItem(child->getStringAttribute("name"), i);
			i++;
		}
	}

	void setPreset(XmlElement* preset)
	{
		currentPreset = preset;
		repaint();
	}


	void paint(Graphics& g) override
	{
		if (currentPreset != nullptr)
		{
			name.setText(currentPreset->getStringAttribute("name"));
			designer.setText(currentPreset->getStringAttribute("designer"));
			

		}
	}

	XmlElement* currentPreset;
	XmlElement* xmlPresetLibrary;
	TextEditor name, designer;
	ComboBox type, characteristic, bank;


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

	}

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
	ScopedPointer<TextButton> scanButton;
	ScopedPointer<TextButton> factoryResetButton;	
	PresetsListComponent *presetListBox;	
	LibraryButtonsPanel *libraryButtonPanel;
	String statusMessage;
    
    #ifdef DEBUG
    DocumentWindow *statusWindow;
    TextEditor *statusText;
    #endif
    
public:
    XmlElement* xmlPresetLibrary;
	TagsPanel *tagsPanel;
	LibraryPanel *libraryPanel;
	PresetEditorPanel *presetEditorPanel;

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
	void selectPreset(XmlElement* preset);
	void getData(uint8_t* dest, XmlElement* preset);
    
    void log(String message="");
    
    String getTagName(int id,TagType type=CHARACTERISTIC);

	void setCurrentProgram(uint8_t* data);


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
