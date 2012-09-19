#ifndef __I8DESK_GAME_FILE_DELETOR_HPP
#define __I8DESK_GAME_FILE_DELETOR_HPP


#include "../../../include/MultiThread/Lock.hpp"
#include "../../../include/MultiThread/Thread.hpp"


namespace i8desk
{

	class DownloadEngine;
	class DelClientGame;

	// ----------------------------------------------
	// class GameFileDeletor

	// ����ָ��ɾ��������Ϸ
	class GameFileDeletor
	{
		enum { MAX_DELETE_GAME = 10 };											// ���ɾ����Ϸ��
		static const size_t DELETE_FILES_TIMEOUT = 1 * 10 * 1000;	


	private:
		IRTDataSvr *rtDataSvr_			;	// ���ݻ���ӿ�
		ISvrPlugMgr *plugMgr_			;	// ���������
		ISysOpt *sysOpt_				;	// ѡ���
		DownloadEngine *downEngine_		;	// ��������
		DelClientGame *delClient_		;	// ɾ���ͻ�����Ϸ

		async::thread::AutoEvent exit_;			// �����˳��¼�
		async::thread::AutoEvent waitHandle_;	// �ȴ��¼�
		async::thread::AutoEvent delTmpFiles_;	// ɾ����ʱĿ¼�ļ��¼�
		async::thread::ThreadImplEx thread_;

	public:
		GameFileDeletor(IRTDataSvr *rtDataSvr,  ISvrPlugMgr *plugMgr, ISysOpt *sysOpt, DownloadEngine *downEngine, DelClientGame *delClient);
		~GameFileDeletor();

	private:
		GameFileDeletor(const GameFileDeletor &);
		GameFileDeletor &operator=(const GameFileDeletor &);

		// ����ӿ�
	public:
		void Start();					// ʧ���׳��쳣
		void Stop();

		void Run();
		void DeleteTmpFiles();			// ɾ����ʱ�ļ�

	private:
		void _DeleteGame();				// ɾ������
		void _DeleteGameImpl(const std::tr1::tuple<long, stdex::tString, DWORD> &);
		void _DeleteTmpFiles();			// ɾ������������ʱ�ļ�
		void _Init();
		DWORD _Thread();
	};
}





#endif