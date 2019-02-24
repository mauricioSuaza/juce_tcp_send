/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include <iostream>
#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (600, 400);

    //setup connect button
    addAndMakeVisible (connectButton);
    connectButton.setButtonText ("Connect to server");
    connectButton.setBounds (10, 10, getWidth() - 20, 40);

    
    //setup rotary knob
    rotaryKnob.setRange (0.0, 1.0);
    rotaryKnob.setSliderStyle (Slider::RotaryVerticalDrag);
    rotaryKnob.setTextBoxStyle (Slider::TextBoxBelow, true, 150, 25);
    rotaryKnob.setBounds (10, 10, 180, 180);
    addAndMakeVisible (rotaryKnob);

    //connect button listener
    connectButton.onClick = [this] {
        if (!tcp_socket.isConnected())
            tcp_socket.connect("127.0.0.1", 11999, 3000);
    };
    //rotary knob listener
    rotaryKnob.onValueChange = [this]
    {
        rotaryKnob.getValue();
        String msg = String(rotaryKnob.getValue(), 4) + "\n";
        MemoryBlock data(256, true);
        data.copyFrom(msg.toUTF8(), 0, msg.length());
        tcp_socket.write(data.getData(), data.getSize());
    };
   
}

MainComponent::~MainComponent()
{
}

void showConnectionErrorMessage (const String& messageText)
{
    AlertWindow::showMessageBoxAsync (AlertWindow::WarningIcon,
                                      "Connection error",
                                      messageText,
                                      "OK");
}


//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setFont (Font (16.0f));
    g.setColour (Colours::white);
    g.drawText ("Hello World!", getLocalBounds(), Justification::centred, true);
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.


}

