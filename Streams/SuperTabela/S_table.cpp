#include <iostream> //std::cout, std::cin
#include <vector> //std::vector<>
#include <fstream> //std::ifstream,std::ofstream
#include <string> //std::string
#include<iomanip>//setw(),setfill()

using namespace std;

struct Valores
{
	string item,//armazena o indice do item
	    quantidade,//armazena a quantidade de itens 
	    valor;// armazena o valor do item
};
//função responsavél por ler as strings do arquivo 1
int readFile1( vector<string> &v){
	ifstream ifs;
	ifs.open("itens.txt");//abre o arquivo
	string line;//recebe a string do arquivo
	while(true){
		getline( ifs,line);// transferindo do fluxo a string para a variavel line 
		v.push_back(line);// inserindo a string no final do vetor
		if(ifs.eof()){//verifica se houve algum erro ou se chegou ao fim do arquivo
			cerr << "Data error in file OR end file!" << endl;
			return EXIT_FAILURE;
		}
	}
	return 0;
}
//função responsavél por ler os valores do arquivo 2
int readFile2( vector<Valores> &v){
	// #parei por aqui pq n sei como ler valores inteiros com espaço entre eles;
	ifstream ifs;
	ifs.open("valores.txt");//lê o arquivo
	Valores val;//armazena os valores lidos do arquivo
	while(true){
		ifs >> val.item >> val.quantidade >> val.valor;
		v.push_back(val);//transfere os valores lidos para o vector de Valores
		if(ifs.eof()){//verifica se houve algum erro ou se chegou ao fim do arquivo
			cerr << "Data error in file OR end file!" << endl;
			return EXIT_FAILURE;
		}

	}
	return 0;
}
//=====Função que imprime uma tabela no terminal e em um arquivo=====//(ainda por fazer)
void print(std::vector<string> &s, vector<Valores> &v){
	ofstream out;//Fluxo de impressão.
	out.open("tabela.txt");//Abre o arquivo pra impressão.
	//=====Imprime a primeira linha da tabela.=====//
	cout << " +";//Imprimindo no terminal.
	out << " +";//Imprimindo no arquivo.
	for (size_t i{0}; i < s.size(); ++i)
	{
		cout <<setw(s[i].size()+3)<<setfill('-') <<"+";//Imprimindo no terminal.
		out <<setw(s[i].size()+3)<<setfill('-') <<"+";//Imprimindo no arquivo.
	}
	cout <<"\n";//Imprimindo no terminal.
	out <<"\n";//Imprimindo no arquivo.
	//=====Imprime a segunda linha da tabela=====//
	for (size_t i{0}; i < s.size(); ++i)
	{
		cout <<" | "<< s[i];//Imprimindo no terminal.
		out <<" | "<< s[i];//Imprimindo no arquivo.
	}
	cout << " |\n";//Imprimindo no terminal.
	out << " |\n";//Imprimindo no arquivo.
	//=====Imprime a terceira linha da tabela=====//
	cout << " +";//Imprimindo no terminal.
	out << " +";//Imprimindo no arquivo.
	for (size_t i{0}; i < s.size(); ++i)
	{
		cout <<setw(s[i].size()+3)<<setfill('-') <<"+";//Imprimindo no terminal.
		out <<setw(s[i].size()+3)<<setfill('-') <<"+";//Imprimindo no arquivo.
	}
	cout << "\n";//Imprimindo no terminal.
	out << "\n";//Imprimindo no arquivo.
	//=====Imprime as demais linhas=====//(CORRIGIR ERRO DE IMPRESSÃO)
	for (size_t i{0}; i < v.size(); ++i)
	{
		cout <<" |"<<setw(s[0].size()+1)<<setfill(' ') << v[i].item  //Imprimindo no terminal.
		     <<" |"<<setw(s[1].size()+1)<<setfill(' ') <<v[i].quantidade
		     <<" |"<<setw(s[2].size()+1)<<setfill(' ') << v[i].valor << " |\n";
		out <<" |"<<setw(s[0].size()+1)<<setfill(' ') << v[i].item  //Imprimindo no terminal.
		     <<" |"<<setw(s[1].size()+1)<<setfill(' ') <<v[i].quantidade
		     <<" |"<<setw(s[2].size()+1)<<setfill(' ') << v[i].valor << " |\n";
	}
	//=====Imprimindo a ultima linha=====//
	cout << " +";
	out << " +";
	for (size_t i{0}; i < s.size(); ++i)
	{
		cout <<setw(s[i].size()+3)<<setfill('-') <<"+";//Imprimindo no terminal.
		out <<setw(s[i].size()+3)<<setfill('-') <<"+";//Imprimindo no arquivo.
	}
	cout <<"\n";
	out <<"\n";
}
int main(/*int argc, char* agrv[]*/){
	//===verifica se os valores passados na linha de comando estão ok===//
	/*if (argc < 1)//Caso não esteja executa essa condição
	{
		cerr << "Usage:" << agrv[0] << " DESTINO DA FONTE" <<endl;
		return 1;	
	}
	//Caso esteja executa esta
	else{*/
	vector<string> strings;//armazena as strings do arquivo1
	vector<Valores> integers;// armazena os Valores do arquivo2
	int result1 = readFile1( strings );
	int result2 = readFile2( integers );
	print( strings, integers);
	cout << "Result1:" <<result1 <<endl;
	cout << "Result2:" <<result2 <<endl;
	
	//}
	return 0;
}