
#include "ActionPerformer.h"

using namespace GameLibrary;

namespace BrawlerLibrary
{
	ActionPerformer::ActionPerformer() : ActionPerformer(Vector2d(0, 0))
	{
		//
	}
	
	ActionPerformer::ActionPerformer(const Vector2d&position) : SpriteActor(position.x, position.y)
	{
		action_current = nullptr;
		side = FaceDirection::LEFT;
	}
	
	ActionPerformer::~ActionPerformer()
	{
		size_t actions_size = actions.size();
		for(size_t i=0; i<actions_size; i++)
		{
			ActionInfo&actInfo = actions.get(i);
			if(actInfo.destruct)
			{
				delete actInfo.action;
			}
		}
	}
	
	void ActionPerformer::addAction(const String&name, Action*action, bool destruct)
	{
		if(action == nullptr)
		{
			throw IllegalArgumentException("action", "cannot be null");
		}
		if(name.length() == 0)
		{
			throw IllegalArgumentException("name", "cannot be empty string");
		}
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
		size_t totalActions = actions.size();
		for(size_t i=0; i<totalActions; i++)
		{
			ActionInfo actInfo = actions.get(i);
			if(actInfo.name.equals(name))
			{
				if(actInfo.name.equals(action_name))
				{
					action_current = nullptr;
					action_name = "";
				}
				for(size_t j=(queue.size()-1); j!=SIZE_MAX; j--)
				{
					if(queue.get(j).first.equals(name))
					{
						queue.remove(j);
					}
				}
				if(actInfo.destruct)
				{
					delete actInfo.action;
				}
				actions.remove(i);
				return;
			}
		}
	}
	
	bool ActionPerformer::hasAction(const String&name) const
	{
		size_t totalActions = actions.size();
		for(size_t i=0; i<totalActions; i++)
		{
			if(actions.get(i).name.equals(name))
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
			ActionInfo&actInfo = actions.get(i);
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
		if(action_current != nullptr && !action_current->finishing)
		{
			action_current->cancel();
		}
		queue.clear();
		action_current = action;
		action_name = name;
		action->perform(this);
	}
	
	void ActionPerformer::performAction(Action*action)
	{
		if(action==action_current && action_current!=nullptr)
		{
			if(!(action->performer != nullptr && (!action->finishing || action->reran)))
			{
				action_current->cancel();
			}
		}
		else
		{
			if(action_current != nullptr && !action_current->finishing)
			{
				action_current->cancel();
			}
		}
		queue.clear();
		action_current = action;
		action_name = "";
		if(action!=nullptr)
		{
			action->perform(this);
		}
	}
	
	void ActionPerformer::queueAction(const GameLibrary::String&name)
	{
		Action*action = nullptr;
		size_t actions_size = actions.size();
		for(size_t i=0; i<actions_size; i++)
		{
			ActionInfo&actInfo = actions.get(i);
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
		
		if(queue.size()==0 && action_current==nullptr)
		{
			performAction(action);
		}
		else
		{
			queue.add(Pair<String, Action*>(name, action));
		}
	}
	
	void ActionPerformer::queueAction(Action*action)
	{
		if(action == nullptr)
		{
			throw IllegalArgumentException("action", "cannot be null");
		}
		if(queue.size()==0 && action_current==nullptr)
		{
			performAction(action);
		}
		else
		{
			queue.add(Pair<String, Action*>("", action));
		}
	}
	
	bool ActionPerformer::setFaceDirection(const FaceDirection&faceSide)
	{
		if(faceSide!=side)
		{
			if(action_current != nullptr)
			{
				if(!action_current->canPerformerSetFaceDirection(faceSide))
				{
					return false;
				}
			}
			side = faceSide;
			if(side == FaceDirection::LEFT)
			{
				setMirroredHorizontal(false);
			}
			else if(side == FaceDirection::RIGHT)
			{
				setMirroredHorizontal(true);
			}
		}
		return true;
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
	}
	
	void ActionPerformer::onActionFinish(const GameLibrary::String&name, Action*action)
	{
		//Open for implementation
	}
	
	void ActionPerformer::whenActionFinish(const String&name, Action*action)
	{
		if(action_current==action && !action->reran)
		{
			action_current = nullptr;
			action_name = "";
		}
		onActionFinish(name, action);
		if(queue.size() > 0)
		{
			Pair<String, Action*>& next = queue.get(0);
			queue.remove(0);
			if(name.length() == 0)
			{
				performAction(next.second);
			}
			else
			{
				performAction(next.first);
			}
		}
	}
}
