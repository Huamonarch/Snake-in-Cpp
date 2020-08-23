#pragma once
#ifndef __MYDATASTRUCTURE_H__
#define __MYDATASTRUCTURE_H__
#include<iostream>
/******************************************************************************************
  * Data Structures in C++
  * Chao Lan, a1933113480@163.com
  * version 1.0
  * 2020.07.08
  * 1.namespace MyVector            ����
  * 2.namespace MyList              �б�
  * 3.namespace SequenceStack       ˳��ջ
  * 4.namespace ListStack           ��ʽջ
  * 5.namespace SequenceQueue       ˳�����
  * 6.namespace ListQueue           ��ʽ����
  * Shanghai Univisity
  ******************************************************************************************/
namespace MyVector
{
	typedef int Rank;
	const int default_capacity=3;
	template<typename T>class Vector
	{
	protected:
		Rank _size; int _capacity; T* _elem;//��ģ ���� ������
		void copyFrom(T const* A, Rank lo, Rank hi);//�������麯�� ����[lo,hi)
		void expand();//��̬����
		void shrink();//��̬����
	public:
		//���캯��
		Vector(int c = default_capacity, int s = 0, T v = 0)//����Ϊc, ��ģΪs�� ����Ԫ�س�ʼ��Ϊv
		{
			_elem = new T[_capacity = c]; for (_size = 0; _size < s; _elem[_size++] = v);
		}//s<=c
		Vector(T const* A, Rank n) { copyFrom(A, 0, n); }//�������帴��
		Vector(T const* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); }//�������临��
		Vector(Vector<T> const& V) { copyFrom(V._elem, 0, V._size); }//�������帴��
		Vector(Vector<T> const& V, Rank lo, Rank hi) { copyFrom(V._elem,lo,hi); }//�������临��
		//��������
			~Vector() { delete[] _elem; }//�ͷ��ڲ��ռ�
		//ֻ�����ʽӿ�
		Rank size()const { return _size; }//��ģ
		bool empty()const { return !_size; }//�п� 

		//��д���ʽӿ�
		T& operator[] (Rank r)const { return _elem[r]; }//����[]��ʵ��Vector������������ʽ���ø�Ԫ��
		Vector<T>& operator= (Vector<T> const&);
		Rank insert(Rank r, const T& e);//�� e ������Ϊr����������r
		Rank insert(T const& e) { return insert(_size, e); }//Ĭ�ϲ�����ĩβ elem[size]���µ�ĩβ��size +=1
		int remove(Rank lo, Rank hi);//ɾ������[lo,hi)��Ԫ�أ������ر�ɾ����Ԫ�ظ���
		T remove(Rank r);
	};//Vector
	//��д���ʽӿ�ʵ��
	template<typename T>Vector<T>& Vector<T>::operator=(Vector<T> const& V)
	{
		if (_elem)
		{
			delete[] _elem;
		}
		copyFrom(V._elem, 0, V._size);
		return *this;
	}//����=
	template<typename T>Rank Vector<T>:: insert(Rank r, T const& e)// 0<=r<=size
	{
		expand();
		for (size_t i = _size; i > r; i--)
		{
			_elem[i] = _elem[i - 1];
		}
		_elem[r] = e;
		_size++;//���¹�ģ
		return r;
	}//����
	template<typename T>int Vector<T>:: remove(Rank lo, Rank hi)
	{
		if (lo == hi)return 0;
		while (hi<_size)
		{
			_elem[lo++] = _elem[hi++];
		}
		_size = lo;//����size  ��Ϊlo++��ȡlo��++  ���һ���� _elem[lo]=_elem[hi];lo++;hi++
				   // �˳�whileѭ����  lo��_elem��������±��1
		shrink();
		return hi - lo;
	}
	template<typename T>T Vector<T>::remove(Rank r)
	{
		T e = _elem[r];
		remove(r, r + 1);
		return e;
	}
	//protected ��Ա����ʵ��
	template<typename T>void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi)
	{
		_elem = new T[_capacity = 2 * (hi - lo)];//����ռ�
		_size = 0;//��ģ����
		while (lo<hi)//����A��_elem[0,hi-lo)
		{
			_elem[_size++] = A[lo++];
		}
	}//���
	template<typename T>void Vector<T>::expand()
	{
		if (_size < _capacity)return;
		if (_capacity < default_capacity)_capacity = default_capacity;//��������С����
		T* oldelem = _elem; _elem = new T[_capacity <<1];
		for (size_t i = 0; i < _size; i++)
		{
			_elem[i] = oldelem[i];
		}
		delete[] oldelem;
	}//�������ݲ���
	template<typename T>void Vector<T>::shrink()
	{
		if (_capacity > _capacity >> 1)return;
		if (_size << 2 > _capacity)return;//װ������ size/capacity>25 ��������
		T* oldelem = _elem; _elem = new T[_capacity >> 1];
		for (size_t i = 0; i < _size; i++)
		{
			_elem[i] = oldelem[i];
		}
		delete[] oldelem;
	}//�������ݲ��� 
}//namespace MyVector
namespace MyList
{
	typedef int Rank;
	template<typename T>struct ListNode 
	{
		//���ԣ���Ա��
		T data; ListNode<T>* pred; ListNode<T>*succ;//����  ǰ��  ���
		//���캯��
		ListNode() {};// header trailer �Ĺ���
		ListNode(T e, ListNode<T>* p = nullptr, ListNode<T>* s = nullptr) :data(e), pred(p), succ(s) {};
		//�����ӿ�
		ListNode<T>* insertAsPred(T const& e);
		ListNode<T>* insertAsSucc(T const& e);
	};//struct ListNode δ��װ����
	//�����ӿ� ʵ��
	template<typename T>ListNode<T>* ListNode<T>::insertAsPred(T const& e)
	{
		ListNode<T>* newnode = new ListNode(e, pred, this);//newnode��ǰ��ָ��this->pred;  newnode�ĺ��ָ��this
		pred->succ = newnode; pred = newnode;//this->pred->succָ��newnode;  this->predָ��newnode
		return newnode;//���ز���Ľڵ�
	}//insertAsPred
	template<typename T>ListNode<T>* ListNode<T>::insertAsSucc(T const& e)
	{
		ListNode<T>* newnode = new ListNode(e, this, succ);//newnode��ǰ��ָ��this;  newnode�ĺ��ָ��succ
		succ->pred = newnode; succ = newnode;//this->succ->predָ��newnode;  this->succָ��newnode
		return newnode;//���ز���Ľڵ�
	}//insertAsSucc

	template<typename T>class List
	{
	private:
		int _size; ListNode<T>* header; ListNode<T>* trailer;//��ģ  ͷ�ڵ�  β�ڵ�
	protected:
		void init();//�б��ʼ��
		int clear();//����������ݽڵ�  ������ͷ�ڵ� β�ڵ�
		void copyNodes(ListNode<T>* p, int n);//����list�� ��p���n��
	public:
		//���캯��
		List() { init(); }//Ĭ�Ϲ��캯��
		List(List<T> const& L);//���帴��
		List(ListNode<T>* p, int n) { copyNodes(p, n); }//����list�� ��p���n��
		List(List<T> const& L, Rank r, int n) { copyNodes(L.goToRankr(r), n); }//����list�� ��r�����n��
		//��������
		~List() { clear(); delete header; delete trailer; };//�ͷ����нڵ�  ��ɾ�����ݽڵ� ��ɾ�� ͷ β
		//ֻ�����ʽӿ�
		Rank size()const { return _size; }//��ģ
		bool empty()const { return _size <= 0; }//�п�
		T& operator[](Rank r)const;//���� [] ��Ч�ʽϵ�
		ListNode<T>* goToRankr(Rank r) const;//������Ϊr�Ľڵ�
		ListNode<T>* first()const { return header->succ; }
		ListNode<T>* last()const { return trailer->pred; }
		//��д���ʽӿ�
		ListNode<T>* insertAsFirst(T const& e) { _size++;return header->insertAsSucc(e); }//��e��Ϊlist���׽ڵ����
		ListNode<T>* insertAsLast(T const& e) { _size++; return trailer->insertAsPred(e); }//��e��Ϊlist��ĩ�ڵ����
		ListNode<T>* insertA(ListNode<T>*p,T const& e) { _size++; return p->insertAsSucc(e); }//��e��Ϊp�ĺ�̲���
		ListNode<T>* insertB(ListNode<T>* p, T const& e) { _size++; return p->insertAsSucc(e); }//��e��Ϊp��ǰ������
		T remove(ListNode<T>* p);//ɾ��p�ڵ㣬������p�ڵ�����Ӧ������
	};//List
	//protected ��Ա����ʵ��
	template<typename T>void List<T>::init()
	{
		header = new ListNode<T>;
		trailer = new ListNode<T>;
		header->succ = trailer; header->pred = nullptr;
		trailer->pred = header; trailer->succ = nullptr;
		_size = 0;
	}//list ��ʼ��
	template<typename T>int List<T>::clear()
	{
		int Oldsize = _size;
		while (_size>0)
		{
			remove(trailer->pred);
		}
		return Oldsize;
	}// �������
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
	//pubilc ��Ա����
	//���캯��
	template<typename T>List<T>::List(List<T> const& L)
	{
		copyNodes(L.first(), L.size());
	}//���帴��

	// ֻ�����ʽӿ�
	template<typename T>T& List<T>::operator[](Rank r)const
	{
		ListNode<T>* p = header->succ;
		while (0<r--)
		{
			p = p->succ;
		}
		return p->data;
	}// ����[] ʵ���±�����  r��ΧΪ[0,size)
	
	template<typename T>ListNode<T>* List<T>::goToRankr(Rank r) const
	{
		ListNode<T>* p = header->succ;
		while (0 < r--)
		{
			p = p->succ;
		}
		return p;
	}
	//��д���ʽӿ�
	template<typename T>T List<T>::remove(ListNode<T>*p)
	{
		T data = p->data;
		p->pred->succ = p->succ;
		p->succ->pred = p->pred;
		delete p;
		_size--;
		return data;
	}// ɾ��p�ڵ� ������p->data
}//MyList
namespace SequenceStack
{
	template<typename T>
	class Seqstack:public MyVector::Vector<T>
	{
		typedef  MyVector::Vector<T> Mvector;
	public:
		void push(const T& e) { Mvector::insert(Mvector::size(), e); }//��ջ
		T pop() { return Mvector::remove(Mvector::size() - 1); }//��ջ
		T& top() { return (*this)[Mvector::size() - 1]; }//ȡ��
	};//Seqstack
}//SequenceStack
namespace ListStack
{
	template<typename T>
	class Liststack:public MyList::List<T>
	{
		typedef MyList::List<T> MList;
	public:
		void push(T const& e) { MList::insertAsFirst(e); }//��ջ
		T pop() { return MList::remove(this->first()); }//��ջ
		T& top() { return this->first()->data; }//ȡ��  �� return (*this)[0]
	}; //Liststack
}//ListStack
namespace SequenceQueue
{
	template<typename T>
	class Seqqueue :public MyVector::Vector<T>
	{
		typedef MyVector::Vector<T> Mvector;
	public:
		void enqueue(T const& e) { Mvector::insert(0, e); }//���
		T dequeue() { return Mvector::remove(Mvector::size()-1);}//����
		T& front() { return (*this)[Mvector::size()-1]; }//ȡ��
	}; //Seqqueue
}//SequenceQueue
namespace ListQueue
{
	template<typename T>
	class Listqueue:public MyList::List<T>
	{
		typedef MyList::List<T> MList;
	public:
		void enqueue(T const& e) { MList::insertAsLast(e); }//���
		T dequeue() { return MList::remove(this->first()); }//����
		T& front() { return (*this)[0]; }//ȡ��
	}; //Listqueue
}//ListQueue

namespace MyBinTree
{
	/* BinNode״̬�����ʵ��ж� */
#define stature(p) ((p)?(p)->height:-1)//�궨�������namespace ����*.h�ļ����ɼ� stature(p) ((p)?(p)->height:-1)
#define IsRoot(x) (!((x).parent))// �ж�x�Ƿ�Ϊ���ڵ�  x�ĸ��ڵ�Ϊ nullptr ����xΪ root
#define IsLChild(x) (!IsRoot(x) &&(&(x)==(x).parent->leftChild)) //�ж�x �Ƿ�������һ����ڵ�
#define IsRChild(x) (!IsRoot(x) &&(&(x)==(x).parent->rightChild)) //�ж�x �Ƿ�������һ���ҽڵ�
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).leftChild)
#define HasRChild(x) ((x).rightChild)
#define HasChild(x) (HasLChild(x)||HasRChild(x))//����ӵ��һ������
#define HasBothChild(x) (HasLChild(x)&&HasRChild(x))//ͬʱӵ����������
#define IsLeaf(x) (! HasChild(x))
	/* ��BinNode �����ض���ϵ�Ľڵ㼰ָ��*/
#define sibling(p) /*�ֵ�*/( IsLChild(*(p)) ? (p)->parent->rightChild:(p)->parent->leftChild)
#define uncle(x) /*����*/( IsLChild(*((x)->parent) ? (x)->parent->parent->rightChild:(p)->parent->parent->leftChild)
#define FromParentTo(x)/* ���Ը��׵�����*/( IsRoot(x) ? _root :(IsLChild(x)?(x).parent->leftChild:(x).parent->rightChild))





	typedef enum{RB_RED,RB_BLACK} RBColor;//�ڵ���ɫ
	template<typename T> struct BinNode
	{
		T data;
		BinNode<T>* parent;     //���ڵ�
		BinNode<T>* leftChild;  //����
		BinNode<T>* rightChild; //�Һ���
		int height;//�߶�
		int npl;//Null Path Length ��ʽ��
		RBColor color;//����� ��ɫ
		//���캯��
		BinNode():
			parent(nullptr),leftChild(nullptr),rightChild(nullptr),height(0),npl(0),color(RB_RED){}
		BinNode(T e,BinNode<T>* p=nullptr,BinNode<T>* lc=nullptr,BinNode<T>* rc=nullptr,int h=0,int l=1,RBColor c=RB_RED):
			data(e),parent(p),leftChild(lc),rightChild(rc),height(h),npl(l),color(c){}
		//�����ӿ�
		int size();//��ǰ�ڵ�ĺ����������� �Ե�ǰ�ڵ�Ϊ����������ģ
		BinNode<T>* insertAsLC(T const&);//���Ӳ���
		BinNode<T>* insertAsRC(T const&);//�Һ��Ӳ���
		//BinNode<T>* succ();              //���ص�ǰ�ڵ��ֱ�Ӻ��  �����������
	};//BinNode
	//�����ӿ�
	template<typename T> BinNode<T>* BinNode<T>::insertAsLC(T const& e)
	{	return leftChild = new BinNode(e, this);}//���Ӳ���
	template<typename T> BinNode<T>* BinNode<T>::insertAsRC(T const& e)
	{	return rightChild = new BinNode(e, this);}//�Һ��Ӳ���

	template<typename T> int BinNode<T>::size()
	{
		int s = 1;//���뱾��
		if (leftChild) s += leftChild->size();
		if (rightChild) s += rightChild->size();
		return s;
	}// size() ��ģ

	template<typename T>class  BinTree
	{//������ģ����
	protected:
		int _size;//���Ĺ�ģ
		BinNode<T>* _root;//���ڵ�
		virtual int updateHeight(BinNode<T>* x);//���½ڵ�x�ĸ߶�
		void updateHeightAbove(BinNode<T>* x);//���½ڵ�x�������ȵĸ߶�
	public:
		//���캯��
		BinTree() : _size(0), _root(nullptr) {}
		~BinTree() { if(0 < _size) remove(_root); }
		// �����ӿ�
		int remove(BinNode<T>* x);//ɾ����xΪ���������������ر�ɾ������ԭ�ȵĹ�ģ
		int size()const { return _size; }//���Ĺ�ģ
		bool empty()const { return !_root; }//�п�   _root==nullptr(Ϊfalse),��   !_root����false�� Ϊtrue
		BinNode<T>* root() { return _root; }//����
		BinNode<T>* insertAsRoot(T const& e);//��Ϊ���ڵ����
		BinNode<T>* insertAsLC(BinNode<T>* x, T const& e);//e��Ϊx�����Ӳ���
		BinNode<T>* insertAsRC(BinNode<T>* x, T const& e);//e��Ϊx���Һ��Ӳ���
		BinNode<T>* attachAsLC(BinNode<T>* x, BinTree<T>*& S);//S��Ϊx������������
		BinNode<T>* attachAsRC(BinNode<T>* x, BinTree <T>*& S);//S��Ϊx������������
		BinTree<T>* secede(BinNode<T>* x);//������x�ӵ�ǰ����ժ����������ת��Ϊһ�Ŷ�������




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
		}//��x���� ������������
	}
	
	//public
	template<typename T>BinNode<T>* BinTree<T>::insertAsRoot(T const& e)
	{
		_size = 1;
		return _root = new BinNode<T>(e);
	}//e�������ڵ����յĶ�����
	//�ӽڵ�Ĳ���
	template<typename T>BinNode<T>* BinTree<T>::insertAsLC(BinNode<T>* x, T const& e)
	{
		_size++;
		x->insertAsLC(e);
		updateHeightAbove(x);
		return x->leftChild;
	}//��ڵ����
	template<typename T>BinNode<T>* BinTree<T>::insertAsRC(BinNode<T>* x, T const& e)
	{
		_size++;
		x->insertAsRC(e);
		updateHeightAbove(x);
		return x->rightChild;
	}//�ҽڵ����

	// �����Ĳ���
	template<typename T>BinNode<T>* BinTree<T>::attachAsLC(BinNode<T>* x, BinTree<T>* &S)//T��Ϊx������������
	{
		if (x->leftChild = S->_root) x->leftChild->parent = x;//���Ա�������Է���������˽�г�Ա
		_size += S->_size;                   //����BinTree���Ա����attachAsLC�����������S��protected��Ա_size,_root
		updateHeightAbove(x);
		S->_root = nullptr;
		S->_size = 0;
		//release(S);//   release( )  ?
		S = nullptr;
		return x;
	}//����������	
	template<typename T>BinNode<T>* BinTree<T>::attachAsRC(BinNode<T>* x, BinTree <T>* &S)//T��Ϊx������������
	{
		if (x->rightChild = S->_root) x->rightChild->parent = x;
		_size += S->_size;
		updateHeightAbove(x);
		S->_root = nullptr;
		S->_size = 0;
		//release(S);//   release( )  ?
		S = nullptr;
		return x;
	}//����������

	//������ɾ��
	template<typename T>int BinTree<T>::remove(BinNode<T>* x)//ɾ���������У�x�ĵĽڵ㼰�����������ر�ɾ���Ľڵ���
	{
		FromParentTo(*x) = nullptr;
		updateHeightAbove(x->parent);
		int n = removeAt(x);
		_size -= n;
		return n;
	}
	template<typename T>static int removeAt(BinNode<T>* x)
	{
		if (!x) return 0;//����
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
}//����ݹ�
template<typename T, typename VST>void travPost_R(BinNode<T>* x, VST& visit)
{
	if (!x) return;
	travPost_R(x->leftChild, visit);
	travPost_R(x->rightChild, visit);
	visit(x->data);
}//����ݹ�
template<typename T, typename VST>void travIn_R(BinNode<T>* x, VST& visit)
{
	if (!x) return;
	travIn_R(x->leftChild, visit);
	visit(x->data);
	travIn_R(x->rightChild, visit);
}//����ݹ�



};//MyBinTree

#endif // !__MYDATASTRUCTURE_H__

