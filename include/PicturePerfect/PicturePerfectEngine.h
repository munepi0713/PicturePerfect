#ifndef PICTURE_PERFECT_ENGINE__H__
#define PICTURE_PERFECT_ENGINE__H__

#include <stdint.h>
#include <string>
#include <memory>

#include <opencv2/opencv.hpp>

#include <Common/Synchronize.h>
#include <Common/InlineSprintf.h>
#include <Common/Parse.h>
#include <Common/InfoContainer.h>
#include <Common/Statistics.h>

#include <PicturePerfectEngine/Exception.h>
#include <PicturePerfectEngine/Executable.h>
#include <PicturePerfectEngine/Storage.h>
#include <PicturePerfectEngine/Archive.h>

namespace PicturePerfect
{

class PicturePerfectEngine;
typedef std::shared_ptr<PicturePerfectEngine> PicturePerfectEnginePtr;

/**
 *
 */
class PicturePerfectEngine : public InfoContainer
{
public :
	virtual ~PicturePerfectEngine();

	// Instance
    void destroy();

	// Configuration
//	virtual void     setImageSize(const cv::Size& size) = 0;
//	virtual cv::Size getImageSize() const = 0;
	static void      setBaseDirectory(const std::wstring& dir);
	static const std::wstring& getBaseDirectory();
	static std::wstring resolvePath(const std::wstring& path);
	virtual void     configure(std::istream& ins);

	// Execution
	virtual ExecutablePtr compile(std::istream& ins) = 0;
	virtual void execute(const ExecutablePtr executable, StoragePtr storage) = 0;
	virtual void rehearse(const cv::Size& imageSize) = 0;

	// Utility
	virtual uint16_t           getOpCode(const std::string& opname) const = 0;
	virtual uint16_t           getMaxOpCode() const = 0;
	virtual const std::string& getOpName(uint16_t opcode) const = 0;
	virtual uint16_t           getNumOperands(uint16_t opcode) const = 0;
	virtual const Statistics&  getStatistics(uint16_t opcode) const = 0;

	template <typename T>
	void forEachOps(ExecutablePtr executble, T& func) {
		for (auto it = executble->begin(); it != _program.end(); it++) {
			func(*it);
			it += _engine->getNumOperands(*it);
		}
	}

	// Factory
    static PicturePerfectEnginePtr createInstance(const std::string& type = "");

protected :
	PicturePerfectEngine();
};

}//end of namespace PicturePerfect


#endif//PICTURE_PERFECT_ENGINE__H__
