#ifndef MATRIX_H
#define MATRIX_H

#include <functional>

template<typename T, unsigned int A, unsigned int B>
class matrix
{
	int size;
	boost::shared_array<T> data;

	T& get(int x, int y, T& invalid)
	{
		if (x < 0 || x >= A || y < 0 || y >= B)
		{
			return invalid;
		}
		return data[x + A * y];
	}

public:
	matrix() : size(A*B), data(new T[size])
	{
	}

	// shift all elements and fill the vacuum with emptyFill
	void shift(int dx, int dy, std::function<T()> emptyFill)
	{
		int xstart=-1,xend=A,xinc=1,
			ystart=-1,yend=B,yinc=1;
		if (dx < 0) { xstart=A;xend=-1;xinc=-1; }
		if (dy < 0) { ystart=B;yend=-1;yinc=-1; }

		for (int x=xstart;x!=xend;x+=xinc)
		for (int y=ystart;y!=yend;y+=yinc)
		{
			std::swap(get(x,y,emptyFill()),get(x-dx,y-dy,emptyFill()));
		}
	}

	// Iterate through all elements
	void foreach(std::function<void(T)> action)
	{
		for(int i=0;i<size;i++)
		{
			action(data[i]);
		}
	}

	T& operator()(unsigned int x, unsigned int y)
	{
		return data[x + A * y];
	}

	int getcolumns() const
	{
		return A;
	}

	int getrows() const
	{
		return B;
	}
};

#endif // MATRIX_H
