
#pragma once

#include "Action.h"
#include "../../../Utilities/FaceDirection.h"

namespace BrawlerLibrary
{
	class ActionPerformer : public fgl::SpriteActor
	{
		friend class Action;
	public:
		ActionPerformer();
		explicit ActionPerformer(const fgl::Vector2d&position);
		virtual ~ActionPerformer();
		
		void addAction(const fgl::String&name, Action*action, bool destruct=true);
		void removeAction(const fgl::String&name);
		bool hasAction(const fgl::String&name) const;
		void performAction(const fgl::String&name);
		void performAction(Action*action);
		void cancelAction();
		bool isPerformingAction() const;
		
		void setFaceDirection(const FaceDirection&side);
		const FaceDirection& getFaceDirection() const;
		
	protected:
		virtual void onAnimationFinish(const fgl::SpriteActorAnimationEvent& evt) override;
		virtual void onActionFinish(const fgl::String&name, Action*action);
		
	private:
		typedef struct
		{
			fgl::String name;
			Action* action;
			bool destruct;
		} ActionInfo;
		
		FaceDirection side;
		fgl::ArrayList<ActionInfo> actions;
		
		fgl::String action_name;
		Action* action_current;
	};
}
