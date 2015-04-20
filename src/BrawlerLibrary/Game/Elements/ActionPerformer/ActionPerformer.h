
#pragma once

#include "Action.h"
#include "../../../Utilities/FaceDirection.h"

namespace BrawlerLibrary
{
	class ActionPerformer : public GameLibrary::SpriteActor
	{
		friend class Action;
	public:
		ActionPerformer();
		ActionPerformer(const GameLibrary::Vector2d&position);
		virtual ~ActionPerformer();
		
		void addAction(const GameLibrary::String&name, Action*action, bool destruct=true);
		void removeAction(const GameLibrary::String&name);
		bool hasAction(const GameLibrary::String&name) const;
		void performAction(const GameLibrary::String&name);
		void performAction(Action*action);
		void cancelAction();
		bool isPerformingAction() const;
		
		void setFaceDirection(const FaceDirection&side);
		const FaceDirection& getFaceDirection() const;
		
	protected:
		virtual void onAnimationFinish(const GameLibrary::String&name, GameLibrary::Animation*animation) override;
		virtual void onActionFinish(const GameLibrary::String&name, Action*action);
		
	private:
		typedef struct
		{
			GameLibrary::String name;
			Action* action;
			bool destruct;
		} ActionInfo;
		
		FaceDirection side;
		GameLibrary::ArrayList<ActionInfo> actions;
		
		GameLibrary::String action_name;
		Action* action_current;
	};
}
