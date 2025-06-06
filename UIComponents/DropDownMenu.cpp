/*
  ==============================================================================

    DropDownMenu.cpp
    Created: 7 May 2025 3:43:27pm
    Author:  danny

  ==============================================================================
*/

#include "DropDownMenu.h"

// DROPDOWNCONTEXT
//==============================================================================

DropDownContext::DropDownContext(DropDownMenu& parentDDMenu) : parent(parentDDMenu)
{
    setAlwaysOnTop(true);
}


void DropDownContext::paint (juce::Graphics& graphics) 
{
    const auto& localBounds = getLocalBounds();
    graphics.setColour(colour_constants::backGround);
    graphics.fillRect(localBounds);
    graphics.setColour(colour_constants::lightMain);
    graphics.drawRect(localBounds);
}

void DropDownContext::resized() 
{
    toFront(false);
    auto parentBounds = getTopLevelComponent()->getLocalArea(&parent, parent.getLocalBounds());
    Rectangle<int> fullBounds = {parentBounds.getX(), parentBounds.getHeight() + parentBounds.getY(), parentBounds.getWidth(), static_cast<int>(parentBounds.getHeight() * buttonEntries.size()) };
    setBounds(fullBounds);
    for (size_t i = 0; i < buttonEntries.size(); ++i) 
    {
        auto bounds = getLocalBounds();
        bounds.setHeight(parentBounds.getHeight());
        bounds.setY(parentBounds.getHeight() * i);
        buttonEntries[i]->setBounds(bounds);
    }
}

void DropDownContext::addEntry(const String& entryName, std::function<void()> callback)
{    
    auto newButton = std::make_unique<TextButton>(entryName);
    auto* buttonRaw = newButton.get();
    addAndMakeVisible(*newButton);
    newButton->setLookAndFeel(&getLookAndFeel());
    newButton->onClick = [this, callback, buttonRaw]()
        { 
            callback(); 
            this->parent.setText(buttonRaw->getButtonText());
            this->setVisible(false);
        };
    //TODO: make all the colour stuff here settable by owner. remove all dependency on colour_constants
    newButton->setColour(TextButton::ColourIds::buttonOnColourId, colour_constants::backGround);
    newButton->setColour(TextButton::ColourIds::buttonColourId, colour_constants::lightMain);
    newButton->setColour(TextButton::ColourIds::textColourOnId, colour_constants::main);
    newButton->setColour(TextButton::ColourIds::textColourOffId, colour_constants::main);
    buttonEntries.emplace_back(std::move(newButton));
    resized();
}


// DROPDOWNMENU
//==============================================================================
DropDownMenu::DropDownMenu() : contextMenu(*this) 
{
    init();
}
DropDownMenu::DropDownMenu(const String& name) : contextMenu(*this)
{
    init();
    setName(name);
}

void DropDownMenu::init()
{
    text = "";
    resized();
}

void DropDownMenu::paint (juce::Graphics& graphics)
{

    const auto& localBounds = getLocalBounds();
    graphics.setColour(backGroundColour);
    graphics.fillRect(localBounds);

    graphics.setColour (colour_constants::main);
    graphics.setFont (juce::FontOptions (14.0f));
    graphics.drawText (text, localBounds, juce::Justification::centred, true);  
}

void DropDownMenu::mouseUp(const juce::MouseEvent& event) 
{
    if (contextMenu.isShowing())
    {
        contextMenu.setVisible(false);
    }
    else
    {
        contextMenu.setVisible(true);
    }
}
void DropDownMenu::resized()
{
}

void DropDownMenu::setText(const String& newText)
{
    text = newText;
    repaint();
}

void DropDownMenu::addToDropDownContext(const String& entryToAdd, std::function<void()> callback)
{
    if (getParentComponent() != nullptr) {
        getTopLevelComponent()->addChildComponent(contextMenu);
    }
    contextMenu.addEntry(entryToAdd, callback);
}

void DropDownMenu::lookAndFeelChanged()
{
    contextMenu.setLookAndFeel(&getLookAndFeel());
}

