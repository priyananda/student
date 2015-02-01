// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 18 sep 2007
// random quote: [Reservior Dogs] Mr. Pink: I don't tip because society says I have to.

#pragma once

//forward declaration
class TargaImage;
class FilterFactory;

//baseclass for all 2D filter kernels
class FilterKernel2D
{
public:
	//constructs a kernel with width k
	FilterKernel2D(int w):k(w){}
	//destructor. override this
	virtual ~FilterKernel2D(){}
	//convolution function.override this
	virtual void convolve(TargaImage * image) = 0;
	//specialized convolution for upsampling.
	virtual void convolve(TargaImage * source,TargaImage * dest,int xfactor,int yfactor) = 0;
protected:
	int k;
};


//represents a separable 2D Filter kernel
class SeparableKernel : public FilterKernel2D
{
public:
	//constructor
	SeparableKernel(int k);
	//destructor
	~SeparableKernel();
	//overridden
	virtual void convolve(TargaImage * image);
	//overridden
	virtual void convolve(TargaImage * source,TargaImage * dest,int xfactor,int yfactor);
private:
	//colvolve a separable kernel in H direction
	void convolveRow(unsigned char * pixel,int w,int h,unsigned char * buffer);
	//colvolve a separable kernel in H direction
	void convolveCol(unsigned char * pixel,int w,int h,unsigned char * buffer);

	//just one row is required
	int * values;

	//make factory a friend
	friend class FilterFactory;
};

//represents a non-separable 2D Filter kernel
class NonSeparableKernel : public FilterKernel2D
{
public:
	//constructor
	NonSeparableKernel(int k);
	//destructor
	~NonSeparableKernel();
	//overridden
	virtual void convolve(TargaImage * image);
private:
	//a matrix(2d array) is required
	int ** values;
	//make factory a friend
	friend class FilterFactory;
};

//factory functions to create instances
class FilterFactory
{
public:
	//factory to create bsplines
	static FilterKernel2D * createBSpline(int k);
	//factory to create boxes
	static FilterKernel2D * createBox(int k);
	//factory to create gaussian kernel
	static FilterKernel2D * createGaussian(int k,float c);
	//factory to create a lanczos sinc kernel
	static FilterKernel2D * createSinc(int k);
	//factory to create a bicubic sinc kernel
	static FilterKernel2D * createBicubic(int k);
};