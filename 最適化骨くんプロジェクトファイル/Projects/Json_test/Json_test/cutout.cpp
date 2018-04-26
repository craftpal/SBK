#include "cutout.h"
using namespace cutout;

CRank::CRank(){x = 0; y = 0;}
void CRank::X(int x){ this->x = x; }
int CRank::X(){ return this->x; }
void CRank::Y(int y){ this->y = y; }
int CRank::Y(){ return this->y; }
void CRank::Xadd(int value){ this->x += value; }
void CRank::Yadd(int value){ this->y += value; }

CSortItem::	CSortItem(int index, int data){
	this->index = index;
	this->data = data;
}
CSortList::CSortList(){}
CSortItem CSortList::get(int index){
	return items[index];
}
void CSortList::add(int index, int data){
	if(!items.size()){
		items.push_back(CSortItem(index, data));
		return;
	}
	for(int i = 0, len = items.size(); i < len; i++){
		if(items[i].data > data){
			items.insert(items.begin() + i, CSortItem(index, data));
			return;
		}
	}
	//�ŏ�����Ō�-1�̂ǂ�ɂ����Ă͂܂�Ȃ������ꍇ��ԍŌ�ɒǉ�
	items.push_back(CSortItem(index, data));
}
int CSortList::size(){ return items.size(); }
void CSortList::clear(){ items.clear(); }
void CSortList::show_items(){
	for(int i = 0, len = items.size(); i < len; i++){
		std::cout << "SortList[" << i << "] : index = " << items[i].index
			<< ", data = " << items[i].data << std::endl;
	}
}

CRectance::CRectance(){
	this->set(0, 0);
	this->ranked = 0;
	this->cleared = false;
}
CRectance::CRectance(int x, int y){
	this->set(x, y);
	this->ranked = 0;
	this->cleared = false;
}
CRectance CRectance::operator-(CRectance rect){
	return CRectance(x - rect.X(), y - rect.Y());
}
void CRectance::X(int x){ this->x = x; }
int CRectance::X(){ return this->x; }
void CRectance::Y(int y){ this->y = y; }
int CRectance::Y(){ return this->y; }
void CRectance::Xadd(int value){ this->x += value; }
void CRectance::Yadd(int value){ this->y += value; }
void CRectance::set(int x, int y){
	this->x = x;
	this->y = y;
}
bool CRectance::insered(CRectance rect){
	return !(this->Y() - rect.Y() < 0) && !(this->X() - rect.X() < 0);
}
CRank& CRectance::Rank(){
	return this->rank;
}
void CRectance::Rank(int value){
	this->ranked = value;
}
int CRectance::Ranked(){ return this->ranked; }
void CRectance::RankUp(){ this->ranked++; }
void CRectance::Clear(){ this->cleared = true; }
bool CRectance::Cleared(){ return this->cleared; }
CRectance CRectance::input_rect(bool explain){
	if(explain){
		std::cout << "�͈͂𒷕��`�Ƃ� X��, Y�� ����͂��Ă�������." << std::endl;
		std::cout << "[����:] ���オ(0,0), �E���Ɍ������Đ��̕����ł�(default)" << std::endl;
		std::cout << "    ��) �����𐳂Ƃ���ꍇ, �㉺�̏����𔽑΂ɂ��ē��͂��Ă�������(�񐄏�)" << std::endl;
		std::cout << "���͂��I����ɂ� X, Y �̂ǂ��炩�̓��͎��� ���̐�(-1�ȉ�) ����͂��Ă�������." << std::endl;
	}
	CRectance input;
	int inX, inY;
	std::cout << "X ->";
	std::cin >> inX;
	if(inX < 0) throw -1;
	std::cout << "Y ->";
	std::cin >> inY;
	if(inY < 0) throw -1;
	input.set(inX, inY);
	return input;
}
CRectance CRectance::input_rect(bool explain, char *str, int count){
	if(explain){
		std::cout << "�͈͂𒷕��`�Ƃ� X��, Y�� ����͂��Ă�������." << std::endl;
		std::cout << "[����:] ���オ(0,0), �E���Ɍ������Đ��̕����ł�(default)" << std::endl;
		std::cout << "    ��) �����𐳂Ƃ���ꍇ, �㉺�̏����𔽑΂ɂ��ē��͂��Ă�������(�񐄏�)" << std::endl;
		std::cout << "���͂��I����ɂ� X, Y �̂ǂ��炩�̓��͎��� ���̐�(-1�ȉ�) ����͂��Ă�������." << std::endl;
	}
	CRectance input;
	int inX, inY;
	std::cout << "[" <<count << str << "]: X ->";
	std::cin >> inX;
	if(inX < 0) throw -1;
	std::cout << "[" <<count << str << "]: Y ->";
	std::cin >> inY;
	if(inY < 0) throw -1;
	input.set(inX, inY);
	return input;
}
void CListRectance::to_rank(){
	//XY�����N�t��
	for(int i = 0, len = v_rec.size(); i < len; i++){
		v_rec[i].Rank().X(1);	//�S�Ẵ����N�� 1 �ɏ�����
		v_rec[i].Rank().Y(1);	//�S�Ẵ����N�� 1 �ɏ�����
	}
	for(int i = 0, len = v_rec.size(); i < len; i++){
		//std::cout << "i = " << i << std::endl;
		for(int j = i; j < len; j++){
			//std::cout << "j = " << j << std::endl;
			if(i == j) continue;
			if(v_rec[i].X() < v_rec[j].X()){	//���������N�t��
				v_rec[j].Rank().Xadd(1);
			} else if(v_rec[i].X() > v_rec[j].X()) {
				v_rec[i].Rank().Xadd(1);
			}
			if(v_rec[i].Y() < v_rec[j].Y()){	//���������N�t��
				v_rec[j].Rank().Yadd(1);
			} else if(v_rec[i].Y() > v_rec[j].Y()) {
				v_rec[i].Rank().Yadd(1);
			}
		}
	}
}
int CListRectance::search_insered(CRectance target, CListRectance parts, int order){
	//�S�̃����N�t��
	parts.to_rank();
	for(int i = 0, len = parts.lenght(); i < len; i++){
		std::cout << "parts(" << i << ") ?CLEAR : " << parts.get(i).Cleared() << std::endl;
		if(target.insered(parts.get(i)) && !parts.get(i).Cleared()){	//�Ώۂɕ��i������Ƃ�
			parts.Rank(i, parts.get(i).Rank().X() + parts.get(i).Rank().Y());
		} else {
			parts.Rank(i, 0);	//�����N�͍Œ�ł�2�ɂȂ�̂�0�͏��O����
		}
		//���ޯ�: �����N�o��
		std::cout << i << ": rank(" << parts.get(i).Rank().X() << " + "
			<< parts.get(i).Rank().Y() << ") = " << parts.get(i).Ranked()
			<< "  CLEA?:" << parts.get(i).Cleared() << std::endl;
	}
	//order�Ԗڂ̗v�f�̃C���f�b�N�X��Ԃ�
	CSortList s_list = CSortList();
	//���ޯ�: �\�[�g���m�F�p
	//std::cout << "Number of sorted parts : " << parts.lenght() << std::endl;
	for(int i = 0, len = parts.lenght(); i < len; i++){
		if(parts.get(i).Ranked()){
			s_list.add(i, parts.get(i).Ranked());
		}
	}
	//���ޯ�: �A�C�e���̈ꗗ�\��
	//s_list.show_items();
	if(order < s_list.size()){
		return s_list.get(order).index;	//�w��order��Ԃ�(�~��)
	} else {
		return -1;
	}
}
CRectance CListRectance::get(int index){
	return v_rec[index];
}
CRectance CListRectance::max_size(){
	CRectance temp = CRectance();
	for(int i = 0, len = this->lenght(); i < len; i++){
		if(temp.X() < v_rec[i].X()) temp.X(v_rec[i].X());
		if(temp.Y() < v_rec[i].Y()) temp.Y(v_rec[i].Y());
	}
	return temp;
}
void CListRectance::add(int x, int y){
	v_rec.push_back(CRectance(x, y));
}
void CListRectance::add(CRectance data){
	v_rec.push_back(data);
}
void CListRectance::set(int index, int x, int y){
	v_rec[index].X(x);
	v_rec[index].Y(y);
}
void CListRectance::setAddX(int index, int x){
	v_rec[index].X(v_rec[index].X() + x);
}
void CListRectance::setAddY(int index, int y){
	v_rec[index].Y(v_rec[index].Y() + y);
}
void CListRectance::setAdd(int index, int x, int y){
	setAddX(index, x);
	setAddY(index, y);
}
void CListRectance::insert(int index, int x, int y){
	v_rec.insert(v_rec.begin()+index, CRectance(x, y));
}
int CListRectance::lenght(){
	return v_rec.size();
}
void CListRectance::Rank(int index, int value){
	v_rec[index].Rank(value);
}
void CListRectance::RankUp(int index){
	v_rec[index].RankUp();
}
int CListRectance::find_index_ofx(int x){
	for(int i = 0, len = this->lenght(); i < len; i++){
		if(v_rec[i].X() == x) return i;
	}
	return -1;	//������Ȃ����ꍇ -1 ��Ԃ�
}
void CListRectance::Clear(int index){
	v_rec[index].Clear();
}
void CListRectance::clear(){
	v_rec.clear();
}
bool CListRectance::del(int index){
	std::cout << " �폜�͈͊m�F��... " << std::endl;
	std::cout << "0 < " << index << " < " << v_rec.size() - 1 << std::endl;
	if(index < 0) return false;
	bool top = false, mid = false, low = false, last = false;
	if(v_rec.size() == 1){
		last = true;
	} else {
		if(index - 1 < 0){
			top = true;
		}
		if(index + 1 > (int)v_rec.size() - 1){
			low = true;
		}
		if(!top && !low){
			mid = true;
			top = low = false;
		}
	}
	//�t���O����
	if(last){
		std::cout << "�Ō�̗v�f�ł� clear ���܂�..." << std::endl;
		v_rec.clear();
		std::cout << "�Ō�̗v�f�ł� clear ���܂���" << std::endl;
		return false;
	}
	if(top){
		std::cout << "top" << std::endl;
		v_rec[index+1].Yadd(v_rec[index].Y());
	}
	if(low){
		std::cout << "low" << std::endl;
		v_rec[index-1].Yadd(v_rec[index].Y());
	}
	if(mid){
		std::cout << "mid" << std::endl;
		if(v_rec[index+1].X() > v_rec[index-1].X()){
			v_rec[index+1].Yadd(v_rec[index].Y());
		} else {
			v_rec[index-1].Yadd(v_rec[index].Y());
		}
	}
	//�폜
	std::cout << " �폜�͈͊m�F���� " << std::endl;
	std::cout << " �폜�J�n... " << std::endl;
	v_rec.erase(v_rec.begin()+index);
	std::cout << " �폜���� " << std::endl;
	return true;
}
CListRectance CListRectance::input_list_rect(){
	CListRectance inputs;
	int count = 0;
	bool loop = true;
	do{
		try{
			inputs.add(CRectance::input_rect(!count));
		}catch(int ex){
			if(ex == -1){
				if(!count){
					std::cout << "�v���O�������I�����܂�." << std::endl;
					exit(0);
				}
				std::cout << "���v��" << count
					<< "�̃f�[�^�����͂���܂���, ���͂��I�����܂�." << std::endl;
				loop = false;
			}
		}
		count++;
	}while(loop);
	return inputs;
}
CListRectance CListRectance::input_list_rect(char *str){
	CListRectance inputs;
	int count = 0;
	bool loop = true;
	do{
		try{
			inputs.add(CRectance::input_rect(!count, str, count + 1));
		}catch(int ex){
			if(ex == -1){
				if(!count){
					std::cout << "�v���O�������I�����܂�." << std::endl;
					exit(0);
				}
				std::cout << "���v��" << count
					<< "�̃f�[�^�����͂���܂���, ���͂��I�����܂�." << std::endl;
				loop = false;
			}
		}
		count++;
	}while(loop);
	return inputs;
}

CXY::CXY(){
	x = 0;
	y = 0;
}
CXY::CXY(int x, int y){
	this->x = x;
	this->y = y;
}

CFrame::CFrame(CXY topL, CXY lowR){
	this->topL = topL;
	this->lowR = lowR;
}
void CFrame::show(){
	std::cout << "(" << topL.x << "," << topL.y << "),("
		<< lowR.x << "," << lowR.y << ")" << std::endl;
}
void CFrame::show(int x){
	std::cout << "(" << topL.x - x << "," << topL.y << "),("
		<< lowR.x - x << "," << lowR.y << ")" << std::endl;
}

void CCoreRectance::init(){
	//�I������
	std::cout << "�I�����蒆..." << std::endl;
	finished = true;
	for(int i = 0, len = lire_targets.lenght(); i < len; i++){
		std::cout << "lire_targets.get(" << i << ").X = " << lire_targets.get(i).X() << std::endl
			<< "lire_targets.get(" << i << ").Y = " << lire_targets.get(i).Y() << std::endl;
		for(int i = 0, len = lire_parts.lenght(); i < len; i++){
			finished = finished && lire_parts.get(i).Cleared();
			//���ޯ�: finished
		}
	}
	for(int i = 0, len = lire_parts.lenght(); i < len; i++){
		std::cout << "[" << i << "]: " << lire_parts.get(i).Cleared() << ", ";
	}
	std::cout << std::endl;
	std::cout << finished << ") �I�����芮��" << std::endl;

	// �ǂ̕��i������Ȃ��Ώ۔͈͂̃C���f�b�N�X�����߂���
	// �e���i���Ώ۔͈͂֓��邩
	std::cout << "�Ώ۔͈͂̌���/�폜����J�n" << std::endl;
	int index_del;
	do{
		for(int i = 0, len = lire_targets.lenght(); i < len; i++){
			std::cout << "lire_targets.get(" << i << ").X = " << lire_targets.get(i).X() << std::endl
				<< "lire_targets.get(" << i << ").Y = " << lire_targets.get(i).Y() << std::endl;
		}
		index_del = -1;
		// �ŏ��̂��̂����ׂ邽�߂̏���
		CSortList target_min;
		for(int i = 0, len = lire_targets.lenght(); i < len; i++){
			target_min.add(i, lire_targets.get(i).Y());
		}
		target_min.show_items();
		// �ŏ���Y�����̑Ώ۔͈͂��̂���ǂ̕��i������Ȃ����̂��폜
		for(int i = 0, len = target_min.size(); i < len; i++){
			bool some_in = false;
			int index_min = target_min.get(i).index;
			for(int j = 0, len2 = lire_parts.lenght(); j < len2; j++){
				if(lire_targets.get(index_min).insered(lire_parts.get(j))){
					some_in = true;
				}
			}
			if(!some_in){
				//��������Ȃ� lire_targets �̃C���f�b�N�X���폜
				index_del = index_min;	//�I������p
				std::cout << "[" << index_del << "]�ɂ͓���Ȃ���!" << std::endl;
				std::cout << "�Ώ۔͈͍폜 [0-" << lire_targets.lenght() - 1 << "] : " << index_del << std::endl;
				if(!lire_targets.del(index_del)){
					std::cout << "�Ō�̗v�f���폜���܂���" << std::endl;
					std::cout << "�u���C�N" << std::endl;
				}
			}
			if(index_del != -1) break;
		}

	}while(index_del != -1);
	std::cout << "�Ώ۔͈͂̌���/�폜����I��!" << std::endl;

	//CSortList���g���� X �ő�l�Ƃ��̃C���f�b�N�X���擾
	CSortList sl_target_x;
	for(int i = 0, len = lire_targets.lenght(); i < len; i++){
		// sl_rec �� �ŏ��̗v�f < �Ō�̗v�f �ƂȂ�悤�ɑ}�������
		sl_target_x.add(i, lire_targets.get(i).X());
	}
	// sl_rec �� �ő�l�̂ق�����擾����(count��1�Ԗڂ̍ő�l,2�Ԗڂ̍ő�l...�Ǝ擾���Ă���)
	if(!count){
		std::cout << "********************" << std::endl;
		std::cout << "Alpha �̐ݒ�l : " << sl_target_x.size() - 1 - count << std::endl;
		std::cout << "********************" << std::endl;
	} else {
		std::cout << "********************" << std::endl;
		std::cout << "Alpha ���Đݒ� : " << sl_target_x.size() - 1 - count << std::endl;
		std::cout << "********************" << std::endl;
	}
	Alpha = sl_target_x.get(sl_target_x.size() - 1 - count).index;
	sl_target_x.show_items();

	// �����͈�Alpha:X,Y �� ���iPart:X,Y �̍������擾 => difRecs{difX, difY}
	// �K�� Alpha > Part �̊֌W�ɂ���A�v�f�� Alpha - Part �̌��ʂɂȂ��Ă���͂��ł���
	difRecs.clear();
	for(int i = 0, len = lire_parts.lenght(); i < len; i++){
		difRecs.add(lire_targets.get(Alpha).X() - lire_parts.get(i).X(),
			lire_targets.get(Alpha).Y() - lire_parts.get(i).Y());
		if(lire_parts.get(i).Cleared()){
			difRecs.Clear(i);
		}
	}
	//�����N�t���ɂ��}�����i�̍œK�C���f�b�N�X�l���擾(error:-1)
	opt = CListRectance::search_insered(lire_targets.get(Alpha), difRecs, 0);
	if(opt == -1){
		std::cout << "Finish!" << std::endl;
		throw 0;	//����I���p�̗�O
	}
	//�㑤y+difY, ����y+difY ������ UppY, LowY �Ƃ���
	UppY = LowY = 0;
	for(int i = 0; i < Alpha; i++){
		UppY += lire_targets.get(i).Y();
	}
	for(int i = lire_targets.lenght() - 1; i > Alpha; i--){
		LowY += lire_targets.get(i).Y();
	}
}
CCoreRectance::CCoreRectance(CListRectance targets, CListRectance parts){
	lire_targets = targets;
	lire_parts = parts;
	count = 0;
	finished = false;
}
CFrame CCoreRectance::cutout(){	//�}���������i�̍��W��Ԃ�
	//���l������
	std::cout << "�������J�n" << std::endl;
	init();
	std::cout << "����������!" << std::endl;
	//���ޯ�//�������Ƃ������W���擾���ێ����Ă���(�㑱�����ɂ�茳�̔z�񂪂����������邽��)
	CFrame result = CFrame(
		CXY(lire_targets.get(Alpha).X() - lire_parts.get(opt).X(), UppY),
		CXY(lire_targets.get(Alpha).X(), UppY + lire_parts.get(opt).Y())
		);
	// lire_targets > lire_parts �̍��������߂�
	CRectance difAlphaOpt;
	difAlphaOpt.set(
		lire_targets.get(Alpha).X() - lire_parts.get(opt).X(),
		lire_targets.get(Alpha).Y() - lire_parts.get(opt).Y()
		);
	//�ǂ��炩�����̏ꍇ�͐؂�o���Ȃ��̂Ŏ��̑Ώ۔͈͂�I������
	std::cout << "difAlphaOpt? X : " << difAlphaOpt.X() << ", Y : " << difAlphaOpt.Y() << std::endl;
	if(difAlphaOpt.X() < 0 || difAlphaOpt.Y() < 0){
		count++;
		if(count < lire_targets.lenght()){
			return cutout();
		} else {
			throw -1;
		}
	}
	//�Đݒ�
	//difAlphaOpt.set(
	//	lire_targets.get(Alpha).X() - lire_parts.get(opt).X(),
	//	lire_targets.get(Alpha).Y() - lire_parts.get(opt).Y()
	//	);
	//�㑤�������ŗ]�������������ɏ�[�܂��͉��[�����킹�؂�o��
	CRectance insertRec;
	CRectance setRec;
	std::cout << "�Ώ۔͈� [0-" << lire_targets.lenght() - 1 << "] " << "Alpha : " << Alpha << std::endl;
	if(UppY < LowY){
		insertRec.set(difAlphaOpt.X(), lire_parts.get(opt).Y());
		setRec.set(lire_targets.get(Alpha).X(), difAlphaOpt.Y());
	} else {
		insertRec.set(lire_targets.get(Alpha).X(), difAlphaOpt.Y());
		setRec.set(difAlphaOpt.X(), lire_parts.get(opt).Y());
		//�����ɍ��킹��̂Ő؂�o�����W��Y���W�����̕�����������
		result.topL.y += difAlphaOpt.Y();
		result.lowR.y += difAlphaOpt.Y();
	}
	std::cout << "���͈̔͂�" << opt << "�w�ڂ̕��i��؂�o���񂾂���˂�!" << std::endl;
	std::cout << "insertRec? X : " << insertRec.X() << ", Y : " << insertRec.Y() << std::endl;
	std::cout << "   setRec? X : " << setRec.X() << ", Y : " << setRec.Y() << std::endl;
	//�Ώ۔͈͂֐؂�o������̑Ώ۔͈͂�ǉ�
	lire_targets.insert(Alpha, insertRec.X(), insertRec.Y());
	//�Ώ۔͈͂���ǉ������͈͂�����
	lire_targets.set(Alpha + 1, setRec.X(), setRec.Y());
	//�؂�o�������i���N���A��Ԃɐ��ڂ�����
	std::cout << "Number [" << opt << "] �̓N���A��!" << std::endl;
	lire_parts.Clear(opt);

	this->count = 0;
	std::cout << "result ��Ԃ���!" << std::endl;
	return result;
}
std::vector<CFrame> CCoreRectance::cutouts(){
	while(!finished){
		try{
			results.push_back(cutout());
			std::cout << "�ؒf���W��Push������!" << std::endl;
		}catch(int ex){
			switch(ex){
					case 0:
						std::cout << "ԯ���// ����I���ł�!" << std::endl;
						break;
					case -1:
						std::cout << "�\�����ʃG���[����!�A������[!" << std::endl;
						break;
			}
		}
	}
	return results;
}
void printLire(CListRectance lire){
	for(int i = 0, len = lire.lenght(); i < len; i++){
		std::cout << "lire_targets.get(" << i << ").X = " << lire.get(i).X() << std::endl
			<< "lire_targets.get(" << i << ").Y = " << lire.get(i).Y() << std::endl;
	}
}

void printLireRank(CListRectance lire){
	for(int i = 0, len = lire.lenght(); i < len; i++){
		std::cout << "lire_targets.Rank.X(" << i << ").X = " << lire.get(i).Rank().X() << std::endl
			<< "lire_targets.Rank.Y(" << i << ").Y = " << lire.get(i).Rank().Y() << std::endl;
	}
}
