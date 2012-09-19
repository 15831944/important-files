#ifndef __NET_LAYER_HEADER_HPP
#define __NET_LAYER_HEADER_HPP



namespace i8desk
{
	
	#pragma pack(push,8)
	#pragma warning(disable:4200)

	enum 
	{
		DRP_MJ_REFRESH	= 0x01,			//ˢ������Ϊ�̣�����ֻ��һ�����Ӧ������ݿա�ֻ�ǳɹ���
		DRP_MJ_READ		= 0x02,			//�����ݣ����У����������ݵ�λ�ã�������ƫ���������Լ����ȡ�Ӧ���ʾ�ɹ�����ʧ�ܣ��ɹ�ʱҪӦ�𴫻ص����ݵĳ��ȣ������󳤶�һ���󣩡�
		DRP_MJ_WRITE	= 0x03,			//û���á�
		DRP_MJ_QUERY	= 0x04			//��ѯ������С��Ӧ����devinfo.
	};

	typedef struct tagDRP
	{
		BYTE			 MajorFunction;//1: Refresh, 2: Read, 3: Write, 4:Query.
		union
		{
			struct 
			{
				LARGE_INTEGER	Offset;
				ULONG			Length;
			}Read;
			struct 
			{
				LARGE_INTEGER   Offset;
				ULONG			Length;
			}Write;
			struct 
			{
				ULONG	DiskSize;
			}Query;
		};
		char buffer[0];
	}DRP,*LPDRP;

	typedef struct tagDSTATUS
	{
		WORD	Status;				// ����״̬
		DWORD	Information;		// �ݲ���
		DWORD	Length;				// �����ļ�����
	}DSTATUS,*LPDSTATUS;


	enum 
	{
		STATUS_SUCCESS		 = 0x0000,
		STATUS_INVALID_CALL	 = 0x2001,
		STATUS_READ_ERROR	 = 0x2002,
		STATUS_WRITE_ERROR   = 0x2003
	};


	typedef struct tagDEVINFO
	{
		UCHAR			Type;	//0:protect 1:readonly 2:read write
		LARGE_INTEGER	Size;
	}DEVINFO, *LPDEVINFO;

	#pragma pack(pop)



	// ���ݰ���С
	const size_t PACKAGE_BUFFER_SIZE = 0x10000 + sizeof(DSTATUS);


	// ���
	inline LPDSTATUS ConstructDSTATUS(char *buf, WORD status, DWORD len)
	{
		LPDSTATUS lpStatus	= reinterpret_cast<LPDSTATUS>(buf);

		lpStatus->Length		= len;
		lpStatus->Information	= len;
		lpStatus->Status		= status;

		return lpStatus;
	}

}








#endif