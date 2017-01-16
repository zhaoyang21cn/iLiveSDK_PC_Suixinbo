#include "stdafx.h"
#include "Util.h"


void _CopyBits2Tex_None_0( uint8* pDst, uint8* pSrc, UINT uLen, const SIZE & size )
{
	memcpy(pDst, pSrc,uLen);
}

void _CopyBits2Tex_None_90( uint8* pDst, uint8* pSrc, UINT uLen, const SIZE & size )
{
	int n = 0;
	int linesize = size.cx * 3;

	for(int x = 0; x < size.cx; x++)
	{
		for(int y = size.cy - 1; y >= 0; y--)
		{
			memcpy(pDst + n,  pSrc + linesize * y + 3 * x, 3);
			n += 3;
		}
	}
}

void _CopyBits2Tex_None_180( uint8* pDst, uint8* pSrc, UINT uLen, const SIZE & size )
{
	int n = 0;
	int linesize = size.cx * 3;

	for(int x = 0; x < size.cx; x ++)
	{
		for(int y = 0; y < size.cy; y ++)
		{
			memcpy(pDst + linesize * (size.cy - y - 1) +  3 * x,  pSrc + linesize * y +  3 * (size.cx - x - 1), 3);
		}
	}
}

void _CopyBits2Tex_None_270( uint8* pDst, uint8* pSrc, UINT uLen, const SIZE & size )
{
	int n = 0;
	int linesize = size.cx * 3;

	for(int x = size.cx - 1; x >= 0; x--)
	{
		for(int y = 0; y < size.cy; y ++)
		{
			memcpy(pDst + n,  pSrc + linesize * y + 3 * x, 3);
			n += 3;
		}
	}
}

bool _ResizeWithMendBlack(uint8* pDst, uint8* pSrc, UINT uDstLen, UINT uSrcLen, const SIZE & dstSize, const SIZE & srcSize, UINT bpp)
{
	if(!pDst || !pSrc)
		return false;

	if(uDstLen == 0 || uDstLen != dstSize.cx * dstSize.cy * bpp)
		return false;

	if(uSrcLen == 0 || uSrcLen != srcSize.cx * srcSize.cy * bpp)
		return false;

	if(dstSize.cx < srcSize.cx)
		return false;

	if(dstSize.cy < srcSize.cy)
		return false;

	UINT dstLineblockSize = dstSize.cx * bpp;
	UINT srcLineblockSize = srcSize.cx * bpp;

	int mendCxLeftEnd = dstSize.cx > srcSize.cx ? (dstSize.cx - srcSize.cx) / 2 : 0;
	int mendCyToEnd = dstSize.cy > srcSize.cy ? (dstSize.cy - srcSize.cy) / 2 : 0;

	for(int y = 0; y < dstSize.cy; y++) 
	{
		if( y >= mendCyToEnd && y < mendCyToEnd + srcSize.cy)
		{
			if(mendCxLeftEnd > 0) 
				memcpy(pDst + (bpp * mendCxLeftEnd) , pSrc, srcLineblockSize);
			else
				memcpy(pDst, pSrc, srcLineblockSize);
			pSrc += srcLineblockSize;
		}
		pDst += dstLineblockSize;
	}
	return true;
}

void *qMalloc(size_t size)
{
	return ::malloc(size);
}
void qFree(void *ptr)
{
	::free(ptr);
}

QImage qt_fromWinHBITMAP( HDC hdc, HBITMAP bitmap, int w, int h )
{
	BITMAPINFO bmi;
	memset(&bmi, 0, sizeof(bmi));
	bmi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth       = w;
	bmi.bmiHeader.biHeight      = -h;
	bmi.bmiHeader.biPlanes      = 1;
	bmi.bmiHeader.biBitCount    = 32;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biSizeImage   = w * h * 4;

	QImage image(w, h, QImage::Format_ARGB32_Premultiplied);
	if (image.isNull())
		return image;

	// Get bitmap bits
	uchar *data = (uchar *)qMalloc(bmi.bmiHeader.biSizeImage);

	if (GetDIBits(hdc, bitmap, 0, h, data, &bmi, DIB_RGB_COLORS)) {
		// Create image and copy data into image.
		for (int y=0; y<h; ++y) {
			void *dest = (void *) image.scanLine(y);
			void *src = data + y * image.bytesPerLine();
			memcpy(dest, src, image.bytesPerLine());
		}
	} else {
		qWarning("qt_fromWinHBITMAP(), failed to get bitmap bits");
	}
	qFree(data);

	return image;
}

void ShowTips( const QString& title, const QString& desc, QWidget* parent /*= NULL */ )
{
	QMessageBox::information( parent, title, desc );
}

void ShowSucTips( const QString& desc, QWidget* parent /*= NULL*/ )
{
	QMessageBox::information( parent, "Succeed", desc );
}

void ShowErrorTips( const QString& desc, QWidget* parent /*= NULL*/ )
{
	QMessageBox::critical( parent, "Error", desc );
}

void ShowCodeErrorTips( const int code, const QString& desc, QWidget* parent /*= NULL*/, const QString& title /*= "Error"*/ )
{
	QString info;
	info += FromBits("´íÎóÂë:   ");
	info += QString::number(code);
	info += FromBits("\n´íÎóÐÅÏ¢: ");
	info += desc;
	QMessageBox::critical( parent, title, info );
}

QString getFileNameByUrl( QString szUrl )
{
	QString ret = szUrl.replace('/', '_').replace(':', '_');
	if ( ret.length()>200 )
	{
		ret = ret.right(200);
	}
	return ret;
}
