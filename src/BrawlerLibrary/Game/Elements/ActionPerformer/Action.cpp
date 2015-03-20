
#include "Action.h"
#include "ActionPerformer.h"

using namespace GameLibrary;

namespace BrawlerLibrary
{
	Action::Action()
	{
		performer = nullptr;
		finishing = false;
		reran = false;
	}
	
	Action::~Action()
	{
		//
	}
	
	void Action::perform(ActionPerformer*actionPerformer)
	{
		if(performer != nullptr && (!finishing || reran))
		{
			throw IllegalStateException("Action is already being performed");
		}
		if(finishing)
		{
			reran = true;
		}
		performer = actionPerformer;
		onPerform();
	}
	
	void Action::cancel()
	{
		if(performer == nullptr)
		{
			throw IllegalStateException("Action is not being performed");
		}
		onCancel();
		performer = nullptr;
	}
	
	void Action::finish()
	{
		if(performer == nullptr)
		{
			throw IllegalStateException("Action is not being performed");
		}
		finishing = true;
		ActionPerformer*performer_old = performer;
		String name_old = performer_old->action_name;
		onFinish();
		performer_old->whenActionFinish(name_old,this);
		if(!reran)
		{
			performer = nullptr;
		}
		else
		{
			reran = false;
		}
		finishing = false;
	}
	
	void Action::onPerform()
	{
		//Open for implementation
	}
	
	void Action::onCancel()
	{
		//Open for implementation
	}
	
	void Action::onFinish()
	{
		//Open for implementation
	}
	
	void Action::onPerformerAnimationFinish(const String&name, Animation*animation)
	{
		//Open for implementation
	}
	
	bool Action::canPerformerSetFaceDirection(const FaceDirection&side)
	{
		return true;
	}
}
