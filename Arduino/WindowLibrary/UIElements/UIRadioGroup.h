#pragma once
#include "../Options.h"
#include <string>
#include <map>
#include <vector>
#include "../Utility/Color.h"
#include "UIElement.h"
#include <SPI.h>
#include "UIRadioButton.h"
#include "../Utility/Rectangle.h"

/// <summary>
/// UIRadioGroup is a container class, some differences from other UIElements
///		* Location is a total of the children (UIRadioButton)
///		* The radio buttons value is retrieved from this element
/// </summary>
/// <seealso cref="UIElement" />
class UIRadioGroup : UIElement
{
public:
	UIRadioGroup(DriverBase &tft, std::string elementName);

	// By default the first radio button added is checked, as one must be checked
	void AddRadioButton(UIRadioButton *radioButton);	
	std::string GetSelectedButton();
	
	void SetSelectedButton(std::string buttonName);
	void SetSelectedButton(uint8_t buttonIdx);
	
	void Update() override;

	sTouchResponse ProcessTouch(Point pt) override;

private:
	uint8_t selectedButton;
	uint8_t buttonCount;
};
