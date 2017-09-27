#include "../Options.h"
#include "../UIElements/UIElement.h"
#ifdef useElementGraph
#include "../Utility/CircularMinMaxBuffer.h"
#ifdef FT8XX
#include "../UIElements/FT8XX/UIPrimitives.h"
#endif
#ifdef RA8875
#include "../UIElements/RA8875/UIPrimitives.h"
#endif

class UIElementGraph : public UIElement
{
public:
	enum eGraphType
	{
		BarGraph,
		LineGraph
	};

	UIElementGraph(DriverBase &tft, Rectangle location, CircularMinMaxBuffer &inValues,
		std::string itemLabel, eUITextFont font,
		tColor textColor, uint8_t textScale, tColor graphColor, tColor bgColor,
		eGraphType graphType=eGraphType::BarGraph,
		uint8_t cornerRadius = 4, std::string elementName = "", uint8_t alpha = 255);

	sTouchResponse ProcessTouch(Point touchPoint) override
	{
		return sTouchResponse(this->elementID, eTouchResponse::NoOp);
	}
	virtual void Update() override;

	CircularMinMaxBuffer GetValues()
	{
		return values;
	}

	void AddValue(float value)
	{
		values.PushItem(value);
		this->Invalidate();
	}

private:
	eUITextFont font;
	uint8_t cornerRadius;
	CircularMinMaxBuffer values;
	uint16_t prevValuesChecksum = 0;
	uint8_t alpha;
	std::string itemLabel;
	eGraphType graphType;
	tColor textColor, graphColor, bgColor;

};

#endif