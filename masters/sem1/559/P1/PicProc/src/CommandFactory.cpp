// CS559 Project 1 : Picture Processor
// author: priyananda( shenoy@cs.wisc.edu )
// date: 16 sep 2007
// random quote: [The Shawshank Redemption] Red: Hope is a dangerous thing. Hope can drive a man insane.

#include "ReadCommand.h"
#include "Darken.h"
#include "FillCommand.h"
#include "Copy.h"
#include "Blank.h"
#include "Dissolve.h"
#include "Opaque.h"
#include "Desaturate.h"
#include "Blur.h"
#include "Che.h"
#include "Rotate.h"
#include "Resize.h"
#include "Stretch.h"
#include "Composite.h"
#include "Sharpen.h"
#include "FlagWarp.h"
#include "Crop.h"
#include "Chromakey.h"
#include "Matte.h"
#include "Painter.h"
#include "Escher.h"
#include "Drops.h"
#include "Swirl.h"

//complicated macro to save time
//case insensitive
#define RETURN_IF(p,str) if( ::_stricmp((p).command,#str) == 0 ) return & str##Command;

static ReadCommand readCommand;
static WriteCommand writeCommand;
static Darken darkenCommand;
static FillCommand fillCommand;
static Blank blankCommand;
static Copy copyCommand;
static Opaque opaqueCommand;
static Dissolve dissolveCommand;
static Desaturate desaturateCommand;
static EmptyCommand nullCommand;
static Blur blurCommand;
static Che cheCommand;
static Rotate rotateCommand;
static Resize resizeCommand;
static Stretch stretchCommand;
static Composite compositeCommand;
static Sharpen sharpenCommand;
static FlagWarp flagCommand;
static Crop cropCommand;
static Chromakey chromakeyCommand;
static Painter painterCommand;
static Matte matteCommand;
static Escher escherCommand;
static Drops dropsCommand;
static Swirl swirlCommand;
static Painter paintCommand;

//this is a factory method which returns an instance
//of the Command object based on the command verb string.
//DONOT make command handling re-entrant. 
Command * CommandFactory::createCommand(const CommandLine & p)
{
	RETURN_IF(p,read)
	RETURN_IF(p,darken)
	RETURN_IF(p,write)
	RETURN_IF(p,fill)
	RETURN_IF(p,blank)
	RETURN_IF(p,copy)
	RETURN_IF(p,dissolve)
	RETURN_IF(p,opaque)
	RETURN_IF(p,desaturate)
	RETURN_IF(p,null)
	RETURN_IF(p,blur)
	RETURN_IF(p,che)
	RETURN_IF(p,rotate)
	RETURN_IF(p,resize)
	RETURN_IF(p,stretch)
	RETURN_IF(p,composite)
	RETURN_IF(p,sharpen)
	RETURN_IF(p,flag)
	RETURN_IF(p,crop)
	RETURN_IF(p,chromakey)
	RETURN_IF(p,matte)
	RETURN_IF(p,painter)
	RETURN_IF(p,escher)
	RETURN_IF(p,drops)
	RETURN_IF(p,swirl)
	RETURN_IF(p,paint);
	return NULL;
}