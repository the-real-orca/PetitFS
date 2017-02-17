#ifndef PetitFS_h
#define PetitFS_h
#include "diskio.h"
#include "pff.h"

#include "Arduino.h"

// Petit FS wrapper
class FileClass {
public:
	inline uint16_t read(uint8_t buf[], uint16_t size)
	{
		uint16_t len;
		pf_read(buf, size, &len);
		return len;
	}
	inline uint16_t read(char buf[], uint16_t size)
	{
		return FileClass::read((uint8_t*)(buf), size);
	}
	
		
	inline void close() {}
	
	FRESULT _error;
};
typedef FileClass& File;
	
class SDClass {
public:
	static inline bool begin() { return (pf_mount(&_fs) == FR_OK); }
	static inline File open(const char filename[]) { SDClass::_file._error = pf_open(filename); return SDClass::_file; }

	static FileClass _file;
	static FATFS _fs;
};
extern SDClass SD;


#endif  // PetitFS_h