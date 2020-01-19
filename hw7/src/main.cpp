#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <memory>
#include <algorithm>
using namespace std;
#endif /* __PROGTEST_ */
/*---------------------------*/
class CITem {
public:
	/*Default Constructor*/
	CITem ( void ) {}
	/*Virtual Destructor*/	
	virtual ~CITem ( void ) {}
	/*Method getWeight*/ 
	virtual int getWeight () const { return 0; }
	/*Method getDanger*/
	virtual bool getDanger () const { return false; }
	/*Method getID*/
	virtual string getID () const { return "default"; }
};
/*---------------------------*/
class CLuggage {
public:
	/*Default Constructor*/
	CLuggage ( void ) { 
		m_Weight = 0; 
		m_Count = 0;
		m_Danger = false;
	}
	/*Virtual Destructor*/
	virtual ~CLuggage ( void ) {}
	/*Virtual Method Add*/
	virtual CLuggage & Add ( const CITem & Item ) {
		Items.push_back ( shared_ptr<CITem> ( new CITem ( Item ) ) );
		m_Weight += Item.getWeight();
		m_Count++;
		if ( m_Danger != true )
			m_Danger = Item.getDanger();  
		m_Contents.push_back ( Item.getID() );

		return *this;
	}
	/*Virtual Method Identical*/
	virtual bool IdenticalContents ( const CLuggage & src ) const {
		vector<string> temp1 = this->m_Contents;
		vector<string> temp2 = src.m_Contents;

		sort ( temp1.begin(), temp1.end() );
		sort ( temp2.begin(), temp2.end() ); 
		return ( temp1 == temp2 );
	}
	/*Virtual Method Print*/
	virtual void Print ( ostream & os ) const {}
	/*Operator <<*/
	friend ostream & operator << ( ostream & os, const CLuggage & x ) { 
		x . Print ( os );
		return os;
	}
protected:
	int m_Weight;
	int m_Count; 
	bool m_Danger;
	vector<shared_ptr<CITem>> Items;
	vector<string> m_Contents;
};
/*---------------------------*/
class CKnife : public CITem {
public:
	/*Default Constructor*/
	CKnife ( int BladeLength ) {
		m_BladeLength = BladeLength;
	}
	/*Default Destructor*/
	~CKnife ( void ) {}
	/*Method getWeight*/ 	
	virtual int getWeight () const { return 100; }
	/*Method getDanger*/
	virtual bool getDanger () const { 
		if ( m_BladeLength > 7 )
			return true;
		return false;
	}
	/*Method getID*/
	virtual string getID () const { return "Knife, blade: " +
											to_string ( m_BladeLength ) + " cm"; }
protected:	
	int m_BladeLength;
};
/*---------------------------*/
class CClothes : public CITem {
public:
	/*Default Constructor*/
	CClothes ( string Desc ) { 
		m_Desc = Desc;
	}
	/*Default Destructor*/
	~CClothes ( void ) {}
	/*Method getWeight*/ 
	virtual int getWeight () const { return 500; }
	/*Method getID*/
	virtual string getID () const { return "Clothes (" + m_Desc + ")"; }
protected:
	string m_Desc;	
};
/*---------------------------*/
class CShoes : public CITem {
public:
	/*Default Constructor*/
	CShoes () {}
	/*Default Destructor*/
	~CShoes ( void ) {}
	/*Method getWeight*/
	virtual int getWeight () const { return 750; }
	/*Method getID*/
	virtual string getID () const { return "Shoes"; }
};
/*---------------------------*/
class CMobile : public CITem {
public:
	/*Default Constructor*/
	CMobile ( string Manufacturer, string Model ) { 
		m_Manufacturer = Manufacturer;
		m_Model = Model;
	}
	/*Default Destructor*/
	~CMobile ( void ) {}
	/*Method getWeight*/
	virtual int getWeight () const { return 150; }
	/*Method getDanger*/
	virtual bool getDanger () const { 
		if ( m_Manufacturer == "Samsung" && m_Model == "Galaxy Note S7" )
			return true;
		return false;
	}
	/*Method getID*/
	virtual string getID () const { return "Mobile " + m_Model + " by: " + m_Manufacturer; }
protected:
	string m_Manufacturer;
	string m_Model;
};
/*---------------------------*/
class CSuitcase : public CLuggage {
public:
	/*Default Constructor*/
	CSuitcase ( int w, int h, int d ) { 
		m_W = w;
		m_H = h;
		m_D = d;
	}
	/*Method Weight*/
	int Weight () const { return m_Weight + 2000; }
	/*Method Count*/
	int Count () const { return m_Count; }
	/*Method Danger*/
	bool Danger () const { return m_Danger; }
	/*Virtual Method Print*/
	virtual void Print ( ostream & os ) const { 
		os << "Suitcase " + to_string(m_W) + "x" + to_string(m_H) + "x" + to_string(m_D) + "\n";
		for ( size_t i = 0; i < m_Contents.size() - 1; i++ ) { 
			os << "+-" << m_Contents[i] << "\n";
		}
		os << "\\-" << m_Contents[m_Contents.size() - 1] << "\n";
	}
protected:
	int m_W;
	int m_H;
	int m_D;	
};
/*---------------------------*/
class CBackpack : public CLuggage {
public:
	/*Default Constructor*/
	CBackpack ( void ) {}
	/*Default Destructor*/
	~CBackpack ( void ) {}
	/*Method Weight*/
	int Weight () const { return m_Weight + 1000; }
	/*Method Count*/
	int Count () const { return m_Count; }
	/*Method Danger*/
	bool Danger () const { return m_Danger; }
	/*Virtual Method Print*/
	virtual void Print ( ostream & os ) const { 
		os << "Backpack\n";
		for ( size_t i = 0; i < m_Contents.size() - 1; i++ ) { 
			os << "+-" << m_Contents[i] << "\n";
		}
		os << "\\-" << m_Contents[m_Contents.size() - 1] << "\n";
	}
};
/*---------------------------*/  
#ifndef __PROGTEST__
int main ( void ) {

	CSuitcase x ( 1, 2, 3 );
	CBackpack y;
	ostringstream os;
	x . Add ( CKnife ( 7 ) );
	x . Add ( CClothes ( "red T-shirt" ) );
	x . Add ( CClothes ( "black hat" ) );
	x . Add ( CShoes () );
	x . Add ( CClothes ( "green pants" ) );
	x . Add ( CClothes ( "blue jeans" ) );
	x . Add ( CMobile ( "Samsung", "J3" ) );
	x . Add ( CMobile ( "Tamtung", "Galaxy Note S7" ) );
	os . str ( "" );
	os << x;
	assert ( os . str () == "Suitcase 1x2x3\n"
	         "+-Knife, blade: 7 cm\n"
	         "+-Clothes (red T-shirt)\n"
	         "+-Clothes (black hat)\n"
	         "+-Shoes\n"
	         "+-Clothes (green pants)\n"
	         "+-Clothes (blue jeans)\n"
	         "+-Mobile J3 by: Samsung\n"
	         "\\-Mobile Galaxy Note S7 by: Tamtung\n" );
	assert ( x . Count () == 8 );
	assert ( x . Weight () == 5150 );
	assert ( !x . Danger () );
	x . Add ( CKnife ( 8 ) );
	os . str ( "" );
	os << x;
	assert ( os . str () == "Suitcase 1x2x3\n"
	         "+-Knife, blade: 7 cm\n"
	         "+-Clothes (red T-shirt)\n"
	         "+-Clothes (black hat)\n"
	         "+-Shoes\n"
	         "+-Clothes (green pants)\n"
	         "+-Clothes (blue jeans)\n"
	         "+-Mobile J3 by: Samsung\n"
	         "+-Mobile Galaxy Note S7 by: Tamtung\n"
	         "\\-Knife, blade: 8 cm\n" );
	assert ( x . Count () == 9 );
	assert ( x . Weight () == 5250 );
	assert ( x . Danger () );
	y . Add ( CKnife ( 7 ) )
	  . Add ( CClothes ( "red T-shirt" ) )
	  . Add ( CShoes () );
	y . Add ( CMobile ( "Samsung", "Galaxy Note S7" ) );
	y . Add ( CShoes () );
	y . Add ( CClothes ( "blue jeans" ) );
	y . Add ( CClothes ( "black hat" ) );
	y . Add ( CClothes ( "green pants" ) );
	os . str ( "" );
	os << y;
	assert ( os . str () == "Backpack\n"
	         "+-Knife, blade: 7 cm\n"
	         "+-Clothes (red T-shirt)\n"
	         "+-Shoes\n"
	         "+-Mobile Galaxy Note S7 by: Samsung\n"
	         "+-Shoes\n"
	         "+-Clothes (blue jeans)\n"
	         "+-Clothes (black hat)\n"
	         "\\-Clothes (green pants)\n" );
	assert ( y . Count () == 8 );
	assert ( y . Weight () == 4750 );
	assert ( y . Danger () );
	y . Add ( CMobile ( "Samsung", "J3" ) );
	y . Add ( CMobile ( "Tamtung", "Galaxy Note S7" ) );
	y . Add ( CKnife ( 8 ) );
	os . str ( "" );
	os << y;
	assert ( os . str () == "Backpack\n"
	         "+-Knife, blade: 7 cm\n"
	         "+-Clothes (red T-shirt)\n"
	         "+-Shoes\n"
	         "+-Mobile Galaxy Note S7 by: Samsung\n"
	         "+-Shoes\n"
	         "+-Clothes (blue jeans)\n"
	         "+-Clothes (black hat)\n"
	         "+-Clothes (green pants)\n"
	         "+-Mobile J3 by: Samsung\n"
	         "+-Mobile Galaxy Note S7 by: Tamtung\n"
	         "\\-Knife, blade: 8 cm\n" );
	assert ( y . Count () == 11 );
	assert ( y . Weight () == 5150 );
	assert ( y . Danger () );
	assert ( !x . IdenticalContents ( y ) );
	assert ( !y . IdenticalContents ( x ) );
	x . Add ( CMobile ( "Samsung", "Galaxy Note S7" ) );
	assert ( !x . IdenticalContents ( y ) );
	assert ( !y . IdenticalContents ( x ) );
	x . Add ( CShoes () );
	assert ( x . IdenticalContents ( y ) );
	assert ( y . IdenticalContents ( x ) );
	assert ( y . IdenticalContents ( y ) );
	assert ( x . IdenticalContents ( x ) );

	// CBackpack z ( y );
	// z.Add ( CShoes() );
	// CBackpack w = z;

	return 0;
}
#endif /* __PROGTEST__ */
