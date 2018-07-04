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

#include "PresetsLibrary.h"
#include "PluginEditor.h"
#include "PluginData.h"

//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]




//==============================================================================
PresetsLibrary::PresetsLibrary (DexedAudioProcessorEditor *editor)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]
    mainWindow = editor;
	xmlPresetLibrary = nullptr;
	
	cartDir = DexedAudioProcessor::dexedCartDir;
	libraryFile = DexedAudioProcessor::dexedAppDir.getChildFile(libraryFilename);
	
#ifdef DEBUG
    statusWindow = new DocumentWindow("Status",Colours::darkgrey,0);    
    statusWindow->setBounds(0,0,450,500);
    statusWindow->setVisible(true);
    statusText = new TextEditor();
    statusText->setMultiLine(true);
	statusText->setReadOnly(true);
    statusText->setBounds(statusWindow->getLocalBounds());
    statusWindow->setContentOwned(statusText,true);
    statusText->setTextToShowWhenEmpty("DEBUG STATUS",Colours::grey);
    statusText->setVisible(true);
#endif
    
    


    setSize (812, 384);
	int width = getLocalBounds().getWidth();
	int height = getLocalBounds().getHeight();
	int toolbarHeight = 34;

	addAndMakeVisible(tagsPanel = new TagsPanel());	
	tagsPanel->setBounds(getLocalBounds().removeFromTop(height-toolbarHeight).removeFromLeft((width/4)));
	addAndMakeVisible(libraryPanel = new LibraryPanel());
	libraryPanel->setBounds(getLocalBounds().removeFromTop(height - toolbarHeight).removeFromRight(width * 3 / 4).removeFromLeft(width / 2));
	addAndMakeVisible(presetEditorPanel = new PresetEditorPanel());
	presetEditorPanel->setBounds(getLocalBounds().removeFromTop(height - toolbarHeight).removeFromRight(width / 4));
	addAndMakeVisible(libraryButtonPanel = new LibraryButtonsPanel());
	libraryButtonPanel->setBounds(getLocalBounds().removeFromBottom(toolbarHeight));
	libraryButtonPanel->addAndMakeVisible(scanButton = new TextButton("Import Directory"));
	scanButton->setBounds(2, 2, 100, 30);
	scanButton->addListener(this);
	libraryButtonPanel->addAndMakeVisible(factoryResetButton = new TextButton("Reset Presets Lib"));
	factoryResetButton->setBounds(104, 2, 120, 30);
	factoryResetButton->addListener(this);
    //[/Constructor]
	loadLibrary();
	log(xmlPresetLibrary->createDocument(String()));
}

PresetsLibrary::~PresetsLibrary()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]
#ifdef DEBUG
    //statusWindow->deleteAllChildren();
    delete statusText;
    delete statusWindow;
    
#endif
	if (xmlPresetLibrary != nullptr)
	{
		delete xmlPresetLibrary;
	}
	
	delete tagsPanel;
	delete libraryPanel;
	delete presetEditorPanel;
	delete libraryButtonPanel;	

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PresetsLibrary::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));


    
    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PresetsLibrary::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}


void PresetsLibrary::buttonClicked(juce::Button *buttonThatWasClicked) {

    
    if ( buttonThatWasClicked == scanButton ) {

		saveLibrary();
        auto path = cartDir.getChildFile (Time::getCurrentTime().toString (true, true));
		FileChooser myChooser("Please select the directory you want to scan",
			cartDir.getChildFile(Time::getCurrentTime().toString(true, true))
			//File::getSpecialLocation(File::userHomeDirectory),
			,"",true
			);
		if (myChooser.browseForDirectory())
		{
			//File scanDir(myChooser.getResult());
			scan(myChooser.getResult());
		}
        
        return;
    }
	if (buttonThatWasClicked == factoryResetButton) {
		generateDefaultXml();
	}


}

XmlElement* PresetsLibrary::makeXmlPreset(String name, uint8_t content[PROGRAM_LENGTH]
										,int typeTag, int bankTag, Array<int> characteristicTags
										,String designer, String comment, bool favorite, bool readOnly)
{
	
	XmlElement* element= new XmlElement("PRESET");
	element->setAttribute("name", name);
	element->setAttribute("typeTag", typeTag);
	element->setAttribute("bankTag", bankTag);
	String serialized = "";
	for (int i = 0; i < characteristicTags.size(); i++)
	{
		if (i != 0)
		{
			serialized += " ";
		}
		serialized += String(characteristicTags.getReference(i));
	}
	element->setAttribute("characteristicTags", serialized);
	element->setAttribute("designer", designer);
	element->setAttribute("comment", comment);
	element->setAttribute("favorite", favorite);   
	element->setAttribute("readOnly", readOnly);
    
	
	element->addTextElement(MemoryBlock(content, PROGRAM_LENGTH).toBase64Encoding());

	/*uint8_t result[PROGRAM_LENGTH];
	MemoryBlock buffer = MemoryBlock(PROGRAM_LENGTH);
	buffer.fromBase64Encoding(element->getAllSubText());
	buffer.copyTo(result,0, PROGRAM_LENGTH);*/
	
	return element;

}


XmlElement* PresetsLibrary::makeXmlTag(String name, bool readOnly)
{
	XmlElement* element = new XmlElement("TAG");
	element->setAttribute("name", name);
	element->setAttribute("readOnly", readOnly);
	return element;

}


void PresetsLibrary::generateDefaultXml()
{
	xmlPresetLibrary = new XmlElement("DEXEDLIBRARY");
	
	xmlPresetLibrary->setAttribute("majorversion", librayVersionMajor);
	xmlPresetLibrary->setAttribute("minorversion", libraryVersionMinor);

	XmlElement *xmlTagsList = new XmlElement("TAGS");
	XmlElement *xmlTagsTypeList = new XmlElement("TYPES");
	XmlElement *xmlTagsCharacteristicList = new XmlElement("CHARACTERISTIC");
	XmlElement *xmlTagsBankList = new XmlElement("BANKS");

	xmlTagsList->addChildElement(xmlTagsTypeList);
	xmlTagsList->addChildElement(xmlTagsCharacteristicList);
	xmlTagsList->addChildElement(xmlTagsBankList);
	// Types Tags
	xmlTagsTypeList->addChildElement(makeXmlTag("Bass",true));
	xmlTagsTypeList->addChildElement(makeXmlTag("Brass",true));
	xmlTagsTypeList->addChildElement(makeXmlTag("Key",true));
	xmlTagsTypeList->addChildElement(makeXmlTag("Lead",true));
	xmlTagsTypeList->addChildElement(makeXmlTag("Organ",true));
	xmlTagsTypeList->addChildElement(makeXmlTag("Pad",true));
	xmlTagsTypeList->addChildElement(makeXmlTag("Percussion",true));
	xmlTagsTypeList->addChildElement(makeXmlTag("Piano",true));
	xmlTagsTypeList->addChildElement(makeXmlTag("Sequence",true));
	xmlTagsTypeList->addChildElement(makeXmlTag("SFX",true));
	xmlTagsTypeList->addChildElement(makeXmlTag("Strings",true));
	xmlTagsTypeList->addChildElement(makeXmlTag("Template",true));
	//characteristicTags default
	xmlTagsCharacteristicList->addChildElement(makeXmlTag("Acid",true));
	xmlTagsCharacteristicList->addChildElement(makeXmlTag("Agressive",true));
	xmlTagsCharacteristicList->addChildElement(makeXmlTag("Ambient",true));
	xmlTagsCharacteristicList->addChildElement(makeXmlTag("Bizare",true));
	xmlTagsCharacteristicList->addChildElement(makeXmlTag("Bright",true));
	xmlTagsCharacteristicList->addChildElement(makeXmlTag("Complex",true));
	xmlTagsCharacteristicList->addChildElement(makeXmlTag("Dark",true));
	xmlTagsCharacteristicList->addChildElement(makeXmlTag("Digital",true));
	xmlTagsCharacteristicList->addChildElement(makeXmlTag("Ensemble",true));
	xmlTagsCharacteristicList->addChildElement(makeXmlTag("Evolving",true));
	xmlTagsCharacteristicList->addChildElement(makeXmlTag("Funky",true));
	xmlTagsCharacteristicList->addChildElement(makeXmlTag("Hard",true));
	xmlTagsCharacteristicList->addChildElement(makeXmlTag("Long",true));
	xmlTagsCharacteristicList->addChildElement(makeXmlTag("Noise",true));
	xmlTagsCharacteristicList->addChildElement(makeXmlTag("Quiet",true));
	xmlTagsCharacteristicList->addChildElement(makeXmlTag("Short",true));
	xmlTagsCharacteristicList->addChildElement(makeXmlTag("Soft",true));
	//xmlTagsBankList default
	xmlTagsBankList->addChildElement(makeXmlTag("Factory", true));

	XmlElement *xmlPresetsList = new XmlElement("PRESETS");

	File startupFile = cartDir.getChildFile("Dexed_01.syx");
	StringArray programNames;
	Cartridge cart;
	int rc = cart.load(startupFile);
	cart.getProgramNames(programNames);
	
	uint8_t presetDatas[PROGRAM_LENGTH];

	for (size_t i = 0; i < 32; i++)
	{
		cart.unpackProgram(presetDatas, i);
		String presetName = programNames.getReference(i);
		xmlPresetsList->addChildElement(makeXmlPreset(presetName, presetDatas,-1,0,Array<int>(),"Dexed","Dexed Factory presets",false,true));

	}


	xmlPresetLibrary->addChildElement(xmlTagsList);
	xmlPresetLibrary->addChildElement(xmlPresetsList);
	// now we can turn the whole thing into a text document…


	
	libraryFile.deleteFile();
	libraryFile.create();
	libraryFile.appendText(xmlPresetLibrary->createDocument(String()));

	//log(libraryXmlDoc);

}
//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]

void PresetsLibrary::scan(File dir)
{
    
    SyxFileFilter *syxFileFilter = new SyxFileFilter();
    TimeSliceThread *timeSliceThread = new TimeSliceThread("Cartridge Directory Scanner");
    DirectoryContentsList *libraryBrowserList;
	timeSliceThread->startThread();
	libraryBrowserList = new DirectoryContentsList(syxFileFilter, *timeSliceThread);
	libraryBrowserList->setDirectory(dir, true, true);
	

	//generateTags();

	//log("Scanning: "+ libraryBrowserList->getDirectory().getFileName());
	libraryPanel->repaint();
	this->repaint();
    while(libraryBrowserList->isStillLoading())
    {
        //wait
    }
    
    
    DirectoryContentsList::FileInfo fileInfos;
    int n = libraryBrowserList->getNumFiles();
    
    log("Files count of "+ libraryBrowserList->getDirectory().getFileName() +": "+String(n));
	
    for (int i=0;i<n; i++) {
		libraryBrowserList->getFileInfo(i, fileInfos);
        if (!fileInfos.isDirectory)
        {
            //sysex file

            File file = libraryBrowserList->getFile(i);
            importCart(file);

            

        }
		

    }
    
	libraryPanel->repaint();
	this->repaint();
    
    timeSliceThread->stopThread(500);
    delete libraryBrowserList;
    delete syxFileFilter;
    delete timeSliceThread;

}

int PresetsLibrary::importCart(File file)
{
    Cartridge cart;
    int rc = cart.load(file);
    if ( rc < 0 ) {
        AlertWindow::showMessageBoxAsync (AlertWindow::WarningIcon,
                                          "Error",
                                          "Unable to open: " + file.getFullPathName());
        return rc;
    }
    if ( rc != 0 ) {
        rc = AlertWindow::showOkCancelBox(AlertWindow::QuestionIcon, "Unable to find DX7 sysex cartridge in file",
                                          "This sysex file is not for the DX7 or it is corrupted. "
                                          "Do you still want to load this file as random data ?");
        if ( rc == 0 )
            return rc;
    }
    
    StringArray programNames;
    cart.getProgramNames(programNames);
    log( "Reading folder...");
    
    for(int j=0; j<programNames.size(); j++)
    {
        
		log(programNames.getReference(j));
        uint8_t unpackPgm[PROGRAM_LENGTH];
        cart.unpackProgram(unpackPgm,j);
        cart.getVoiceSysex();
    }
    
    return rc;
    
}

int PresetsLibrary::loadLibrary()
{
	if (!libraryFile.existsAsFile())
		return -1;
	xmlPresetLibrary = XmlDocument::parse(libraryFile);
	if (xmlPresetLibrary == NULL)
		return 1;
	return 0;
}

int PresetsLibrary::saveLibrary()
{
	//generateDefaultXml();

	return 1;
}

void PresetsLibrary::log(juce::String message)
{
#ifdef DEBUG
	if (message == "_CLEAR")
	{
		statusText->clear();
	}
	else {
		statusText->setText(statusText->getText() + newLine + message);
	}
#endif
}



//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SysexPresetsLibrary" componentName=""
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



