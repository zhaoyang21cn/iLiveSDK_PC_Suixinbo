#pragma once
#include "bicmdcodecbase.h"
#include "xptypes.h"

namespace AVGUDT
{
    enum SumCmds
    {
        AVGUDTSubCmd_UDTDataOut                  = 0xA1,
        AVGUDTSubCmd_UDTDataOutAck               = 0xA2,
        AVGUDTSubCmd_UDTDataIn                   = 0xA4,
        AVGUDTSubCmd_UDTDataInRequestC2S         = 0xA5,
        AVGUDTSubCmd_UDTDataInRequestC2SRet      = 0xA6,
        AVGUDTSubCmd_UDTDataInResend             = 0xA8,
        AVGUDTSubCmd_UDTDataOutEmpty             = 0xA9,
        AVGUDTSubCmd_UDTDataOutEmptyAck          = 0xAA,
		AVGUDTSubCmd_UDTTestSpeed				 = 0xD5,
		AVGUDTSubCmd_UDTTestSpeedAck			 = 0xD6,

        AVGUDTSubCmd_UDTDataOut_V2                  = 0x1A1,
        AVGUDTSubCmd_UDTDataOutAck_V2               = 0x1A2,
        AVGUDTSubCmd_UDTDataIn_V2                   = 0x1A4,
        AVGUDTSubCmd_UDTDataInRequestC2S_V2         = 0x1A5,
        AVGUDTSubCmd_UDTDataInRequestC2SRet_V2      = 0x1A6,
        AVGUDTSubCmd_UDTDataInResend_V2             = 0x1A8,
        AVGUDTSubCmd_UDTDataOutEmpty_V2             = 0x1A9,
        AVGUDTSubCmd_UDTDataOutEmptyAck_V2          = 0x1AA,
        AVGUDTSubCmd_UDTTestSpeed_V2				= 0x1D5,
        AVGUDTSubCmd_UDTTestSpeedAck_V2			    = 0x1D6,
    };

    const uint8 cSTX = 0x02;
    const uint8 cETX = 0x03;
}

struct _XP_CLS UDTCodecBaseEncode :public pt_obj
{	
	UDTCodecBaseEncode();
	virtual ~UDTCodecBaseEncode();

	uint8 cSTX;

	uint16 wLen;
	uint32 dwSeq;
	uint16 wSubCmd;
	uint32 dwUin;  //uin是32位的
	uint32 dwRoomID;
	uint32 dwLocation;
	uint16 wTimeStamp;
	uint32 dwReverse;

	bi_buf bufBody;
	uint8 cETX;
};

struct _XP_CLS UDTCodecBaseDecode :public UDTCodecBaseEncode
{
    UDTCodecBaseDecode():UDTCodecBaseEncode()
    {
        this->dwSenderDeq = 0;
    }
    //uint64 u64Uin;
    uint32 dwSenderDeq;
};

//DECLARE_CMDCODEC(UDTCodecBase, UDTCodecBaseEncode, UDTCodecBaseDecode)
class _XP_CLS UDTCodecBase : public CBICmdCodecBase<UDTCodecBaseEncode, UDTCodecBaseDecode>
{ 
protected: 
        virtual void SetCodeStruct(); 
        virtual void SetDecodeStruct(UDTCodecBaseEncode* pPack_CS); 
public: 
        static boolean CreateCodec(CBICmdCodec** p) 
        { 
            (*p) = new UDTCodecBase; 
            if (NULL == (*p)) 
            { 
                return false; 
            } 
            return true; 
        } 
};

struct UDTDataOutCodec :public UDTCodecBase
{
	void SetCodeStruct()
    {
        UDTCodecBase::SetCodeStruct();
    }

	void SetDecodeStruct(UDTCodecBaseEncode*p)
	{ 
        UDTCodecBase::SetDecodeStruct(p);
		CBIPack pack;
		pack.SetBufferIn(m_pOutST->bufBody.pbuf, m_pOutST->bufBody.ulen);

		pack.Getuint16(wUploadResendFlag);
		pack.Getuint16(wAckSeqNum);

        //CBIBuffer bufSeq;

        for (uint16 u = 0; u < wAckSeqNum; u++)
        {
            uint32 uSeq = 0;
            pack.Getuint32(uSeq);

            bufSeq.Append((uint8*)&uSeq, sizeof(uSeq));
        }
	}

	uint16 wUploadResendFlag;
	uint16 wAckSeqNum;
    CBIBuffer bufSeq;
};

struct UDTDataInCodec :public UDTCodecBase
{
	void SetCodeStruct()
    {
        UDTCodecBase::SetCodeStruct();

    }

	void SetDecodeStruct(UDTCodecBaseEncode*p)
    {
        UDTCodecBase::SetDecodeStruct(p);
    }

};

struct UDTDataInRequestC2SCodec :public UDTCodecBase
{
	struct ResultList
	{
		uint32 dwUin;
		uint32 dwSeq;
	};

	void SetCodeStruct()
    {
        UDTCodecBase::SetCodeStruct();
        m_pCurPackOut->AddBuf(bufResultList);
        //CodeBufferLenHead(bufResultList, uint16);
    }

	void SetDecodeStruct(UDTCodecBaseEncode*p)
	{
        UDTCodecBase::SetDecodeStruct(p);
        CBIPack pack;
        pack.SetBufferIn(m_pOutST->bufBody.pbuf, m_pOutST->bufBody.ulen);

        pack.Getuint16(wResultNum);

        for (uint16 u = 0; u < wResultNum; u++)
        {

            uint32 dwUserAccount = 0; 
            uint32 dwUserSeq = 0; 
            uint8 cResult = 0;
            pack.Getuint32(dwUserAccount);
            pack.Getuint32(dwUserSeq);
            pack.Getuint8(cResult);

            bufResultList.Append((uint8*)&dwUserAccount, sizeof(dwUserAccount));
            bufResultList.Append((uint8*)&dwUserSeq, sizeof(dwUserSeq));

        }

	}
    uint16 wResultNum;
    uint32 dwReserve;
    CBIBuffer bufResultList;

};

struct UDTDataInResendCodec :public UDTCodecBase
{
    void SetCodeStruct()
    {
        UDTCodecBase::SetCodeStruct();

    }
	void SetDecodeStruct(UDTCodecBaseEncode*p)
    {
        UDTCodecBase::SetDecodeStruct(p);

    }
};

struct UDTDataOutEmptyCodec :public UDTCodecBase
{
	void SetCodeStruct()
    {
        UDTCodecBase::SetCodeStruct();

    }
	void SetDecodeStruct(UDTCodecBaseEncode*p)
    {
		UDTCodecBase::SetDecodeStruct(p);
        
        CBIPack pack;
        pack.SetBufferIn(m_pOutST->bufBody.pbuf, m_pOutST->bufBody.ulen);

        pack.Getuint32(dwNeedReSend);
        pack.Getuint32(dwReserve);

	}

	uint32 dwNeedReSend;
	uint32 dwReserve;

};


//UDT V2
struct _XP_CLS UDTCodecBaseEncode_V2 :public pt_obj
{	
    UDTCodecBaseEncode_V2();
    virtual ~UDTCodecBaseEncode_V2();

    uint8 cSTX;

    uint16 wLen;
    uint32 dwSeq;
    uint16 wSubCmd;
    uint64 u64Uin;  //uin是64位的
    uint32 dwRoomID;
    uint32 dwLocation;
    uint16 wTimeStamp;
    uint64 u64Reverse;
    uint8  cSeqType;//当前包的视频源类型
    uint32 dwSenderSeq;//当前包的视频源类型
    uint16 wTLVLen;//bufTLV内部TLV结构个数
    bi_buf bufTLV;//TLV/变长	tag：short    len：short，value的长度        tag值列表：

    bi_buf bufBody;
    uint8 cETX;
};

struct _XP_CLS UDTCodecBaseDecode_V2 :public UDTCodecBaseEncode_V2
{
    UDTCodecBaseDecode_V2():UDTCodecBaseEncode_V2()
    {
        this->dwSenderDeq = 0;
    }
    //uint64 u64Uin;
    uint32 dwSenderDeq;
};

//DECLARE_CMDCODEC(UDTCodecBase_V2, UDTCodecBaseEncode_V2, UDTCodecBaseDecode_V2)
class _XP_CLS UDTCodecBase_V2 : public CBICmdCodecBase<UDTCodecBaseEncode_V2, UDTCodecBaseDecode_V2>
{ 
protected: 
    virtual void SetCodeStruct(); 
    virtual void SetDecodeStruct(UDTCodecBaseEncode_V2* pPack_CS); 
public: 
    static boolean CreateCodec(CBICmdCodec** p) 
    { 
        (*p) = new UDTCodecBase_V2; 
        if (NULL == (*p)) 
        { 
            return false; 
        } 
        return true; 
    } 
};

struct UDTDataOutCodec_V2 :public UDTCodecBase_V2
{
    void SetCodeStruct()
    {
        UDTCodecBase_V2::SetCodeStruct();
    }

    void SetDecodeStruct(UDTCodecBaseEncode_V2*p)
    { 
        UDTCodecBase_V2::SetDecodeStruct(p);
        CBIPack pack;
        pack.SetBufferIn(m_pOutST->bufBody.pbuf, m_pOutST->bufBody.ulen);

        pack.Getuint16(wUploadResendFlag);
        pack.Getuint16(wAckSeqNum);

        //CBIBuffer bufSeq;

        for (uint16 u = 0; u < wAckSeqNum; u++)
        {
            uint32 uSeq = 0;
            pack.Getuint32(uSeq);

            bufSeq.Append((uint8*)&uSeq, sizeof(uSeq));
        }
    }

    uint16 wUploadResendFlag;
    uint16 wAckSeqNum;
    CBIBuffer bufSeq;
};

struct UDTDataInCodec_V2 :public UDTCodecBase_V2
{
    void SetCodeStruct()
    {
        UDTCodecBase_V2::SetCodeStruct();

    }

    void SetDecodeStruct(UDTCodecBaseEncode_V2*p)
    {
        UDTCodecBase_V2::SetDecodeStruct(p);
    }

};

struct UDTDataInRequestC2SCodec_V2 :public UDTCodecBase_V2
{
    struct ResultList
    {
        uint32 dwUin;
        uint32 dwSeq;
    };

    void SetCodeStruct()
    {
        UDTCodecBase_V2::SetCodeStruct();
        m_pCurPackOut->AddBuf(bufResultList);
        //CodeBufferLenHead(bufResultList, uint16);
    }

    void SetDecodeStruct(UDTCodecBaseEncode_V2*p)
    {
        UDTCodecBase_V2::SetDecodeStruct(p);
        CBIPack pack;
        pack.SetBufferIn(m_pOutST->bufBody.pbuf, m_pOutST->bufBody.ulen);

        pack.Getuint16(wResultNum);

        for (uint16 u = 0; u < wResultNum; u++)
        {

            uint64 ullUserAccount = 0; 
            uint8 cSubType = 0;
            uint32 dwUserSeq = 0; 
            uint8 cResult = 0;
            pack.Getuint64(ullUserAccount);
            pack.Getuint8(cSubType);
            pack.Getuint32(dwUserSeq);
            pack.Getuint8(cResult);

            bufResultList.Append((uint8*)&ullUserAccount, sizeof(uint64));
            bufResultList.Append((uint8*)&cSubType, sizeof(uint8));
            bufResultList.Append((uint8*)&dwUserSeq, sizeof(uint32));
            bufResultList.Append((uint8*)&cResult, sizeof(uint8));
        }

    }
    uint16 wResultNum;
    uint32 dwReserve;
    CBIBuffer bufResultList;

};

struct UDTDataInResendCodec_V2 :public UDTCodecBase_V2
{
    void SetCodeStruct()
    {
        UDTCodecBase_V2::SetCodeStruct();

    }
    void SetDecodeStruct(UDTCodecBaseEncode_V2*p)
    {
        UDTCodecBase_V2::SetDecodeStruct(p);

    }
};

struct UDTDataOutEmptyCodec_V2 :public UDTCodecBase_V2
{
    void SetCodeStruct()
    {
        UDTCodecBase_V2::SetCodeStruct();

    }
    void SetDecodeStruct(UDTCodecBaseEncode_V2*p)
    {
        UDTCodecBase_V2::SetDecodeStruct(p);

        CBIPack pack;
        pack.SetBufferIn(m_pOutST->bufBody.pbuf, m_pOutST->bufBody.ulen);

        pack.Getuint32(dwNeedReSend);
        pack.Getuint32(dwReserve);

    }

    uint32 dwNeedReSend;
    uint32 dwReserve;

};
