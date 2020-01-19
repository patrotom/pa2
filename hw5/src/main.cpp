#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <memory>
using namespace std;

class CDate {

private:
	int16_t m_Year;
    int8_t m_Month;
    int8_t m_Day;
public:
//---------------------------------------------------------------------------------------------
	CDate ( int y, int m, int d ) { 
		m_Year = y;
		m_Month = m;
		m_Day = d;
	}
//---------------------------------------------------------------------------------------------
	int Compare ( const CDate & x ) const {
      if ( m_Year != x . m_Year )
        return m_Year - x . m_Year;
      if ( m_Month != x . m_Month )
        return m_Month - x . m_Month;
      return m_Day - x . m_Day;
    }
//---------------------------------------------------------------------------------------------
	int Year ( void ) const {
	      return m_Year;
	}
//---------------------------------------------------------------------------------------------
    int Month ( void ) const {
      return m_Month;
    }
//---------------------------------------------------------------------------------------------
    int Day ( void ) const {
      return m_Day;
    }
//---------------------------------------------------------------------------------------------
    friend ostream & operator << ( ostream & os, const CDate & x ) {
      char oldFill = os . fill ();
      return os << setfill ( '0' ) << setw ( 4 ) << x . m_Year << "-" 
                                   << setw ( 2 ) << (int) x . m_Month << "-" 
                                   << setw ( 2 ) << (int) x . m_Day 
                << setfill ( oldFill );
    }
//---------------------------------------------------------------------------------------------
};
#endif /* __PROGTEST__ */
/**************************************/
class CInvoice {

private:
	string m_Seller;
	string m_Buyer;
	CDate m_Date = CDate (0, 0, 0);
	unsigned int m_Amount;
	double m_VAT;
	size_t m_Order;
	string m_TrueBuyer;
	string m_TrueSeller;
public:
	/*Default constructor*/
	CInvoice ( const CDate & date, const string & seller, const string & buyer, 
			   unsigned int amount, double VAT ) {		      
		m_Date = date;
		m_Seller = seller;
		m_Buyer = buyer;
		m_Amount = amount;
		m_VAT = VAT;
	}
	/*Overloaded operator ==*/
	bool operator == ( const CInvoice & x ) const { 
    	if ( x.Date().Year() == this->Date().Year() && 
    		 x.Date().Month() == this->Date().Month() && 
    		 x.Date().Day() == this->Date().Day() && 
			 x.getTrueBuyer() == this->getTrueBuyer() && x.getTrueSeller() == this->getTrueSeller() &&
    		 x.Amount() == this->Amount() && x.VAT() == this->VAT() )
    		return true;
    	return false;
   }
   /*Method insertOrder*/
   void insertOrder ( size_t & ID ) { 
   		m_Order = ID;
   }
   /*Method getOrder*/
   size_t getOrder () const { 
   		return m_Order;
   }
   /*Method setTrueBuyer*/
   void setTrueBuyer ( const string & name ) { 
   		m_TrueBuyer = name;	
   }
   /*Method setTrueSeller*/
   void setTrueSeller ( const string & name ) { 
   		m_TrueSeller = name;	
   }
   /*Method getTrueSeller*/
   string getTrueSeller () const { 
   		return m_TrueSeller;	
   }
   /*Method getTrueBuyer*/
   string getTrueBuyer () const { 
   		return m_TrueBuyer;	
   }
   /*Method Date*/
   CDate Date ( void ) const { return m_Date; }
   /*Method Buyer*/
   string Buyer ( void ) const { return m_Buyer; }
   /*Method Seller*/
   string Seller ( void ) const { return m_Seller; }
   /*Method Amount*/
   int Amount ( void ) const { return m_Amount; }
   /*Method VAT*/
   double VAT ( void ) const { return m_VAT; }
	
};

struct SetKeyHasher {
	size_t operator() ( const CInvoice & k ) const {

		CDate Date = k.Date();

		return ( ( hash<int>()( Date.Year() ) ) ^ ( hash<int>()( Date.Month() ) ) ^
				 ( hash<int>()( Date.Day() ) ) ^ ( hash<string>()( k.Seller() ) ) ^	 
				 ( hash<string>()( k.Buyer() ) ) ^ ( hash<int>()( k.Amount() ) ) ^
				 ( hash<double>()( k.VAT() ) ) );
	}	
};
/**************************************/
class CSortOpt {

private:
	std::vector<int> sortKey;
	std::vector<bool> sortModule;
public:
	static const int BY_DATE = 0;
    static const int BY_BUYER = 1;
    static const int BY_SELLER = 2;
    static const int BY_AMOUNT = 3;
    static const int BY_VAT = 4;
    /*Default constructor*/
	CSortOpt ( void ) {}
	/*Method AddKey*/
    CSortOpt & AddKey( int key, bool ascending = true ) {     		
    	sortKey.push_back ( key );
    	sortModule.push_back ( ascending );
    	return *this;
    }
    /*Overloaded operator ()*/
    bool operator () ( const CInvoice & a, const CInvoice & b ) const {  

    	for ( size_t i = 0; i < sortKey.size(); i++ ) { 
    		if ( sortKey[i] == BY_DATE ) { 
    			CDate dateA = a.Date();
    			CDate dateB = b.Date();
    			if ( ! ( dateA.Compare(dateB) == dateB.Compare(dateA) ) )
    				return ( dateA.Compare(dateB) > dateB.Compare(dateA) ) ^ sortModule[i];
    		}
    		else if ( sortKey[i] == BY_BUYER ) {
    			string x = a.Buyer();
    			string y = b.Buyer();	
    			std::transform ( x.begin(), x.end(), x.begin(), ::tolower );
    			std::transform ( y.begin(), y.end(), y.begin(), ::tolower );
    			if ( ! ( x == y ) )
    				return ( x > y ) ^ sortModule[i];
    		}
    		else if ( sortKey[i] == BY_SELLER ) {
    			string x = a.Seller();
    			string y = b.Seller();	
    			std::transform ( x.begin(), x.end(), x.begin(), ::tolower );
    			std::transform ( y.begin(), y.end(), y.begin(), ::tolower );
    			if ( ! ( x == y ) )
    				return ( x > y ) ^ sortModule[i];
    		}
			else if ( sortKey[i] == BY_AMOUNT ) {
    			if ( ! ( a.Amount() == b.Amount() ) )
    				return ( a.Amount() > b.Amount() ) ^ sortModule[i];
    		}
    		else if ( sortKey[i] == BY_VAT ) {
    			if ( ! ( a.VAT() == b.VAT() ) )
    				return ( a.VAT() > b.VAT() ) ^ sortModule[i];
    		}
    	}
		return  ( a.getOrder() < b.getOrder() ); 
    }
};
/**************************************/
class CVATRegister {

private:
	string transformName ( const string & temp ) const;
	std::set<std::string> companyNames;
	std::unordered_set<CInvoice, SetKeyHasher> InvoicesIssued;
	std::unordered_set<CInvoice, SetKeyHasher> InvoicesAccepted;
	/*--------------------------------------------------------*/
	std::map<string,string> nameDatabase;
	std::map<string,std::unordered_set<CInvoice, SetKeyHasher>> unmatcheDatabase; /*Unmatchnute faktury mapovane nazvom firmy, po stringovej transformacii*/	
	size_t orderCount;
public:
	/*Default Constructor*/
	CVATRegister ( void ) { orderCount = 1; }
    /*Method RegisterCompany*/
    bool RegisterCompany ( const string & name ) { 
    	auto trueName = transformName ( name );
    	if ( companyNames.find ( trueName ) != companyNames.end() )
    		return false;
    	companyNames.insert ( trueName );
    	nameDatabase.insert ( { trueName, name } );
		/*Vytvorim si prazdny set, kde sa budu evidovat nematchnute faktury a tento set namapujem na novo-vytvorenu firmu*/
    	unmatcheDatabase.insert ( { trueName, std::unordered_set<CInvoice, SetKeyHasher>() } ); /*<-- Mapovacia cast, vkladam*/
   
    	return true;
    }
    /*Method AddIssued*/
    bool AddIssued ( const CInvoice & x ) { 

    	CInvoice temp ( x.Date(), nameDatabase[transformName (x.Seller()) ], nameDatabase[transformName (x.Buyer()) ],  
    					x.Amount(), x.VAT() );

    	temp.setTrueBuyer ( transformName ( x.Buyer() ) );
    	temp.setTrueSeller ( transformName ( x.Seller() ) );

    	if ( InvoicesIssued.find ( temp ) != InvoicesIssued.end() )
    		return false;

    	if ( companyNames.find ( temp.getTrueBuyer() ) == companyNames.end() || companyNames.find ( temp.getTrueSeller() ) == companyNames.end() )
    		return false;

    	if ( temp.getTrueBuyer() == temp.getTrueSeller() )
    		return false;
    	temp.insertOrder ( orderCount );

    	//--------------------------------------------------------------------------------------
    	if ( InvoicesAccepted.find ( temp ) == InvoicesAccepted.end() ) {
    		unmatcheDatabase[temp.getTrueSeller()].insert(temp);
    		unmatcheDatabase[temp.getTrueBuyer()].insert(temp);		
    	}
    	else {
			unmatcheDatabase[temp.getTrueSeller()].erase(temp);
    		unmatcheDatabase[temp.getTrueBuyer()].erase(temp);
    	}	
    	//--------------------------------------------------------------------------------------

    	InvoicesIssued.insert ( temp );

    	orderCount++;
    	return true;
    }
    /*Method AddAccepted*/
    bool AddAccepted ( const CInvoice  & x ) { 

    	CInvoice temp ( x.Date(), nameDatabase[transformName (x.Seller())], nameDatabase[transformName (x.Buyer())],  
    					x.Amount(), x.VAT() );

    	temp.setTrueBuyer ( transformName ( x.Buyer() ) );
    	temp.setTrueSeller ( transformName ( x.Seller() ) );

    	if ( InvoicesAccepted.find ( temp ) != InvoicesAccepted.end() )
    		return false;

    	if ( companyNames.find ( temp.getTrueBuyer() ) == companyNames.end() || companyNames.find ( temp.getTrueSeller() ) == companyNames.end() )
    		return false;

    	if ( temp.getTrueBuyer() == temp.getTrueSeller() )
    		return false;

    	temp.insertOrder ( orderCount );

    	//--------------------------------------------------------------------------------------
    	if ( InvoicesIssued.find ( temp ) == InvoicesIssued.end() ) {
    		unmatcheDatabase[temp.getTrueSeller()].insert(temp);
    		unmatcheDatabase[temp.getTrueBuyer()].insert(temp);		
    	}
    	else {
			unmatcheDatabase[temp.getTrueSeller()].erase(temp);
    		unmatcheDatabase[temp.getTrueBuyer()].erase(temp);
    	}
    	//--------------------------------------------------------------------------------------	

    	InvoicesAccepted.insert ( temp );

    	orderCount++;
    	return true;	
    }
    /*Method DelIssued*/
    bool DelIssued ( const CInvoice  & x ) {

		CInvoice temp ( x.Date(), nameDatabase[transformName (x.Seller())], nameDatabase[transformName (x.Buyer())],  
    					x.Amount(), x.VAT() );

		temp.setTrueBuyer ( transformName ( x.Buyer() ) );
    	temp.setTrueSeller ( transformName ( x.Seller() ) );

    	if ( InvoicesIssued.find ( temp ) == InvoicesIssued.end() )
    		return false;

		temp = *(InvoicesIssued.find ( temp ));

    	//--------------------------------------------------------------------------------------
    	if ( InvoicesAccepted.find ( temp ) != InvoicesAccepted.end() ) {
    		unmatcheDatabase[temp.getTrueSeller()].insert(temp);
    		unmatcheDatabase[temp.getTrueBuyer()].insert(temp);
    	}
    	else {
    		unmatcheDatabase[temp.getTrueSeller()].erase( temp );
    		unmatcheDatabase[temp.getTrueBuyer()].erase( temp );
    	}
    	//--------------------------------------------------------------------------------------

    	InvoicesIssued.erase ( temp );
    	return true;
    }
    /*Method DelAccepted*/
    bool DelAccepted ( const CInvoice  & x ) { 
    	
    	CInvoice temp ( x.Date(), nameDatabase[transformName (x.Seller())], nameDatabase[transformName (x.Buyer())],  
    					x.Amount(), x.VAT() );

    	temp.setTrueBuyer ( transformName ( x.Buyer() ) );
    	temp.setTrueSeller ( transformName ( x.Seller() ) );

    	if ( InvoicesAccepted.find ( temp ) == InvoicesAccepted.end() )
    		return false;

    	temp = *(InvoicesAccepted.find ( temp ));

    	//--------------------------------------------------------------------------------------
    	if ( InvoicesIssued.find ( temp ) != InvoicesIssued.end() ) {
    		unmatcheDatabase[temp.getTrueSeller()].insert(temp);
    		unmatcheDatabase[temp.getTrueBuyer()].insert(temp);
    	}
    	else {
    		unmatcheDatabase[temp.getTrueSeller()].erase( temp );
    		unmatcheDatabase[temp.getTrueBuyer()].erase( temp );
    	}
    	//--------------------------------------------------------------------------------------

    	InvoicesAccepted.erase ( temp );
    	return true;
    }
    /*Method Unmatched*/
    list<CInvoice> Unmatched ( const string & company, const CSortOpt & sortBy ) const { 

    	std::list<CInvoice> unmatchedList;
    	std::vector<CInvoice> unmatchedVector;

    	if ( unmatcheDatabase.find( transformName(company)) == unmatcheDatabase.end() )
    		return std::list<CInvoice>();

    	assert(unmatcheDatabase.find( transformName(company)) != unmatcheDatabase.end() || cout << company << endl);

    	for ( auto unmatched : unmatcheDatabase.at( transformName(company) ) )
    		unmatchedVector.push_back ( unmatched );
	
    	sort ( unmatchedVector.begin(), unmatchedVector.end(), sortBy );	

    	for ( auto unmatched : unmatchedVector )
    		unmatchedList.push_back (unmatched);

    	return unmatchedList;
    }
};
/*Method transformName*/
string CVATRegister::transformName ( const string & temp ) const {
	string tempName;  
	tempName.clear();
    unique_copy ( temp.begin(), temp.end(), back_insert_iterator<string>(tempName),
                                     [](char a,char b){ return isspace(a) && isspace(b);} );

    tempName.erase ( tempName.begin(), std::find_if(tempName.begin(), tempName.end(), std::bind1st(std::not_equal_to<char>(), ' ')) );

    tempName.erase ( std::find_if(tempName.rbegin(), tempName.rend(), std::bind1st(std::not_equal_to<char>(), ' ') ).base(), tempName.end());
    


    std::transform ( tempName.begin(), tempName.end(), tempName.begin(), ::tolower );
    
    return tempName;
}


#ifndef __PROGTEST__
/*Help function equalLists*/
bool equalLists ( const list<CInvoice> & a, const list<CInvoice> & b ) { 

	if ( a.size() != b.size() )
		return false;

	std::vector<CInvoice> v1;
	std::vector<CInvoice> v2;

	for ( auto it = a.begin(); it != a.end(); ++it )
		v1.push_back ((*it));
	for ( auto it = b.begin(); it != b.end(); ++it )
		v2.push_back ((*it));

	for ( size_t i = 0; i < a.size(); i++ ) { 
		if ( ! ( v1[i].Date().Year() == v2[i].Date().Year() && 
    		 v1[i].Date().Month() == v2[i].Date().Month() && 
    		 v1[i].Date().Day() == v2[i].Date().Day() && 
			 v1[i].Buyer() == v2[i].Buyer() && v1[i].Seller() == v2[i].Seller() &&
    		 v1[i].Amount() == v2[i].Amount() && v1[i].VAT() == v2[i].VAT() ) )
			return false;
	}
	return true;	
}	


int main ( void ) {
  CVATRegister r;

  assert ( r . RegisterCompany ( "first Company" ) );
  assert ( r . RegisterCompany ( "Second     Company" ) );
  assert ( r . RegisterCompany ( "ThirdCompany, Ltd." ) );
  assert ( r . RegisterCompany ( "Third Company, Ltd." ) );
  assert ( !r . RegisterCompany ( "Third Company, Ltd." ) );
  assert ( !r . RegisterCompany ( " Third  Company,  Ltd.  " ) );
  assert ( r . AddIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", "Second Company ", 100, 20 ) ) );
  assert ( r . AddIssued ( CInvoice ( CDate ( 2000, 1, 2 ), "FirSt Company", "Second Company ", 200, 30 ) ) );
  assert ( r . AddIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", "Second Company ", 100, 30 ) ) );
  assert ( r . AddIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", "Second Company ", 300, 30 ) ) );
  assert ( r . AddIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", " Third  Company,  Ltd.   ", 200, 30 ) ) );
  assert ( r . AddIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "Second Company ", "First Company", 300, 30 ) ) );
  assert ( r . AddIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "Third  Company,  Ltd.", "  Second    COMPANY ", 400, 34 ) ) );
  assert ( !r . AddIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", "Second Company ", 300, 30 ) ) );
  assert ( !r . AddIssued ( CInvoice ( CDate ( 2000, 1, 4 ), "First Company", "First   Company", 200, 30 ) ) );
  assert ( !r . AddIssued ( CInvoice ( CDate ( 2000, 1, 4 ), "Another Company", "First   Company", 200, 30 ) ) );
  	
  assert ( equalLists ( r . Unmatched ( "First Company", CSortOpt () . AddKey ( CSortOpt::BY_SELLER, true ) . AddKey ( CSortOpt::BY_BUYER, false ) . AddKey ( CSortOpt::BY_DATE, false ) ),
           list<CInvoice>
           {
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Third Company, Ltd.", 200, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 )
           } ) );
  assert ( equalLists ( r . Unmatched ( "First Company", CSortOpt () . AddKey ( CSortOpt::BY_DATE, true ) . AddKey ( CSortOpt::BY_SELLER, true ) . AddKey ( CSortOpt::BY_BUYER, true ) ),
           list<CInvoice>
           {
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Third Company, Ltd.", 200, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 )
           } ) );
  assert ( equalLists ( r . Unmatched ( "First Company", CSortOpt () . AddKey ( CSortOpt::BY_VAT, true ) . AddKey ( CSortOpt::BY_AMOUNT, true ) . AddKey ( CSortOpt::BY_DATE, true ) . AddKey ( CSortOpt::BY_SELLER, true ) . AddKey ( CSortOpt::BY_BUYER, true ) ),
           list<CInvoice>
           {
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Third Company, Ltd.", 200, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 )
           } ) );
  assert ( equalLists ( r . Unmatched ( "First Company", CSortOpt () ),
           list<CInvoice>
           {
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
             CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Third Company, Ltd.", 200, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 )
           } ) );
  assert ( equalLists ( r . Unmatched ( "second company", CSortOpt () . AddKey ( CSortOpt::BY_DATE, false ) ),
           list<CInvoice>
           {
             CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "Third Company, Ltd.", "Second     Company", 400, 34.000000 )
           } ) );
  assert ( equalLists ( r . Unmatched ( "last company", CSortOpt () . AddKey ( CSortOpt::BY_VAT, true ) ),
           list<CInvoice>
           {
           } ) );
  assert ( r . AddAccepted ( CInvoice ( CDate ( 2000, 1, 2 ), "First Company", "Second Company ", 200, 30 ) ) );
  assert ( r . AddAccepted ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", " Third  Company,  Ltd.   ", 200, 30 ) ) );
  assert ( r . AddAccepted ( CInvoice ( CDate ( 2000, 1, 1 ), "Second company ", "First Company", 300, 32 ) ) );
  assert ( equalLists ( r . Unmatched ( "First Company", CSortOpt () . AddKey ( CSortOpt::BY_SELLER, true ) . AddKey ( CSortOpt::BY_BUYER, true ) . AddKey ( CSortOpt::BY_DATE, true ) ),
           list<CInvoice>
           {
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 32.000000 )
           } ) );
  assert ( !r . DelIssued ( CInvoice ( CDate ( 2001, 1, 1 ), "First Company", "Second Company ", 200, 30 ) ) );
  assert ( !r . DelIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "A First Company", "Second Company ", 200, 30 ) ) );
  assert ( !r . DelIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", "Second Hand", 200, 30 ) ) );
  assert ( !r . DelIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", "Second Company", 1200, 30 ) ) );
  assert ( !r . DelIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", "Second Company", 200, 130 ) ) );

  assert ( r . DelIssued ( CInvoice ( CDate ( 2000, 1, 2 ), "First Company", "Second Company", 200, 30 ) ) );

  assert ( equalLists ( r . Unmatched ( "First Company", CSortOpt () . AddKey ( CSortOpt::BY_SELLER, true ) . AddKey ( CSortOpt::BY_BUYER, true ) . AddKey ( CSortOpt::BY_DATE, true ) ),
           list<CInvoice>
           {
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 32.000000 )
           } ) );
  assert ( r . DelAccepted ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", " Third  Company,  Ltd.   ", 200, 30 ) ) );
  assert ( equalLists ( r . Unmatched ( "First Company", CSortOpt () . AddKey ( CSortOpt::BY_SELLER, true ) . AddKey ( CSortOpt::BY_BUYER, true ) . AddKey ( CSortOpt::BY_DATE, true ) ),
           list<CInvoice>
           {
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Third Company, Ltd.", 200, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 32.000000 )
           } ) );
  assert ( r . DelIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", " Third  Company,  Ltd.   ", 200, 30 ) ) );
  assert ( equalLists ( r . Unmatched ( "First Company", CSortOpt () . AddKey ( CSortOpt::BY_SELLER, true ) . AddKey ( CSortOpt::BY_BUYER, true ) . AddKey ( CSortOpt::BY_DATE, true ) ),
           list<CInvoice>
           {
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 ),
             CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 32.000000 )
           } ) );

  
  assert ( r . AddIssued ( CInvoice ( CDate ( 2000, 1, 2 ), "First Company", "Second Company", 200, 30 ) ) );
  assert ( r . AddAccepted ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", "THird  Company,  Ltd.", 200, 30 ) ) );
  assert ( r . AddIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", " Third  Company,  Ltd.   ", 200, 30 ) ) );

  return 0;
}
#endif /* __PROGTEST__ */
  /*list<CInvoice> t = r . Unmatched ( "First Company", CSortOpt () . AddKey ( CSortOpt::BY_SELLER, true ) . AddKey ( CSortOpt::BY_BUYER, true ) . AddKey ( CSortOpt::BY_DATE, true ) );

  for ( auto it = t.begin(); it != t.end(); ++it ) { 
  	CDate Date = (*it).Date(); 
  	cout <<  Date.Year() << "/" << Date.Month() << "/" << Date.Day() << " : |" 
  		 << (*it).Seller() << "| |" << (*it).Buyer() << "| |" << (*it).Amount() << "| |" << (*it).VAT() << "| > " << (*it).getOrder() << endl;
  }*/
  