
#include <iostream>
#include <string>
using namespace std;


struct Money
{
	string currency ;
	double amount ;
};


class Wallet
{
public:
	Wallet() ; // constructor
	Wallet(const Wallet &) ; // deep copy constructor
	~ Wallet() ;
	// destructor

	Money* CreateClone()const ; // to create the clone of the pinter
	int Size() const ; // to reach private size
	
	const Wallet & operator +=(const Wallet & rhs); // to update lhs with the rhs by adding
    const Wallet & operator = (const Wallet &rhs) ; // to update lhs with the rhs by deleting
	bool ifExists(Money & rhs) const; // to check if the currency in the rhs exists in the lhs
	void Add(  Money &rhs )  ; // to add the amount of the currency in the rhs to the lhs
	const Wallet &Change ( Money & rhs) ; // if rhs's currency doesn't exist then a new currency should be created in the lhs
	bool Equal( const Wallet &rhs) const ; // to see if rhs and lhs are equal or not
	bool isGreater ( Money& rhs) const; // to see lhs or rhs is greater than the other
	void DecreaseFromWallet ( Money& rhs) ;
	bool OkeytoDecrease ( Money& rhs) ; // to see if this -> 's currency exists in the lhs and this -> 's amount is greater than rhs
	const Wallet & DeleteCurrency ( Money& rhs) ; // to remove the currency from our wallet
	const Wallet & AddForTheFirstElement ( Money &rhs) ; // to create the first element of our wallet
	string toPrint() const; // to have a string of what is going to be printed
	bool MoneyisMore(Money &rhs) ;  


private:
	Money* pinter ;
	int size ;
};



// free functions -------------------------------------------------------------------------
Wallet operator+ (  const Wallet &lhs , Money &rhs)  ;
Wallet operator+ ( const Wallet &lhs , const Wallet &rhs)  ;
Wallet operator- (const Wallet &lhs , Money& rhs) ;
ostream &  operator << (ostream & os, const Wallet & walletname);
bool operator <=  (Money&lhs, const Wallet&rhs);
bool operator >=  (const Wallet& lhs, Money& rhs);
bool operator ==  (const Wallet& lhs, const Wallet& rhs);