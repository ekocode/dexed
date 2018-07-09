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
class PresetsTagsPanel  : public Component
{
public:
    //==============================================================================
    PresetsTagsPanel ();
    ~PresetsTagsPanel();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    

    void paint (Graphics& g) override;
    void resized() override;

	void performLayout();
	void addButton(TagButton* button);
    //[/UserMethods]


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	FlexBox typeFlexBox;
	FlexBox characteristicFlexBox;
	FlexBox bankFlexBox;
	OwnedArray<TagButton> typeButtons;
	OwnedArray<TagButton> characteristicButtons;
	OwnedArray<TagButton> bankButtons;
    
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetsTagsPanel)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
