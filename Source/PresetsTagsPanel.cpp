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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PresetsTagsPanel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
PresetsTagsPanel::PresetsTagsPanel ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]


    //[UserPreSize]
    //[/UserPreSize]
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
    //setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

PresetsTagsPanel::~PresetsTagsPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PresetsTagsPanel::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PresetsTagsPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]
	performLayout();
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void PresetsTagsPanel::performLayout()
{
	int width = getWidth();
	typeFlexBox.performLayout(Rectangle<int>(0, 0, width, 200));
	characteristicFlexBox.performLayout(Rectangle<int>(0, 22 * 5, width, 200));
	bankFlexBox.performLayout(Rectangle<int>(0, 22 * 12, width, 200));
}

void PresetsTagsPanel::addButton(TagButton * button)
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


//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PresetsTagsPanel" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff323e44"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
