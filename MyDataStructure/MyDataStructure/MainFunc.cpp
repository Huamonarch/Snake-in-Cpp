#include<iostream>
#include"MyDataStructureH.h"
//using std::ostream;
//class MyPoint
//{
//public:
//	MyPoint(double x=0.0, double y = 0.0, double z = 0.0):_x(x),_y(y),_z(z){}
//	virtual ~MyPoint()=default;
//	friend ostream& operator<<(ostream& os,const MyPoint &pt);
//	double x() { return _x; }
//	double y() { return _y; }
//	double z() { return _z; }
//	virtual void printout() { std::cout<<"虚函数"<<std::endl; }
//	virtual void printout2() { std::cout << "虚函数2" << std::endl; }
//private:
//	double _x, _y, _z;
//};
//inline ostream& operator<<(ostream& os, const MyPoint& pt)
//{
//	os << "(" << pt._x << "," << pt._y<< "," << pt._z << ")";
//	return os;
//}

int main()
{
	//using namespace std;
	//int* test1 = new int(5);
	//cout<<test1<<endl;
	//delete test1;
	//test1 = nullptr;
	//return 0;
	/*using std::cout;
	using std::endl;
	cout<<"MyPoint的大小:"<<sizeof(MyPoint)<<endl;
	MyPoint p1(1, 2, 3);
	cout << "MyPoint的大小:" << sizeof(MyPoint) << endl;
	cout<<p1<<endl;*/
	using namespace MyBinTree;
	BinTree<int> tree1;
	tree1.insertAsRoot(1);
	tree1.insertAsLC(tree1.root(), 2);
	tree1.insertAsRC(tree1.root(), 3);
	std::cout << tree1.size() << std::endl;
	BinTree<int> tree2;
	BinTree<int>* ptree2 = &tree2;
	tree2.insertAsRoot(4);
	tree2.insertAsLC(tree2.root(), 5);
	tree2.insertAsRC(tree2.root(), 6);
	tree1.attachAsLC(tree1.root()->leftChild, ptree2);
	std::cout<<tree1.size()<<std::endl;
	VST<int> visit;
	travIn_R(tree1.root(), visit);

	
	return 0;
}