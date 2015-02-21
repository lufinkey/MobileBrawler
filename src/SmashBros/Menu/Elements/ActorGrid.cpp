
#include "ActorGrid.h"

namespace SmashBros
{
	namespace Menu
	{
		ActorGrid::ActorGrid(const Vector2d&pos, unsigned int cols, const Vector2d&space)
		{
			position = pos;
			columns = cols;
			spacing = space;
		}
		
		ActorGrid::~ActorGrid()
		{
			//
		}
		
		void ActorGrid::setActorPosition(unsigned int index, Actor*actor)
		{
			if(actor != nullptr)
			{
				unsigned int col = index%columns;
				unsigned int row = index/columns;
				actor->x = position.x + (((double)col) * spacing.x);
				actor->y = position.y + (((double)row) * spacing.y);
			}
		}
		
		void ActorGrid::add(Actor*actor)
		{
			unsigned int index = actors.size();
			setActorPosition(index, actor);
			actors.add(actor);
		}
		
		void ActorGrid::clear()
		{
			actors.clear();
		}
		
		void ActorGrid::setPosition(const Vector2d&pos)
		{
			position = pos;
			for(unsigned int i=0; i<actors.size(); i++)
			{
				setActorPosition(i, actors.get(i));
			}
		}
		
		const Vector2d& ActorGrid::getPosition() const
		{
			return position;
		}
		
		const ArrayList<Actor*>& ActorGrid::getActors() const
		{
			return actors;
		}
		
		unsigned int ActorGrid::getColumns() const
		{
			return columns;
		}
		
		const Vector2d& ActorGrid::getSpacing() const
		{
			return spacing;
		}
	}
}
