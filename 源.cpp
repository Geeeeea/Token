#include"Token.h"

int  main() {
	
	ifstream in("in.txt", ios::in);
	istreambuf_iterator<char> beg(in), end;
	string strdata(beg, end);//����string st;st.assign(beg,end);
	sw2 = strdata;
	//cout << strdata << endl;


	cout << sw2 << endl;
	
	//sw2 = "123+333";
    ch = sw2[0];
	l = sw2.size();
	cout << l << endl;
	Tokens tokenlist = Tokens();

	
	if (!tokenlist.f())
	{
		cout << "�ڵ�"<<tokenlist.Lineshow<<"�дʷ���������" << endl;
			
	}
	else {
		cout << "��i��token" << "\tLex��Ϣ" << "\t\tLine��Ϣ" << "\tSem��Ϣ" << endl;
		for (int i = 0; i < tokenlist.tokens.size(); i++)
		{

			cout << i << "\t\t" << sym_lex[tokenlist.tokens[i].Lex] << "\t\t" << tokenlist.tokens[i].Lineshow << "\t\t" << tokenlist.tokens[i].Sem << endl;

		}
	}

	
	return 1;
}
