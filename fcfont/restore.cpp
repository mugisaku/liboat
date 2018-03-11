#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cstdint>


constexpr int  w =  8;
constexpr int  h = 16;


struct
glyph
{
  uint16_t  unicode;

  uint16_t  data[h];

};


constexpr const glyph
table[] =
{
{0x0020,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,}},
{0x0021,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x00A0,0x025C,0x025C,0x025C,0x025C,0x00A0,0x025C,0x00F0,}},
{0x0022,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0A28,0x2597,0x2597,0x279C,0x0C30,}},
{0x0023,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0220,0x0998,0x2557,0x0DDC,0x0998,0x2557,0x0DDC,0x0330,}},
{0x0024,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0080,0x0A68,0x2557,0x9A6C,0x3558,0x2A67,0x955C,0x3FF0,}},
{0x0025,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0808,0x2627,0x999C,0x3660,0x0998,0x2767,0x9CDC,0x3030,}},
{0x0026,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0280,0x0960,0x279C,0x265C,0x25B8,0x9A67,0x355C,0x0FF0,}},
{0x0028,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0008,0x0027,0x009C,0x009C,0x009C,0x0098,0x0037,0x000C,}},
{0x0029,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0800,0x2600,0x0DC0,0x09C0,0x09C0,0x09C0,0x2700,0x0C00,}},
{0x002A,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0080,0x0A78,0x2667,0x0D5C,0x0958,0x2777,0x0E7C,0x00C0,}},
{0x002B,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0080,0x0270,0x0A68,0x2557,0x0F7C,0x0270,0x00C0,}},
{0x002C,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2800,0x9700,0x2700,0x9C00,0x3000,}},
{0x002D,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0AA8,0x2557,0x0FFC,0x0000,0x0000,}},
{0x002E,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2800,0x9700,0x9700,0x3C00,}},
{0x002F,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0008,0x0027,0x009C,0x0270,0x09C0,0x2700,0x9C00,0x3000,}},
{0x0030,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0AA0,0x2558,0x97D7,0x9797,0x9797,0x9697,0x355C,0x0FF0,}},
{0x0031,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0280,0x0970,0x2570,0x0D70,0x0970,0x0960,0x255C,0x0FF0,}},
{0x0032,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0AA0,0x2558,0x97D7,0x3C97,0x025C,0x2968,0x9557,0x3FFC,}},
{0x0033,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0AA0,0x2558,0x9697,0x3D57,0x2BD8,0x9697,0x355C,0x0FF0,}},
{0x0034,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x00A0,0x025C,0x095C,0x095C,0x2658,0x9557,0x3F5C,0x00F0,}},
{0x0035,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2AA8,0x9557,0x96AC,0x9558,0x2FD7,0x9AA7,0x355C,0x0FF0,}},
{0x0036,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0AA0,0x2558,0x9697,0x9558,0x97D7,0x9697,0x355C,0x0FF0,}},
{0x0037,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0AA8,0x2557,0x0FD7,0x0097,0x025C,0x0970,0x25C0,0x0F00,}},
{0x0038,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0AA0,0x2558,0x9697,0x2558,0x97D7,0x9697,0x355C,0x0FF0,}},
{0x0039,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0AA0,0x2558,0x9697,0x3557,0x2FD7,0x9A97,0x355C,0x0FF0,}},
{0x003A,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0280,0x0970,0x0970,0x0280,0x0970,0x0970,0x03C0,0x0000,}},
{0x003B,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0280,0x0970,0x0970,0x0280,0x0970,0x0270,0x09C0,0x0300,}},
{0x003C,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0028,0x0297,0x097C,0x2680,0x0D68,0x03D7,0x003C,}},
{0x003D,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0AA8,0x2557,0x0FFC,0x0AA8,0x2557,0x0FFC,}},
{0x003E,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0A00,0x25A0,0x0F58,0x00A7,0x0A5C,0x25F0,0x0F00,}},
{0x003F,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0AA0,0x2558,0x9797,0x3E5C,0x0970,0x0280,0x0970,0x03C0,}},
{0x0040,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x02A0,0x0958,0x2697,0x9557,0x9797,0x9658,0x3557,0x0FFC,}},
{0x0041,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0280,0x0960,0x25DC,0x259C,0x2558,0x97F7,0x9727,0x3C0C,}},
{0x0042,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2AA0,0x9558,0x96A7,0x9558,0x97F7,0x96A7,0x955C,0x3FF0,}},
{0x0043,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x02A0,0x0958,0x25D7,0x973C,0x9628,0x3597,0x0D5C,0x03F0,}},
{0x0044,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2A80,0x9560,0x97D8,0x9797,0x9797,0x969C,0x9570,0x3FC0,}},
{0x0045,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2AA8,0x9557,0x96AC,0x955C,0x97F0,0x96A8,0x9557,0x3FFC,}},
{0x0046,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2AA8,0x9557,0x97FC,0x96A8,0x9557,0x97FC,0x9700,0x3C00,}},
{0x0047,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x02A0,0x0958,0x25D7,0x9728,0x9797,0x36A7,0x0D57,0x03FC,}},
{0x0048,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2808,0x9727,0x96A7,0x9557,0x97F7,0x9727,0x9727,0x3C0C,}},
{0x0049,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0AA0,0x255C,0x0D70,0x0970,0x0970,0x0960,0x255C,0x0FF0,}},
{0x004A,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0028,0x0097,0x0097,0x2897,0x9797,0x9697,0x355C,0x0FF0,}},
{0x004B,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2808,0x9727,0x979C,0x965C,0x9560,0x97D8,0x9737,0x3C0C,}},
{0x004C,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2800,0x9700,0x9700,0x9700,0x9700,0x96A8,0x9557,0x3FFC,}},
{0x004D,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2808,0x9627,0x9597,0x9557,0x9777,0x97E7,0x9727,0x3C0C,}},
{0x004E,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2808,0x9627,0x95A7,0x9567,0x9757,0x97D7,0x9737,0x3C0C,}},
{0x004F,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0280,0x0960,0x25D8,0x9737,0x9627,0x359C,0x0D70,0x03C0,}},
{0x0050,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2AA0,0x9558,0x96A7,0x955C,0x97F0,0x9700,0x9700,0x3C00,}},
{0x0051,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0280,0x0960,0x25D8,0x97B7,0x9667,0x3698,0x0D77,0x03CC,}},
{0x0052,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2AA0,0x9558,0x96A7,0x955C,0x9760,0x97D8,0x9737,0x3C0C,}},
{0x0053,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0AA0,0x2558,0x96F7,0x35AC,0x2B58,0x96A7,0x3D5C,0x03F0,}},
{0x0054,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2AA8,0x9557,0x3D7C,0x0970,0x0970,0x0970,0x0970,0x03C0,}},
{0x0055,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2808,0x9727,0x9727,0x9727,0x9727,0x96A7,0x355C,0x0FF0,}},
{0x0056,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2808,0x9727,0x9627,0x35E7,0x259C,0x0D9C,0x0370,0x00C0,}},
{0x0057,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2808,0x9727,0x97A7,0x9667,0x9557,0x35DC,0x279C,0x0C30,}},
{0x0058,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2808,0x9627,0x359C,0x0D5C,0x0960,0x25D8,0x9737,0x3C0C,}},
{0x0059,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2808,0x9627,0x359C,0x0D70,0x0370,0x0270,0x0270,0x00C0,}},
{0x005A,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2AA8,0x9557,0x3F97,0x025C,0x0970,0x25A8,0x9557,0x3FFC,}},
{0x005B,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x00A8,0x0257,0x027C,0x0270,0x0270,0x0268,0x0257,0x00FC,}},
{0x005E,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0080,0x0260,0x09DC,0x0330,0x0000,0x0000,0x0000,0x0000,}},
{0x005F,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2AA8,0x9557,0x3FFC,}},
{0x0060,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0200,0x0980,0x0370,0x00C0,0x0000,0x0000,0x0000,0x0000,}},
{0x0061,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x02A0,0x0958,0x0AA7,0x2557,0x96A7,0x3557,}},
{0x0062,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2800,0x9700,0x97A0,0x9658,0x95F7,0x9727,0x96A7,0x955C,}},
{0x0063,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x02A0,0x2958,0x97F7,0x9708,0x96A7,0x3D5C,}},
{0x0064,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0008,0x0027,0x0AA7,0x2567,0x97D7,0x9737,0x96A7,0x3557,}},
{0x0065,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0AA0,0x2558,0x96A7,0x9557,0x96A8,0x3557,}},
{0x0066,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x00A8,0x0257,0x2968,0x9557,0x3D7C,0x0970,0x0970,0x0970,}},
{0x0067,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0AA8,0x2557,0x96A7,0x3557,0x0EA7,0x095C,}},
{0x0068,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2800,0x9700,0x97A0,0x9658,0x95F7,0x9727,0x9727,0x9727,}},
{0x0069,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0280,0x0970,0x0280,0x0970,0x0970,0x0970,0x0970,0x0970,}},
{0x006A,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0028,0x0097,0x0028,0x0097,0x0097,0x2897,0x9697,0x355C,}},
{0x006B,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0A00,0x25C0,0x25C8,0x25A7,0x255C,0x2560,0x25D8,0x25F7,}},
{0x006C,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0A80,0x2570,0x0D70,0x0970,0x0970,0x0970,0x0970,0x0970,}},
{0x006D,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2A20,0x9598,0x9777,0x9667,0x9667,0x9667,}},
{0x006E,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x28A0,0x9658,0x95F7,0x9727,0x9727,0x9727,}},
{0x006F,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0AA0,0x2558,0x97F7,0x9727,0x96A7,0x355C,}},
{0x0070,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2AA0,0x9558,0x96A7,0x955C,0x97F0,0x9700,}},
{0x0071,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0AA8,0x2557,0x96A7,0x3557,0x0FF7,0x0027,}},
{0x0072,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x28A0,0x9658,0x95D7,0x973C,0x9700,0x9700,}},
{0x0073,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x02A8,0x0957,0x25AC,0x0D58,0x0A97,0x255C,}},
{0x0074,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0280,0x0960,0x255C,0x0D70,0x0970,0x0960,0x035C,}},
{0x0075,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2808,0x9727,0x9727,0x9727,0x9697,0x3577,}},
{0x0076,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2808,0x9727,0x9627,0x359C,0x259C,0x0D70,}},
{0x0077,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2808,0x97A7,0x9667,0x9667,0x35DC,0x259C,}},
{0x0078,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2808,0x9627,0x359C,0x095C,0x25D8,0x9737,}},
{0x0079,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2808,0x9727,0x3697,0x0D9C,0x0A70,0x25C0,}},
{0x007A,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0AA8,0x2557,0x0F9C,0x025C,0x0968,0x2557,}},
{0x007B,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0028,0x0097,0x0A5C,0x2570,0x0F60,0x0258,0x00D7,0x003C,}},
{0x007C,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0080,0x0270,0x0270,0x0270,0x0270,0x0270,0x0270,0x00C0,}},
{0x007D,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0A00,0x2580,0x0D68,0x0357,0x027C,0x0970,0x25C0,0x0F00,}},
{0x007E,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,}},
{0x2160,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0AA0,0x255C,0x0D70,0x0970,0x0970,0x0960,0x255C,0x0FF0,}},
{0x2161,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2AA8,0x9557,0x35DC,0x259C,0x259C,0x2598,0x9557,0x3FFC,}},
{0x2162,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2AA8,0x9557,0x3777,0x2667,0x2667,0x2667,0x9557,0x3FFC,}},
{0x2164,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2808,0x9727,0x9627,0x359C,0x259C,0x0D70,0x0370,0x00C0,}},
{0x2169,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2808,0x9627,0x359C,0x0D70,0x0260,0x29D8,0x9737,0x3C0C,}},
{0x2190,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0200,0x09C0,0x25A8,0x9557,0x9557,0x35FC,0x0DC0,0x0300,}},
{0x2191,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0280,0x0960,0x2558,0x9557,0x3D7C,0x0970,0x0970,0x03C0,}},
{0x2192,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0080,0x0260,0x2A58,0x9557,0x9557,0x3F5C,0x0270,0x00C0,}},
{0x2193,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0280,0x0970,0x0970,0x2968,0x9557,0x355C,0x0D70,0x03C0,}},
{0x25A0,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2AA8,0x9557,0x9557,0x9557,0x9557,0x9557,0x9557,0x3FFC,}},
{0x25A1,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2AA8,0x9557,0x9FF7,0x9C27,0x9C27,0x9AA7,0x9557,0x3FFC,}},
{0x25B2,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0280,0x0970,0x0960,0x2558,0x9557,0x9557,0x3FFC,}},
{0x25B3,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0280,0x0960,0x27DC,0x2798,0x9AA7,0x9557,0x3FFC,}},
{0x25BC,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2AA8,0x9557,0x9557,0x355C,0x255C,0x0D70,0x0970,0x03C0,}},
{0x25BD,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2AA8,0x9557,0x9BE7,0x379C,0x269C,0x0D70,0x0970,0x03C0,}},
{0x25C6,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0280,0x0960,0x2558,0x9557,0x9557,0x355C,0x0D70,0x03C0,}},
{0x25C7,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0280,0x0960,0x27D8,0x9C37,0x9827,0x369C,0x0D70,0x03C0,}},
{0x25CB,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0AA0,0x2558,0x97D7,0x9C37,0x9827,0x9697,0x355C,0x0FF0,}},
{0x25CE,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0AA0,0x2558,0x9697,0x9D77,0x9967,0x9697,0x355C,0x0FF0,}},
{0x25CF,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0AA0,0x2558,0x9557,0x9557,0x9557,0x9557,0x355C,0x0FF0,}},
{0x3000,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,}},
{0x3001,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2000,0x9800,0x3700,0x0C00,}},
{0x3002,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0800,0x2600,0x99C0,0x3700,0x0C00,}},
{0x300C,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x00A8,0x0257,0x027C,0x0270,0x0270,0x0270,0x0270,0x00C0,}},
{0x300D,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0080,0x0270,0x0270,0x0270,0x0A70,0x2570,0x0FC0,}},
{0x300E,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0AA8,0x2557,0x27A7,0x2657,0x267C,0x2670,0x2570,0x0FC0,}},
{0x300F,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x00A8,0x0257,0x0277,0x0A67,0x2567,0x26A7,0x2557,0x0FFC,}},
{0x3010,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x00A8,0x0257,0x025C,0x0270,0x0260,0x0258,0x0257,0x00FC,}},
{0x3011,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2A00,0x95C0,0x35C0,0x0DC0,0x09C0,0x25C0,0x95C0,0x3F00,}},
{0x301C,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0A00,0x2588,0x9F67,0x30DC,0x0030,0x0000,}},
{0x3041,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0200,0x29A0,0x955C,0x299C,0x955C,0x355C,0x0FF0,}},
{0x3042,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0200,0x29A0,0x955C,0x3998,0x2557,0x9967,0x35DC,0x0F30,}},
{0x3043,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0820,0x2798,0x2637,0x0DE7,0x030C,}},
{0x3044,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2020,0x9C98,0x9C37,0x9C27,0x9A27,0x35CC,0x0F00,}},
{0x3045,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x02A0,0x095C,0x2558,0x0EA7,0x095C,0x03F0,}},
{0x3046,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x02A0,0x095C,0x0958,0x27F7,0x0C27,0x02A7,0x095C,0x03F0,}},
{0x3047,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0280,0x0960,0x255C,0x0E70,0x0960,0x275C,0x0CF0,}},
{0x3048,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0A80,0x2560,0x955C,0x3E70,0x0960,0x27D8,0x9C97,0x303C,}},
{0x3049,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0220,0x099C,0x2560,0x0958,0x25E7,0x0D9C,0x0330,}},
{0x304A,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0220,0x2998,0x9577,0x39AC,0x2558,0x99E7,0x359C,0x0F30,}},
{0x304B,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0220,0x2998,0x9567,0x39DC,0x279C,0x279C,0x9E70,0x30C0,}},
{0x304C,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0088,0x0266,0x00DD,0x0223,0x2998,0x9567,0x39DC,0x279C,0x279C,0x9E70,0x30C0,}},
{0x304D,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2AA8,0x9557,0x2A68,0x9557,0x2F7C,0x9AA0,0x355C,0x0FF0,}},
{0x304E,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0088,0x0266,0x00DD,0x2AAB,0x9557,0x2A68,0x9557,0x2F7C,0x9AA0,0x355C,0x0FF0,}},
{0x304F,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0080,0x0270,0x09C0,0x2700,0x2600,0x0D80,0x0370,0x00C0,}},
{0x3050,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0088,0x0266,0x00DD,0x00B3,0x0270,0x09C0,0x2700,0x2600,0x0D80,0x0370,0x00C0,}},
{0x3051,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0020,0x2298,0x9957,0x9FDC,0x9C9C,0x989C,0x379C,0x0C30,}},
{0x3052,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0088,0x0266,0x00DD,0x0023,0x2298,0x9957,0x9FDC,0x9C9C,0x989C,0x379C,0x0C30,}},
{0x3053,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0AA8,0x2557,0x0FFC,0x2000,0x9AA8,0x3557,0x0FFC,}},
{0x3054,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0088,0x0266,0x00DD,0x0033,0x0AA8,0x2557,0x0FFC,0x2000,0x9AA8,0x3557,0x0FFC,}},
{0x3055,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0080,0x2A68,0x9557,0x3F6C,0x20DC,0x9AA0,0x355C,0x0FF0,}},
{0x3056,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0088,0x0266,0x00DD,0x00B3,0x2A68,0x9557,0x3F6C,0x20DC,0x9AA0,0x355C,0x0FF0,}},
{0x3057,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0800,0x2700,0x2700,0x2700,0x2708,0x26A7,0x0D5C,0x03F0,}},
{0x3058,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0088,0x0266,0x00DD,0x0833,0x2700,0x2700,0x2700,0x2708,0x26A7,0x0D5C,0x03F0,}},
{0x3059,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0020,0x2A98,0x9557,0x3D9C,0x095C,0x029C,0x0970,0x03C0,}},
{0x305A,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0088,0x0266,0x00DD,0x0023,0x2A98,0x9557,0x3D9C,0x095C,0x029C,0x0970,0x03C0,}},
{0x305B,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0820,0x2698,0x9557,0x37DC,0x279C,0x26A0,0x0D5C,0x03F0,}},
{0x305C,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0088,0x0266,0x00DD,0x0823,0x2698,0x9557,0x37DC,0x279C,0x26A0,0x0D5C,0x03F0,}},
{0x305D,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0AA0,0x255C,0x2A68,0x9557,0x3DFC,0x09A0,0x035C,0x00F0,}},
{0x305E,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0088,0x0266,0x00DD,0x0AA3,0x255C,0x2A68,0x9557,0x3DFC,0x09A0,0x035C,0x00F0,}},
{0x305F,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0800,0x2680,0x9568,0x3757,0x27BC,0x2668,0x9CD7,0x303C,}},
{0x3060,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0088,0x0266,0x00DD,0x0833,0x2680,0x9568,0x3757,0x27BC,0x2668,0x9CD7,0x303C,}},
{0x3061,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0200,0x29A8,0x9557,0x3958,0x27F7,0x0EA7,0x095C,0x03F0,}},
{0x3062,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0088,0x0266,0x00DD,0x0233,0x29A8,0x9557,0x3958,0x27F7,0x0EA7,0x095C,0x03F0,}},
{0x3063,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x00A0,0x0A58,0x25A7,0x0F5C,0x00F0,}},
{0x3064,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x02A0,0x2958,0x97F7,0x3C27,0x029C,0x0970,0x03C0,}},
{0x3065,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0088,0x0266,0x00DD,0x0033,0x02A0,0x2958,0x97F7,0x3C27,0x029C,0x0970,0x03C0,}},
{0x3066,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2AA8,0x9557,0x3E5C,0x09F0,0x2700,0x26A0,0x0D5C,0x03F0,}},
{0x3067,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0088,0x0266,0x00DD,0x2AAB,0x9557,0x3E5C,0x09F0,0x2700,0x26A0,0x0D5C,0x03F0,}},
{0x3068,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2000,0x9828,0x3697,0x097C,0x27C0,0x26A8,0x0D57,0x03FC,}},
{0x3069,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0088,0x0266,0x00DD,0x2033,0x9828,0x3697,0x097C,0x27C0,0x26A8,0x0D57,0x03FC,}},
{0x306A,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0820,0x2698,0x95B7,0x376C,0x265C,0x9D98,0x9F77,0x30CC,}},
{0x306B,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2000,0x9CA8,0x9E57,0x9CFC,0x9E00,0x99A8,0x3757,0x0CFC,}},
{0x306C,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0820,0x279C,0x2658,0x2557,0x9597,0x9967,0x9757,0x3CFC,}},
{0x306D,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0200,0x29A0,0x9558,0x3977,0x25E7,0x2597,0x9D97,0x333C,}},
{0x306E,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0AA0,0x2558,0x9F77,0x9E67,0x99E7,0x359C,0x0F30,}},
{0x306F,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2020,0x9E98,0x9957,0x9FDC,0x9E98,0x9957,0x995C,0x33F0,}},
{0x3070,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0088,0x0266,0x00DD,0x2023,0x9E98,0x9957,0x9FDC,0x9E98,0x9957,0x995C,0x33F0,}},
{0x3071,{0x0000,0x0000,0x0000,0x0000,0x0008,0x0026,0x0099,0x0037,0x202C,0x9E98,0x9957,0x9FDC,0x9E98,0x9957,0x995C,0x33F0,}},
{0x3072,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2820,0x9798,0x2797,0x9C97,0x9C9C,0x9A9C,0x3570,0x0FC0,}},
{0x3073,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0088,0x0266,0x00DD,0x2823,0x9798,0x2797,0x9C97,0x9C9C,0x9A9C,0x3570,0x0FC0,}},
{0x3074,{0x0000,0x0000,0x0000,0x0000,0x0008,0x0026,0x0099,0x0037,0x282C,0x9798,0x2797,0x9C97,0x9C9C,0x9A9C,0x3570,0x0FC0,}},
{0x3075,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0A80,0x2570,0x0DA0,0x2958,0x9FD7,0x9E97,0x397C,0x03C0,}},
{0x3076,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0088,0x0266,0x00DD,0x0AB3,0x2570,0x0DA0,0x2958,0x9FD7,0x9E97,0x397C,0x03C0,}},
{0x3077,{0x0000,0x0000,0x0000,0x0000,0x0008,0x0026,0x0099,0x0037,0x0A8C,0x2570,0x0DA0,0x2958,0x9FD7,0x9E97,0x397C,0x03C0,}},
{0x3078,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0200,0x0980,0x2760,0x9CD8,0x3037,0x000C,0x0000,}},
{0x3079,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0088,0x0266,0x00DD,0x0033,0x0200,0x0980,0x2760,0x9CD8,0x3037,0x000C,0x0000,}},
{0x307A,{0x0000,0x0000,0x0000,0x0000,0x0008,0x0026,0x0099,0x0037,0x000C,0x0200,0x0980,0x2760,0x9CD8,0x3037,0x000C,0x0000,}},
{0x307B,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x22A8,0x9957,0x9E98,0x9957,0x9E98,0x9957,0x995C,0x33F0,}},
{0x307C,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0088,0x0266,0x00DD,0x22AB,0x9957,0x9E98,0x9957,0x9E98,0x9957,0x995C,0x33F0,}},
{0x307D,{0x0000,0x0000,0x0000,0x0000,0x0008,0x0026,0x0099,0x0037,0x22A8,0x9957,0x9E98,0x9957,0x9E98,0x9957,0x995C,0x33F0,}},
{0x307E,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2AA8,0x9557,0x2A68,0x9557,0x296C,0x9658,0x9577,0x3FCC,}},
{0x307F,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2A20,0x959C,0x3998,0x2557,0x9DDC,0x999C,0x959C,0x3F30,}},
{0x3080,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0200,0x29A0,0x9558,0x25F7,0x99C8,0x35A7,0x255C,0x0FF0,}},
{0x3081,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0820,0x279C,0x2658,0x2597,0x9D77,0x9967,0x95E7,0x3F0C,}},
{0x3082,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0200,0x2980,0x9570,0x2988,0x9567,0x3DA7,0x095C,0x03F0,}},
{0x3083,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0080,0x0260,0x2958,0x95E7,0x3D9C,0x0370,0x00C0,}},
{0x3084,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0820,0x279C,0x2658,0x95E7,0x369C,0x0DF0,0x09C0,0x0300,}},
{0x3085,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0080,0x0A60,0x2658,0x2567,0x275C,0x0E70,0x00C0,}},
{0x3086,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0080,0x2260,0x9958,0x9777,0x9E67,0x995C,0x3370,0x00C0,}},
{0x3087,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0080,0x0260,0x025C,0x0960,0x25DC,0x0F30,}},
{0x3088,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0080,0x0268,0x0257,0x0A7C,0x2568,0x9A57,0x957C,0x3FC0,}},
{0x3089,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0280,0x0970,0x26A0,0x9558,0x97F7,0x3EA7,0x095C,0x03F0,}},
{0x308A,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0820,0x279C,0x279C,0x279C,0x279C,0x0C9C,0x0270,0x00C0,}},
{0x308B,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0AA0,0x255C,0x0E60,0x0958,0x26B7,0x0D67,0x095C,0x03F0,}},
{0x308C,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0220,0x299C,0x955C,0x39DC,0x259C,0x9D98,0x39F7,0x030C,}},
{0x308D,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0AA0,0x255C,0x0A60,0x2558,0x9FF7,0x32A7,0x095C,0x03F0,}},
{0x308F,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x08A0,0x2658,0x9577,0x35E7,0x2727,0x9727,0x379C,0x0C30,}},
{0x3092,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0080,0x2A60,0x9558,0x25A7,0x955C,0x9A68,0x3557,0x0FFC,}},
{0x3093,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0080,0x0270,0x09C0,0x09C0,0x2588,0x2567,0x9FDC,0x3030,}},
{0x309B,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2200,0x99C0,0x99C0,0x3300,0x0000,0x0000,0x0000,0x0000,}},
{0x309C,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0800,0x2600,0x99C0,0x3700,0x0C00,0x0000,0x0000,0x0000,}},
{0x30A1,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0AA8,0x2557,0x0FA7,0x025C,0x0270,0x09C0,}},
{0x30A2,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2AA8,0x9557,0x3EF7,0x09E7,0x099C,0x09F0,0x2700,}},
{0x30A3,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0020,0x009C,0x0270,0x0970,0x2770,0x0E70,}},
{0x30A4,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0008,0x0027,0x0027,0x009C,0x0A5C,0x25DC,0x0F9C,0x009C,}},
{0x30A5,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0080,0x0A60,0x255C,0x27DC,0x0E9C,0x0970,}},
{0x30A6,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0080,0x0270,0x2A68,0x9557,0x9FF7,0x3027,0x029C,0x0970,}},
{0x30A7,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0AA8,0x2557,0x0F7C,0x0A68,0x2557,}},
{0x30A8,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2AA8,0x9557,0x3DFC,0x09C0,0x09C0,0x29A8,0x9557,}},
{0x30A9,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0020,0x0A98,0x2557,0x0A5C,0x259C,0x0F5C,}},
{0x30AA,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0020,0x2A98,0x9557,0x3F9C,0x025C,0x29DC,0x979C,0x3E5C,}},
{0x30AB,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0200,0x29A8,0x9557,0x3DF7,0x09E7,0x09E7,0x2727,0x9C9C,}},
{0x30AC,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0088,0x0266,0x00DD,0x0233,0x29A8,0x9557,0x3DF7,0x09E7,0x09E7,0x2727,0x9C9C,}},
{0x30AD,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0200,0x09A8,0x2A57,0x9568,0x2A57,0x955C,0x3FDC,0x009C,}},
{0x30AE,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0088,0x0266,0x00DD,0x0233,0x09A8,0x2A57,0x9568,0x2A57,0x955C,0x3FDC,0x009C,}},
{0x30AF,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0200,0x09A8,0x0957,0x27F7,0x9C27,0x309C,0x0A70,0x25C0,}},
{0x30B0,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0088,0x0266,0x00DD,0x0233,0x09A8,0x0957,0x27F7,0x9C27,0x309C,0x0A70,0x25C0,}},
{0x30B1,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0800,0x26A8,0x2557,0x27DC,0x9C9C,0x309C,0x029C,0x0970,}},
{0x30B2,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0088,0x0266,0x00DD,0x0833,0x26A8,0x2557,0x27DC,0x9C9C,0x309C,0x029C,0x0970,}},
{0x30B3,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0AA8,0x2557,0x0FF7,0x0027,0x0027,0x0AA7,0x2557,}},
{0x30B4,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0088,0x0266,0x00DD,0x0033,0x0AA8,0x2557,0x0FF7,0x0027,0x0027,0x0AA7,0x2557,}},
{0x30B5,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0820,0x2698,0x9557,0x37DC,0x279C,0x0C9C,0x0270,0x09C0,}},
{0x30B6,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0088,0x0266,0x00DD,0x0823,0x2698,0x9557,0x37DC,0x279C,0x0C9C,0x0270,0x09C0,}},
{0x30B7,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2808,0x9727,0x2827,0x9727,0x3C27,0x0A9C,0x2570,}},
{0x30B8,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0088,0x0266,0x00DD,0x0033,0x2808,0x9727,0x2827,0x9727,0x3C27,0x0A9C,0x2570,}},
{0x30B9,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0AA0,0x255C,0x0FDC,0x009C,0x0260,0x29D8,0x9737,}},
{0x30BA,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0088,0x0266,0x00DD,0x0033,0x0AA0,0x255C,0x0FDC,0x009C,0x0260,0x29D8,0x9737,}},
{0x30BB,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0800,0x26A8,0x9557,0x37E7,0x279C,0x2730,0x26A0,0x0D5C,}},
{0x30BC,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0088,0x0266,0x00DD,0x0833,0x26A8,0x9557,0x37E7,0x279C,0x2730,0x26A0,0x0D5C,}},
{0x30BD,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2008,0x9827,0x3727,0x0C27,0x009C,0x029C,0x0970,}},
{0x30BE,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0088,0x0266,0x00DD,0x0033,0x2008,0x9827,0x3727,0x0C27,0x009C,0x029C,0x0970,}},
{0x30BF,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0200,0x09A8,0x0957,0x26F7,0x9DA7,0x335C,0x0A70,0x25C0,}},
{0x30C0,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0088,0x0266,0x00DD,0x0233,0x09A8,0x0957,0x26F7,0x9DA7,0x335C,0x0A70,0x25C0,}},
{0x30C1,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0008,0x0AA7,0x255C,0x2A68,0x9557,0x3F7C,0x0270,0x09C0,}},
{0x30C2,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0088,0x0266,0x00DD,0x003B,0x0AA7,0x255C,0x2A68,0x9557,0x3F7C,0x0270,0x09C0,}},
{0x30C3,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0888,0x2667,0x2667,0x0EA7,0x095C,}},
{0x30C4,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2208,0x99E7,0x99E7,0x99E7,0x3327,0x029C,0x0970,}},
{0x30C5,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0088,0x0266,0x00DD,0x0033,0x2208,0x99E7,0x99E7,0x99E7,0x3327,0x029C,0x0970,}},
{0x30C6,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0AA8,0x2557,0x2AA8,0x9557,0x3F7C,0x0270,0x09C0,0x2700,}},
{0x30C7,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0088,0x0266,0x00DD,0x0AAB,0x2557,0x2AA8,0x9557,0x3F7C,0x0270,0x09C0,0x2700,}},
{0x30C8,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0200,0x09C0,0x09C0,0x09A0,0x0958,0x09F7,0x09CC,0x09C0,}},
{0x30C9,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0088,0x0266,0x00DD,0x0233,0x09C0,0x09C0,0x09A0,0x0958,0x09F7,0x09CC,0x09C0,}},
{0x30CA,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0080,0x2A68,0x9557,0x3F7C,0x0270,0x0270,0x09C0,0x2700,}},
{0x30CB,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0AA0,0x255C,0x0FF0,0x0000,0x0000,0x2AA8,0x9557,}},
{0x30CC,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2AA0,0x955C,0x3ADC,0x259C,0x0E60,0x29D8,0x9737,}},
{0x30CD,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0280,0x2968,0x9557,0x3F9C,0x0260,0x2958,0x9777,0x3E7C,}},
{0x30CE,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0008,0x0027,0x0027,0x0027,0x0027,0x009C,0x0A70,0x25C0,}},
{0x30CF,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0080,0x0260,0x20D8,0x9C37,0x9C27,0x9C27,0x9C27,}},
{0x30D0,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0088,0x0266,0x00DD,0x0033,0x0080,0x0260,0x20D8,0x9C37,0x9C27,0x9C27,0x9C27,}},
{0x30D1,{0x0000,0x0000,0x0000,0x0000,0x0008,0x0026,0x0099,0x0037,0x000C,0x0080,0x0260,0x20D8,0x9C37,0x9C27,0x9C27,0x9C27,}},
{0x30D2,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2000,0x9C28,0x9A97,0x957C,0x9FC0,0x9C00,0x9AA8,0x3557,}},
{0x30D3,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0088,0x0266,0x00DD,0x2033,0x9C28,0x9A97,0x957C,0x9FC0,0x9C00,0x9AA8,0x3557,}},
{0x30D4,{0x0000,0x0000,0x0000,0x0000,0x0008,0x0026,0x0099,0x0037,0x200C,0x9C28,0x9A97,0x957C,0x9FC0,0x9C00,0x9AA8,0x3557,}},
{0x30D5,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2AA8,0x9557,0x3FF7,0x0027,0x009C,0x2A9C,0x9570,}},
{0x30D6,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0088,0x0266,0x00DD,0x0033,0x2AA8,0x9557,0x3FF7,0x0027,0x009C,0x2A9C,0x9570,}},
{0x30D7,{0x0000,0x0000,0x0000,0x0000,0x0008,0x0026,0x0099,0x0037,0x000C,0x2AA8,0x9557,0x3FF7,0x0027,0x009C,0x2A9C,0x9570,}},
{0x30D8,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0200,0x0980,0x2760,0x9CD8,0x3037,0x000C,0x0000,}},
{0x30D9,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0088,0x0266,0x00DD,0x0033,0x0200,0x0980,0x2760,0x9CD8,0x3037,0x000C,0x0000,}},
{0x30DA,{0x0000,0x0000,0x0000,0x0000,0x0008,0x0026,0x0099,0x0037,0x000C,0x0200,0x0980,0x2760,0x9CD8,0x3037,0x000C,0x0000,}},
{0x30DB,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0200,0x29A8,0x9557,0x3DEC,0x2998,0x99F7,0x99E7,0x39CC,}},
{0x30DC,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0088,0x0266,0x00DD,0x0233,0x29A8,0x9557,0x3DEC,0x2998,0x99F7,0x99E7,0x39CC,}},
{0x30DD,{0x0000,0x0000,0x0000,0x0000,0x0008,0x0026,0x0099,0x0037,0x020C,0x29A8,0x9557,0x3DEC,0x2998,0x99F7,0x99E7,0x39CC,}},
{0x30DE,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2AA8,0x9557,0x3BF7,0x26A7,0x0D5C,0x0360,0x00DC,}},
{0x30DF,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2A00,0x95A8,0x2B57,0x96A8,0x2D57,0x9AAC,0x3558,0x0FF7,}},
{0x30E0,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0200,0x09C0,0x09C0,0x09E0,0x279C,0x2698,0x9577,}},
{0x30E1,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0008,0x0027,0x0A27,0x259C,0x0F58,0x0277,0x09E7,0x270C,}},
{0x30E2,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2AA8,0x9557,0x29A8,0x9557,0x3DFC,0x09A8,0x0357,}},
{0x30E3,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0200,0x09A8,0x0957,0x25B7,0x0F7C,0x0270,}},
{0x30E4,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0800,0x2728,0x2697,0x9567,0x36DC,0x0DF0,0x09C0,0x09C0,}},
{0x30E5,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x02A0,0x095C,0x03DC,0x0A98,0x2557,}},
{0x30E6,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0AA0,0x255C,0x0FDC,0x009C,0x009C,0x2A98,0x9557,}},
{0x30E7,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x02A8,0x0957,0x03A7,0x0257,0x02A7,0x0957,}},
{0x30E8,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0AA8,0x2557,0x0EA7,0x0957,0x03F7,0x0AA7,0x2557,}},
{0x30E9,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0AA0,0x255C,0x2AA8,0x9557,0x3FF7,0x0027,0x0A9C,0x2570,}},
{0x30EA,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0808,0x2727,0x2727,0x2727,0x2727,0x0C27,0x029C,0x0970,}},
{0x30EB,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0080,0x0A70,0x2670,0x2670,0x2670,0x2678,0x2667,0x9E5C,}},
{0x30EC,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0200,0x09C0,0x09C0,0x09C0,0x09C8,0x09E7,0x099C,0x0970,}},
{0x30ED,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2AA8,0x9557,0x9FF7,0x9C27,0x9C27,0x9AA7,0x9557,}},
{0x30EE,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0AA8,0x2557,0x27F7,0x0C27,0x029C,0x0970,}},
{0x30EF,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2AA8,0x9557,0x9FF7,0x3027,0x0027,0x029C,0x0970,}},
{0x30F2,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2AA8,0x9557,0x3AA7,0x2557,0x0FE7,0x0A9C,0x2570,}},
{0x30F3,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2808,0x9627,0x3DE7,0x0327,0x009C,0x2A9C,0x9570,}},
{0x30F4,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0088,0x0266,0x00DD,0x00B3,0x0270,0x2A68,0x9557,0x9FF7,0x3027,0x029C,0x0970,}},
{0x30F5,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0080,0x0A68,0x2557,0x0E77,0x09E7,0x2797,}},
{0x30F6,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0200,0x09A8,0x0957,0x27DC,0x0C9C,0x0270,}},
{0x30FB,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0280,0x0970,0x0970,0x03C0,0x0000,}},
{0x30FC,{0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2000,0x9AA8,0x3557,0x0FFC,0x0000,}},
};




int
main(int  argc, char**  argv)
{
    for(auto&  gly: table)
    {
      printf("{0x%02X,{",gly.unicode);

        for(int  y = 0;  y < 8;  ++y)
        {
          auto  src = gly.data[8+y];

          int  n = 0;

            for(int  x = 0;  x < 8;  ++x)
            {
                if((src>>14) == 1)
                {
                  n |= (0x80>>x);
                }


              src <<= 2;
            }


          printf("0x%02X,",n);
        }


      printf("}},\n");
    }


  return 0;
}




