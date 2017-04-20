#include "UIButton.h"

UIButton::UIButton(Rectangle location, Theme *theme) :
  UIElement(Point(location.x1, location.y1),false,true, theme)
{
  elementArea=location;
  clickable=theme->LoadTheme(eThemeObjType::clickable,eThemeObjState::defaultState);
  active=theme->LoadTheme(eThemeObjType::clickable, eThemeObjState::activeState);
}

void UIButton::setTouchArea()
{
  if(enabled)
    touchArea=new Rectangle (elementArea.x1, elementArea.y1, elementArea.x2, elementArea.y2);
  else
    touchArea=new Rectangle(-1,-1,-1,-1);
}

void UIButton::update(RA8875 *lcd)
{
  sThemeSettings currentSettings=clickable;
  if(lcd->touched())
  {
    uint16_t *x, *y;
    lcd->touchReadPixel(x,y);
    if(touchArea->contains(Point((int)x,(int)y)))
    {
      if(!touched)
      {
        currentSettings=active;
        touched=true;
        needsUpdate=true;
      } else
      {
        // We were touched, we are touched, continue
        return;
      }
    } else
    {
        // We are outside the control
        if(!touched)
        {
          // We werent in touch mode, so dont redraw
          return;
        }
        currentSettings=clickable;
        touched=false;
        needsUpdate=true;
    }
  } else
  {
    if(touched)
    {
      // We had been touching, now we arent
      touched=false;
      needsUpdate=true;
      currentSettings=clickable;
    }
  }

  if(!needsUpdate)
  {
    return;
  }

  drawBorder(lcd,currentSettings);
  fillButton(lcd,currentSettings);

  // Draw all childElements
  for(unsigned int i=0; i<childElements.size(); i++)
  {
    childElements[i]->Invalidate();
    childElements[i]->update(lcd);
  }
  needsUpdate=false;
}

void UIButton::drawBorder(RA8875 *lcd, sThemeSettings themeSettings)
{
  uint16_t buttonBorderColor=themeSettings.borderColor;
  // First draw border
  if(cornerType==eButtonCornerType::Square)
  {
    for(int i=0; i<borderSize; i++)
    {
      lcd->drawRect(elementArea.x1+i,elementArea.y1+i, elementArea.x2-i, elementArea.y2-i, buttonBorderColor);
    }
    drawShadow(lcd,themeSettings);
  }
  if(cornerType==eButtonCornerType::Rounded)
  {
    uint8_t radius=5;
    if((abs(elementArea.x2-elementArea.x1)<5) || (abs(elementArea.x2-elementArea.x1)<5))
    {
      radius=1;
    }
    for(int i=0; i<borderSize; i++)
    {
      lcd->drawRoundRect(elementArea.x1+i, elementArea.y1+i, elementArea.x2-i, elementArea.y2-i, radius, buttonBorderColor);
    }

    // For now I dont feel like doing the math for the shadow, Ill add it
    //TODO: Shadow for rounded corners
  }
}

void UIButton::drawShadow(RA8875 *lcd, sThemeSettings themeSettings)
{
  int shadowOffsetX=5;
  int shadowOffsetY=5;
  if(abs(elementArea.x2-elementArea.x1)<5)
  {
    shadowOffsetX=1;
  }
  if(abs(elementArea.y2-elementArea.y1)<5)
  {
    shadowOffsetY=1;
  }
  uint8_t dropShadowThickness=themeSettings.shadowThickness;
  uint16_t shadowColor=themeSettings.shadowColor;
  // Now add shadowColor
  for(int i=1; i<=dropShadowThickness; i++)
  {
    for(int x=elementArea.x1+shadowOffsetX; x<elementArea.x2; x++)
    {
      if(shadowInterpolated)
      {
        // We combine the 2 colors, adding shadowOpacity*shadowColor to the backgroundColor
        uint16_t newColor=Color::CombineColor(shadowColor,lcd->getPixel(x,elementArea.y2+i),shadowOpacity);
        lcd->drawPixel(x,elementArea.y2+i,newColor);
      } else
      {
        lcd->drawPixel(x,elementArea.y2+i,shadowColor);
      }
    }
    for(int y=elementArea.y1+shadowOffsetY; y<elementArea.y2; y++)
    {
      if(shadowInterpolated)
      {
        // We combine the 2 colors, adding shadowOpacity*shadowColor to the backgroundColor
        uint16_t newColor=Color::CombineColor(shadowColor,lcd->getPixel(elementArea.x2+i,y),shadowOpacity);
        lcd->drawPixel(elementArea.x2+i,y,newColor);
      } else
      {
        lcd->drawPixel(elementArea.x2+i,y,shadowColor);
      }
    }
  }
}

void UIButton::fillButton(RA8875 *lcd, sThemeSettings themeSettings)
{
  uint16_t bgColor=themeSettings.bgColor;
  if(cornerType==eButtonCornerType::Square)
  {
    lcd->fillRect(elementArea.x1+borderSize,elementArea.y1+borderSize,
      elementArea.x2-borderSize, elementArea.y2-borderSize,bgColor);
  } else
  {
    uint8_t radius=5;
    if((abs(elementArea.x2-elementArea.x1)<5) || (abs(elementArea.x2-elementArea.x1)<5))
    {
      radius=1;
    }

    lcd->fillRoundRect(elementArea.x1+borderSize,elementArea.y1+borderSize,
      elementArea.x2-borderSize, elementArea.y2-borderSize,radius, bgColor);
  }
}

void UIButton::setButtonText(std::string buttonText)
{

}
