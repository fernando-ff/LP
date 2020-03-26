#include<iostream> // std::cout, std::cin
#include<vector> // std::vector
#include<string> // std::string
#include<fstream> // std::ifstream, std::ofstream

using namespace std;
//Pede ao usuário o nome do arquivo que deve ser lido.
string askUserFileName(ifstream & ifs_, string msg_=""){
	cout << "===================================\n";
	string fileName;//armazena o nome do arquivo.
	while(true){
		cout << msg_;
		getline( cin, fileName );//leitura do nome do arquivo.
		ifs_.open( fileName.c_str() );//conversão da string.
		if( !ifs_.fail() ) return fileName;//caso ocorra uma falha retorna o nome do arquivo
		fileName.clear();//limpando a string.
		cout << " Unable to open the file . Try again .\n";//caso o nome seja invalido
		if ( msg_ == "" ) msg_ = " Enter file name : ";//Pede um novo arquivo, caso o anterior seja invalido
	}
}
//lê os valores existentes no arquivo e os armazenam em um vector de inteiros
int readingIntegers( ifstream &ifs_, vector<int> &integers_){
	int val;//auxilia na leitura do arquivo
	while(ifs_ >> val){//lendo os valores do fluxo e armazenando em val
		integers_.push_back(val);//colocando os valores armazenados em val no fim do vector
		if(ifs_.eof()){//caso chegue ao final do arquivo ou exista um erro nos dados
			cerr << " Data error in file OR end file!" << endl ;
			return EXIT_FAILURE;
		}
	}
	return 0;	
}
//abre e grava os valores do vector no arquivo
void recordingData( ofstream & out_, std::vector<int> & integers_ ){

	out_.open("Invertidos.txt");//abrindo o arquivo
	int i {(sizeof(integers_)/sizeof(integers_[0])) - 1};//pegando o tamanho do vector
	while( i >=  0)
	{
		out_ << integers_[i] << " ";// imprimindo os valores do maior para o menor.
		i--;
	}
}
int main(){

	ifstream ifs;//inicializando o fluxo
	ofstream out;//inicializando o fluxo
	std::vector<int> integers;//inicializando o vector
	askUserFileName( ifs, "Please, enter a file name: " );
	readingIntegers( ifs, integers );
	recordingData  ( out, integers );
	cout << "Finish recording\n==================================\n";
	ifs.close();//fechando o arquivo
	out.close();//fechando o arquivo

}