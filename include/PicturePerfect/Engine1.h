#ifndef PICTURE_PERFECT_OPEN_CV__H__
#define PICTURE_PERFECT_OPEN_CV__H__

#include <stdint.h>

#include <cassert>
#include <string>

#include <opencv2/opencv.hpp>
#include <opencv2/ocl/ocl.hpp>

#include <PicturePerfectEngine/PicturePerfectEngine.h>

namespace Sakura
{

/**
 *
 */
class Engine : public PicturePerfect::PicturePerfectEngine
{
public :
 	Engine(bool enableOpenCL = true);
	virtual ~Engine();

	// Configuration
//	virtual void     setImageSize(const cv::Size& size);
//	virtual cv::Size getImageSize() const;

	// Execution
	virtual PicturePerfect::ExecutablePtr compile(std::istream& ins);
	virtual void execute(const PicturePerfect::ExecutablePtr executable, PicturePerfect::StoragePtr userStorage);
	virtual void rehearse(const cv::Size& imageSize);

	// Utility
	virtual uint16_t           getOpCode(const std::string& opname) const;
	virtual uint16_t           getMaxOpCode() const;
	virtual const std::string& getOpName(uint16_t opcode) const;
	virtual uint16_t           getNumOperands(uint16_t opcode) const;
	virtual const Statistics&  getStatistics(uint16_t opcode) const { return _statistics[opcode]; }

protected :
	static  void  initialize(const std::string& filter = "*");
	static  void  finalize();

private :
	PicturePerfect::ArchivePtr  _registers;
	std::vector<Statistics>     _statistics;
};

typedef std::vector<PicturePerfect::DataSlot*> RegisterMap;

struct ExecutionUnit
{
	virtual const char* getName() const = 0;
	virtual PicturePerfect::ProgramIterator operator()(uint32_t index, PicturePerfect::ProgramIterator program, RegisterMap& regs) = 0;
};

struct NI : public ExecutionUnit
{
	virtual const char* getName() const { return "NI"; }
	virtual PicturePerfect::ProgramIterator operator()(uint32_t, PicturePerfect::ProgramIterator program, RegisterMap&) {
		PICTUREPERFECT_THROW(NotImplementedException, "NI is not implemented.");
	}
};

struct MU : public ExecutionUnit
{
	virtual const char* getName() const { return "MU"; }
	virtual PicturePerfect::ProgramIterator operator()(uint32_t index, PicturePerfect::ProgramIterator program, RegisterMap& regs);
};

struct VF : public ExecutionUnit
{
	virtual const char* getName() const { return "VF"; }
	virtual PicturePerfect::ProgramIterator operator()(uint32_t index, PicturePerfect::ProgramIterator program, RegisterMap& regs);
};

struct IF : public ExecutionUnit
{
	virtual const char* getName() const { return "IF"; }
	virtual PicturePerfect::ProgramIterator operator()(uint32_t index, PicturePerfect::ProgramIterator program, RegisterMap& regs);
};

struct AF : public ExecutionUnit
{
	virtual const char* getName() const { return "AF"; }
	virtual PicturePerfect::ProgramIterator operator()(uint32_t index, PicturePerfect::ProgramIterator program, RegisterMap& regs);
};

struct IFg : public ExecutionUnit
{
	virtual const char* getName() const { return "IFg"; }
	virtual PicturePerfect::ProgramIterator operator()(uint32_t index, PicturePerfect::ProgramIterator program, RegisterMap& regs);
};

}//end of namespace Sakura

#endif//PICTURE_PERFECT_OPEN_CV__H__
