
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

		virtual void onPerform();
		virtual void onCancel();
		virtual void onFinish();
		virtual void onPerformerAnimationFinish(const GameLibrary::String&name, GameLibrary::Animation*animation);
		
	private:
		void perform(ActionPerformer*performer);
		void cancel();
		
		ActionPerformer*performer;
		bool finishing;
		bool reran;
	};
}
