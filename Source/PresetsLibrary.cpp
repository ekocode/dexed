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

//
int Tag::maxid = 0;


//==============================================================================
PresetsLibrary::PresetsLibrary (DexedAudioProcessorEditor *editor)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]
    mainWindow = editor;
	
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
    
    
    cartDir = DexedAudioProcessor::dexedCartDir;
    //libraryBrowserList=new DirectoryContentsList(cartDir,true,true);
	
    //TRACE("%s",cartDir.getFileName().toStdString().c_str());
    //[UserPreSize]
    //[/UserPreSize]

    setSize (812, 384);


    //[Constructor] You can add your own custom stuff here..
    


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
    //[/Constructor]
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
}
void PresetsLibrary::generateTags()
{
	// Types Tags
	typeTags.add(Tag("Bass"));
	typeTags.add(Tag("Brass"));

	typeTags.add(Tag("Key"));

	typeTags.add(Tag("Lead"));

	typeTags.add(Tag("Organ"));

	typeTags.add(Tag("Pad"));
	typeTags.add(Tag("Percussion"));
	typeTags.add(Tag("Piano"));

	typeTags.add(Tag("Sequence"));
	typeTags.add(Tag("SFX"));
	typeTags.add(Tag("Strings"));

	typeTags.add(Tag("Template"));

	//characteristicTags default
	characteristicTags.add(Tag("Acid"));
	characteristicTags.add(Tag("Agressive"));
	characteristicTags.add(Tag("Ambient"));
	characteristicTags.add(Tag("Bizare"));
	characteristicTags.add(Tag("Bright"));
	characteristicTags.add(Tag("Complex"));
	characteristicTags.add(Tag("Dark"));
	characteristicTags.add(Tag("Digital"));
	characteristicTags.add(Tag("Ensemble"));
	characteristicTags.add(Tag("Evolving"));
	characteristicTags.add(Tag("Funky"));
	characteristicTags.add(Tag("Hard"));
	characteristicTags.add(Tag("Long"));
	characteristicTags.add(Tag("Noise"));
	characteristicTags.add(Tag("Quiet"));
	characteristicTags.add(Tag("Short"));
	characteristicTags.add(Tag("Soft"));

	bankTags.add(Tag("Default"));

}
//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]

void PresetsLibrary::scan(File dir)
{
    
    SyxFileFilter *syxFileFilter = new SyxFileFilter();
    TimeSliceThread *timeSliceThread = new TimeSliceThread("Cartridge Directory Scanner");
    DirectoryContentsList *libraryBrowserList;
    //cartDir.
	timeSliceThread->startThread();
	libraryBrowserList = new DirectoryContentsList(syxFileFilter, *timeSliceThread);
	libraryBrowserList->setDirectory(dir, true, true);
	

	//generateTags();

	log("Scanning: "+ libraryBrowserList->getDirectory().getFileName());
	libraryPanel->repaint();
	this->repaint();
    while(libraryBrowserList->isStillLoading())
    {
        //wait (500);
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
        //log(libraryBrowserList->getDirectory().getFullPathName()+"|"+fileInfos.filename+" | "+programNames.getReference(j));
        uint8_t unpackPgm[161];
        cart.unpackProgram(unpackPgm,j);
        cart.getVoiceSysex();
        
        //result += String((char *)unpackPgm)+newLine;
    }
    
    return rc;
    
}

int PresetsLibrary::loadLibrary()
{
	return 1;
}

int PresetsLibrary::saveLibrary()
{
	XmlElement xmlPresetLibrary("DEXEDLIBRARY");
	xmlPresetLibrary.setAttribute("majorversion", librayVersionMajor);
	xmlPresetLibrary.setAttribute("minorversion", libraryVersionMinor);

	XmlElement *xmlTagsList = new XmlElement("TAGS");
	XmlElement *xmlPresetsList = new XmlElement("PRESETS");
	for (int i = 0; i < 10; ++i)
	{
		// create an inner element…
		XmlElement* xmlPreset = new XmlElement("PRESET");
		xmlPreset->setAttribute("name", "preset"+String(i));
		xmlPreset->setAttribute("favorite", true);
		// …and add our new element to the parent node
		xmlPresetsList->addChildElement(xmlPreset);
	}
	xmlPresetLibrary.addChildElement(xmlTagsList);
	xmlPresetLibrary.addChildElement(xmlPresetsList);
	// now we can turn the whole thing into a text document…
	String myXmlDoc = xmlPresetLibrary.createDocument(String());
	log("_CLEAR");
	log(myXmlDoc);
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



