
#pragma once

#include "../Utilities/ArrayList.h"
#include "../Utilities/Dictionary.h"
#include "../Utilities/Geometry/Rectangle.h"

namespace GameLibrary
{
	typedef enum LayoutRuleType
	{
		LAYOUTRULE_LEFT,
		LAYOUTRULE_TOP,
		LAYOUTRULE_RIGHT,
		LAYOUTRULE_BOTTOM,
		LAYOUTRULE_CENTER_X,
		LAYOUTRULE_CENTER_Y,
		LAYOUTRULE_WIDTH,
		LAYOUTRULE_HEIGHT,
		LAYOUTRULE_ASPECTRATIO // width/height
	} LayoutRuleType;
	String LayoutRuleType_toString(const LayoutRuleType& layoutRuleType);
	LayoutRuleType LayoutRuleType_fromString(const String& layoutRuleType, bool*valid);
	
	typedef enum LayoutValueType
	{
		LAYOUTVALUE_PIXEL,
		LAYOUTVALUE_RATIO
	} LayoutValueType;
	String LayoutValueType_toString(const LayoutValueType& layoutValueType);
	LayoutValueType LayoutValueType_fromString(const String& layoutValueType, bool*valid);
	
	typedef struct LayoutRule
	{
		LayoutRuleType ruleType;
		double value;
		LayoutValueType valueType;
	} LayoutRule;
	
	/*! Automatically lays out Actor and ScreenElement objects based on a given frame*/
	class AutoLayoutManager
	{
	public:
		/*! default constructor*/
		AutoLayoutManager();
		/*! copy constructor*/
		AutoLayoutManager(const AutoLayoutManager&);
		/*! assignment operator*/
		AutoLayoutManager& operator=(const AutoLayoutManager&);
		
		void setRule(const LayoutRuleType& ruleType, double value, const LayoutValueType& valueType=LAYOUTVALUE_PIXEL);
		void setRules(const Dictionary& rules);
		bool hasRules() const;
		LayoutRule* getRule(const LayoutRuleType& ruleType) const;
		void setOffsetByContainer(bool toggle);
		bool isOffsetByContainer() const;

		void removeAllRules();
		
		RectangleD calculateFrame(const RectangleD& currentFrame, const RectangleD& containerFrame) const;
		
	private:
		ArrayList<LayoutRule> rules;
		bool containerOffset;
	};
}
