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
struct TagButton;
//[/Headers]

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
	

    
    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void setPreset(XmlElement* preset);
    
    void presetEdited();
    void savePreset();
    
    void setTags();
    void makeTags();
	static Array<int> getTagsButtonsState(OwnedArray<TagButton>* tagsButtons);
	static void setTagsButtonsState(OwnedArray<TagButton>* tagsButtons, Array<int> tagsOn);
    static void unselectAllTagsButtons(OwnedArray<TagButton>* tagsButtons);
    void addButton(TagButton* button);
    void buttonClicked(Button* button) override;
    void performLayout();
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    PresetsLibrary * presetsLibrary;
    XmlElement * currentPreset;
    XmlElement* xmlPresetLibrary;
    FlexBox characteristicFlexBox;
    OwnedArray<TagButton> characteristicButtons;
	//ScopedPointer<OwnedArray<TagButton>> p_editCharacteristicButtons;
    TextEditor name, designer;
    ComboBox type, bank;
    ScopedPointer<TextButton> saveButton;
    //[/UserVariables]
	
    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetEditorPanel)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
