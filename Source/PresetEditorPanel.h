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

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "PresetsLibrary.h"
//[/Headers]
struct TagButton;
//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class PresetEditorPanel  : public Component, public Button::Listener
{
public:
    //==============================================================================
    
	PresetEditorPanel(PresetsLibrary* presetLibrary);
    ~PresetEditorPanel();

	void makeTags();	
	void setPreset(XmlElement* preset);
	void buttonClicked(Button* button) override;
	void presetEdited();
	void savePreset();
	void setTags();
	void performLayout();
	void addButton(TagButton* button);

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]
	PresetsLibrary * presetLibrary;
	XmlElement * currentPreset;
	XmlElement* xmlPresetLibrary;
	FlexBox characteristicFlexBox;
	OwnedArray<TagButton> characteristicButtons;
	TextEditor name, designer;
	ComboBox type, bank;
	ScopedPointer<TextButton> saveButton;
    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetEditorPanel)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
