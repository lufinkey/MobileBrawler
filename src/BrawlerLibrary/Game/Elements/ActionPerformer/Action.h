
#pragma once

#include <GameLibrary/GameLibrary.h>

namespace BrawlerLibrary
{
	class ActionPerformer;
	
	class Action
	{
		friend class ActionPerformer;
	public:
		Action();
		virtual ~Action();
		
		ActionPerformer*getActionPerformer() const;
		
	protected:
		void finish();
		
		//called when this action begins performing
		virtual void onPerform();
		//called when this action is cancelled
		virtual void onCancel();
		//called when this action is internally told to finish via the finish() function
		virtual void onFinish();
		//called when an action gets pushed on top of this action
		virtual void onActionPush();
		//called when the action on top of this action gets popped
		virtual void onActionPop();
		
		virtual void onPerformerAnimationFinish(const GameLibrary::SpriteActorAnimationEvent& evt);
		
	private:
		void perform(ActionPerformer*performer);
		void cancel();
		
		ActionPerformer*performer;
		bool finishing;
		bool cancelling;
		bool reran;
	};
}
