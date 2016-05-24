#ifndef PICTURE_PERFECT_ENGINE__STORAGE__H__
#define PICTURE_PERFECT_ENGINE__STORAGE__H__

#include <memory>

#include <opencv2/opencv.hpp>

#include <Common/IntTypes.h>

namespace PicturePerfect
{

/**
 * Storage Address.
 *  Storage has 32bit address space.
 *  From MSbit,
 *   0:1 is also used for Usage code: 00:Neutral, 01:Source, 10:Result, 11:Cache.
 *   2:3  Memory type. 00:CPU, 10:GPU,
 *   4:7  Data type. 0000:V1D, 0100:I1D, 0101:I3D, 0110:I1B, 0111:I3B, 1001:S, 1010:A1D, 1111:L
 *   8:31 Offset.
 */
#define getStorageMemoryType(addr)  ((addr) & 0xC0000000u)
#define getStorageDataType(addr)    ((addr) & 0x3C000000u)
#define getStorageType(addr)        ((addr) & 0xFC000000u)
#define getStorageUsage(addr)       ((addr) & 0x03000000u)

const uint32_t  MEM_CPU   = (0x00000000u);
const uint32_t  MEM_GPU   = (0x80000000u);

const uint32_t  DATA_V1D  = (0x00000000u);
const uint32_t  DATA_I1D  = (0x10000000u);
const uint32_t  DATA_I3D  = (0x14000000u);
const uint32_t  DATA_I1B  = (0x18000000u);
const uint32_t  DATA_I3B  = (0x1C000000u);
const uint32_t  DATA_S    = (0x24000000u);
const uint32_t  DATA_A1D  = (0x28000000u);
const uint32_t  DATA_L    = (0x3C000000u);

const uint32_t  USAGE_REG = (0x00000000u);
const uint32_t  USAGE_SRC = (0x01000000u);
const uint32_t  USAGE_RES = (0x02000000u);
const uint32_t  USAGE_CAS = (0x03000000u);

const uint32_t  TYPE_V1D    = (MEM_CPU | DATA_V1D);
const uint32_t  TYPE_I1D    = (MEM_CPU | DATA_I1D);
const uint32_t  TYPE_I3D    = (MEM_CPU | DATA_I3D);
const uint32_t  TYPE_I1B    = (MEM_CPU | DATA_I1B);
const uint32_t  TYPE_I3B    = (MEM_CPU | DATA_I3B);
const uint32_t  TYPE_S      = (MEM_CPU | DATA_S  );
const uint32_t  TYPE_A1D    = (MEM_CPU | DATA_A1D);
const uint32_t  TYPE_L      = (MEM_CPU | DATA_L  );
const uint32_t  TYPE_V1Dg   = (MEM_GPU | DATA_V1D);
const uint32_t  TYPE_I1Dg   = (MEM_GPU | DATA_I1D);
const uint32_t  TYPE_I3Dg   = (MEM_GPU | DATA_I3D);
const uint32_t  TYPE_I1Bg   = (MEM_GPU | DATA_I1B);
const uint32_t  TYPE_I3Bg   = (MEM_GPU | DATA_I3B);

const uint32_t  ADDR_V1D    = (MEM_CPU | DATA_V1D | USAGE_REG);
const uint32_t  ADDR_I1D    = (MEM_CPU | DATA_I1D | USAGE_REG);
const uint32_t  ADDR_I3D    = (MEM_CPU | DATA_I3D | USAGE_REG);
const uint32_t  ADDR_I1B    = (MEM_CPU | DATA_I1B | USAGE_REG);
const uint32_t  ADDR_I3B    = (MEM_CPU | DATA_I3B | USAGE_REG);
const uint32_t  ADDR_S      = (MEM_CPU | DATA_S   | USAGE_REG);
const uint32_t  ADDR_A1D    = (MEM_CPU | DATA_A1D | USAGE_REG);
const uint32_t  ADDR_L      = (MEM_CPU | DATA_L   | USAGE_REG);
const uint32_t  ADDR_V1Dg   = (MEM_GPU | DATA_V1D | USAGE_REG);
const uint32_t  ADDR_I1Dg   = (MEM_GPU | DATA_I1D | USAGE_REG);
const uint32_t  ADDR_I3Dg   = (MEM_GPU | DATA_I3D | USAGE_REG);
const uint32_t  ADDR_I1Bg   = (MEM_GPU | DATA_I1B | USAGE_REG);
const uint32_t  ADDR_I3Bg   = (MEM_GPU | DATA_I3B | USAGE_REG);

const uint32_t  ADDR_SV1D   = (MEM_CPU | DATA_V1D | USAGE_SRC);
const uint32_t  ADDR_SI1D   = (MEM_CPU | DATA_I1D | USAGE_SRC);
const uint32_t  ADDR_SI3D   = (MEM_CPU | DATA_I3D | USAGE_SRC);
const uint32_t  ADDR_SI1B   = (MEM_CPU | DATA_I1B | USAGE_SRC);
const uint32_t  ADDR_SI3B   = (MEM_CPU | DATA_I3B | USAGE_SRC);
const uint32_t  ADDR_SS     = (MEM_CPU | DATA_S   | USAGE_SRC);
const uint32_t  ADDR_SA1D   = (MEM_CPU | DATA_A1D | USAGE_SRC);
const uint32_t  ADDR_SL     = (MEM_CPU | DATA_L   | USAGE_SRC);
const uint32_t  ADDR_SV1Dg  = (MEM_GPU | DATA_V1D | USAGE_SRC);
const uint32_t  ADDR_SI1Dg  = (MEM_GPU | DATA_I1D | USAGE_SRC);
const uint32_t  ADDR_SI3Dg  = (MEM_GPU | DATA_I3D | USAGE_SRC);
const uint32_t  ADDR_SI1Bg  = (MEM_GPU | DATA_I1B | USAGE_SRC);
const uint32_t  ADDR_SI3Bg  = (MEM_GPU | DATA_I3B | USAGE_SRC);

const uint32_t  ADDR_RV1D   = (MEM_CPU | DATA_V1D | USAGE_RES);
const uint32_t  ADDR_RI1D   = (MEM_CPU | DATA_I1D | USAGE_RES);
const uint32_t  ADDR_RI3D   = (MEM_CPU | DATA_I3D | USAGE_RES);
const uint32_t  ADDR_RI1B   = (MEM_CPU | DATA_I1B | USAGE_RES);
const uint32_t  ADDR_RI3B   = (MEM_CPU | DATA_I3B | USAGE_RES);
const uint32_t  ADDR_RS     = (MEM_CPU | DATA_S   | USAGE_RES);
const uint32_t  ADDR_RA1D   = (MEM_CPU | DATA_A1D | USAGE_RES);
const uint32_t  ADDR_RL     = (MEM_CPU | DATA_L   | USAGE_RES);
const uint32_t  ADDR_RV1Dg  = (MEM_GPU | DATA_V1D | USAGE_RES);
const uint32_t  ADDR_RI1Dg  = (MEM_GPU | DATA_I1D | USAGE_RES);
const uint32_t  ADDR_RI3Dg  = (MEM_GPU | DATA_I3D | USAGE_RES);
const uint32_t  ADDR_RI1Bg  = (MEM_GPU | DATA_I1B | USAGE_RES);
const uint32_t  ADDR_RI3Bg  = (MEM_GPU | DATA_I3B | USAGE_RES);

const uint32_t  ADDR_CV1D   = (MEM_CPU | DATA_V1D | USAGE_CAS);
const uint32_t  ADDR_CI1D   = (MEM_CPU | DATA_I1D | USAGE_CAS);
const uint32_t  ADDR_CI3D   = (MEM_CPU | DATA_I3D | USAGE_CAS);
const uint32_t  ADDR_CI1B   = (MEM_CPU | DATA_I1B | USAGE_CAS);
const uint32_t  ADDR_CI3B   = (MEM_CPU | DATA_I3B | USAGE_CAS);
const uint32_t  ADDR_CS     = (MEM_CPU | DATA_S   | USAGE_CAS);
const uint32_t  ADDR_CA1D   = (MEM_CPU | DATA_A1D | USAGE_CAS);
const uint32_t  ADDR_CL     = (MEM_CPU | DATA_L   | USAGE_CAS);
const uint32_t  ADDR_CV1Dg  = (MEM_GPU | DATA_V1D | USAGE_CAS);
const uint32_t  ADDR_CI1Dg  = (MEM_GPU | DATA_I1D | USAGE_CAS);
const uint32_t  ADDR_CI3Dg  = (MEM_GPU | DATA_I3D | USAGE_CAS);
const uint32_t  ADDR_CI1Bg  = (MEM_GPU | DATA_I1B | USAGE_CAS);
const uint32_t  ADDR_CI3Bg  = (MEM_GPU | DATA_I3B | USAGE_CAS);

const uint32_t  ADDR_MASK_STORAGE = 0xFFFFFFFFu;
const uint32_t  ADDR_MASK_ARCHIVE = 0x3FFFFFFFu;
const uint32_t  ADDR_MASK_IVPAIR  = 0x03FFFFFFu;

const uint32_t  ADDR_BLOCK_SIZE   = 0x01000000u;

struct DataSlot {
	virtual ~DataSlot() {}
	template <typename T>
	T& operator()() { return *static_cast<T*>(_at()); }
	template <typename T>
	const T& operator()() const { return *static_cast<T*>(_at()); }
	template <typename T>
	T& at() { return *static_cast<T*>(_at()); }
	template <typename T>
	const T& at() const { return *static_cast<const T*>(const_cast<DataSlot*>(this)->_at()); }
	void* data() { return _at(); }
protected :
	virtual void* _at() = 0;
};

// 
class PicturePerfectEngine;

/**
 *  Smart Pointer.
 */
class Storage;
typedef std::shared_ptr<Storage> StoragePtr;

/**
 *
 */
class  Storage
{
public :
    Storage();
	virtual ~Storage() = 0;

	virtual bool       exists(uint32_t address) const = 0;
	virtual void       clear() = 0;

	virtual cv::Size   getImageSize() const = 0;

	virtual DataSlot*  getSlot(uint32_t address) = 0;

	/**
	 *  Get item at the specified address.
	 *  Create item if the item does not exist.
	 */
	template <typename T>
	T&                 at(uint32_t addr) {
		return getSlot(addr)->at<T>();
	}
	/**
	*  Get item at the specified address.
	*  Throw an exception if the item does not exist.
	*/
	template <typename T>
	const T&           at(uint32_t addr) const {
		if ( !exists(addr) ) {
			PICTUREPERFECT_THROW(InvalidStorageAccessException, (boost::format(" addr=0x%08x [%s]") % addr % __FUNCTION__).str());
		}
		return const_cast<Storage*>(this)->getSlot(addr)->at<T>();
	}

	// Utility
	/** Check if the data at the address is valid. */
	virtual void  	   validate(uint32_t address) const = 0;
	virtual uint32_t   getNumSlots() const = 0;

	// Static Utility
	static uint32_t    decodeAddress(const std::string& exp);
	static const char* toDataTypeName(uint32_t dataType);

	static StoragePtr  createInstance(const cv::Size& imageSize);
};

/**
 *
 */
class  StorageMapper : public Storage
{
public :
	struct Block {
		StoragePtr storage;
		uint32_t   logical;
		uint32_t   real;
		uint32_t   size;

		Block() {}
		Block(uint32_t l, StoragePtr st, uint32_t r, uint32_t s) : storage(st), logical(l), real(r), size(s) {}
		Block(const Block& x) : storage(x.storage), logical(x.logical), real(x.real), size(x.size) {}

		void set(uint32_t l, StoragePtr st, uint32_t r, uint32_t s) {
			storage = st;
			logical = l;
			real = r;
			size = s;
		}
	};
	typedef std::vector<Block> Blocks;

	virtual ~StorageMapper() {}

	virtual bool       exists(uint32_t address) const;
	virtual void       clear();
	virtual DataSlot*  getSlot(uint32_t address);
	virtual void  	   validate(uint32_t address) const;
	virtual cv::Size   getImageSize() const;
	virtual uint32_t   getNumSlots() const;

	static StoragePtr  createInstance(const std::vector<Block>& blocks);

protected:
	Blocks::iterator       findBlock(uint32_t address);
	Blocks::const_iterator findBlock(uint32_t address) const;

private :
    StorageMapper(const std::vector<Block>& blocks);

	Blocks      _blocks;
};

}//end of namespace PicturePerfect

#endif//PICTURE_PERFECT_ENGINE__STORAGE__H__
