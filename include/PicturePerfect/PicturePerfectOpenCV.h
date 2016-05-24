#ifndef PICTURE_PERFECT_OPEN_CV__H__
#define PICTURE_PERFECT_OPEN_CV__H__

#include <stdint.h>

#include <cassert>
#include <string>

#include <opencv/highgui.h>

#include <Common/Parse.h>
#include <PicturePerfectEngine/PicturePerfectEngine.h>

class PicturePerfectOpenCV;

typedef PicturePerfect::Packet       Packet;
typedef PicturePerfect::PacketStore  PacketStore;


/**
 *
 */
class OperatorMap : public std::map<uint32_t, Operator*>
{
public :
	void  clear();
	~OperatorMap();
};

/**
 *
 */
class PicturePerfectOpenCV : public PicturePerfect::PicturePerfectEngine
{
public :
    enum DepthType
    {
        DEPTH_8U,
        DEPTH_16S,
    };

 	PicturePerfectOpenCV();
	virtual ~PicturePerfectOpenCV();
    virtual void   execute(std::istream& ins, PacketStore& regs);

	virtual uint32_t  getOpecodeByName(const std::string& name);

    void      initPacket(Packet& packet, IplImage* image = 0, double value = 0);
    IplImage* createImage(unsigned int channels = 1, DepthType depth = DEPTH_8U);
    IplImage* loadImage(const std::string& name, int iscolor);

    int        getWidth() const { return _width; }
    int        getHeight() const { return _height; }

    void       setWidth(int w) { _width = w; }
    void       setHeight(int h) { _height = h; }

    void       writeStatistics(std::ostream& outs);

	static  void  initialize(const std::string& filter = "*");
	static  void  finalize();

protected :
    typedef struct {
        uint64_t  time;
        uint64_t  calls;
    } Stat;
	typedef std::map<std::string, std::string> ConstantMap;
	typedef std::map<std::string, IplImage*> ImageMap;
    typedef std::map<std::string, Stat> StatMap;
    int          _width;
    int          _height;
	ConstantMap  _constants;
    ImageMap     _imageCache;
    StatMap      _statistics;

private :
    typedef std::map<std::string, uint32_t> OpecodeMap;
	static OpecodeMap*  _opecodes;
    static OperatorMap* _operators;
};

#endif//PICTURE_PERFECT_OPEN_CV__H__
