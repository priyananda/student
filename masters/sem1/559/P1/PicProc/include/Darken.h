// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 16 sep 2007
// random quote: [Apocalypse Now] Kilgore: I love the smell of napalm in the morning.

#include "Command.h"

class TargaImage;

//this command makes the image more darker
//format: darken <variable> <factor>
class Darken : public Command
{
public:
	//overriding these functions
	virtual bool extract(const CommandLine &);
	virtual void execute();

	float darkenFactor() const { return factor; }
private:
	TargaImage * image;
	float factor;
};