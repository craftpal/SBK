#pragma once

#include <iostream>
#include <vector>

namespace cutout{
	class CRank {
	private:
		int x, y;
	public:
		CRank();
		void X(int x);
		int X();
		void Y(int y);
		int Y();
		void Xadd(int value);
		void Yadd(int value);
	};


	class CSortItem {
	public:
		int index;
		int data;
		CSortItem(int index, int data);
	};

	class CSortList {
	private:
		std::vector<CSortItem> items;
	public:
		CSortList();
		CSortItem get(int index);
		void add(int index, int data);
		int size();
		void clear();
		void show_items();
	};

	class CRectance {
	private:
		int x, y;
		int ranked;
		CRank rank;
		bool cleared;
	public:
		CRectance();
		CRectance(int x, int y);
		CRectance operator-(CRectance rect);
		void X(int x);
		int X();
		void Y(int y);
		int Y();
		void Xadd(int value);
		void Yadd(int value);
		void set(int x, int y);
		bool insered(CRectance rect);
		CRank& Rank();
		void Rank(int value);
		int Ranked();
		void RankUp();
		void Clear();
		bool Cleared();
		static CRectance input_rect(bool explain);
		static CRectance input_rect(bool explain, char *str, int count);
	};

	class CListRectance {
	private:
		std::vector<CRectance> v_rec;
		void to_rank();
	public:
		static int search_insered(CRectance target, CListRectance parts, int order);
		CRectance get(int index);
		CRectance max_size();
		void add(int x, int y);
		void add(CRectance data);
		void set(int index, int x, int y);
		void setAddX(int index, int x);
		void setAddY(int index, int y);
		void setAdd(int index, int x, int y);
		void insert(int index, int x, int y);
		int lenght();
		void Rank(int index, int value);
		void RankUp(int index);
		int find_index_ofx(int x);
		void Clear(int index);
		void clear();
		bool del(int index);
		static CListRectance input_list_rect();
		static CListRectance input_list_rect(char *str);
	};

	class CXY {
	public:
		int x;
		int y;
		CXY();
		CXY(int x, int y);
	};

	class CFrame {
	public:
		CXY topL;
		CXY lowR;
		CFrame(CXY topL, CXY lowR);
		void show();
		//左 X からの相対座標( Y は絶対)
		void show(int x);
	};

	class CCoreRectance {
	private:
		std::vector<CFrame> results;
		bool finished;
		int Alpha,		//切り出し範囲として選択された分割範囲の番号
			opt,		//最適と推測された切り出し部品の番号
			UppY, LowY,	//切り出し範囲の上側・下側の余白サイズ
			count;		//切り出し範囲の昇順の何番目を選ぶか
		CListRectance lire_targets, lire_parts, difRecs;
		//初期化
		void init();
	public:
		CCoreRectance(CListRectance targets, CListRectance parts);
		CFrame cutout();
		std::vector<CFrame> cutouts();
	};
}