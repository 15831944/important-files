#include "stdafx.h"
#include "ConfigBusiness.h"

#include "../../../../include/Utility/utility.h"
#include <map>


namespace i8desk
{
	namespace business
	{
		namespace config
		{
			struct AreaInfo
			{
				size_t ParentID;
				size_t SelfID;
				TCHAR Name[MAX_PATH];

				AreaInfo()
				{
					memset(this, 0, sizeof(*this));
				}
				template < typename T, size_t N >
				AreaInfo(size_t parentID, size_t selfID, T (&arr)[N])
					: ParentID(parentID)
					, SelfID(selfID)
				{
					utility::Strcpy(Name, arr);
				}
			};

			typedef std::map<size_t, AreaInfo> ProvinceInfo;
			typedef std::map<size_t, AreaInfo> CityInfo;
			ProvinceInfo Provience;
			CityInfo City;

			static struct InitArea
			{
				InitArea()
				{
					Provience[110000] = AreaInfo(0, 110000, _T("����"));
					Provience[500000] = AreaInfo(0, 500000, _T("����"));
					Provience[350000] = AreaInfo(0, 350000, _T("����"));
					Provience[620000] = AreaInfo(0, 620000, _T("����"));
					Provience[440000] = AreaInfo(0, 440000, _T("�㶫"));
					Provience[450000] = AreaInfo(0, 450000, _T("����"));
					Provience[520000] = AreaInfo(0, 520000, _T("����"));
					Provience[460000] = AreaInfo(0, 460000, _T("����"));
					Provience[130000] = AreaInfo(0, 130000, _T("�ӱ�"));
					Provience[410000] = AreaInfo(0, 410000, _T("����"));
					Provience[230000] = AreaInfo(0, 230000, _T("������"));
					Provience[420000] = AreaInfo(0, 420000, _T("����"));
					Provience[430000] = AreaInfo(0, 430000, _T("����"));
					Provience[220000] = AreaInfo(0, 220000, _T("����"));
					Provience[320000] = AreaInfo(0, 320000, _T("����"));
					Provience[360000] = AreaInfo(0, 360000, _T("����"));
					Provience[210000] = AreaInfo(0, 210000, _T("����"));
					Provience[150000] = AreaInfo(0, 150000, _T("���ɹ�"));
					Provience[640000] = AreaInfo(0, 640000, _T("����"));
					Provience[630000] = AreaInfo(0, 630000, _T("�ຣ"));
					Provience[370000] = AreaInfo(0, 370000, _T("ɽ��"));
					Provience[140000] = AreaInfo(0, 140000, _T("ɽ��"));
					Provience[610000] = AreaInfo(0, 610000, _T("����"));
					Provience[310000] = AreaInfo(0, 310000, _T("�Ϻ�"));
					Provience[510000] = AreaInfo(0, 510000, _T("�Ĵ�"));
					Provience[120000] = AreaInfo(0, 120000, _T("���"));
					Provience[540000] = AreaInfo(0, 540000, _T("����"));
					Provience[650000] = AreaInfo(0, 650000, _T("�½�"));
					Provience[530000] = AreaInfo(0, 530000, _T("����"));
					Provience[330000] = AreaInfo(0, 330000, _T("�㽭"));
					Provience[340000] = AreaInfo(0, 340000, _T("����"));
					Provience[1000000] = AreaInfo(0, 1000000, _T("����"));
					Provience[2000000] = AreaInfo(0, 2000000, _T("OEMר������"));


					//---ws

					City[230600] = AreaInfo(230000, 230600, _T("����"));
					City[232700] = AreaInfo(230000, 232700, _T("���˰���"));
					City[230100] = AreaInfo(230000, 230100, _T("������"));
					City[230400] = AreaInfo(230000, 230400, _T("�׸�"));
					City[231100] = AreaInfo(230000, 231100, _T("�ں�"));
					City[230300] = AreaInfo(230000, 230300, _T("����"));
					City[230800] = AreaInfo(230000, 230800, _T("��ľ˹"));
					City[231000] = AreaInfo(230000, 231000, _T("ĵ����"));
					City[230900] = AreaInfo(230000, 230900, _T("��̨��"));
					City[230200] = AreaInfo(230000, 230200, _T("�������"));
					City[230500] = AreaInfo(230000, 230500, _T("˫Ѽɽ"));
					City[231200] = AreaInfo(230000, 231200, _T("�绯"));
					City[230700] = AreaInfo(230000, 230700, _T("����"));
					City[420700] = AreaInfo(420000, 420700, _T("����"));
					City[422800] = AreaInfo(420000, 422800, _T("��ʩ����������������"));
					City[421100] = AreaInfo(420000, 421100, _T("�Ƹ�"));
					City[420200] = AreaInfo(420000, 420200, _T("��ʯ"));
					City[420800] = AreaInfo(420000, 420800, _T("����"));
					City[421000] = AreaInfo(420000, 421000, _T("����"));
					City[429000] = AreaInfo(420000, 429000, _T("ʡֱϽ"));
					City[420200] = AreaInfo(420000, 420200, _T("��ʯ"));
					City[420800] = AreaInfo(420000, 420800, _T("����"));
					City[421000] = AreaInfo(420000, 421000, _T("����"));
					City[429000] = AreaInfo(420000, 429000, _T("ʡֱϽ"));
					City[420300] = AreaInfo(420000, 420300, _T("ʮ��"));
					City[421300] = AreaInfo(420000, 421300, _T("����"));
					City[420100] = AreaInfo(420000, 420100, _T("�人"));
					City[421200] = AreaInfo(420000, 421200, _T("����"));
					City[420600] = AreaInfo(420000, 420600, _T("�差"));
					City[420900] = AreaInfo(420000, 420900, _T("Т��"));
					City[420500] = AreaInfo(420000, 420500, _T("�˲�"));
					City[430700] = AreaInfo(430000, 430700, _T("����"));
					City[430100] = AreaInfo(430000, 430100, _T("��ɳ"));
					City[431000] = AreaInfo(430000, 431000, _T("����"));
					City[430400] = AreaInfo(430000, 430400, _T("����"));
					City[431200] = AreaInfo(430000, 431200, _T("����"));
					City[431300] = AreaInfo(430000, 431300, _T("¦��"));
					City[430500] = AreaInfo(430000, 430500, _T("����"));
					City[430300] = AreaInfo(430000, 430300, _T("��̶"));
					City[433100] = AreaInfo(430000, 433100, _T("��������������������"));
					City[430900] = AreaInfo(430000, 430900, _T("����"));
					City[431100] = AreaInfo(430000, 431100, _T("����"));
					City[430600] = AreaInfo(430000, 430600, _T("����"));
					City[430800] = AreaInfo(430000, 430800, _T("�żҽ�"));
					City[430200] = AreaInfo(430000, 430200, _T("����"));
					City[220800] = AreaInfo(220000, 220800, _T("�׳�"));
					City[220600] = AreaInfo(220000, 220600, _T("��ɽ"));
					City[220100] = AreaInfo(220000, 220100, _T("����"));
					City[220200] = AreaInfo(220000, 220200, _T("����"));
					City[220400] = AreaInfo(220000, 220400, _T("��Դ"));
					City[220300] = AreaInfo(220000, 220300, _T("��ƽ"));
					City[220700] = AreaInfo(220000, 220700, _T("��ԭ"));
					City[220500] = AreaInfo(220000, 220500, _T("ͨ��"));
					City[222400] = AreaInfo(220000, 222400, _T("�ӱ߳�����������"));
					City[320400] = AreaInfo(320000, 320400, _T("����"));
					City[320800] = AreaInfo(320000, 320800, _T("����"));
					City[320700] = AreaInfo(320000, 320700, _T("���Ƹ�"));
					City[320100] = AreaInfo(320000, 320100, _T("�Ͼ�"));
					City[320600] = AreaInfo(320000, 320600, _T("��ͨ"));
					City[320500] = AreaInfo(320000, 320500, _T("����"));
					City[321300] = AreaInfo(320000, 321300, _T("��Ǩ"));
					City[321200] = AreaInfo(320000, 321200, _T("̩��"));
					City[320200] = AreaInfo(320000, 320200, _T("����"));
					City[320300] = AreaInfo(320000, 320300, _T("����"));
					City[320900] = AreaInfo(320000, 320900, _T("�γ�"));
					City[321000] = AreaInfo(320000, 321000, _T("����"));
					City[321100] = AreaInfo(320000, 321100, _T("��"));
					City[361000] = AreaInfo(360000, 361000, _T("����"));
					City[360700] = AreaInfo(360000, 360700, _T("����"));
					City[360800] = AreaInfo(360000, 360800, _T("����"));
					City[360200] = AreaInfo(360000, 360200, _T("������"));
					City[360400] = AreaInfo(360000, 360400, _T("�Ž�"));
					City[360100] = AreaInfo(360000, 360100, _T("�ϲ�"));
					City[360300] = AreaInfo(360000, 360300, _T("Ƽ��"));
					City[361100] = AreaInfo(360000, 361100, _T("����"));
					City[360500] = AreaInfo(360000, 360500, _T("����"));
					City[360900] = AreaInfo(360000, 360900, _T("�˴�"));
					City[360600] = AreaInfo(360000, 360600, _T("ӥ̶"));
					City[210300] = AreaInfo(210000, 210300, _T("��ɽ"));
					City[210500] = AreaInfo(210000, 210500, _T("��Ϫ"));
					City[211300] = AreaInfo(210000, 211300, _T("����"));
					City[210200] = AreaInfo(210000, 210200, _T("����"));
					City[210600] = AreaInfo(210000, 210600, _T("����"));
					City[210400] = AreaInfo(210000, 210400, _T("��˳"));
					City[210900] = AreaInfo(210000, 210900, _T("����"));
					City[211400] = AreaInfo(210000, 211400, _T("��«��"));
					City[210700] = AreaInfo(210000, 210700, _T("����"));
					City[211000] = AreaInfo(210000, 211000, _T("����"));
					City[211100] = AreaInfo(210000, 211100, _T("�̽�"));
					City[210100] = AreaInfo(210000, 210100, _T("����"));
					City[211200] = AreaInfo(210000, 211200, _T("����"));
					City[210800] = AreaInfo(210000, 210800, _T("Ӫ��"));
					City[152900] = AreaInfo(150000, 152900, _T("��������"));
					City[150800] = AreaInfo(150000, 150800, _T("�����׶���"));
					City[150200] = AreaInfo(150000, 150200, _T("��ͷ"));
					City[150400] = AreaInfo(150000, 150400, _T("���"));
					City[150600] = AreaInfo(150000, 150600, _T("������˹"));
					City[150100] = AreaInfo(150000, 150100, _T("���ͺ���"));
					City[150700] = AreaInfo(150000, 150700, _T("���ױ���"));
					City[150500] = AreaInfo(150000, 150500, _T("ͨ��"));
					City[150300] = AreaInfo(150000, 150300, _T("�ں�"));
					City[150900] = AreaInfo(150000, 150900, _T("�����첼��"));
					City[152500] = AreaInfo(150000, 152500, _T("���ֹ�����"));
					City[152200] = AreaInfo(150000, 152200, _T("�˰���"));
					City[640400] = AreaInfo(640000, 640400, _T("��ԭ"));
					City[640200] = AreaInfo(640000, 640200, _T("ʯ��ɽ"));
					City[640300] = AreaInfo(640000, 640300, _T("����"));
					City[640100] = AreaInfo(640000, 640100, _T("����"));
					City[640500] = AreaInfo(640000, 640500, _T("����"));
					City[632600] = AreaInfo(630000, 632600, _T("�������������"));
					City[632200] = AreaInfo(630000, 632200, _T("��������������"));
					City[632100] = AreaInfo(630000, 632100, _T("����"));
					City[632500] = AreaInfo(630000, 632500, _T("���ϲ���������"));
					City[632800] = AreaInfo(630000, 632800, _T("�����ɹ������������"));
					City[632300] = AreaInfo(630000, 632300, _T("���ϲ���������"));
					City[630100] = AreaInfo(630000, 630100, _T("����"));
					City[632700] = AreaInfo(630000, 632700, _T("��������������"));
					City[371600] = AreaInfo(370000, 371600, _T("����"));
					City[371400] = AreaInfo(370000, 371400, _T("����"));
					City[370500] = AreaInfo(370000, 370500, _T("��Ӫ"));
					City[371700] = AreaInfo(370000, 371700, _T("����"));
					City[370100] = AreaInfo(370000, 370100, _T("����"));
					City[370800] = AreaInfo(370000, 370800, _T("����"));
					City[371200] = AreaInfo(370000, 371200, _T("����"));
					City[371500] = AreaInfo(370000, 371500, _T("�ĳ�"));
					City[371300] = AreaInfo(370000, 371300, _T("����"));
					City[370200] = AreaInfo(370000, 370200, _T("�ൺ"));
					City[371100] = AreaInfo(370000, 371100, _T("����"));
					City[370900] = AreaInfo(370000, 370900, _T("̩��"));
					City[371000] = AreaInfo(370000, 371000, _T("����"));
					City[370700] = AreaInfo(370000, 370700, _T("Ϋ��"));
					City[370600] = AreaInfo(370000, 370600, _T("��̨"));
					City[370400] = AreaInfo(370000, 370400, _T("��ׯ"));
					City[370300] = AreaInfo(370000, 370300, _T("�Ͳ�"));
					City[140400] = AreaInfo(140000, 140400, _T("����"));
					City[140200] = AreaInfo(140000, 140200, _T("��ͬ"));
					City[140500] = AreaInfo(140000, 140500, _T("����"));
					City[140700] = AreaInfo(140000, 140700, _T("����"));
					City[141000] = AreaInfo(140000, 141000, _T("�ٷ�"));
					City[141100] = AreaInfo(140000, 141100, _T("����"));
					City[140600] = AreaInfo(140000, 140600, _T("˷��"));
					City[140100] = AreaInfo(140000, 140100, _T("̫ԭ"));
					City[140900] = AreaInfo(140000, 140900, _T("����"));
					City[140300] = AreaInfo(140000, 140300, _T("��Ȫ"));
					City[140800] = AreaInfo(140000, 140800, _T("�˳�"));
					City[610900] = AreaInfo(610000, 610900, _T("����"));
					City[610300] = AreaInfo(610000, 610300, _T("����"));
					City[610700] = AreaInfo(610000, 610700, _T("����"));
					City[611000] = AreaInfo(610000, 611000, _T("����"));
					City[610200] = AreaInfo(610000, 610200, _T("ͭ��"));
					City[610500] = AreaInfo(610000, 610500, _T("μ��"));
					City[610100] = AreaInfo(610000, 610100, _T("����"));
					City[610400] = AreaInfo(610000, 610400, _T("����"));
					City[610600] = AreaInfo(610000, 610600, _T("�Ӱ�"));
					City[610800] = AreaInfo(610000, 610800, _T("����"));
					City[310101] = AreaInfo(310000, 310101, _T("����"));
					City[310103] = AreaInfo(310000, 310103, _T("¬��"));
					City[310104] = AreaInfo(310000, 310104, _T("���"));
					City[310105] = AreaInfo(310000, 310105, _T("����"));
					City[310106] = AreaInfo(310000, 310106, _T("����"));
					City[310107] = AreaInfo(310000, 310107, _T("����"));
					City[310108] = AreaInfo(110000, 310108, _T("բ��"));
					City[310109] = AreaInfo(310000, 310109, _T("���"));
					City[310110] = AreaInfo(310000, 310110, _T("����"));
					City[310112] = AreaInfo(310000, 310112, _T("����"));
					City[310113] = AreaInfo(310000, 310113, _T("��ɽ"));
					City[310114] = AreaInfo(310000, 310114, _T("�ζ�"));
					City[310115] = AreaInfo(310000, 310115, _T("�ֶ�����"));
					City[310116] = AreaInfo(310000, 310116, _T("��ɽ"));
					City[310117] = AreaInfo(310000, 310117, _T("�ɽ�"));
					City[310118] = AreaInfo(310000, 310118, _T("����"));
					City[310119] = AreaInfo(310000, 310119, _T("�ϻ�"));
					City[310120] = AreaInfo(310000, 310120, _T("����"));
					City[310230] = AreaInfo(310000, 310230, _T("����"));




					//----gh
					City[513200] = AreaInfo(510000, 513200, _T("���Ӳ���Ǽ��������"));
					City[511900] = AreaInfo(510000, 511900, _T("����"));
					City[510100] = AreaInfo(510000, 510100, _T("�ɶ�"));
					City[511700] = AreaInfo(510000, 511700, _T("����"));
					City[510600] = AreaInfo(510000, 510600, _T("����"));
					City[513300] = AreaInfo(510000, 513300, _T("���β���������"));
					City[511600] = AreaInfo(510000, 511600, _T("�㰲"));
					City[510800] = AreaInfo(510000, 510800, _T("��Ԫ"));
					City[511100] = AreaInfo(510000, 511100, _T("��ɽ"));
					City[513400] = AreaInfo(510000, 513400, _T("��ɽ����������"));
					City[511400] = AreaInfo(510000, 511400, _T("üɽ"));
					City[510700] = AreaInfo(510000, 510700, _T("����"));
					City[511300] = AreaInfo(510000, 511300, _T("�ϳ�"));
					City[511000] = AreaInfo(510000, 511000, _T("�ڽ�"));
					City[510400] = AreaInfo(510000, 510400, _T("��֦��"));
					City[510900] = AreaInfo(510000, 510900, _T("����"));
					City[511800] = AreaInfo(510000, 511800, _T("�Ű�"));
					City[511500] = AreaInfo(510000, 511500, _T("�˱�"));
					City[512000] = AreaInfo(510000, 512000, _T("����"));
					City[510300] = AreaInfo(510000, 510300, _T("�Թ�"));
					City[510500] = AreaInfo(510000, 510500, _T("����"));
					City[120101] = AreaInfo(120000, 120101, _T("��ƽ"));
					City[120102] = AreaInfo(120000, 120102, _T("�Ӷ�"));
					City[120103] = AreaInfo(120000, 120103, _T("����"));
					City[120104] = AreaInfo(120000, 120104, _T("�Ͽ�"));
					City[120105] = AreaInfo(120000, 120105, _T("�ӱ�"));
					City[120106] = AreaInfo(120000, 120106, _T("����"));
					City[120107] = AreaInfo(120000, 120107, _T("����"));
					City[120108] = AreaInfo(120000, 120108, _T("����"));
					City[120109] = AreaInfo(120000, 120109, _T("���"));
					City[120110] = AreaInfo(120000, 120110, _T("����"));
					City[120111] = AreaInfo(120000, 120111, _T("����"));
					City[120112] = AreaInfo(120000, 120112, _T("����"));
					City[120113] = AreaInfo(120000, 120113, _T("����"));
					City[120114] = AreaInfo(120000, 120114, _T("����"));
					City[120115] = AreaInfo(120000, 120115, _T("����"));
					City[120221] = AreaInfo(120000, 120221, _T("����"));
					City[120223] = AreaInfo(120000, 120223, _T("����"));
					City[120225] = AreaInfo(120000, 120225, _T("����"));
					City[542500] = AreaInfo(540000, 542500, _T("����"));
					City[542100] = AreaInfo(540000, 542100, _T("����"));
					City[540100] = AreaInfo(540000, 540100, _T("����"));
					City[542600] = AreaInfo(540000, 542600, _T("��֥"));
					City[542400] = AreaInfo(540000, 542400, _T("����"));
					City[542300] = AreaInfo(540000, 542300, _T("�տ���"));
					City[542200] = AreaInfo(540000, 542200, _T("ɽ��"));
					City[652900] = AreaInfo(650000, 652900, _T("������"));
					City[654200] = AreaInfo(650000, 654200, _T("����"));
					City[652800] = AreaInfo(650000, 652800, _T("���������ɹ�������"));
					City[652700] = AreaInfo(650000, 652700, _T("���������ɹ�������"));
					City[652300] = AreaInfo(650000, 652300, _T("��������������"));
					City[652200] = AreaInfo(650000, 652200, _T("����"));
					City[653200] = AreaInfo(650000, 653200, _T("����"));
					City[653100] = AreaInfo(650000, 653100, _T("��ʲ"));
					City[650200] = AreaInfo(650000, 650200, _T("��������"));
					City[653000] = AreaInfo(650000, 653000, _T("�������տ¶�����������"));
					City[654300] = AreaInfo(650000, 654300, _T("����̩"));
					City[659000] = AreaInfo(650000, 659000, _T("ʡֱϽ"));
					City[652100] = AreaInfo(650000, 652100, _T("��³��"));
					City[650100] = AreaInfo(650000, 650100, _T("��³ľ��"));
					City[654000] = AreaInfo(650000, 654000, _T("���������������"));
					City[530500] = AreaInfo(530000, 530500, _T("��ɽ"));
					City[532300] = AreaInfo(530000, 532300, _T("��������������"));
					City[532900] = AreaInfo(530000, 532900, _T("�������������"));
					City[533100] = AreaInfo(530000, 533100, _T("�º���徰����������"));
					City[533400] = AreaInfo(530000, 533400, _T("�������������"));
					City[532500] = AreaInfo(530000, 532500, _T("��ӹ���������������"));
					City[530100] = AreaInfo(530000, 530100, _T("����"));
					City[530700] = AreaInfo(530000, 530700, _T("����"));
					City[530900] = AreaInfo(530000, 530900, _T("�ٲ�"));
					City[533300] = AreaInfo(530000, 533300, _T("ŭ��������������"));
					City[530300] = AreaInfo(530000, 530300, _T("����"));
					City[530800] = AreaInfo(530000, 530800, _T("˼é"));
					City[532600] = AreaInfo(530000, 532600, _T("��ɽ׳������������"));
					City[532800] = AreaInfo(530000, 532800, _T("��˫���ɴ���������"));
					City[530400] = AreaInfo(530000, 530400, _T("��Ϫ"));
					City[530600] = AreaInfo(530000, 530600, _T("��ͨ"));
					City[330100] = AreaInfo(330000, 330100, _T("����"));
					City[330500] = AreaInfo(330000, 330500, _T("����"));
					City[330400] = AreaInfo(330000, 330400, _T("����"));
					City[330700] = AreaInfo(330000, 330700, _T("��"));
					City[331100] = AreaInfo(330000, 331100, _T("��ˮ"));
					City[330200] = AreaInfo(330000, 330200, _T("����"));
					City[330600] = AreaInfo(330000, 330600, _T("����"));
					City[331000] = AreaInfo(330000, 331000, _T("̨��"));
					City[330300] = AreaInfo(330000, 330300, _T("����"));
					City[330900] = AreaInfo(330000, 330900, _T("��ɽ"));
					City[330800] = AreaInfo(330000, 330800, _T("����"));
					City[340800] = AreaInfo(340000, 340800, _T("����"));
					City[340300] = AreaInfo(340000, 340300, _T("����"));
					City[341400] = AreaInfo(340000, 341400, _T("����"));
					City[341700] = AreaInfo(340000, 341700, _T("����"));
					City[341100] = AreaInfo(340000, 341100, _T("����"));
					City[341200] = AreaInfo(340000, 341200, _T("����"));
					City[340100] = AreaInfo(340000, 340100, _T("�Ϸ�"));
					City[340600] = AreaInfo(340000, 340600, _T("����"));
					City[340400] = AreaInfo(340000, 340400, _T("����"));
					City[341000] = AreaInfo(340000, 341000, _T("��ɽ"));
					City[341500] = AreaInfo(340000, 341500, _T("����"));
					City[340500] = AreaInfo(340000, 340500, _T("��ɽ"));
					City[341300] = AreaInfo(340000, 341300, _T("����"));
					City[340700] = AreaInfo(340000, 340700, _T("ͭ��"));
					City[340200] = AreaInfo(340000, 340200, _T("�ߺ�"));
					City[341800] = AreaInfo(340000, 341800, _T("����"));
					City[341600] = AreaInfo(340000, 341600, _T("����"));
					City[1000001] = AreaInfo(1000000, 1000001, _T("��������"));
					City[1000002] = AreaInfo(1000000, 1000002, _T("̩��"));
					City[1000003] = AreaInfo(1000000, 1000003, _T("ӡ��������"));
					City[1000004] = AreaInfo(1000000, 1000004, _T("�¼���"));
					City[1000005] = AreaInfo(1000000, 1000005, _T("����"));
					City[1000006] = AreaInfo(1000000, 1000006, _T("����"));
					City[2000001] = AreaInfo(2000000, 2000001, _T("����"));
					City[2000002] = AreaInfo(2000000, 2000002, _T("�Ϻ�"));
					City[2000003] = AreaInfo(2000000, 2000003, _T("���"));
					City[2000004] = AreaInfo(2000000, 2000004, _T("����"));
					City[2000005] = AreaInfo(2000000, 2000005, _T("����"));
					City[2000006] = AreaInfo(2000000, 2000006, _T("�㶫"));
					City[2000007] = AreaInfo(2000000, 2000007, _T("����"));
					City[2000008] = AreaInfo(2000000, 2000008, _T("�ӱ�"));
					City[2000009] = AreaInfo(2000000, 2000009, _T("����"));
					City[2000010] = AreaInfo(2000000, 2000010, _T("ɽ��"));
					City[2000011] = AreaInfo(2000000, 2000011, _T("����"));
					City[2000012] = AreaInfo(2000000, 2000012, _T("������"));
					City[2000013] = AreaInfo(2000000, 2000013, _T("����"));
					City[2000014] = AreaInfo(2000000, 2000014, _T("����"));
					City[2000015] = AreaInfo(2000000, 2000015, _T("���ɹ�"));
					City[2000016] = AreaInfo(2000000, 2000016, _T("�㽭"));
					City[2000017] = AreaInfo(2000000, 2000017, _T("����"));
					City[2000018] = AreaInfo(2000000, 2000018, _T("����"));
					City[2000019] = AreaInfo(2000000, 2000019, _T("����"));
					City[2000020] = AreaInfo(2000000, 2000020, _T("����"));
					City[2000021] = AreaInfo(2000000, 2000021, _T("����"));
					City[2000022] = AreaInfo(2000000, 2000022, _T("����"));
					City[2000023] = AreaInfo(2000000, 2000023, _T("�½�"));
					City[2000024] = AreaInfo(2000000, 2000024, _T("ɽ��"));
					City[2000025] = AreaInfo(2000000, 2000025, _T("����"));
					City[2000026] = AreaInfo(2000000, 2000026, _T("����"));
					City[2000027] = AreaInfo(2000000, 2000027, _T("����"));
					City[2000028] = AreaInfo(2000000, 2000028, _T("����"));
					City[2000029] = AreaInfo(2000000, 2000029, _T("�ຣ"));
					City[2000030] = AreaInfo(2000000, 2000030, _T("�Ĵ�"));
					City[2000031] = AreaInfo(2000000, 2000031, _T("����"));





					//---yp

					City[110101] = AreaInfo(110000, 110101, _T("����"));
					City[110102] = AreaInfo(110000, 110102, _T("����"));
					City[110103] = AreaInfo(110000, 110103, _T("����"));
					City[110104] = AreaInfo(110000, 110104, _T("����"));
					City[110105] = AreaInfo(110000, 110105, _T("����"));
					City[110106] = AreaInfo(110000, 110106, _T("��̨"));
					City[110107] = AreaInfo(110000, 110107, _T("ʯ��ɽ"));
					City[110108] = AreaInfo(110000, 110108, _T("����"));
					City[110109] = AreaInfo(110000, 110109, _T("��ͷ��"));
					City[110111] = AreaInfo(110000, 110111, _T("��ɽ"));
					City[110112] = AreaInfo(110000, 110112, _T("ͨ��"));
					City[110113] = AreaInfo(110000, 110113, _T("˳��"));
					City[110114] = AreaInfo(110000, 110114, _T("��ƽ"));
					City[110115] = AreaInfo(110000, 110115, _T("����"));
					City[110116] = AreaInfo(110000, 110116, _T("����"));
					City[110117] = AreaInfo(110000, 110117, _T("ƽ��"));
					City[110228] = AreaInfo(110000, 110228, _T("����"));
					City[110229] = AreaInfo(110000, 110229, _T("����"));

					City[500101] = AreaInfo(500000, 500101, _T("����"));
					City[500102] = AreaInfo(500000, 500102, _T("����"));
					City[500103] = AreaInfo(500000, 500103, _T("������"));
					City[500104] = AreaInfo(500000, 500104, _T("��ɿ�"));
					City[500105] = AreaInfo(500000, 500105, _T("����"));
					City[500106] = AreaInfo(500000, 500106, _T("ɳƺ��"));
					City[500107] = AreaInfo(500000, 500107, _T("������"));
					City[500108] = AreaInfo(500000, 500108, _T("�ϰ�"));
					City[500109] = AreaInfo(500000, 500109, _T("����"));
					City[500110] = AreaInfo(500000, 500110, _T("��ʢ"));
					City[500111] = AreaInfo(500000, 500111, _T("˫��"));
					City[500112] = AreaInfo(500000, 500112, _T("�山"));
					City[500113] = AreaInfo(500000, 500113, _T("����"));
					City[500114] = AreaInfo(500000, 500114, _T("ǭ��"));
					City[500115] = AreaInfo(500000, 500115, _T("����"));
					City[500222] = AreaInfo(500000, 500222, _T("�뽭"));
					City[500223] = AreaInfo(500000, 500223, _T("����"));
					City[500224] = AreaInfo(500000, 500224, _T("ͭ��"));
					City[500225] = AreaInfo(500000, 500225, _T("����"));
					City[500226] = AreaInfo(500000, 500226, _T("�ٲ�"));
					City[500227] = AreaInfo(500000, 500227, _T("�ɽ"));
					City[500228] = AreaInfo(500000, 500228, _T("��ƽ"));
					City[500229] = AreaInfo(500000, 500229, _T("�ǿ�"));
					City[500230] = AreaInfo(500000, 500230, _T("�ᶼ"));
					City[500231] = AreaInfo(500000, 500231, _T("�潭"));
					City[500232] = AreaInfo(500000, 500232, _T("��¡"));
					City[500233] = AreaInfo(500000, 500233, _T("����"));
					City[500234] = AreaInfo(500000, 500234, _T("����"));
					City[500235] = AreaInfo(500000, 500235, _T("����"));
					City[500236] = AreaInfo(500000, 500236, _T("���"));
					City[500237] = AreaInfo(500000, 500237, _T("��ɽ"));
					City[500238] = AreaInfo(500000, 500238, _T("��Ϫ"));
					City[500240] = AreaInfo(500000, 500240, _T("ʯ��"));
					City[500241] = AreaInfo(500000, 500241, _T("��ɽ"));
					City[500242] = AreaInfo(500000, 500242, _T("����"));
					City[500243] = AreaInfo(500000, 500243, _T("��ˮ"));
					City[500381] = AreaInfo(500000, 500381, _T("����"));
					City[500382] = AreaInfo(500000, 500382, _T("�ϴ�"));
					City[500383] = AreaInfo(500000, 500383, _T("����"));
					City[500384] = AreaInfo(500000, 500384, _T("�ϴ�"));

					City[350100] = AreaInfo(350000, 350100, _T("����"));
					City[350800] = AreaInfo(350000, 350800, _T("����"));
					City[350700] = AreaInfo(350000, 350700, _T("��ƽ"));
					City[350900] = AreaInfo(350000, 350900, _T("����"));
					City[350300] = AreaInfo(350000, 350300, _T("����"));
					City[350500] = AreaInfo(350000, 350500, _T("Ȫ��"));
					City[350400] = AreaInfo(350000, 350400, _T("����"));
					City[350200] = AreaInfo(350000, 350200, _T("����"));
					City[350600] = AreaInfo(350000, 350600, _T("����"));

					City[620400] = AreaInfo(620000, 620400, _T("����"));
					City[621100] = AreaInfo(620000, 621100, _T("����"));
					City[623000] = AreaInfo(620000, 623000, _T("���ϲ���������"));
					City[620200] = AreaInfo(620000, 620200, _T("������"));
					City[620300] = AreaInfo(620000, 620300, _T("���"));
					City[620900] = AreaInfo(620000, 620900, _T("��Ȫ"));
					City[620100] = AreaInfo(620000, 620100, _T("����"));
					City[622900] = AreaInfo(620000, 622900, _T("���Ļ���������"));
					City[621200] = AreaInfo(620000, 621200, _T("¤��"));
					City[620800] = AreaInfo(620000, 620800, _T("ƽ��"));
					City[621000] = AreaInfo(620000, 621000, _T("����"));
					City[620500] = AreaInfo(620000, 620500, _T("��ˮ"));
					City[620600] = AreaInfo(620000, 620600, _T("����"));
					City[620700] = AreaInfo(620000, 620700, _T("��Ҵ"));

					City[445100] = AreaInfo(440000, 445100, _T("����"));
					City[441900] = AreaInfo(440000, 441900, _T("��ݸ"));
					City[440600] = AreaInfo(440000, 440600, _T("��ɽ"));
					City[440100] = AreaInfo(440000, 440100, _T("����"));
					City[441600] = AreaInfo(440000, 441600, _T("��Դ"));
					City[441300] = AreaInfo(440000, 441300, _T("����"));
					City[440700] = AreaInfo(440000, 440700, _T("����"));
					City[445200] = AreaInfo(440000, 445200, _T("����"));
					City[440900] = AreaInfo(440000, 440900, _T("ï��"));
					City[441400] = AreaInfo(440000, 441400, _T("÷��"));
					City[441800] = AreaInfo(440000, 441800, _T("��Զ"));
					City[440500] = AreaInfo(440000, 440500, _T("��ͷ"));
					City[441500] = AreaInfo(440000, 441500, _T("��β"));
					City[440200] = AreaInfo(440000, 440200, _T("�ع�"));
					City[440300] = AreaInfo(440000, 440300, _T("����"));
					City[441700] = AreaInfo(440000, 441700, _T("����"));
					City[445300] = AreaInfo(440000, 445300, _T("�Ƹ�"));
					City[440800] = AreaInfo(440000, 440800, _T("տ��"));
					City[441200] = AreaInfo(440000, 441200, _T("����"));
					City[442000] = AreaInfo(440000, 442000, _T("��ɽ"));
					City[440400] = AreaInfo(440000, 440400, _T("�麣"));

					City[451000] = AreaInfo(450000, 451000, _T("��ɫ"));
					City[450500] = AreaInfo(450000, 450500, _T("����"));
					City[451400] = AreaInfo(450000, 451400, _T("����"));
					City[450600] = AreaInfo(450000, 450600, _T("���Ǹ�"));
					City[450300] = AreaInfo(450000, 450300, _T("����"));
					City[450800] = AreaInfo(450000, 450800, _T("���"));
					City[451200] = AreaInfo(450000, 451200, _T("�ӳ�"));
					City[451100] = AreaInfo(450000, 451100, _T("����"));
					City[451300] = AreaInfo(450000, 451300, _T("����"));
					City[450200] = AreaInfo(450000, 450200, _T("����"));
					City[450100] = AreaInfo(450000, 450100, _T("����"));
					City[450700] = AreaInfo(450000, 450700, _T("����"));
					City[450400] = AreaInfo(450000, 450400, _T("����"));
					City[450900] = AreaInfo(450000, 450900, _T("����"));

					City[520400] = AreaInfo(520000, 520400, _T("��˳"));
					City[522400] = AreaInfo(520000, 522400, _T("�Ͻ�"));
					City[520100] = AreaInfo(520000, 520100, _T("����"));
					City[520200] = AreaInfo(520000, 520200, _T("����ˮ"));
					City[522600] = AreaInfo(520000, 522600, _T("ǭ�������嶱��������"));
					City[522700] = AreaInfo(520000, 522700, _T("ǭ�ϲ���������������"));
					City[522300] = AreaInfo(520000, 522300, _T("ǭ���ϲ���������������"));
					City[522200] = AreaInfo(520000, 522200, _T("ͭ��"));
					City[520300] = AreaInfo(520000, 520300, _T("����"));

					City[469000] = AreaInfo(460000, 469000, _T("ʡֱϽ"));
					City[460100] = AreaInfo(460000, 460100, _T("����"));
					City[460200] = AreaInfo(460000, 460200, _T("����"));

					City[130600] = AreaInfo(130000, 130600, _T("����"));
					City[130900] = AreaInfo(130000, 130900, _T("����"));
					City[130800] = AreaInfo(130000, 130800, _T("�е�"));
					City[130400] = AreaInfo(130000, 130400, _T("����"));
					City[131100] = AreaInfo(130000, 131100, _T("��ˮ"));
					City[131000] = AreaInfo(130000, 131000, _T("�ȷ�"));
					City[130300] = AreaInfo(130000, 130300, _T("�ػʵ�"));
					City[130100] = AreaInfo(130000, 130100, _T("ʯ��ׯ"));
					City[130200] = AreaInfo(130000, 130200, _T("��ɽ"));
					City[130500] = AreaInfo(130000, 130500, _T("��̨"));
					City[130700] = AreaInfo(130000, 130700, _T("�żҿ�"));

					City[410500] = AreaInfo(410000, 410500, _T("����"));
					City[410600] = AreaInfo(410000, 410600, _T("�ױ�"));
					City[410800] = AreaInfo(410000, 410800, _T("����"));
					City[410200] = AreaInfo(410000, 410200, _T("����"));
					City[410300] = AreaInfo(410000, 410300, _T("����"));
					City[411300] = AreaInfo(410000, 411300, _T("����"));
					City[410400] = AreaInfo(410000, 410400, _T("ƽ��ɽ"));
					City[411200] = AreaInfo(410000, 411200, _T("����Ͽ"));
					City[411400] = AreaInfo(410000, 411400, _T("����"));
					City[410700] = AreaInfo(410000, 410700, _T("����"));
					City[411500] = AreaInfo(410000, 411500, _T("����"));
					City[411000] = AreaInfo(410000, 411000, _T("���"));
					City[410100] = AreaInfo(410000, 410100, _T("֣��"));
					City[411600] = AreaInfo(410000, 411600, _T("�ܿ�"));
					City[411700] = AreaInfo(410000, 411700, _T("פ���"));
					City[411100] = AreaInfo(410000, 411100, _T("���"));
					City[410900] = AreaInfo(410000, 410900, _T("���"));
					City[411800] = AreaInfo(410000, 411800, _T("��Դ"));
				}
			}initArea;
			

			void GetProvinceName(const std::tr1::function<void(LPCTSTR, size_t)> &callback)
			{
				for(ProvinceInfo::const_iterator iter = Provience.begin(); iter != Provience.end(); ++iter)
				{
					callback(iter->second.Name, iter->first);
				}
			}

			void GetCityName(size_t parentID, const std::tr1::function<void(LPCTSTR, size_t)> &callback)
			{
				for(CityInfo::const_iterator iter = City.begin(); iter != City.end(); ++iter)
				{
					if( parentID == iter->second.ParentID )
						callback(iter->second.Name, iter->first);
				}
			}


			namespace detail
			{
				static struct
				{
					int type_;
					LPCTSTR name_;
				}diskType[] = 
				{
					{ 1, _T("����") },
					{ 2, _T("����") },
					{ 3, _T("���") }
				};


				static struct
				{
					int type_;
					LPCTSTR name_;
				}networkType[] = 
				{
					{ 1, _T("����") },
					{ 2, _T("ADSL") },
					{ 3, _T("����") }
				};
			}

			void GetDiskType(const std::tr1::function<void(LPCTSTR, size_t)> &callback)
			{
				for(size_t i = 0; i != _countof(detail::diskType); ++i)
					callback(detail::diskType[i].name_, detail::diskType[i].type_);
			}

			void GetNetworkType(const std::tr1::function<void(LPCTSTR, size_t)> &callback)
			{
				for(size_t i = 0; i != _countof(detail::networkType); ++i)
					callback(detail::networkType[i].name_, detail::networkType[i].type_);
			}

			stdex::tString GetDiskNameByType(size_t type)
			{
				for(size_t i = 0; i != _countof(detail::diskType); ++i)
				{
					if( type == detail::diskType[i].type_ )
						return detail::diskType[i].name_;
				}

				return _T("");
			}

			stdex::tString GetNetworkByType(size_t type)
			{
				for(size_t i = 0; i != _countof(detail::networkType); ++i)
				{
					if( type == detail::networkType[i].type_ )
						return detail::networkType[i].name_;
				}

				return _T("");
			}

			// ��ȡ���̲�Ʒ����
			void GetDiskProduct(const std::tr1::function<void(LPCTSTR, size_t)> &callback)
			{
				static struct
				{
					LPCTSTR type_;
					LPCTSTR name_;
				}diskProduct[] = 
				{
					{ _T("��"),		_T("��") },
					{ _T("����"),	_T("����") },
					{ _T("����"),	_T("����") },
					{ _T("��������"),	_T("��������") },
					{ _T("˳������"),	_T("˳������") },
					{ _T("����"),	_T("����") },
					{ _T("DOL"),	_T("DOL") },
					{ _T("VHD"),	_T("VHD") },
					{ _T("��������"),	_T("��������") },
					{ _T("�������"),	_T("�������") },
					{ _T("MZD"),	_T("MZD") },
					{ _T("�涫����"),	_T("�涫����") }
				};

				for(size_t i = 0; i != _countof(diskProduct); ++i)
					callback(diskProduct[i].name_, (int)diskProduct[i].type_);
			}


			// ��ȡ�շ��������
			void GetFeeProductName(const std::tr1::function<void(LPCTSTR, size_t)> &callback)
			{
				static struct
				{
					LPCTSTR type_;
					LPCTSTR name_;
				}feeProduct[] = 
				{
					{ _T("��"),		_T("��") },
					{ _T("����"),	_T("����") },
					{ _T("��ʤ����"),	_T("��ʤ����") },
					{ _T("�º���Pubwin"),	_T("�º���Pubwin") },
					{ _T("����һ��ͨ"),	_T("����һ��ͨ") },
					{ _T("��ţ"),	_T("��ţ") },
					{ _T("���ܼ�"),	_T("���ܼ�") },
					{ _T("����һ��ͨ"),	_T("����һ��ͨ") },
					{ _T("����ͬ��"),	_T("����ͬ��") },
					{ _T("��Ƽ"),	_T("��Ƽ") }
				};

				for(size_t i = 0; i != _countof(feeProduct); ++i)
					callback(feeProduct[i].name_, (int)feeProduct[i].type_);
			}

			// ��ȡ�Ļ��������
			void GetCulturalProductName(const std::tr1::function<void(LPCTSTR, size_t)> &callback)
			{
				static struct
				{
					LPCTSTR type_;
					LPCTSTR name_;
				}culturalProduct[] = 
				{
					{ _T("��"),		_T("��") },
					{ _T("����"),	_T("����") },
					{ _T("�����ȷ�"),	_T("�����ȷ�") },
					{ _T("������"),	_T("������") },
					{ _T("����΢ע"),	_T("����΢ע") },
					{ _T("���ڱ�"),	_T("���ڱ�") }
				};

				for(size_t i = 0; i != _countof(culturalProduct); ++i)
					callback(culturalProduct[i].name_, (int)culturalProduct[i].type_);
			}

			bool IsValidPath(LPCTSTR path)
			{
				stdex::tString Dvr;
				Dvr = path;
				size_t pos = Dvr.find_first_of(_T('\\'));
				Dvr = Dvr.substr(0, pos);
				if(!PathFileExists(Dvr.c_str()))
					return false;

				TCHAR text[MAX_PATH] = {0};
				utility::Strcpy(text, path);
				::PathRemoveBackslash(text);

				if(!PathFileExists((LPCTSTR)text))
				{
					if( !utility::mkpath((LPCTSTR)text) )
						return false;
				}

				return true;

			}

		}
	}
}