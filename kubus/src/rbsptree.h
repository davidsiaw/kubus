#ifndef RBSPTREE_H
#define RBSPTREE_H

#include <stdio.h>

/**
* Used to describe a rectangle
*/
struct FRectangle {
	float x1;
	float y1;
	float x2;
	float y2;
	float Width() { return x2-x1; }
	float Height() { return y2-y1; }
};

// A rectangular BSP tree from Nagato
template<typename TData, typename TContext>
class RBSPNode
{
	enum {TOP, BOTTOM};
	enum {LEFT, RIGHT};

	RBSPNode* child[2];
	FRectangle rect;
	bool hasData;
	TData data;	// If this is not NULL, this is a leaf
	float spacing;

public:

	typedef void(*ManageResult)(FRectangle rect, TData data, TContext context);

	void RetrieveRectangles (ManageResult manageresultcb, TContext context)
	{
		if (child[LEFT])
		{
			child[LEFT]->RetrieveRectangles(manageresultcb, context);
			child[RIGHT]->RetrieveRectangles(manageresultcb, context);
		}

		if (hasData)
		{
			manageresultcb(rect, data, context);
		}
	}

	int Count()
	{
		// Duplicated code (see RetrieveRectangles) better way to do this?
		int res = 0;
		if (child[LEFT])
		{
			res += child[LEFT]->Count();
			res += child[RIGHT]->Count();
		}

		if (hasData)
		{
			res += 1;
		}
	}

	RBSPNode(FRectangle rect, float spacing=0.0)
	{
		child[LEFT] = child[RIGHT] = NULL;
		this->rect = rect;
		this->hasData = false;
		this->spacing = spacing;
	}

	~RBSPNode()
	{
		if (child[LEFT])
		{
			delete child[LEFT];
			delete child[RIGHT];
		}
	}

	bool Insert(FRectangle rect, TData data)
	{
		// If I already have an image, I reject
		if (this->hasData)
		{
			return false;
		}

		// If I don't have an image, and I have children, then try inserting into both children
		if (child[LEFT] != NULL)
		{
			if ( !child[LEFT]->Insert(rect,data) )
			{
				if ( !child[RIGHT]->Insert(rect,data) )
				{
					return false;
				}
			}
			return true;
		}

		// If I don't have an image, and I don't have children, I should see if I can take this image

		if (this->rect.Width() < rect.Width() || this->rect.Height() < rect.Height() )
		{
			return false;
		}

		// If it fits perfectly, I take in the image
		if (this->rect.Width() == rect.Width() && this->rect.Height() == rect.Height() )
		{
			this->data = data;
			this->hasData = true;
			return true;
		}

		// If it fits along my length or width, then i split to make a child that has just the right size and insert
		if (this->rect.Width() == rect.Width() )
		{
			SplitHeight(rect.Height());
			return this->child[LEFT]->Insert(rect,data);
		}

		// If it fits along my length or width, then i split to make a child that has just the right size
		if (this->rect.Height() == rect.Height() )
		{
			SplitWidth(rect.Width());
			return this->child[TOP]->Insert(rect,data);
		}

		// If I am just too big, then I split along my length or width.

		if (this->rect.Width() > rect.Width() && this->rect.Height() > rect.Height() )
		{
			float dw = this->rect.Width() - rect.Width();
			float dh = this->rect.Height() - rect.Height();

			if (dh > dw)
			{
				SplitHeight(rect.Height());
				return this->child[TOP]->Insert(rect,data);
			}
			else
			{
				SplitWidth(rect.Width());
				return this->child[LEFT]->Insert(rect,data);
			}

		}

		// If I am just too small, then I reject.
		return false;

	}

private:

	// Split into two rectangles to one on the left and one on the right
	void SplitWidth(float howmuch)
	{
		FRectangle new_rect;
		new_rect.x1 = this->rect.x1;
		new_rect.x2 = this->rect.x1 + howmuch;
		new_rect.y1 = this->rect.y1;
		new_rect.y2 = this->rect.y2;
		this->child[LEFT] = new RBSPNode(new_rect,spacing);

		new_rect.x1 = this->rect.x1 + howmuch + spacing;
		new_rect.x2 = this->rect.x2;
		new_rect.y1 = this->rect.y1;
		new_rect.y2 = this->rect.y2;
		this->child[RIGHT] = new RBSPNode(new_rect,spacing);
	}

	// Split into two rectangles to one on the top and one on the bottom
	void SplitHeight(float howmuch)
	{
		FRectangle new_rect;
		new_rect.x1 = this->rect.x1;
		new_rect.x2 = this->rect.x2;
		new_rect.y1 = this->rect.y1;
		new_rect.y2 = this->rect.y1 + howmuch;
		this->child[TOP] = new RBSPNode(new_rect,spacing);

		new_rect.x1 = this->rect.x1;
		new_rect.x2 = this->rect.x2;
		new_rect.y1 = this->rect.y1 + howmuch + spacing;
		new_rect.y2 = this->rect.y2;
		this->child[BOTTOM] = new RBSPNode(new_rect,spacing);
	}

};

#endif // RBSPTREE_H