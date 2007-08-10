//
// Basic integer types
//

typedef signed char int8;
typedef signed short int16;
typedef signed int int32;
typedef signed long long int64;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;



//
// Endian integer types
//

typedef uint8 eint16[2];
typedef uint8 eint32[4];
typedef uint8 eint64[8];

static inline int16 XeeBEInt16(const uint8 *b) { return ((int16)b[0]<<8)|(int16)b[1]; }
static inline int32 XeeBEInt32(const uint8 *b) { return ((int32)b[0]<<24)|((int32)b[1]<<16)|((int32)b[2]<<8)|(int32)b[3]; }
static inline int64 XeeBEInt64(const uint8 *b) { return ((int64)b[0]<<56)|((int64)b[1]<<48)|((int64)b[2]<<40)|((int64)b[3]<<32)|((int64)b[4]<<24)||((int64)b[5]<<16)|((int64)b[6]<<8)|(int64)b[7]; }
static inline uint16 XeeBEUInt16(const uint8 *b) { return ((uint16)b[0]<<8)|(uint16)b[1]; }
static inline uint32 XeeBEUInt32(const uint8 *b) { return ((uint32)b[0]<<24)|((uint32)b[1]<<16)|((uint32)b[2]<<8)|(uint32)b[3]; }
static inline uint64 XeeBEUInt64(const uint8 *b) { return ((uint64)b[0]<<56)|((uint64)b[1]<<48)|((uint64)b[2]<<40)|((uint64)b[3]<<32)|((uint64)b[4]<<24)||((uint64)b[5]<<16)|((uint64)b[6]<<8)|(uint64)b[7]; }
static inline int16 XeeLEInt16(const uint8 *b) { return ((int16)b[1]<<8)|(int16)b[0]; }
static inline int32 XeeLEInt32(const uint8 *b) { return ((int32)b[3]<<24)|((int32)b[2]<<16)|((int32)b[1]<<8)|(int32)b[0]; }
static inline int64 XeeLEInt64(const uint8 *b) { return ((int64)b[7]<<56)|((int64)b[6]<<48)|((int64)b[5]<<40)|((int64)b[4]<<32)|((int64)b[3]<<24)||((int64)b[2]<<16)|((int64)b[1]<<8)|(int64)b[0]; }
static inline uint16 XeeLEUInt16(const uint8 *b) { return ((uint16)b[1]<<8)|(uint16)b[0]; }
static inline uint32 XeeLEUInt32(const uint8 *b) { return ((uint32)b[3]<<24)|((uint32)b[2]<<16)|((uint32)b[1]<<8)|(uint32)b[0]; }
static inline uint64 XeeLEUInt64(const uint8 *b) { return ((uint64)b[7]<<56)|((uint64)b[6]<<48)|((uint64)b[5]<<40)|((uint64)b[4]<<32)|((uint64)b[3]<<24)||((uint64)b[2]<<16)|((uint64)b[1]<<8)|(uint64)b[0]; }

static inline void XeeSetBEInt16(uint8 *b,int16 n) { b[0]=(n>>8)&0xff; b[1]=n&0xff; }
static inline void XeeSetBEInt32(uint8 *b,int32 n) { b[0]=(n>>24)&0xff; b[1]=(n>>16)&0xff; b[2]=(n>>8)&0xff; b[3]=n&0xff; }
static inline void XeeSetBEUInt16(uint8 *b,uint16 n) { b[0]=(n>>8)&0xff; b[1]=n&0xff; }
static inline void XeeSetBEUInt32(uint8 *b,uint32 n) { b[0]=(n>>24)&0xff; b[1]=(n>>16)&0xff; b[2]=(n>>8)&0xff; b[3]=n&0xff; }
static inline void XeeSetLEInt16(uint8 *b,int16 n) { b[1]=(n>>8)&0xff; b[0]=n&0xff; }
static inline void XeeSetLEInt32(uint8 *b,int32 n) { b[3]=(n>>24)&0xff; b[2]=(n>>16)&0xff; b[1]=(n>>8)&0xff; b[0]=n&0xff; }
static inline void XeeSetLEUInt16(uint8 *b,uint16 n) { b[1]=(n>>8)&0xff; b[0]=n&0xff; }
static inline void XeeSetLEUInt32(uint8 *b,uint32 n) { b[3]=(n>>24)&0xff; b[2]=(n>>16)&0xff; b[1]=(n>>8)&0xff; b[0]=n&0xff; }



//
// Integer utils
//

static inline int imin(int a,int b) { return a<b?a:b; }
static inline int imax(int a,int b) { return a>b?a:b; }
static inline int iabs(int a) { return a>=0?a:-a; }



//
// Spans
//

#define XeeEmptySpan XeeMakeSpan(0,0)

typedef struct XeeSpan { int start,length; } XeeSpan;

static inline XeeSpan XeeMakeSpan(int start,int length) { XeeSpan span={start,length}; return span; }
static inline int XeeSpanStart(XeeSpan span) { return span.start; }
static inline int XeeSpanEnd(XeeSpan span) { return span.start+span.length-1; }
static inline int XeeSpanPastEnd(XeeSpan span) { return span.start+span.length; }
static inline int XeeSpanLength(XeeSpan span) { return span.length; }
static inline BOOL XeeSpanEmpty(XeeSpan span) { return span.length==0; }
static inline BOOL XeePointInSpan(int point,XeeSpan span) { return point>=XeeSpanStart(span)&&point<XeeSpanPastEnd(span); }
static inline BOOL XeePointInSpan(int point,XeeSpan span) { return point>=XeeSpanStart(span)&&point<XeeSpanPastEnd(span); }
static inline BOOL XeeSpanStartsInSpan(XeeSpan span,XeeSpan inspan) { return XeePointInSpan(XeeSpanStart(span),inspan); }
static inline BOOL XeeSpanEndsInSpan(XeeSpan span,XeeSpan inspan) { return XeePointInSpan(XeeSpanEnd(span),inspan); }
static inline BOOL XeeSpansIdentical(XeeSpan span1,XeeSpan span2) { return span1.start==span2.start&&span1.length==span2.length; }
static inline XeeSpan XeeSpanShifted(XeeSpan span,int offset) { return XeeMakeSpan(XeeSpanStart(span)+offset,XeeSpanLength(span)); }
static inline void XeeLogSpan(XeeSpan s) { NSLog(@"XeeSpan(%d,%d)",s.start,s.length); }

XeeSpan XeeSpanUnion(XeeSpan span1,XeeSpan span2);
XeeSpan XeeSpanIntersection(XeeSpan span1,XeeSpan span2);
XeeSpan XeeSpanDifference(XeeSpan old,XeeSpan new);



//
// Matrices
//

typedef struct
{
	float a00,a01,a02;
	float a10,a11,a12;
} XeeMatrix;

static inline XeeMatrix XeeMakeMatrix(float a00,float a01,float a02,float a10,float a11,float a12)
{ XeeMatrix mtx={a00,a01,a02,a10,a11,a12}; return mtx; }
static inline XeeMatrix XeeTranslationMatrix(float x,float y) { return XeeMakeMatrix(1,0,x,0,1,y); }
static inline XeeMatrix XeeScaleMatrix(float x,float y) { return XeeMakeMatrix(x,0,0,0,y,0); }
static inline void XeeLogMatrix(XeeMatrix m) { NSLog(@"XeeMatrix(%f,%f,%f,  %f,%f,%f)",m.a00,m.a01,m.a02,m.a10,m.a11,m.a12); }

XeeMatrix XeeMultiplyMatrices(XeeMatrix a,XeeMatrix b);
XeeMatrix XeeInverseMatrix(XeeMatrix m);
XeeMatrix XeeTransformRectToRectMatrix(NSRect r1,NSRect r2);
NSPoint XeeTransformPoint(XeeMatrix m,NSPoint p);
NSRect XeeTransformRect(XeeMatrix m,NSRect r);
void XeeGLLoadMatrix(XeeMatrix m);
void XeeGLMultMatrix(XeeMatrix m);

//
// Transformations
//

#define XeeUnknownTransformation 0
#define XeeNoTransformation 1
#define XeeMirrorHorizontalTransformation 2
#define XeeRotate180Transformation 3
#define XeeMirrorVerticalTransformation 4
#define XeeTransposeTransfromation 5 // uncertain
#define XeeRotateCWTransformation 6
#define XeeTransverseTransformation 7 // uncertain
#define XeeRotateCCWTransformation 8

#define XeeFirstFlippedTransformation 5

typedef unsigned int XeeTransformation;

static inline BOOL XeeTransformationIsFlipped(XeeTransformation trans) { return trans>=XeeFirstFlippedTransformation; }
static inline BOOL XeeTransformationIsNonTrivial(XeeTransformation trans) { return trans!=XeeUnknownTransformation&&trans!=XeeNoTransformation; }

XeeTransformation XeeInverseOfTransformation(XeeTransformation trans);
XeeTransformation XeeCombineTransformations(XeeTransformation a,XeeTransformation b);
XeeMatrix XeeMatrixForTransformation(XeeTransformation trans,float w,float h);



//
// Time
//

double XeeGetTime();



//
// Hex Data
//

NSString *XeeHexDump(uint8 *data,int length,int maxlen);
