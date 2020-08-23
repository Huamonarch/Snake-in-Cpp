#pragma once
#ifndef __MYDATASTRUCTURE_H__
#define __MYDATASTRUCTURE_H__
#include<iostream>
/******************************************************************************************
  * Data Structures in C++
  * Chao Lan, a1933113480@163.com
  * version 1.0
  * 2020.07.08
  * 1.namespace MyVector            向量
  * 2.namespace MyList              列表
  * 3.namespace SequenceStack       顺序栈
  * 4.namespace ListStack           链式栈
  * 5.namespace SequenceQueue       顺序队列
  * 6.namespace ListQueue           链式队列
  * Shanghai Univisity
  ******************************************************************************************/
namespace MyVector
{
	typedef int Rank;
	const int default_capacity=3;
	template<typename T>class Vector
	{
	protected:
		Rank _size; int _capacity; T* _elem;//规模 容量 数据区
		void copyFrom(T const* A, Rank lo, Rank hi);//复制数组函数 区间[lo,hi)
		void expand();//动态扩容
		void shrink();//动态缩容
	public:
		//构造函数
		Vector(int c = default_capacity, int s = 0, T v = 0)//容量为c, 规模为s， 所有元素初始化为v
		{
			_elem = new T[_capacity = c]; for (_size = 0; _size < s; _elem[_size++] = v);
		}//s<=c
		Vector(T const* A, Rank n) { copyFrom(A, 0, n); }//数组整体复制
		Vector(T const* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); }//数组区间复制
		Vector(Vector<T> const& V) { copyFrom(V._elem, 0, V._size); }//向量整体复制
		Vector(Vector<T> const& V, Rank lo, Rank hi) { copyFrom(V._elem,lo,hi); }//向量区间复制
		//析构函数
			~Vector() { delete[] _elem; }//释放内部空间
		//只读访问接口
		Rank size()const { return _size; }//规模
		bool empty()const { return !_size; }//判空 

		//可写访问接口
		T& operator[] (Rank r)const { return _elem[r]; }//重载[]，实现Vector的类似数组形式引用各元素
		Vector<T>& operator= (Vector<T> const&);
		Rank insert(Rank r, const T& e);//将 e 插入秩为r处，并返回r
		Rank insert(T const& e) { return insert(_size, e); }//默认插入至末尾 elem[size]是新的末尾，size +=1
		int remove(Rank lo, Rank hi);//删除区间[lo,hi)的元素，并返回被删除的元素个数
		T remove(Rank r);
	};//Vector
	//可写访问接口实现
	template<typename T>Vector<T>& Vector<T>::operator=(Vector<T> const& V)
	{
		if (_elem)
		{
			delete[] _elem;
		}
		copyFrom(V._elem, 0, V._size);
		return *this;
	}//重载=
	template<typename T>Rank Vector<T>:: insert(Rank r, T const& e)// 0<=r<=size
	{
		expand();
		for (size_t i = _size; i > r; i--)
		{
			_elem[i] = _elem[i - 1];
		}
		_elem[r] = e;
		_size++;//更新规模
		return r;
	}//插入
	template<typename T>int Vector<T>:: remove(Rank lo, Rank hi)
	{
		if (lo == hi)return 0;
		while (hi<_size)
		{
			_elem[lo++] = _elem[hi++];
		}
		_size = lo;//更新size  因为lo++是取lo再++  最后一次是 _elem[lo]=_elem[hi];lo++;hi++
				   // 退出while循环后  lo比_elem数组最大下标大1
		shrink();
		return hi - lo;
	}
	template<typename T>T Vector<T>::remove(Rank r)
	{
		T e = _elem[r];
		remove(r, r + 1);
		return e;
	}
	//protected 成员函数实现
	template<typename T>void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi)
	{
		_elem = new T[_capacity = 2 * (hi - lo)];//分配空间
		_size = 0;//规模清零
		while (lo<hi)//复制A至_elem[0,hi-lo)
		{
			_elem[_size++] = A[lo++];
		}
	}//深复制
	template<typename T>void Vector<T>::expand()
	{
		if (_size < _capacity)return;
		if (_capacity < default_capacity)_capacity = default_capacity;//不低于最小容量
		T* oldelem = _elem; _elem = new T[_capacity <<1];
		for (size_t i = 0; i < _size; i++)
		{
			_elem[i] = oldelem[i];
		}
		delete[] oldelem;
	}//倍增扩容策略
	template<typename T>void Vector<T>::shrink()
	{
		if (_capacity > _capacity >> 1)return;
		if (_size << 2 > _capacity)return;//装填因子 size/capacity>25 则不用缩容
		T* oldelem = _elem; _elem = new T[_capacity >> 1];
		for (size_t i = 0; i < _size; i++)
		{
			_elem[i] = oldelem[i];
		}
		delete[] oldelem;
	}//减半缩容策略 
}//namespace MyVector
namespace MyList
{
	typedef int Rank;
	template<typename T>struct ListNode 
	{
		//属性（成员）
		T data; ListNode<T>* pred; ListNode<T>*succ;//数据  前驱  后继
		//构造函数
		ListNode() {};// header trailer 的构造
		ListNode(T e, ListNode<T>* p = nullptr, ListNode<T>* s = nullptr) :data(e), pred(p), succ(s) {};
		//操作接口
		ListNode<T>* insertAsPred(T const& e);
		ListNode<T>* insertAsSucc(T const& e);
	};//struct ListNode 未封装数据
	//操作接口 实现
	template<typename T>ListNode<T>* ListNode<T>::insertAsPred(T const& e)
	{
		ListNode<T>* newnode = new ListNode(e, pred, this);//newnode的前驱指向this->pred;  newnode的后继指向this
		pred->succ = newnode; pred = newnode;//this->pred->succ指向newnode;  this->pred指向newnode
		return newnode;//返回插入的节点
	}//insertAsPred
	template<typename T>ListNode<T>* ListNode<T>::insertAsSucc(T const& e)
	{
		ListNode<T>* newnode = new ListNode(e, this, succ);//newnode的前驱指向this;  newnode的后继指向succ
		succ->pred = newnode; succ = newnode;//this->succ->pred指向newnode;  this->succ指向newnode
		return newnode;//返回插入的节点
	}//insertAsSucc

	template<typename T>class List
	{
	private:
		int _size; ListNode<T>* header; ListNode<T>* trailer;//规模  头节点  尾节点
	protected:
		void init();//列表初始化
		int clear();//清楚所有数据节点  不包括头节点 尾节点
		void copyNodes(ListNode<T>* p, int n);//复制list中 自p起的n项
	public:
		//构造函数
		List() { init(); }//默认构造函数
		List(List<T> const& L);//整体复制
		List(ListNode<T>* p, int n) { copyNodes(p, n); }//复制list中 自p起的n项
		List(List<T> const& L, Rank r, int n) { copyNodes(L.goToRankr(r), n); }//复制list中 第r项起的n项
		//析构函数
		~List() { clear(); delete header; delete trailer; };//释放所有节点  先删除数据节点 再删除 头 尾
		//只读访问接口
		Rank size()const { return _size; }//规模
		bool empty()const { return _size <= 0; }//判空
		T& operator[](Rank r)const;//重载 [] 但效率较低
		ListNode<T>* goToRankr(Rank r) const;//返回秩为r的节点
		ListNode<T>* first()const { return header->succ; }
		ListNode<T>* last()const { return trailer->pred; }
		//可写访问接口
		ListNode<T>* insertAsFirst(T const& e) { _size++;return header->insertAsSucc(e); }//将e作为list的首节点插入
		ListNode<T>* insertAsLast(T const& e) { _size++; return trailer->insertAsPred(e); }//将e作为list的末节点插入
		ListNode<T>* insertA(ListNode<T>*p,T const& e) { _size++; return p->insertAsSucc(e); }//将e作为p的后继插入
		ListNode<T>* insertB(ListNode<T>* p, T const& e) { _size++; return p->insertAsSucc(e); }//将e作为p的前驱插入
		T remove(ListNode<T>* p);//删除p节点，并返回p节点所对应的数据
	};//List
	//protected 成员函数实现
	template<typename T>void List<T>::init()
	{
		header = new ListNode<T>;
		trailer = new ListNode<T>;
		header->succ = trailer; header->pred = nullptr;
		trailer->pred = header; trailer->succ = nullptr;
		_size = 0;
	}//list 初始化
	template<typename T>int List<T>::clear()
	{
		int Oldsize = _size;
		while (_size>0)
		{
			remove(trailer->pred);
		}
		return Oldsize;
	}// 数据清除
	template<typename T>void List<T>::copyNodes(ListNode<T>*p,int n)
	{
		init();
		ListNode<T>* q = header;
		while (0<n--)
		{
			q = q->insertAsSucc(p->data);
			p = p->succ;
			_size++;
		}
	}
	//pubilc 成员函数
	//构造函数
	template<typename T>List<T>::List(List<T> const& L)
	{
		copyNodes(L.first(), L.size());
	}//整体复制

	// 只读访问接口
	template<typename T>T& List<T>::operator[](Rank r)const
	{
		ListNode<T>* p = header->succ;
		while (0<r--)
		{
			p = p->succ;
		}
		return p->data;
	}// 重载[] 实现下标索引  r范围为[0,size)
	
	template<typename T>ListNode<T>* List<T>::goToRankr(Rank r) const
	{
		ListNode<T>* p = header->succ;
		while (0 < r--)
		{
			p = p->succ;
		}
		return p;
	}
	//可写访问接口
	template<typename T>T List<T>::remove(ListNode<T>*p)
	{
		T data = p->data;
		p->pred->succ = p->succ;
		p->succ->pred = p->pred;
		delete p;
		_size--;
		return data;
	}// 删除p节点 并返回p->data
}//MyList
namespace SequenceStack
{
	template<typename T>
	class Seqstack:public MyVector::Vector<T>
	{
		typedef  MyVector::Vector<T> Mvector;
	public:
		void push(const T& e) { Mvector::insert(Mvector::size(), e); }//入栈
		T pop() { return Mvector::remove(Mvector::size() - 1); }//出栈
		T& top() { return (*this)[Mvector::size() - 1]; }//取顶
	};//Seqstack
}//SequenceStack
namespace ListStack
{
	template<typename T>
	class Liststack:public MyList::List<T>
	{
		typedef MyList::List<T> MList;
	public:
		void push(T const& e) { MList::insertAsFirst(e); }//入栈
		T pop() { return MList::remove(this->first()); }//出栈
		T& top() { return this->first()->data; }//取顶  或 return (*this)[0]
	}; //Liststack
}//ListStack
namespace SequenceQueue
{
	template<typename T>
	class Seqqueue :public MyVector::Vector<T>
	{
		typedef MyVector::Vector<T> Mvector;
	public:
		void enqueue(T const& e) { Mvector::insert(0, e); }//入队
		T dequeue() { return Mvector::remove(Mvector::size()-1);}//出队
		T& front() { return (*this)[Mvector::size()-1]; }//取首
	}; //Seqqueue
}//SequenceQueue
namespace ListQueue
{
	template<typename T>
	class Listqueue:public MyList::List<T>
	{
		typedef MyList::List<T> MList;
	public:
		void enqueue(T const& e) { MList::insertAsLast(e); }//入队
		T dequeue() { return MList::remove(this->first()); }//出队
		T& front() { return (*this)[0]; }//取首
	}; //Listqueue
}//ListQueue

namespace MyBinTree
{
	/* BinNode状态与性质的判断 */
#define stature(p) ((p)?(p)->height:-1)//宏定义会无视namespace 整个*.h文件均可见 stature(p) ((p)?(p)->height:-1)
#define IsRoot(x) (!((x).parent))// 判断x是否为根节点  x的父节点为 nullptr ，则x为 root
#define IsLChild(x) (!IsRoot(x) &&(&(x)==(x).parent->leftChild)) //判断x 是否是树的一个左节点
#define IsRChild(x) (!IsRoot(x) &&(&(x)==(x).parent->rightChild)) //判断x 是否是树的一个右节点
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).leftChild)
#define HasRChild(x) ((x).rightChild)
#define HasChild(x) (HasLChild(x)||HasRChild(x))//至少拥有一个孩子
#define HasBothChild(x) (HasLChild(x)&&HasRChild(x))//同时拥有两个孩子
#define IsLeaf(x) (! HasChild(x))
	/* 与BinNode 具有特定关系的节点及指针*/
#define sibling(p) /*兄弟*/( IsLChild(*(p)) ? (p)->parent->rightChild:(p)->parent->leftChild)
#define uncle(x) /*叔叔*/( IsLChild(*((x)->parent) ? (x)->parent->parent->rightChild:(p)->parent->parent->leftChild)
#define FromParentTo(x)/* 来自父亲的引用*/( IsRoot(x) ? _root :(IsLChild(x)?(x).parent->leftChild:(x).parent->rightChild))





	typedef enum{RB_RED,RB_BLACK} RBColor;//节点颜色
	template<typename T> struct BinNode
	{
		T data;
		BinNode<T>* parent;     //父节点
		BinNode<T>* leftChild;  //左孩子
		BinNode<T>* rightChild; //右孩子
		int height;//高度
		int npl;//Null Path Length 左式堆
		RBColor color;//红黑树 颜色
		//构造函数
		BinNode():
			parent(nullptr),leftChild(nullptr),rightChild(nullptr),height(0),npl(0),color(RB_RED){}
		BinNode(T e,BinNode<T>* p=nullptr,BinNode<T>* lc=nullptr,BinNode<T>* rc=nullptr,int h=0,int l=1,RBColor c=RB_RED):
			data(e),parent(p),leftChild(lc),rightChild(rc),height(h),npl(l),color(c){}
		//操作接口
		int size();//当前节点的后代总数，或称 以当前节点为根的子树规模
		BinNode<T>* insertAsLC(T const&);//左孩子插入
		BinNode<T>* insertAsRC(T const&);//右孩子插入
		//BinNode<T>* succ();              //返回当前节点的直接后继  （中序遍历）
	};//BinNode
	//操作接口
	template<typename T> BinNode<T>* BinNode<T>::insertAsLC(T const& e)
	{	return leftChild = new BinNode(e, this);}//左孩子插入
	template<typename T> BinNode<T>* BinNode<T>::insertAsRC(T const& e)
	{	return rightChild = new BinNode(e, this);}//右孩子插入

	template<typename T> int BinNode<T>::size()
	{
		int s = 1;//计入本身
		if (leftChild) s += leftChild->size();
		if (rightChild) s += rightChild->size();
		return s;
	}// size() 规模

	template<typename T>class  BinTree
	{//二叉树模板类
	protected:
		int _size;//树的规模
		BinNode<T>* _root;//根节点
		virtual int updateHeight(BinNode<T>* x);//更新节点x的高度
		void updateHeightAbove(BinNode<T>* x);//更新节点x及其祖先的高度
	public:
		//构造函数
		BinTree() : _size(0), _root(nullptr) {}
		~BinTree() { if(0 < _size) remove(_root); }
		// 操作接口
		int remove(BinNode<T>* x);//删除以x为根的子树，并返回被删除子树原先的规模
		int size()const { return _size; }//树的规模
		bool empty()const { return !_root; }//判空   _root==nullptr(为false),则   !_root（！false） 为true
		BinNode<T>* root() { return _root; }//树根
		BinNode<T>* insertAsRoot(T const& e);//作为根节点插入
		BinNode<T>* insertAsLC(BinNode<T>* x, T const& e);//e作为x的左孩子插入
		BinNode<T>* insertAsRC(BinNode<T>* x, T const& e);//e作为x的右孩子插入
		BinNode<T>* attachAsLC(BinNode<T>* x, BinTree<T>*& S);//S作为x的左子树接入
		BinNode<T>* attachAsRC(BinNode<T>* x, BinTree <T>*& S);//S作为x的右子树接入
		BinTree<T>* secede(BinNode<T>* x);//将子树x从当前树中摘除，并将其转化为一颗独立子树




	};//BinTree
	//protected
	int max(int a,int b)
	{
		if(a>b) return a;
		else return b;
	}
	template<typename T>int BinTree<T>::updateHeight(BinNode<T>* x)
	{
		return x->height = 1 + max(stature(x->leftChild), stature(x->rightChild));
	}
	template<typename T>void BinTree<T>::updateHeightAbove(BinNode<T>* x) 
	{
		while (x)
		{
			updateHeight(x);
			x = x->parent;
		}//从x出发 覆盖历代祖先
	}
	
	//public
	template<typename T>BinNode<T>* BinTree<T>::insertAsRoot(T const& e)
	{
		_size = 1;
		return _root = new BinNode<T>(e);
	}//e当作根节点插入空的二叉树
	//子节点的插入
	template<typename T>BinNode<T>* BinTree<T>::insertAsLC(BinNode<T>* x, T const& e)
	{
		_size++;
		x->insertAsLC(e);
		updateHeightAbove(x);
		return x->leftChild;
	}//左节点插入
	template<typename T>BinNode<T>* BinTree<T>::insertAsRC(BinNode<T>* x, T const& e)
	{
		_size++;
		x->insertAsRC(e);
		updateHeightAbove(x);
		return x->rightChild;
	}//右节点插入

	// 子树的插入
	template<typename T>BinNode<T>* BinTree<T>::attachAsLC(BinNode<T>* x, BinTree<T>* &S)//T作为x的左子树接入
	{
		if (x->leftChild = S->_root) x->leftChild->parent = x;//类成员函数可以访问类对象的私有成员
		_size += S->_size;                   //这里BinTree类成员函数attachAsLC访问了其对象S的protected成员_size,_root
		updateHeightAbove(x);
		S->_root = nullptr;
		S->_size = 0;
		//release(S);//   release( )  ?
		S = nullptr;
		return x;
	}//左子树插入	
	template<typename T>BinNode<T>* BinTree<T>::attachAsRC(BinNode<T>* x, BinTree <T>* &S)//T作为x的右子树接入
	{
		if (x->rightChild = S->_root) x->rightChild->parent = x;
		_size += S->_size;
		updateHeightAbove(x);
		S->_root = nullptr;
		S->_size = 0;
		//release(S);//   release( )  ?
		S = nullptr;
		return x;
	}//右子树插入

	//子树的删除
	template<typename T>int BinTree<T>::remove(BinNode<T>* x)//删除二叉树中，x的的节点及其后代，并返回被删除的节点数
	{
		FromParentTo(*x) = nullptr;
		updateHeightAbove(x->parent);
		int n = removeAt(x);
		_size -= n;
		return n;
	}
	template<typename T>static int removeAt(BinNode<T>* x)
	{
		if (!x) return 0;//空树
		int n = 1 + removeAt(x->leftChild) + removeAt(x->rightChild);
		delete x;
		x = nullptr;
		return n;
	}
	template<typename T>BinTree<T>* BinTree<T>::secede(BinNode<T>* x)
	{
		FromParentTo(*x) = nullptr;
		updateHeightAbove(x->parent);
		BinTree<T>* S = new BinTree<T>;
		S->_root = x;
		x->parent = nullptr;
		S->_size = x->size();
		_size -= S->_size;
		return S;
	}
	template<typename T>
	class VST
	{
	public:
		void operator() (T data)
		{
			std::cout << "data is:" << data << std::endl;
		}
	};
template<typename T,typename VST>void travPre_R(BinNode<T>* x, VST& visit)
{
	if (!x) return;
	visit(x->data);
	travPre_R(x->leftChild, visit);
	travPre_R(x->rightChild, visit);
}//先序递归
template<typename T, typename VST>void travPost_R(BinNode<T>* x, VST& visit)
{
	if (!x) return;
	travPost_R(x->leftChild, visit);
	travPost_R(x->rightChild, visit);
	visit(x->data);
}//后序递归
template<typename T, typename VST>void travIn_R(BinNode<T>* x, VST& visit)
{
	if (!x) return;
	travIn_R(x->leftChild, visit);
	visit(x->data);
	travIn_R(x->rightChild, visit);
}//中序递归



};//MyBinTree

#endif // !__MYDATASTRUCTURE_H__

