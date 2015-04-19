
#include "ActionPerformer.h"

using namespace GameLibrary;

namespace BrawlerLibrary
{
	ActionPerformer::ActionPerformer()
		: side(FaceDirection::LEFT), action_current(nullptr)
	{
		//
	}
	
	ActionPerformer::ActionPerformer(const Vector2d&position)
		: SpriteActor(position.x, position.y), side(FaceDirection::LEFT), action_current(nullptr)
	{
		//
	}
	
	ActionPerformer::~ActionPerformer()
	{
		size_t actions_size = actions.size();
		for(size_t i=0; i<actions_size; i++)
		{
			ActionInfo actInfo = actions.get(i);
			if(actInfo.destruct)
			{
				delete actInfo.action;
			}
		}
	}
	
	void ActionPerformer::addAction(const String&name, Action*action, bool destruct)
	{
		if(hasAction(name))
		{
			throw IllegalArgumentException("name", "duplicate action name");
		}
		
		ActionInfo actInfo;
		actInfo.name = name;
		actInfo.action = action;
		actInfo.destruct = destruct;
		actions.add(actInfo);
	}
	
	void ActionPerformer::removeAction(const String&name)
	{
		size_t actions_size = actions.size();
		for(size_t i=0; i<actions_size; i++)
		{
			ActionInfo actInfo = actions.get(i);
			if(actInfo.name.equals(name))
			{
				if(actInfo.destruct)
				{
					delete actInfo.action;
				}
				actions.remove(i);
				return;
			}
		}
		throw IllegalArgumentException("name", "action does not exist");
	}
	
	bool ActionPerformer::hasAction(const String&name) const
	{
		size_t actions_size = actions.size();
		for(size_t i=0; i<actions_size; i++)
		{
			ActionInfo actInfo = actions.get(i);
			if(actInfo.name.equals(name))
			{
				return true;
			}
		}
		return false;
	}
	
	void ActionPerformer::performAction(const String&name)
	{
		Action*action = nullptr;
		size_t actions_size = actions.size();
		for(size_t i=0; i<actions_size; i++)
		{
			ActionInfo actInfo = actions.get(i);
			if(actInfo.name.equals(name))
			{
				action = actInfo.action;
				i = actions_size;
			}
		}
		
		if(action == nullptr)
		{
			throw IllegalArgumentException("name", "action does not exist");
		}
		else if(action->performer != nullptr && ((!action->finishing && !action->cancelling) || action->reran))
		{
			throw IllegalArgumentException("perform", "cannot perform on multiple performers");
		}
		else if(action_current != nullptr && ((!action_current->finishing && !action_current->cancelling) || action_current->reran))
		{
			throw IllegalStateException("current action must be cancelled or finished before another action is performed");
		}
		else if(action_current==action && action_current->cancelling)
		{
			throw IllegalArgumentException("action", "action is cancelling");
		}
		
		action_current = action;
		action_name = name;
		
		action_current->perform(this);
	}
	
	void ActionPerformer::performAction(Action*action)
	{
		if(action == nullptr)
		{
			throw IllegalArgumentException("action", "cannot be null");
		}
		else if(action->performer != nullptr && ((!action->finishing && !action->cancelling) || action->reran))
		{
			throw IllegalArgumentException("perform", "cannot perform on multiple performers");
		}
		else if(action_current != nullptr && ((!action_current->finishing && !action_current->cancelling) || action_current->reran))
		{
			throw IllegalStateException("current action must be cancelled or finished before another action is performed");
		}
		else if(action_current == action && action_current->cancelling)
		{
			throw IllegalArgumentException("action", "action is cancelling");
		}
		
		action_current = action;
		action_name = "";
		
		action_current->perform(this);
	}
	
	void ActionPerformer::cancelAction()
	{
		if(action_current == nullptr)
		{
			throw IllegalStateException("action is not being performed");
		}
		else if(action_current->cancelling)
		{
			throw IllegalStateException("action is already cancelling");
		}
		action_current->cancel();
	}
	
	bool ActionPerformer::isPerformingAction() const
	{
		if(action_current == nullptr || ((action_current->finishing || action_current->cancelling) && !action_current->reran))
		{
			return false;
		}
		return true;
	}
	
	void ActionPerformer::setFaceDirection(const FaceDirection&faceSide)
	{
		side = faceSide;
		if(side==FaceDirection::LEFT)
		{
			setMirroredHorizontal(false);
		}
		else if(side==FaceDirection::RIGHT)
		{
			setMirroredHorizontal(true);
		}
	}
	
	const FaceDirection& ActionPerformer::getFaceDirection() const
	{
		return side;
	}
	
	void ActionPerformer::onAnimationFinish(const String&name, Animation*animation)
	{
		if(action_current != nullptr)
		{
			action_current->onPerformerAnimationFinish(name, animation);
		}
		
		//Open for implementation
	}
	
	void ActionPerformer::onActionFinish(const String&name, Action*action)
	{
		//Open for implementation
	}
}
