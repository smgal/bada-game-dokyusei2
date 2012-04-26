
#include <string.h>

namespace dokyu
{
	namespace
	{
		typedef unsigned char  byte;
		typedef unsigned short word;

		struct THeader
		{
			byte  manufacture;
			byte  version;
			byte  encording;
			byte  bit_per_pixel;
			short x1, y1, x2, y2;
			short h_dpi, v_dpi;
			byte  palette[16][3];
			byte  reserved;
			byte  planes;
			short bytes_per_line;
			short palette_info;
			short h_screensize;
			short v_screensize;
			byte  filler[54];
		};
	}

	template <typename TPixel>
	bool LoadPCX(const unsigned char* p_stream, unsigned long stream_size, TPixel*& p_out_buffer, int& out_width, int& out_height)
	{
		return false;
	}

	template <>
	bool LoadPCX<unsigned long>(const unsigned char* p_stream, unsigned long stream_size, unsigned long*& p_out_buffer, int& out_width, int& out_height)
	{
		typedef int _COMPILE_TIME_ASSERT[(sizeof(THeader) == 128) ? 1 : -1];

		typedef unsigned long TPixel;

		const unsigned char* p_stream_end = p_stream + stream_size;

		THeader header;

		memcpy(&header, p_stream, sizeof(header));

		p_stream += sizeof(header);

		////////

		out_width    = (header.x2 + 1);
		out_height   = (header.y2 + 1);
		p_out_buffer = new TPixel[out_width * out_height];

		memset(p_out_buffer, 0, sizeof(TPixel) * out_width * out_height);

		int  x = 0;
		int  y = 0;
		byte plane = 1;

		while (p_stream < p_stream_end)
		{
			byte len;
			byte data;

			byte ch = *p_stream++;

			if ((ch & 0xC0) == 0xC0)
			{
				len = ch & 0x3F;
				// worry for out-of-range in the mal-coded PCX file
				data = *p_stream++;
			}
			else
			{
				len  = 1;
				data = ch;
			}

			while (len-- > 0)
			{
				if (x >= int(header.bytes_per_line))
				{
					plane <<= 1;
					if (plane == 0x10)
					{
						++y;
						plane = 1;
					}
					x = 0;
				}

				for (int shift = 0; shift < 8; shift++)
				{
					if (data & (0x80 >> shift))
					{
						p_out_buffer[y * out_width + 8*x + shift] |= plane;
					}
				}
				++x;
			}
		}
#if 0
		{
			TPixel palette[16];

			for (int i = 0; i < 16; i++)
			{
				TPixel r = (header.palette[i][0] >> 3) & 0x1F;
				TPixel g = (header.palette[i][1] >> 2) & 0x3F;
				TPixel b = (header.palette[i][2] >> 3) & 0x1F;

				palette[i] = (r << 11) | (g << 5) | (b);
			}

			TPixel* p_buffer     = p_out_buffer;
			TPixel* p_buffer_end = p_out_buffer + out_width * out_height;

			while (p_buffer < p_buffer_end)
			{
				*p_buffer = palette[*p_buffer];
				++p_buffer;
			}
		}
#else
		{
			TPixel palette[16];

			for (int i = 0; i < 16; i++)
			{
				TPixel r = header.palette[i][0];
				TPixel g = header.palette[i][1];
				TPixel b = header.palette[i][2];

				palette[i] = 0xFF000000 | (r << 16) | (g << 8) | (b);
			}

			TPixel* p_buffer     = p_out_buffer;
			TPixel* p_buffer_end = p_out_buffer + out_width * out_height;

			while (p_buffer < p_buffer_end)
			{
				*p_buffer = palette[*p_buffer];
				++p_buffer;
			}
		}
#endif
		return true;
	}
}
