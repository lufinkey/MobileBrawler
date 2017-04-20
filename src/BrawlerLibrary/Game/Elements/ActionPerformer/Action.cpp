
#include "Action.h"
#include "ActionPerformer.h"

using namespace fgl;

namespace BrawlerLibrary
{
	Action::Action()
		: performer(nullptr), finishing(false), cancelling(false), reran(false)
	{
		//
	}
	
	Action::~Action()
	{
		//
	}
	
	void Action::perform(ActionPerformer*actionPerformer)
	{
		if(actionPerformer == nullptr)
		{
			throw IllegalArgumentException("performer", "null");
		}
		else if(cancelling)
		{
			throw IllegalStateException("action is cancelling");
		}
		else if(performer != nullptr && (!finishing || reran))
		{
			throw IllegalStateException("action is already being performed");
		}
		
		if(finishing)
		{
			reran = true;
		}
		performer = actionPerformer;
		if(!reran)
		{
			finishing = false;
			cancelling = false;
			onPerform();
		}
	}
	
	void Action::cancel()
	{
		if(cancelling)
		{
			throw IllegalStateException("action is already cancelling");
		}
		else if(finishing)
		{
			throw IllegalStateException("action is finishing");
		}
		else if(performer==nullptr)
		{
			throw IllegalStateException("action is not being performed");
		}
		cancelling = true;
		ActionPerformer*actionPerformer = performer;
		onCancel();
		performer = nullptr;
		actionPerformer->action_current = nullptr;
		actionPerformer->action_name = "";
		cancelling = false;
	}
	
	void Action::finish()
	{
		if(finishing)
		{
			throw IllegalStateException("action is already finishing");
		}
		else if(cancelling)
		{
			throw IllegalStateException("action is cancelling");
		}
		else if(performer == nullptr)
		{
			throw IllegalStateException("action is not being performed");
		}
		finishing = true;
		ActionPerformer*actionPerformer = performer;
		String action_name = actionPerformer->action_name;
		onFinish();
		actionPerformer->onActionFinish(action_name, this);
		finishing = false;
		if(reran)
		{
			onPerform();
		}
		else
		{
			actionPerformer->action_current = nullptr;
			actionPerformer->action_name = "";
		}
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
		
	void Action::onActionPush()
	{
		//Open for implementation
	}
	
	void Action::onActionPop()
	{
		//Open for implementation
	}
	
	void Action::onPerformerAnimationFinish(const SpriteActorAnimationEvent& evt)
	{
		//Open for implementation
	}
}
