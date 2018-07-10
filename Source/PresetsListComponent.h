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
#include "DXLookNFeel.h"
#include "PresetsLibrary.h"
class PresetsLibrary;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class PresetsListComponent  : public Component , public TableListBoxModel
{
public:
    //==============================================================================
	PresetsListComponent(PresetsLibrary * presetsLibrary);
    ~PresetsListComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void loadData(XmlElement * xmlPresetLibrary);
    int getNumRows() override;
    void paintRowBackground(Graphics& g, int rowNumber, int /*width*/, int /*height*/, bool rowIsSelected) override;
    void paintCell(Graphics& g, int rowNumber, int columnId,
                   int width, int height, bool /*rowIsSelected*/) override;
    void sortOrderChanged(int newSortColumnId, bool isForwards) override;
    void selectedRowsChanged(int row) override;
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;

	
    TableListBox table;     // the table component itself


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	
	Font font{ 14.0f };
    PresetsLibrary* presetsLibrary;
	//std::unique_ptr<XmlElement> demoData;  // This is the XML document loaded from the embedded file "demo table data.xml"
	XmlElement* columnList = nullptr;     // A pointer to the sub-node of demoData that contains the list of columns
	Array<XmlElement*> dataList = nullptr;     // A pointer to the sub-node of demoData that contains the list of data rows
	int numRows;                          // The number of rows of data we've got
	OwnedArray<Button> favoriteButtons;
	String getAttributeNameForColumnId(const int columnId) const;
    
    //==============================================================================
    // A comparator used to sort our data when the user clicks a column header
    class LibraryDataSorter
    {
    public:
        LibraryDataSorter(const String& attributeToSortBy, bool forwards)
        : attributeToSort(attributeToSortBy),
        direction(forwards ? 1 : -1)
        {
        }
        
        int compareElements(XmlElement* first, XmlElement* second) const
        {
            auto result = first->getStringAttribute(attributeToSort)
            .compareNatural(second->getStringAttribute(attributeToSort));
            
            if (result == 0)
                result = first->getStringAttribute("ID")
                .compareNatural(second->getStringAttribute("ID"));
            
            return direction * result;
        }
        
    private:
        String attributeToSort;
        int direction;
        
	
    //[/UserVariables]
	
	};
    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetsListComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
