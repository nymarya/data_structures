#include "hash_tbl.h"
#include <vector>
#include <cassert>
#include <iomanip>

 struct Account{
    int bank_code;
    int branch_code;
    int account_code;
    float balance;
    std::string name;

    using AcctKey = std::pair < std::string , int >;

    Account( int b=1, int ag=11, int ac=11111, float c=0.0, 
    std::string n="Anonimo")
    :bank_code(b), branch_code(ag), account_code(ac), balance(c), name(n)
    {/*empty*/}

    AcctKey get_key()
    {
        std::pair<std::string, int> p(name, account_code);
        return p; 
    }
    
     friend std::ostream &operator<<( std::ostream & _os, const Account & acct );
};

 std::ostream &operator<<( std::ostream & _os, const Account & acct ){
        _os << "[ Cliente: <" << std::setw(18) << acct.name <<
            "> | Banco: <" << std::setw(5)  << acct.bank_code <<
            "> | Agência: <" << std::setw(5) << acct.branch_code <<
            "> | Conta: <" << std::setw(6) << acct.account_code <<
            "> | Saldo: <R$" << std::setw(10) << std::fixed << std::setprecision(2) << acct.balance << "> ]";
        return _os;
    }

struct KeyHash {
    std::size_t operator()( const Account::AcctKey & k_ ) const
    {

    return (std::hash <std::string >()( k_.first )  xor
        std::hash < int >()( k_.second )) ;
    }
};

struct KeyEqual{
    bool operator()( const Account::AcctKey &lhs, const Account::AcctKey &rhs) const{
        return (lhs.first == rhs.first and lhs.second == rhs.second);
    }
};

int main(){

    std::vector<Account> accounts = {
        Account( 1, 51, 98765, 2000.50, "John Lennon"),
        Account( 2, 10, 56789, 1500.25, "Ringo Starr"),
        Account( 3, 40, 54321, 10000.0, "Paul McCartney"),
        Account( 4, 91, 12345, 1111.75, "George Harrison"),
        Account( 5, 67, 13579, 2100.00, "Pete Best"),
        Account( 6, 76, 24680, 2010.00, "Stuart Sutcliffe"),
    };

    //Cria tabela hash de tamanho 5
    HashTbl< AcctKey, Account, KeyHash, KeyEqual> hash_table(5);
    
    //Teste empty()
    assert( hash_table.empty());
    
    //Teste insert()
    assert( hash_table.insert( accounts[0].get_key(), accounts[0]) );
    assert( hash_table.empty() == false);
    assert( hash_table.count() == 1);

    assert( hash_table.insert( accounts[1].get_key(), accounts[1]) );
    assert( hash_table.insert( accounts[2].get_key(), accounts[2]) );
    assert( hash_table.insert( accounts[3].get_key(), accounts[3]) );
    assert( hash_table.insert( accounts[4].get_key(), accounts[4]) );
    
    //Teste print()
    hash_table.print();
    std::cout << std::endl;

    //Teste remove()
    assert( hash_table.remove( accounts[0].get_key() ));
    assert( hash_table.count() == 4);

    std::cout << "Removendo \"" << accounts[0].name << " \": \n";
    hash_table.print();
    std::cout << std::endl;

    //Teste retrieve()
    Account ac;
    assert( hash_table.retrieve( accounts[0].get_key(), ac ) == false);
    
    assert( hash_table.retrieve( accounts[3].get_key(), ac ));

    KeyEqual cmp;
    assert( cmp(ac.get_key(), accounts[3].get_key()) );

    //Teste rehash()
    assert( hash_table.insert( accounts[5].get_key(), accounts[5]) );

    Account acc(1, 77, 89898, 9000.80, "David Bowie"); //!< Rehash chamado aqui
    assert( hash_table.insert( acc.get_key(), acc) );

    Account a;
    assert( hash_table.insert( a.get_key(), a) );

    hash_table.print();
    std::cout << "\n>>>Passou em todos os testes!\n";

    return 0;
}