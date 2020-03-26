#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;
/**!
*Printthetable’sheadertotheterminal(std::cout).
*@paramfields_Referencetothelistofheaderfieldstobeprinted.
*/
void printHeader(const std::vector<string>&fields_)
{
	cout<<" +";
	for (size_t i{0}; i < fields_.size(); ++i)
	{
		cout <<setw(fields_[i].size()+3)<<setfill('-') <<"+";
	}
	cout<<"\n";
	//Cria e imprime delimitadores verticais e após isso insere os valores existentes no vetor. 
	for (size_t i{0}; i < fields_.size() ; ++i)
	{
		cout<<" | "<<fields_[i] ;
	}
	cout<<" |\n";
	//Cria e imprime delimitadores horizontais com espaçamentos variados.
	cout <<" +";
	for (size_t i{0}; i < fields_.size(); ++i)
	{
		cout <<setw(fields_[i].size()+3)<<setfill('-') <<"+";
	}
	cout<<"\n";	
}
int main(){
	std::vector<std::string>fieldNames={"ITEM","QUANTIDADE","VALOR UNITARIO"};
	printHeader(fieldNames);
	return EXIT_SUCCESS;
}