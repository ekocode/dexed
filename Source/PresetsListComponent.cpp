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

#include "PresetsListComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
PresetsListComponent::PresetsListComponent (PresetsLibrary * presetsLibrary)
{
    this->presetsLibrary = presetsLibrary;
	
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]
	// Load some data from an embedded XML file..
	loadData(presetsLibrary->xmlPresetLibrary);

	// Create our table component and add it to this component..
	addAndMakeVisible(table);
	table.setModel(this);


	// give it a border
	table.setColour(ListBox::outlineColourId, Colours::grey);
	table.setOutlineThickness(1);

	// Add some columns to the table header, based on the column list in our database..
	/*forEachXmlChildElement(*columnList, columnXml)
	{*/
    int width=(presetsLibrary->libraryPanel->getWidth()-20)/4;
		table.getHeader().addColumn("Name",1,width,width, width,TableHeaderComponent::defaultFlags);
        table.getHeader().addColumn("Instrument", 2, width, width, width, TableHeaderComponent::defaultFlags);
        table.getHeader().addColumn("Bank", 3, width, width, width, TableHeaderComponent::defaultFlags);
        table.getHeader().addColumn("Designer", 4, width, width, width, TableHeaderComponent::defaultFlags);
        table.getHeader().addColumn("", 5, 20, 20, 20, TableHeaderComponent::defaultFlags); //Favorite star
	//}

	// we could now change some initial settings..
	table.getHeader().setSortColumnId(1, true); // sort forwards by the ID column
	//table.getHeader().setColumnVisible(7, false); // hide the "length" column until the user shows it

												  // un-comment this line to have a go of stretch-to-fit mode
												  // table.getHeader().setStretchToFitActive (true);

	table.setMultipleSelectionEnabled(false);
	table.getViewport()->setScrollBarsShown(false, false, true);

    //[UserPreSize]
    //[/UserPreSize]

    setSize (presetsLibrary->libraryPanel->getWidth(), presetsLibrary->libraryPanel->getHeight());


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

PresetsListComponent::~PresetsListComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

void PresetsListComponent::loadData(XmlElement* xmlPresetLibrary)
{
        dataList = xmlPresetLibrary->getChildByName(XML_TAG_PRESETS);
        numRows = dataList->getNumChildElements();
	
}

//==============================================================================
void PresetsListComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

   // g.fillAll (DXLookNFeel::background);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PresetsListComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]
	/*Rectangle<int> bounds = presetsLibrary->getLocalBounds();
	bounds.removeFromBottom(40);*/
	table.setBoundsInset(BorderSize(0,0,2,2));
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

int PresetsListComponent::getNumRows()
{
	return numRows;
}

void PresetsListComponent::paintRowBackground(Graphics & g, int rowNumber, int, int, bool rowIsSelected)
{
   
    if (rowIsSelected)
        g.fillAll(DXLookNFeel::librarySelectedBackground);
    else if (rowNumber % 2)
        g.fillAll(DXLookNFeel::libraryDarkBackground);
    else
    {
        g.fillAll(DXLookNFeel::libraryDarkBackgroundAlt);
    }
}

void PresetsListComponent::paintCell(Graphics & g, int rowNumber, int columnId, int width, int height, bool)
{
	g.setColour(DXLookNFeel::libraryText);
	g.setFont(font);
    Justification::Flags justification;
    justification = Justification::centredLeft;
    String text;

    if (auto* rowElement = dataList->getChildElement(rowNumber))
    {
        
        if(columnId==2) //Instrument type
        {
            auto value = rowElement->getIntAttribute(getAttributeNameForColumnId(columnId));
            if(value==-1)
            {
                text="Undefined";
            }
            else
            {
                text = presetsLibrary->getTagName(value,TagType::TYPE);
            }
            
        }
        else if(columnId==3) //Bank
        {
            auto value = rowElement->getIntAttribute(getAttributeNameForColumnId(columnId));
            if(value==-1)
            {
                text="User";
            }
            else
            {
                
                text = presetsLibrary->getTagName(value,TagType::BANK);
            }
            
        }
        else if(columnId==5) //favorite
        {
            auto value = rowElement->getIntAttribute(getAttributeNameForColumnId(columnId));
            justification = Justification::centred;
            if(value==0)
            {
                text="";
            }
            else
            {
                
                text = "*";
            }
            
        }
        else
        {
            text = rowElement->getStringAttribute(getAttributeNameForColumnId(columnId));
        }

        g.drawText(text, 2, 0, width - 4, height, justification, true);
    }

	

	//g.setColour(getLookAndFeel().findColour(ListBox::backgroundColourId));
    g.setColour(DXLookNFeel::fillColour);
	g.fillRect(width - 1, 0, 1, height);
}

String PresetsListComponent::getAttributeNameForColumnId(const int columnId) const
{
	switch (columnId)
	{
	case 1:
		return "name";
	case 2:
		return "typeTag";
	case 3:
		return "bankTag";
	case 4:
		return "designer";
	case 5:
		return "favorite";
	default:
		return "";
		break;
	}

}


void PresetsListComponent::sortOrderChanged(int newSortColumnId, bool isForwards)
{
	if (newSortColumnId != 0)
	{
		LibraryDataSorter sorter(getAttributeNameForColumnId(newSortColumnId), isForwards);
		dataList->sortChildElements(sorter);

		table.updateContent();
	}
}

void PresetsListComponent::selectedRowsChanged(int row)
{
	presetsLibrary->selectPreset(dataList->getChildElement(row));
}

//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PresetsListComponent" componentName=""
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
