#pragma once


//Created By ZR @ 2010-08-26
//Version 1
//this file is for virtual scsi disk network comunication protocol
//all Ver fileds are based on value 1 


// ��ǰ�汾��
enum { VER = 1 };


typedef enum _OP_CODE
{
	OP_READ=1,
	OP_WRITE,
	OP_GET_DISK_SIZE
}OP_CODE;

typedef enum _REQ_STATUS
{
	STATUS_OK=1,
	STATUS_ERR 
}REQ_STATUS;

typedef struct _OP_PARAM_STRUCT
{
	UCHAR  Ver;   //�汾��,���ݰ汾�Ž�������Param���������ݽṹ�����Ժ�I8_SCSI__NET_PROTO_REQ��Ver��һ�� 
	union Param
	{
		struct _READ
		{
			LARGE_INTEGER offset;
			LARGE_INTEGER len;
		};
		struct _WRITE
		{
			LARGE_INTEGER offset;
			LARGE_INTEGER len;
			UINT          offset_to_write;//��ʾҪд�����ݴӱ����ݽṹ��ʼλ�õ�ƫ�� 
			                              //���磬�����ݽṹ��ƫ�ƣ���I8_SCSI__NET_PROTO_REQ.op_param_offset
										  //��ֵ��Ϊ482��offset_to_writeΪ5,��ʵ��Ҫд���������������ݰ���λ��Ϊ
										  // 482+5=487
		};
	};
}OP_PARAM_STRUCT;



typedef struct  _I8_SCSI__NET_PROTO_REQ
{
	UCHAR       ver;     //�汾��,���ݰ汾�Ž���������������ݽṹ 
	REQ_STATUS  status;  //�Կͻ��˷���ȥ��������˵�����壬�ͻ��˽��շ�������ݰ�ʱ�����ֶδ���֮ǰ����������Ƿ�ɹ�      
	OP_CODE		op_code;
	UINT		packetsize; //sizeof(I8_SCSI__NET_PROTO)+op_param_len
	UINT		op_param_offset;
	UINT		op_param_len;
}I8_SCSI__NET_PROTO,*PI8_SCSI__NET_PROTO;
