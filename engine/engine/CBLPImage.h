#pragma once

#include "IImage.h"

class CMemFile;

class CBLPImage : public IImage
{
private:
	DISALLOW_COPY_AND_ASSIGN(CBLPImage);

public:
	CBLPImage();
	~CBLPImage();

public:
	virtual ECOLOR_FORMAT getColorFormat() const { return Format; }
	virtual const dimension2d& getDimension() const { return Size; }
	virtual uint32_t getNumMipLevels() const { return NumMipMaps; }

	virtual bool isCube() const { return false; }
	virtual uint32_t	 getNumFaces() const { return 1; }

	virtual bool copyMipmapData(uint32_t face, uint32_t level, void* dest, uint32_t pitch, uint32_t width, uint32_t height) const;

public:
	bool loadFile(CMemFile* file);
	bool fromImageData(const uint8_t* src, const dimension2d& size, ECOLOR_FORMAT format, bool mipmap);
	const void* getMipmapData(uint32_t level) const;

	void copy16BitMipMap(const uint8_t* src, uint8_t* tgt,
		uint32_t width, uint32_t height, uint32_t pitchsrc, uint32_t pitchtgt) const;

	uint32_t getMipmapDataSize(uint32_t level) const { return MipmapDataSize[level]; }
	uint32_t getMipmapPitch(uint32_t level) const { return MipmapPitch[level]; }
	uint32_t getAlphaDepth() const { return AlphaDepth; }

private:
	dimension2d		Size;
	ECOLOR_FORMAT	Format;
	uint32_t			NumMipMaps;
	uint32_t			MipmapDataSize[16];
	uint32_t			MipmapPitch[16];
	uint32_t			AlphaDepth;
	uint8_t*		FileData;

public:
#	pragma pack (1)

	//------------------------------------------------------------------------------
	struct SBLPHeader {
		/*0x00*/    uint32_t      magic;           	     // always 'BLP2'
		/*0x04*/    uint32_t  _version;            	     // Version, always 1
		/*0x08*/    uint8_t   _compress;           	     // Compression: 1 for uncompressed, 2 for DXTC
		/*0x09*/    uint8_t   _alphaDepth;         	     // Alpha channel bit depth: 0, 1 or 8
		/*0x0A*/    uint8_t   _alphaCompress;      	     // Something about alpha? (compressed, alpha:0 or 1): 0, (compressed, alpha:8): 1, uncompressed: 2,4 or 8 (mostly 8)
		/*0x0B*/    uint8_t   _mipmap;             	     // when 0 there is only 1 mipmaplevel. compressed: 0, 1 or 2, uncompressed: 1 or 2 (mostly 1)
		/*0x0C*/    uint32_t  _xres;	           	     // X resolution (power of 2)
		/*0x10*/    uint32_t  _yres;	         	     // Y resolution (power of 2)
		/*0x14*/    uint32_t  _mipmapOfs[16];                // offsets for every mipmap level (or 0 when there is no more mipmap level)
		/*0x54*/    uint32_t  _mipmapSize[16];   	     // sizes for every mipmap level (or 0 when there is no more mipmap level) 
	};

#	pragma pack ()
};