#ifndef PICTUREPERFECTENGINE__COMPILER__H__
#define PICTUREPERFECTENGINE__COMPILER__H__


#include <string>
#include <iostream>

#include <PicturePerfectEngine/Program.h>
#include <PicturePerfectEngine/Storage.h>


namespace PicturePerfect
{

class Compiler
{
public :
	virtual ~Compiler();
	virtual void  execute(std::istream& ins, Program& program, Storage& storage) = 0;
	virtual void  destroy();

	static Compiler*  createInstance(const std::string& type = "");
};

}//end of namespace PicturePerfect

#endif//PICTUREPERFECTENGINE__COMPILER__H__
