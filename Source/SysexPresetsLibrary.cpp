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

#include "SysexPresetsLibrary.h"
#include "PluginEditor.h"
#include "PluginData.h"

//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
SysexPresetsLibrary::SysexPresetsLibrary (DexedAudioProcessorEditor *editor, DirectoryContentsList *cartBrowserList)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]
    mainWindow = editor;
    cartDir = DexedAudioProcessor::dexedCartDir;
    libraryBrowserList=cartBrowserList;
    statusText="TEST";
    //TRACE("%s",cartDir.getFileName().toStdString().c_str());
    //[UserPreSize]
    //[/UserPreSize]

    setSize (812, 384);


    //[Constructor] You can add your own custom stuff here..
    addAndMakeVisible(scanButton = new TextButton("SCAN LIBRARY"));
    scanButton->setBounds(10, 10, 70, 30);
    scanButton->addListener(this);
    //[/Constructor]
}

SysexPresetsLibrary::~SysexPresetsLibrary()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void SysexPresetsLibrary::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    
    int x = 10, y = 50, width = 812-20 , height = 200;
    Colour fillColour = Colours::white;
    //[UserPaintCustomArguments] Customize the painting arguments here..
    //[/UserPaintCustomArguments]
    g.setColour (fillColour);
    g.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    g.drawMultiLineText(statusText, x, y, 812-20);
    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void SysexPresetsLibrary::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}


void SysexPresetsLibrary::buttonClicked(juce::Button *buttonThatWasClicked) {
    
   
    if ( buttonThatWasClicked == scanButton ) {
        
        scan(libraryBrowserList);
        return;
    }
}
//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]

void SysexPresetsLibrary::scan(DirectoryContentsList *cartBrowserList)
{
    //cartDir.
    statusText="Scanning...";
    this->repaint();
    String result="";
    DirectoryContentsList::FileInfo fileInfos;
    int n = cartBrowserList->getNumFiles();
    //result += "Files count: "+String(n)+newLine;
    
    for (int i=0;i<n; i++) {
        cartBrowserList->getFileInfo(i, fileInfos);
        if (!fileInfos.isDirectory)
        {
            //sysex file
            
            File file = cartBrowserList->getFile(i);
            
            
            Cartridge cart;
            int rc = cart.load(file);
            if ( rc < 0 ) {
                AlertWindow::showMessageBoxAsync (AlertWindow::WarningIcon,
                                                  "Error",
                                                  "Unable to open: " + file.getFullPathName());
                return;
            }
            if ( rc != 0 ) {
                rc = AlertWindow::showOkCancelBox(AlertWindow::QuestionIcon, "Unable to find DX7 sysex cartridge in file",
                                                  "This sysex file is not for the DX7 or it is corrupted. "
                                                  "Do you still want to load this file as random data ?");
                if ( rc == 0 )
                    return;
            }
            
            StringArray programNames;
            cart.getProgramNames(programNames);
            
            for(int j=0; j<programNames.size(); j++)
            {
               
                
                result += cartBrowserList->getDirectory().getFullPathName()+"|"+fileInfos.filename+" | "+programNames.getReference(j)+newLine;
                uint8_t unpackPgm[161];
                cart.unpackProgram(unpackPgm,j);
                
                //result += String((char *)unpackPgm)+newLine;
            }
            
        }
        
    }
    statusText = result;
    
    
    
    
    this->repaint();
    
    
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
