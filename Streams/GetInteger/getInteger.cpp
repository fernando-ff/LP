#include<iostream>//std::cin,std::cout
#include<string>//std::string
#include<iomanip>//setw(),setfill()
#include<sstream>//istringstream,ostringstream
#include<fstream>
using namespace std;
string getInteger(string msg_ = " "){
	ostringstream oss;//fluxo devolve o valor como string
	string line;
	string Name{"Forneça um inteiro valido:"};//mensagem para ao usuario
	int value;
	while(true){//repete enquanto o usuario não digitiar um valor valido
		cout << msg_;//imprime a mensagem para o usuario 
		getline( cin,line );// lê os valores do teclado e armazena no fluxo de string
		istringstream iss(line);//fluxo que recebe o valor como string
		//verifica se houve algum erro na entrada e avisa ao usuario que houve
		if (iss.fail() or iss.eof()){
			cerr << setw(20) << setfill('=') << "Error\n"
			     << setw(20) << setfill('=') <<endl;
		}
		else{//se não tem
			iss >> value >> ws // transfere o valor existente no fluxo iss para value;
		 	oss << value;//e da variavel value é transferido o valor para o fluxo oss
		 	return oss.str();//oss é convertido em string e é retornado
		}
		cout << "Unable the read the value, try again.\n";//Caso o vallor não seja valido imprime na tela
		if (msg_ == " ") msg_ = "Forneça um inteiro valido:";	
	}
	return "ERROR";
}
int main(){
	auto val = getInteger("Forneça um inteiro:");
	
	if (val == "ERROR") cout << "Error!";
	else cout << "The value:" << val << " is valid!"<< endl;


	return 0;
}