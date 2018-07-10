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

#include "PresetEditorPanel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
PresetEditorPanel::PresetEditorPanel (PresetsLibrary* presetLibrary)
{
    //[Constructor_pre] You can add your own custom stuff here..
    
	currentPreset = nullptr;
	this->presetsLibrary = presetLibrary;
	xmlPresetLibrary = presetLibrary->xmlPresetLibrary;

	characteristicFlexBox.alignContent = FlexBox::AlignContent::flexStart;
	characteristicFlexBox.flexDirection = FlexBox::Direction::row;
	characteristicFlexBox.justifyContent = FlexBox::JustifyContent::flexStart;
	characteristicFlexBox.alignItems = FlexBox::AlignItems::flexStart;
	characteristicFlexBox.flexWrap = FlexBox::Wrap::wrap;

	
	//name.setReadOnly(true);
	//designer.setReadOnly(true);
	//type.setEnabled(false);
	//bank.setEnabled(false);

	addAndMakeVisible(name);
	name.setInputRestrictions(10);
	name.setBounds(0, 0, 100, 20);
	addAndMakeVisible(designer);
	designer.setBounds(0, 22, 100, 20);
	designer.setInputRestrictions(10);
	/*name.addListener(this);
	designer.addListener(this);*/


	addAndMakeVisible(type);
	type.setBounds(0, 44, 100, 20);
	type.setTextWhenNothingSelected("Undefined");
	addAndMakeVisible(bank);
	bank.setBounds(0, 66, 100, 20);
	bank.setTextWhenNothingSelected("Undefined");
	addAndMakeVisible(saveButton = new TextButton("SAVE"));
	saveButton->setBounds(0, 300, 50, 30);
	saveButton->addListener(this);


    //[/Constructor_pre]
    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

PresetEditorPanel::~PresetEditorPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}



//==============================================================================
void PresetEditorPanel::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

   // g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PresetEditorPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]
	performLayout();
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}





//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PresetEditorPanel::makeTags()
{
    if (xmlPresetLibrary == nullptr)
        return;
    type.clear();
    //characteristic.clear();
    bank.clear();
    
    XmlElement* typeElements = (xmlPresetLibrary->getChildByName(XML_TAG_TAGS))->getChildByName(XML_TAG_TYPES);
    XmlElement* bankElements = (xmlPresetLibrary->getChildByName(XML_TAG_TAGS))->getChildByName(XML_TAG_BANKS);
    XmlElement* characteristicElements = (xmlPresetLibrary->getChildByName(XML_TAG_TAGS))->getChildByName(XML_TAG_CHARACTERISTICS);
    
    
    int i;
    i = 1; //offset because combobox can't handle 0
    forEachXmlChildElement(*typeElements, child)
    {
        type.addItem(child->getStringAttribute("name"), i);
        i++;
    }
    i = 0;
    forEachXmlChildElement(*characteristicElements, child)
    {
        addButton(new TagButton(child->getStringAttribute("name"), i, TagType::CHARACTERISTIC));
        i++;
    }
    
    i = 1; //offset because combobox can't handle 0
    forEachXmlChildElement(*bankElements, child)
    {
        bank.addItem(child->getStringAttribute("name"), i);
        i++;
    }
    performLayout();
}

void PresetEditorPanel::setPreset(XmlElement * preset)
{
    currentPreset = preset;
    setTags();
    repaint();
}

void PresetEditorPanel::buttonClicked(Button * button)
{
    
    //presetEdited();
    if (button == saveButton)
    {
        savePreset();
    }
}

void PresetEditorPanel::presetEdited()
{
}

void PresetEditorPanel::savePreset()
{
    TRACE("Save Preset");
    presetsLibrary->setPresetName(currentPreset, name.getText());
    currentPreset->setAttribute("designer", designer.getText());
    currentPreset->setAttribute("bankTag", bank.getSelectedId() - 1);
    currentPreset->setAttribute("typeTag", type.getSelectedId() - 1);
	currentPreset->setAttribute("characteristicTags", presetsLibrary->arrayToXml(getTagsButtonsState(&characteristicButtons)));

    presetsLibrary->selectPreset(currentPreset);
    presetsLibrary->repaint();
}

Array<int> PresetEditorPanel::getTagsButtonsState(OwnedArray<TagButton>* tagsButtons)
{
    TagButton* button;	
    Array<int> output;
        for (int i=0; i < tagsButtons->size(); i++) 
		{    
            button = tagsButtons->getUnchecked(i);
            if(button->getToggleState())
            {
                output.add(i);
            }
        }
    return output;    
}

void PresetEditorPanel::setTagsButtonsState(OwnedArray<TagButton>* tagsButtons,Array<int> tagsOn)
{
		//all tags off
        unselectAllTagsButtons(tagsButtons);
    
        //select the list id
        TagButton* button;
        for (int i=0; i<tagsOn.size();i++) {
    
            if(i<tagsButtons->size())
            {
                button = tagsButtons->getUnchecked(tagsOn.getReference(i));
                button->setToggleState(true,dontSendNotification);
            }
        }
}

void PresetEditorPanel::unselectAllTagsButtons(OwnedArray<TagButton>* tagsButtons)
{
    TagButton* button;
    for (int i=0; i<tagsButtons->size();i++) {
        
        button = tagsButtons->getUnchecked(i);
        button->setToggleState(false,dontSendNotification);
    }
}

void PresetEditorPanel::setTags()
{
    if (currentPreset == nullptr)
        return;
    
    name.setText(currentPreset->getStringAttribute("name"));
    designer.setText(currentPreset->getStringAttribute("designer"));
    int bankValue = currentPreset->getIntAttribute("bankTag");
    int typeValue = currentPreset->getIntAttribute("typeTag");
   
	setTagsButtonsState(&characteristicButtons,presetsLibrary->xmlToArray(currentPreset->getStringAttribute("characteristicTags")));

    
    if (bankValue > -1)
    {
        bank.setSelectedId(bankValue+1);
    }
    else
    {
        bank.setSelectedId(0);
    }
    
    if (typeValue > -1)
    {
        type.setSelectedId(typeValue + 1);
    }
    else
    {
        type.setSelectedId(0);
    }
    repaint();
}

void PresetEditorPanel::performLayout()
{
    int width = getWidth();
    characteristicFlexBox.performLayout(Rectangle<int>(0, 100, width, 200));
}

void PresetEditorPanel::addButton(TagButton * button)
{
    characteristicFlexBox.items.add(FlexItem((getWidth() / 3) - 2, 20).withMargin(1));
    auto &flexItem = characteristicFlexBox.items.getReference(characteristicFlexBox.items.size() - 1);
    characteristicButtons.add(button);
    flexItem.associatedComponent = button;
    addAndMakeVisible(button);
    //button->addListener(this);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PresetEditorPanel" componentName=""
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
