#include "UIRadioGroup.h"

UIRadioGroup::UIRadioGroup(DriverBase &tft, std::string elementName) :
	UIElement(tft, Rectangle(0, 0, 0, 0), elementName, eElementType::RadioGroup)
{
	buttonCount = 0;
}

void UIRadioGroup::AddRadioButton(UIRadioButton *radioButton)
{
	if (buttonCount == 0)
	{
		radioButton->SetChecked(true);
		selectedButton = 0;
	}

	UIElement::AddChildElement(radioButton);

	if (radioButton->IsChecked())
	{
		// Clear the rest of the radio buttons in the group
		for (int i = 0; i < childElements.size(); i++)
		{
			if (childElements[i]->GetElementType()==eElementType::RadioButton)
			{				
				if (selectedButton != i)
					((UIRadioButton *)(childElements[i]))->SetChecked(false);
			}
		}
	}

	this->location.add(radioButton->GetLocation());
}

std::string UIRadioGroup::GetSelectedButton()
{
	for (int i = 0; i < childElements.size(); i++)
	{
		// Make sure child is a RadioButton
		if (childElements[i]->GetElementType() == eElementType::RadioButton)					
		{
			if (((UIRadioButton *)(childElements[i]))->IsChecked())
				return ((UIRadioButton *)(childElements[i]))->getElementName();
		}
	}
	return "";
}

void UIRadioGroup::SetSelectedButton(std::string buttonName)
{
	for (int i = 0; i < childElements.size(); i++)
	{
		// Make sure child is a RadioButton
		if (childElements[i]->GetElementType() == eElementType::RadioButton)
		{
			if (((UIRadioButton *)(childElements[i]))->getElementName() == buttonName)
				if (!((UIRadioButton *)(childElements[i]))->IsChecked())
				{
					((UIRadioButton *)(childElements[i]))->SetChecked(true);
					childElements[i]->Update();
				}
			else
				if (((UIRadioButton *)(childElements[i]))->IsChecked())
				{
					((UIRadioButton *)(childElements[i]))->SetChecked(false);
					childElements[i]->Update();
				}
		}
	}
}

void UIRadioGroup::SetSelectedButton(uint8_t buttonIdx)
{
	uint8_t i = 0, j = 0;
	while (i <= childElements.size())
	{
		if (childElements[i]->GetElementType() == eElementType::RadioButton)
		{
			j++;
			if (j == buttonIdx)
			{
				if (!((UIRadioButton *)(childElements[i]))->IsChecked())
				{
					((UIRadioButton *)(childElements[i]))->SetChecked(true);
					childElements[i]->Update();
				}
			}
			else
			{
				if (((UIRadioButton *)(childElements[i]))->IsChecked())
				{
					((UIRadioButton *)(childElements[i]))->SetChecked(false);
					childElements[i]->Update();
				}
			}		
		}
		i++;
	}
}

/// <summary>
/// The standard update is fine for this, as the only displayable objects in this
///	are children
/// </summary>
void UIRadioGroup::Update()
{
	UIElement::Update();
}

sTouchResponse UIRadioGroup::ProcessTouch(Point pt)
{
	int radioButtonIdx=0;
	for (int i = 0; i < childElements.size(); i++)
	{
		if (childElements[i]->GetElementType()== eElementType::RadioButton)
		{
			if (childElements[i]->GetLocation().contains(pt))
			{
				if (!((UIRadioButton *)(childElements[i]))->IsChecked() && childElements[i]->isEnabled())
				{
					SetSelectedButton(radioButtonIdx);
					return sTouchResponse(childElements[i]->getElementID(), eTouchResponse::ControlTouched);
				}
			}
			radioButtonIdx++;
		}
	}
}