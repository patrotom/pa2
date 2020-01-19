#ifndef __PROGTEST__
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <set>
#include <list>
#include <map>
#include <vector>
#include <queue>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <functional>
using namespace std;
#endif /* __PROGTEST__ */


class OrderingDoesNotExistException {
};

class DuplicateMatchException {
};

template <typename _M>
class CContest {
private:
	struct m_Struct { 
		int t_Counter;
		vector<m_Struct*> t_Ptr;
		m_Struct() { t_Counter = 0; }
	};
	std::map<std::pair<string,string>,_M> m_Matches;
public:
	/*Default constructor*/
	CContest ( void ) {}
	/*Default destructor*/
	~CContest ( void ){}
	/*Method AddMatch*/
	CContest & AddMatch ( const string & contestant1, const string & contestant2, _M result ) {  
		if ( m_Matches.find ({contestant1,contestant2}) != m_Matches.end() || 
			 m_Matches.find ({contestant2,contestant1}) != m_Matches.end() )
			throw DuplicateMatchException();	
		m_Matches.insert ({{contestant1,contestant2},result});
		return (*this);	
	}
	/*Method IsOrdered*/ /*Using algorhitm Topological sort to iterate trough my graph + adding matches to list to be returned*/
	bool IsOrdered ( std::function<int(_M)> comparator ) const { 
		string match;
		int count = 0;	
		unordered_map<string,m_Struct> m_Database;
		/*--------------------------------------------------*/
		for ( auto it:m_Matches ) { 
			if ( comparator ( it.second ) == 0  )	
				return false;
			else if ( comparator ( it.second ) < 0 ) { 
				m_Database[it.first.second].t_Ptr.push_back ( & m_Database[it.first.first] );
				m_Database[it.first.first].t_Counter++;	
			}
			else if ( comparator ( it.second ) > 0 ) { 
				m_Database[it.first.first].t_Ptr.push_back ( & m_Database[it.first.second] );
				m_Database[it.first.second].t_Counter++;
			}		
		}
		/*--------------------------------------------------*/
		while ( ! m_Database.empty() ) { 
			for ( auto it:m_Database ) { 
				if ( it.second.t_Counter == 0 ) {
					count++;
					match = it.first;
				}
			}
			if ( count == 1 ) { 
				for ( auto it:m_Database[match].t_Ptr )
					( it->t_Counter ) --;
				m_Database.erase ( match );
				count = 0;
			}
			else
				return false;	
		} 
		return true;
	}
	/*Method Results*/ /*Using algorhitm Topological sort to iterate trough my graph*/
	std::list<string> Results ( std::function<int(_M)> comparator ) const { 
		unordered_map<string,m_Struct> m_Database;
		list<string> m_List;
		string match;
		int count = 0;
		/*--------------------------------------------------*/
		for ( auto it:m_Matches ) { 
			if ( comparator ( it.second ) == 0  )	
				throw OrderingDoesNotExistException();
			else if ( comparator ( it.second ) < 0 ) { 
				m_Database[it.first.second].t_Ptr.push_back ( & m_Database[it.first.first] );
				m_Database[it.first.first].t_Counter++;	
			}
			else if ( comparator ( it.second ) > 0 ) { 
				m_Database[it.first.first].t_Ptr.push_back ( & m_Database[it.first.second] );
				m_Database[it.first.second].t_Counter++;
			}		
		}
		/*--------------------------------------------------*/
		while ( ! m_Database.empty() ) { 
			for ( auto itMap:m_Database ) { 
				if ( itMap.second.t_Counter == 0 ) {
					count++;
					match = itMap.first;
				}
			}
			if ( count == 1 ) { 
				for ( auto vecPtrs:m_Database[match].t_Ptr )
					( vecPtrs->t_Counter ) --;
				m_List.push_back(match);
				m_Database.erase(match);
				count = 0;
			}
			else
				throw OrderingDoesNotExistException();	
		}
		return m_List;	
	}
};

#ifndef __PROGTEST__
/*Struct CMatch*/
struct CMatch {
public:
	CMatch ( int a, int b ) : m_A ( a ), m_B ( b ) {}	
	int m_A;
	int m_B;
};
/*Class HigherScoreThreshold*/
class HigherScoreThreshold {
public:
	HigherScoreThreshold ( int diffAtLeast ) : m_DiffAtLeast ( diffAtLeast ) {}
	int operator () ( const CMatch & x ) const { 
		return ( x . m_A > x . m_B + m_DiffAtLeast ) - ( x . m_B > x . m_A + m_DiffAtLeast );
	}
private:
	int m_DiffAtLeast;    
};
/*Function HigherScore*/
int HigherScore ( const CMatch & x ) {
  return ( x . m_A > x . m_B ) - ( x . m_B > x . m_A );
}
/*------------------------------------------------------------------------------------*/
int main ( void ) {

	CContest<CMatch>  x;

	x . AddMatch ( "C++", "Pascal", CMatch ( 10, 3 ) )
      . AddMatch ( "C++", "Java", CMatch ( 8, 1 ) )
      . AddMatch ( "Pascal", "Basic", CMatch ( 40, 0 ) )
      . AddMatch ( "Java", "PHP", CMatch ( 6, 2 ) )
      . AddMatch ( "Java", "Pascal", CMatch ( 7, 3 ) )
      . AddMatch ( "PHP", "Basic", CMatch ( 10, 0 ) ); 	  

	assert ( ! x . IsOrdered ( HigherScore ) );
	try
	{
	  list<string> res = x . Results ( HigherScore );
	  assert ( "Exception missing!" == NULL );
	}
	catch ( const OrderingDoesNotExistException & e )
	{
	}
	catch ( ... )
	{
	  assert ( "Invalid exception thrown!" == NULL );
	}

	x . AddMatch ( "PHP", "Pascal", CMatch ( 3, 6 ) ); 

	assert ( x . IsOrdered ( HigherScore ) );
	try
	{
	  list<string> res = x . Results ( HigherScore );
	  assert ( ( res == list<string>{ "C++", "Java", "Pascal", "PHP", "Basic" } ) );
	}
	catch ( ... )
	{
	  assert ( "Unexpected exception!" == NULL );
	}
	assert ( ! x . IsOrdered ( HigherScoreThreshold ( 3 ) ) );
	try
	{
	  list<string> res = x . Results ( HigherScoreThreshold ( 3 ) );
	  assert ( "Exception missing!" == NULL );
	}
	catch ( const OrderingDoesNotExistException & e )
	{
	}
	catch ( ... )
	{
	  assert ( "Invalid exception thrown!" == NULL );
	}
	
	assert ( x . IsOrdered ( [] ( const CMatch & x )
	{
	  return ( x . m_A < x . m_B ) - ( x . m_B < x . m_A ); 
	} ) );
	try
	{
	  list<string> res = x . Results ( [] ( const CMatch & x )
	  {
	    return ( x . m_A < x . m_B ) - ( x . m_B < x . m_A ); 
	  } );
	  assert ( ( res == list<string>{ "Basic", "PHP", "Pascal", "Java", "C++" } ) );
	}
	catch ( ... )
	{
	  assert ( "Unexpected exception!" == NULL );
	}
	
	CContest<bool>  y;

	y . AddMatch ( "Python", "PHP", true )
	  . AddMatch ( "PHP", "Perl", true )
	  . AddMatch ( "Perl", "Bash", true )
	  . AddMatch ( "Bash", "JavaScript", true )
	  . AddMatch ( "JavaScript", "VBScript", true );

	assert ( y . IsOrdered ( [] ( bool v )
	{
	  return v ? 10 : - 10;
	} ) );
	try
	{
	  list<string> res = y . Results ( [] ( bool v )
	  {
	    return v ? 10 : - 10;
	  });
	  assert ( ( res == list<string>{ "Python", "PHP", "Perl", "Bash", "JavaScript", "VBScript" } ) );
	}
	catch ( ... )
	{
	  assert ( "Unexpected exception!" == NULL );
	}

	y . AddMatch ( "PHP", "JavaScript", false );
	assert ( !y . IsOrdered ( [] ( bool v )
	{
	  return v ? 10 : - 10;
	} ) );
	try
	{
	  list<string> res = y . Results ( [] ( bool v )
	  {
	    return v ? 10 : - 10;
	  } );
	  assert ( "Exception missing!" == NULL );
	}
	catch ( const OrderingDoesNotExistException & e )
	{
	}
	catch ( ... )
	{
	  assert ( "Invalid exception thrown!" == NULL );
	}
	
	try
	{
	  y . AddMatch ( "PHP", "JavaScript", false );
	  assert ( "Exception missing!" == NULL );
	}
	catch ( const DuplicateMatchException & e )
	{
	}
	catch ( ... )
	{
	  assert ( "Invalid exception thrown!" == NULL );
	}
	
	try
	{
	  y . AddMatch ( "JavaScript", "PHP", true );
	  assert ( "Exception missing!" == NULL );
	}
	catch ( const DuplicateMatchException & e )
	{
	}
	catch ( ... )
	{
	  assert ( "Invalid exception thrown!" == NULL );
	}
	return 0;
}
/*------------------------------------------------------------------------------------*/
#endif /* __PROGTEST__ */
