
#include "AutoLayoutManager.h"
#include "AutoLayoutCalculator.h"

namespace GameLibrary
{
	String LayoutRuleType_toString(const LayoutRuleType& layoutRuleType)
	{
		switch(layoutRuleType)
		{
			case LAYOUTRULE_LEFT:
			return "LAYOUTRULE_LEFT";

			case LAYOUTRULE_TOP:
			return "LAYOUTRULE_TOP";
			
			case LAYOUTRULE_RIGHT:
			return "LAYOUTRULE_RIGHT";
			
			case LAYOUTRULE_BOTTOM:
			return "LAYOUTRULE_BOTTOM";
			
			case LAYOUTRULE_CENTER_X:
			return "LAYOUTRULE_CENTER_X";
			
			case LAYOUTRULE_CENTER_Y:
			return "LAYOUTRULE_CENTER_Y";
			
			case LAYOUTRULE_WIDTH:
			return "LAYOUTRULE_WIDTH";
			
			case LAYOUTRULE_HEIGHT:
			return "LAYOUTRULE_HEIGHT";
			
			case LAYOUTRULE_ASPECTRATIO:
			return "LAYOUTRULE_ASPECTRATIO";
		}
		return "";
	}
	
	LayoutRuleType LayoutRuleType_fromString(const String& layoutRuleType, bool*valid)
	{
		if(valid!=nullptr)
		{
			*valid = true;
		}
		if(layoutRuleType.equals("LAYOUTRULE_LEFT"))
		{
			return LAYOUTRULE_LEFT;
		}
		else if(layoutRuleType.equals("LAYOUTRULE_TOP"))
		{
			return LAYOUTRULE_TOP;
		}
		else if(layoutRuleType.equals("LAYOUTRULE_RIGHT"))
		{
			return LAYOUTRULE_RIGHT;
		}
		else if(layoutRuleType.equals("LAYOUTRULE_BOTTOM"))
		{
			return LAYOUTRULE_BOTTOM;
		}
		else if(layoutRuleType.equals("LAYOUTRULE_CENTER_X"))
		{
			return LAYOUTRULE_CENTER_X;
		}
		else if(layoutRuleType.equals("LAYOUTRULE_CENTER_Y"))
		{
			return LAYOUTRULE_CENTER_Y;
		}
		else if(layoutRuleType.equals("LAYOUTRULE_WIDTH"))
		{
			return LAYOUTRULE_WIDTH;
		}
		else if(layoutRuleType.equals("LAYOUTRULE_HEIGHT"))
		{
			return LAYOUTRULE_HEIGHT;
		}
		else if(layoutRuleType.equals("LAYOUTRULE_ASPECTRATIO"))
		{
			return LAYOUTRULE_ASPECTRATIO;
		}
		if(valid!=nullptr)
		{
			*valid = false;
		}
		return LAYOUTRULE_LEFT;
	}
	
	String LayoutValueType_toString(const LayoutValueType& layoutValueType)
	{
		switch(layoutValueType)
		{
			case LAYOUTVALUE_PIXEL:
			return "LAYOUTVALUE_PIXEL";
			
			case LAYOUTVALUE_RATIO:
			return "LAYOUTVALUE_RATIO";
		}
		return "";
	}
	
	LayoutValueType LayoutValueType_fromString(const String& layoutValueType, bool*valid)
	{
		if(valid!=nullptr)
		{
			*valid = true;
		}
		if(layoutValueType.equals("LAYOUTVALUE_PIXEL"))
		{
			return LAYOUTVALUE_PIXEL;
		}
		else if(layoutValueType.equals("LAYOUTVALUE_RATIO"))
		{
			return LAYOUTVALUE_RATIO;
		}
		if(valid!=nullptr)
		{
			*valid = false;
		}
		return LAYOUTVALUE_PIXEL;
	}
	
	AutoLayoutManager::AutoLayoutManager() : containerOffset(false)
	{
		//
	}
	
	AutoLayoutManager::AutoLayoutManager(const AutoLayoutManager& autoLayoutMgr)
	{
		rules = autoLayoutMgr.rules;
		containerOffset = autoLayoutMgr.containerOffset;
	}
	
	AutoLayoutManager& AutoLayoutManager::operator=(const AutoLayoutManager& autoLayoutMgr)
	{
		rules = autoLayoutMgr.rules;
		containerOffset = autoLayoutMgr.containerOffset;
		return *this;
	}
	
	void AutoLayoutManager::setRule(const LayoutRuleType& ruleType, double value, const LayoutValueType& valueType)
	{
		for(size_t rules_size=rules.size(), i=0; i<rules_size; i++)
		{
			if(rules[i].ruleType==ruleType)
			{
				rules.remove(i);
				i = rules_size;
			}
		}
		LayoutRule rule;
		rule.ruleType = ruleType;
		rule.value = value;
		rule.valueType = valueType;
		rules.add(rule);
	}
	
	void AutoLayoutManager::setRules(const Dictionary& rulesDict)
	{
		removeAllRules();
		const ArrayList<Pair<String, Any> >& contents = rulesDict.getContents();
		for(size_t contents_size=contents.size(), i=0; i<contents_size; i++)
		{
			const Pair<String, Any> pair = contents.get(i);
			bool valid = false;
			LayoutRuleType ruleType = LayoutRuleType_fromString(pair.first, &valid);
			if(valid)
			{
				if(pair.second.is<Dictionary>())
				{
					const Dictionary& ruleData = pair.second.as<const Dictionary&>(false);
					Any value_any = ruleData.get("value");
					Any valueType_any = ruleData.get("valueType");
					if(!value_any.empty() && value_any.is<Number>())
					{
						double value = value_any.as<Number>(false).asDouble();
						LayoutValueType valueType = LAYOUTVALUE_PIXEL;
						if(!valueType_any.empty() && valueType_any.is<String>())
						{
							String valueType_str = valueType_any.as<String>(false);
							bool validValue = false;
							valueType = LayoutValueType_fromString(valueType_str, &validValue);
							if(!validValue)
							{
								valueType = LAYOUTVALUE_PIXEL;
							}
						}
						setRule(ruleType, value, valueType);
					}
				}
			}
		}
	}
	
	bool AutoLayoutManager::hasRules() const
	{
		if(rules.size()>0)
		{
			return true;
		}
		return false;
	}
	
	LayoutRule* AutoLayoutManager::getRule(const LayoutRuleType& ruleType) const
	{
		for(size_t rules_size=rules.size(), i=0; i<rules_size; i++)
		{
			LayoutRule* rule = (LayoutRule*)&rules[i];
			if(rule->ruleType==ruleType)
			{
				return rule;
			}
		}
		return nullptr;
	}
	
	void AutoLayoutManager::setOffsetByContainer(bool toggle)
	{
		containerOffset = toggle;
	}
	
	bool AutoLayoutManager::isOffsetByContainer() const
	{
		return containerOffset;
	}
	
	void AutoLayoutManager::removeAllRules()
	{
		rules.clear();
	}
	
	RectangleD AutoLayoutManager::calculateFrame(const RectangleD& currentFrame, const RectangleD& containerFrame) const
	{
		AutoLayoutCalculator layoutCalc(currentFrame, containerFrame);
		for(size_t rules_size=rules.size(), i=0; i<rules_size; i++)
		{
			const LayoutRule& rule = rules[i];
			switch(rule.ruleType)
			{
				case LAYOUTRULE_LEFT:
				layoutCalc.setLeft(rule.value, rule.valueType);
				break;
				
				case LAYOUTRULE_TOP:
				layoutCalc.setTop(rule.value, rule.valueType);
				break;
				
				case LAYOUTRULE_RIGHT:
				layoutCalc.setRight(rule.value, rule.valueType);
				break;
				
				case LAYOUTRULE_BOTTOM:
				layoutCalc.setBottom(rule.value, rule.valueType);
				break;
				
				case LAYOUTRULE_CENTER_X:
				layoutCalc.setCenterX(rule.value, rule.valueType);
				break;
				
				case LAYOUTRULE_CENTER_Y:
				layoutCalc.setCenterY(rule.value, rule.valueType);
				break;
				
				case LAYOUTRULE_WIDTH:
				layoutCalc.setWidth(rule.value, rule.valueType);
				break;
				
				case LAYOUTRULE_HEIGHT:
				layoutCalc.setHeight(rule.value, rule.valueType);
				break;
				
				case LAYOUTRULE_ASPECTRATIO:
				layoutCalc.setAspectRatio(rule.value);
				break;
			}
		}
		if(containerOffset)
		{
			RectangleD calculatedFrame = layoutCalc.getCalculatedFrame();
			calculatedFrame.x += containerFrame.x;
			calculatedFrame.y += containerFrame.y;
			return calculatedFrame;
		}
		return layoutCalc.getCalculatedFrame();
	}
}
