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
	//最初から最後-1のどれにも当てはまらなかった場合一番最後に追加
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
		std::cout << "範囲を長方形とし X幅, Y幅 を入力してください." << std::endl;
		std::cout << "[注意:] 左上が(0,0), 右下に向かって正の方向です(default)" << std::endl;
		std::cout << "    例) 左下を正とする場合, 上下の順序を反対にして入力してください(非推奨)" << std::endl;
		std::cout << "入力を終えるには X, Y のどちらかの入力時に 負の数(-1以下) を入力してください." << std::endl;
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
		std::cout << "範囲を長方形とし X幅, Y幅 を入力してください." << std::endl;
		std::cout << "[注意:] 左上が(0,0), 右下に向かって正の方向です(default)" << std::endl;
		std::cout << "    例) 左下を正とする場合, 上下の順序を反対にして入力してください(非推奨)" << std::endl;
		std::cout << "入力を終えるには X, Y のどちらかの入力時に 負の数(-1以下) を入力してください." << std::endl;
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
	//XYランク付け
	for(int i = 0, len = v_rec.size(); i < len; i++){
		v_rec[i].Rank().X(1);	//全てのランクを 1 に初期化
		v_rec[i].Rank().Y(1);	//全てのランクを 1 に初期化
	}
	for(int i = 0, len = v_rec.size(); i < len; i++){
		//std::cout << "i = " << i << std::endl;
		for(int j = i; j < len; j++){
			//std::cout << "j = " << j << std::endl;
			if(i == j) continue;
			if(v_rec[i].X() < v_rec[j].X()){	//昇順ランク付け
				v_rec[j].Rank().Xadd(1);
			} else if(v_rec[i].X() > v_rec[j].X()) {
				v_rec[i].Rank().Xadd(1);
			}
			if(v_rec[i].Y() < v_rec[j].Y()){	//昇順ランク付け
				v_rec[j].Rank().Yadd(1);
			} else if(v_rec[i].Y() > v_rec[j].Y()) {
				v_rec[i].Rank().Yadd(1);
			}
		}
	}
}
int CListRectance::search_insered(CRectance target, CListRectance parts, int order){
	//全体ランク付け
	parts.to_rank();
	for(int i = 0, len = parts.lenght(); i < len; i++){
		std::cout << "parts(" << i << ") ?CLEAR : " << parts.get(i).Cleared() << std::endl;
		if(target.insered(parts.get(i)) && !parts.get(i).Cleared()){	//対象に部品が入るとき
			parts.Rank(i, parts.get(i).Rank().X() + parts.get(i).Rank().Y());
		} else {
			parts.Rank(i, 0);	//ランクは最低でも2になるので0は除外する
		}
		//ﾃﾞﾊﾞｯｸ: ランク出力
		std::cout << i << ": rank(" << parts.get(i).Rank().X() << " + "
			<< parts.get(i).Rank().Y() << ") = " << parts.get(i).Ranked()
			<< "  CLEA?:" << parts.get(i).Cleared() << std::endl;
	}
	//order番目の要素のインデックスを返す
	CSortList s_list = CSortList();
	//ﾃﾞﾊﾞｯｸ: ソート数確認用
	//std::cout << "Number of sorted parts : " << parts.lenght() << std::endl;
	for(int i = 0, len = parts.lenght(); i < len; i++){
		if(parts.get(i).Ranked()){
			s_list.add(i, parts.get(i).Ranked());
		}
	}
	//ﾃﾞﾊﾞｯｸ: アイテムの一覧表示
	//s_list.show_items();
	if(order < s_list.size()){
		return s_list.get(order).index;	//指定orderを返す(降順)
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
	return -1;	//見つからなかい場合 -1 を返す
}
void CListRectance::Clear(int index){
	v_rec[index].Clear();
}
void CListRectance::clear(){
	v_rec.clear();
}
bool CListRectance::del(int index){
	std::cout << " 削除範囲確認中... " << std::endl;
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
	//フラグ判定
	if(last){
		std::cout << "最後の要素です clear します..." << std::endl;
		v_rec.clear();
		std::cout << "最後の要素です clear しました" << std::endl;
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
	//削除
	std::cout << " 削除範囲確認完了 " << std::endl;
	std::cout << " 削除開始... " << std::endl;
	v_rec.erase(v_rec.begin()+index);
	std::cout << " 削除完了 " << std::endl;
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
					std::cout << "プログラムを終了します." << std::endl;
					exit(0);
				}
				std::cout << "合計で" << count
					<< "個のデータが入力されました, 入力を終了します." << std::endl;
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
					std::cout << "プログラムを終了します." << std::endl;
					exit(0);
				}
				std::cout << "合計で" << count
					<< "個のデータが入力されました, 入力を終了します." << std::endl;
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
	//終了判定
	std::cout << "終了判定中..." << std::endl;
	finished = true;
	for(int i = 0, len = lire_targets.lenght(); i < len; i++){
		std::cout << "lire_targets.get(" << i << ").X = " << lire_targets.get(i).X() << std::endl
			<< "lire_targets.get(" << i << ").Y = " << lire_targets.get(i).Y() << std::endl;
		for(int i = 0, len = lire_parts.lenght(); i < len; i++){
			finished = finished && lire_parts.get(i).Cleared();
			//ﾃﾞﾊﾞｯｸ: finished
		}
	}
	for(int i = 0, len = lire_parts.lenght(); i < len; i++){
		std::cout << "[" << i << "]: " << lire_parts.get(i).Cleared() << ", ";
	}
	std::cout << std::endl;
	std::cout << finished << ") 終了判定完了" << std::endl;

	// どの部品も入らない対象範囲のインデックスを求めたい
	// 各部品が対象範囲へ入るか
	std::cout << "対象範囲の結合/削除判定開始" << std::endl;
	int index_del;
	do{
		for(int i = 0, len = lire_targets.lenght(); i < len; i++){
			std::cout << "lire_targets.get(" << i << ").X = " << lire_targets.get(i).X() << std::endl
				<< "lire_targets.get(" << i << ").Y = " << lire_targets.get(i).Y() << std::endl;
		}
		index_del = -1;
		// 最小のものから比べるための準備
		CSortList target_min;
		for(int i = 0, len = lire_targets.lenght(); i < len; i++){
			target_min.add(i, lire_targets.get(i).Y());
		}
		target_min.show_items();
		// 最小のYをもつの対象範囲ものからどの部品も入らないものを削除
		for(int i = 0, len = target_min.size(); i < len; i++){
			bool some_in = false;
			int index_min = target_min.get(i).index;
			for(int j = 0, len2 = lire_parts.lenght(); j < len2; j++){
				if(lire_targets.get(index_min).insered(lire_parts.get(j))){
					some_in = true;
				}
			}
			if(!some_in){
				//何も入らない lire_targets のインデックスを削除
				index_del = index_min;	//終了判定用
				std::cout << "[" << index_del << "]には入らないよ!" << std::endl;
				std::cout << "対象範囲削除 [0-" << lire_targets.lenght() - 1 << "] : " << index_del << std::endl;
				if(!lire_targets.del(index_del)){
					std::cout << "最後の要素を削除しました" << std::endl;
					std::cout << "ブレイク" << std::endl;
				}
			}
			if(index_del != -1) break;
		}

	}while(index_del != -1);
	std::cout << "対象範囲の結合/削除判定終了!" << std::endl;

	//CSortListを使って X 最大値とそのインデックスを取得
	CSortList sl_target_x;
	for(int i = 0, len = lire_targets.lenght(); i < len; i++){
		// sl_rec は 最初の要素 < 最後の要素 となるように挿入される
		sl_target_x.add(i, lire_targets.get(i).X());
	}
	// sl_rec の 最大値のほうから取得する(countで1番目の最大値,2番目の最大値...と取得していく)
	if(!count){
		std::cout << "********************" << std::endl;
		std::cout << "Alpha の設定値 : " << sl_target_x.size() - 1 - count << std::endl;
		std::cout << "********************" << std::endl;
	} else {
		std::cout << "********************" << std::endl;
		std::cout << "Alpha を再設定 : " << sl_target_x.size() - 1 - count << std::endl;
		std::cout << "********************" << std::endl;
	}
	Alpha = sl_target_x.get(sl_target_x.size() - 1 - count).index;
	sl_target_x.show_items();

	// 分割範囲Alpha:X,Y と 部品Part:X,Y の差分を取得 => difRecs{difX, difY}
	// 必ず Alpha > Part の関係にあり、要素は Alpha - Part の結果になっているはずである
	difRecs.clear();
	for(int i = 0, len = lire_parts.lenght(); i < len; i++){
		difRecs.add(lire_targets.get(Alpha).X() - lire_parts.get(i).X(),
			lire_targets.get(Alpha).Y() - lire_parts.get(i).Y());
		if(lire_parts.get(i).Cleared()){
			difRecs.Clear(i);
		}
	}
	//ランク付けにより挿入部品の最適インデックス値を取得(error:-1)
	opt = CListRectance::search_insered(lire_targets.get(Alpha), difRecs, 0);
	if(opt == -1){
		std::cout << "Finish!" << std::endl;
		throw 0;	//正常終了用の例外
	}
	//上側y+difY, 下側y+difY を求め UppY, LowY とする
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
CFrame CCoreRectance::cutout(){	//挿入した部品の座標を返す
	//数値初期化
	std::cout << "初期化開始" << std::endl;
	init();
	std::cout << "初期化完了!" << std::endl;
	//ﾃﾞﾊﾞｯｸ//左上を基準とした座標を取得し保持しておく(後続処理により元の配列がおきかえられるため)
	CFrame result = CFrame(
		CXY(lire_targets.get(Alpha).X() - lire_parts.get(opt).X(), UppY),
		CXY(lire_targets.get(Alpha).X(), UppY + lire_parts.get(opt).Y())
		);
	// lire_targets > lire_parts の差分を求める
	CRectance difAlphaOpt;
	difAlphaOpt.set(
		lire_targets.get(Alpha).X() - lire_parts.get(opt).X(),
		lire_targets.get(Alpha).Y() - lire_parts.get(opt).Y()
		);
	//どちらかが負の場合は切り出せないので次の対象範囲を選択する
	std::cout << "difAlphaOpt? X : " << difAlphaOpt.X() << ", Y : " << difAlphaOpt.Y() << std::endl;
	if(difAlphaOpt.X() < 0 || difAlphaOpt.Y() < 0){
		count++;
		if(count < lire_targets.lenght()){
			return cutout();
		} else {
			throw -1;
		}
	}
	//再設定
	//difAlphaOpt.set(
	//	lire_targets.get(Alpha).X() - lire_parts.get(opt).X(),
	//	lire_targets.get(Alpha).Y() - lire_parts.get(opt).Y()
	//	);
	//上側か下側で余白が小さい方に上端または下端を合わせ切り出す
	CRectance insertRec;
	CRectance setRec;
	std::cout << "対象範囲 [0-" << lire_targets.lenght() - 1 << "] " << "Alpha : " << Alpha << std::endl;
	if(UppY < LowY){
		insertRec.set(difAlphaOpt.X(), lire_parts.get(opt).Y());
		setRec.set(lire_targets.get(Alpha).X(), difAlphaOpt.Y());
	} else {
		insertRec.set(lire_targets.get(Alpha).X(), difAlphaOpt.Y());
		setRec.set(difAlphaOpt.X(), lire_parts.get(opt).Y());
		//下側に合わせるので切り出し座標のY座標をその分増加させる
		result.topL.y += difAlphaOpt.Y();
		result.lowR.y += difAlphaOpt.Y();
	}
	std::cout << "この範囲で" << opt << "層目の部品を切り出すんだからねっ!" << std::endl;
	std::cout << "insertRec? X : " << insertRec.X() << ", Y : " << insertRec.Y() << std::endl;
	std::cout << "   setRec? X : " << setRec.X() << ", Y : " << setRec.Y() << std::endl;
	//対象範囲へ切り出した後の対象範囲を追加
	lire_targets.insert(Alpha, insertRec.X(), insertRec.Y());
	//対象範囲から追加した範囲を除く
	lire_targets.set(Alpha + 1, setRec.X(), setRec.Y());
	//切り出した部品をクリア状態に推移させる
	std::cout << "Number [" << opt << "] はクリアよ!" << std::endl;
	lire_parts.Clear(opt);

	this->count = 0;
	std::cout << "result を返すよ!" << std::endl;
	return result;
}
std::vector<CFrame> CCoreRectance::cutouts(){
	while(!finished){
		try{
			results.push_back(cutout());
			std::cout << "切断座標をPushしたよ!" << std::endl;
		}catch(int ex){
			switch(ex){
					case 0:
						std::cout << "ﾔｯﾀね// 正常終了です!" << std::endl;
						break;
					case -1:
						std::cout << "予期せぬエラーだね!、やったー!" << std::endl;
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
