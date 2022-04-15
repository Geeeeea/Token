#pragma once
#include<string>
#include<iostream>
#include<map>
#include<vector>
#include<fstream>
#define MAXRESERVED 21
using namespace std;
//������
typedef enum
{
    /*���ǵ��ʷ���*/
    ENDFILE, ERROR,
    /*������*/
    PROGRAM, PROCEDURE, TYPE, VAR, IF,
    THEN, ELSE, FI, WHILE, DO,
    ENDWH, BEGIN, END, READ, WRITE,
    ARRAY, OF, RECORD, RETURN, INTEGER, CHAR,
    /*����*/
    INTEGER_T, CHAR_T,
    /*���ַ��������*/
    ID, INTC, CHARC, INTC_VAL, CHARC_VAL,
    /*�������*/
    ASSIGN, EQ, LT, PLUS, MINUS,
    TIMES, DIVIDE, LPAREN, RPAREN, DOT,//��������OVER
    COLON, SEMI, COMMA, LMIDPAREN, RMIDPAREN,
    UNDERRANGE,

    Program, ProgramHead, ProgramName, DeclarePart,
    TypeDec, TypeDeclaration, TypeDecList, TypeDecMore,
    TypeId, TypeName, BaseType, StructureType,//TypeName��ʵ����Ӧ����TypeDef
    ArrayType, Low, Top, RecType,
    FieldDecList, FieldDecMore, IdList, IdMore,
    VarDec, VarDeclaration, VarDecList, VarDecMore,
    VarIdList, VarIdMore, ProcDec, ProcDeclaration,
    ProcDecMore, ProcName, ParamList, ParamDecList,
    ParamMore, Param, FormList, FidMore,
    ProcDecPart, ProcBody, ProgramBody, StmList,
    StmMore, Stm, AssCall, AssignmentRest,
    ConditionalStm, StmL, LoopStm, InputStm,
    InVar, OutputStm, ReturnStm, CallStmRest,
    ActParamList, ActParamMore, RelExp, OtherRelE,
    Exp, OtherTerm, Term, OtherFactor,
    Factor, Variable, VariMore, FieldVar,
    FieldVarMore, CmpOp, AddOp, MultOp
}LexType;

//��Ӧ�����ֵ��ֵ�
map < LexType, string >sym_lex ={
    {PROGRAM, "PROGRAM"},
    { TYPE, "TYPE" },
    { VAR, "VAR" },
    { PROCEDURE, "PROCEDURE" },
    { BEGIN, "BEGIN" },
    { END, "END" },
    { ARRAY, "ARRAY" },
    { OF, "OF" },
    { RECORD, "RECORD" },
    { IF, "IF" },
    { THEN, "THEN" },
    { ELSE, "ELSE" },
    { FI, "FI" },
    { WHILE, "WHILE" },
    { DO, "DO" },
    { ENDWH, "ENDWH" },
    { READ, "READ" },
    { WRITE, "WRITE" },
    { RETURN, "RETURN" },
    { INTEGER, "INTEGER" },
    { CHAR, "CHAR" },
    { ID, "ID" },
    { INTC, "INTC" },
    { CHARC, "CHAR" },
    { ASSIGN, "ASSIGN" },
    { EQ, "EQ" },
    { LT, "LT" },
    { PLUS, "PLUS" },
    { MINUS, "MINUS" },
    { TIMES, "TIMES" },
    { DIVIDE, "DIVIDE" },
    { LPAREN, "LPAREN" },
    { RPAREN, "RPAREN" },
    { DOT, "DOT" },
    { COLON, "COLON" },
    { SEMI, "SEMI" },
    { COMMA, "COMMA" },
    { LMIDPAREN, "LMIDPAREN" },
    { RMIDPAREN, "RMIDPAREN" },
    { UNDERRANGE, "UNDERRANGE" },
    { ENDFILE, "EOF" },
    { ERROR, "ERROR" }
};
vector<string> sx;

//һ��token
struct Token
{
    int Lineshow;//��Դ������ֵ�����
    LexType Lex;//�ʷ���Ϣ
    string Sem;//������Ϣ
};

//toekn����
class Tokens {
 
public:
	//��ǰtoken�����Ƿ�Ϸ�
	int flag;

	//��ǰ������λ��
	int Lineshow;

	//��ǰ���������
    LexType Lex;
    string sem;//��ʶ����ֵ

    //token����
    vector<Token>tokens;

    Tokens() {
        flag = 0;
        Lineshow = 0;
    }
    //�õ�token����
    
    bool f();
   bool isBlank(char a);
    bool getTokenlist(string str);  
    void addToken(LexType lex, string name);
    string readStr();
    bool isNum(string str);
    bool isString(string str);//������
    bool isSeparator(char ch);//�жϷָ���
    string str_lex(string x);
    bool dealState(int state);

	
};

enum state { s0, s1, s2,s3, s4, s5,s6,s7,s8 };//0�ǳ�ʼ״̬,1������,2����ĸ,3��+-��4��:,5��=,6��{,7��}.8��,
int input(char ch){
    if ( (ch >= '0' && ch <= '9'))
        return 0;
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
        return 1;

    if (ch == '(' || ch == ')' || ch == '[' || ch == ']'  || ch == ',' || ch == ';')
        return 2;
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '<')
        return 2;

    if (ch == ':')
        return 3;
    if (ch == '=')
        return 4;
    if (ch == '{')
        return 5;
    if (ch == '}')
        return 6;
    if (ch == '.')
        return 7;
    if (ch == ' ' || ch == '\t' || ch == '\n')
        return 8;
   
    }
  
int T[9][9]= {//1,a,-,:,=,{,},., 
                1,2,8,3,8,4,7,5,0,
                1,7,8,8,8,8,8,8,0,
                6,2,8,8,8,8,8,8,0,
                7,7,7,7,8,7,7,7,7,
                4,4,4,4,4,4,8,4,4,
                0,0,0,0,0,0,0,8,0,
                6,6,8,8,8,8,8,8,0,
                0,0,0,0,0,0,0,0,0,//ʧ��
                0,0,0,0,0,0,0,0,0//�ɹ�
};
char ch;
int state = s0;
string s;//�洢��ǰ�����token
string sw2;
int l;
int sw = 0;
bool Tokens::isBlank(char a) {
    if (a == ' ')
        return true;
    if (a == '\n')
    {
        Lineshow++;
        return true;
    }
    if (a == '\t')
        return true;
    return false;
}

bool Tokens::f() {
   
   // cout << "a:" << input(ch) << endl;
    while (sw < l)
    {
        
        if (ch == '.') {
            
            if (sw < l - 1 && sw2[sw + 1] == '.')
            {//..
               // cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
                Token ok;
                ok.Lex = UNDERRANGE;
                ok.Sem = "NULL";
                ok.Lineshow = Lineshow;
                tokens.push_back(ok);
                s.clear();
                sw += 2;
            }
            else {
                if ((sw + 1) != sw2.length()) {
                   // cout << Lineshow << " ����������Լ����֣����Ǻ��滹�г���" << endl;
                    Token ok;
                    ok.Lex = DOT;
                    ok.Sem = "NULL";
                    ok.Lineshow = Lineshow;
                    tokens.push_back(ok);
                    sw++;
                }
                else {
                    if (sw == l - 1) {
                        Token ok;
                        ok.Lex = DOT;
                        ok.Sem = "NULL";
                        ok.Lineshow = Lineshow;
                        tokens.push_back(ok);
                        sw++;
                        return true;
                    }
                    
                }
               
            }
        }
        else
        {
           // cout << "����-------------------\n";
            while ((T[state][input(ch)] != s0) && sw < l)
            {
                state = T[state][input(ch)];
                //cout << "\nch�ǣ�" << ch << endl;
               // cout << "state��:" << state << endl;
                if (!isBlank(ch))
                {
                    
                    s.push_back(ch);
                }
               
                //if (ch == '{') {
                //    int k = sw;
                //    int flag = 0;
                //    while (k < l && flag == 0) {
                //        if (sw2[k] == '}')
                //            flag = 1;
                //        k++;
                //       // cout << k <<"  " << sw2[k]<<" "<<flag << endl;
                //    }
                //    //cout << "������k" << k << "sw " << sw2[k] << endl;
                //        if (flag == 1) {//�ɹ������ע��
                //            state = 0;
                //            sw = k;
                //            ch = sw2[sw];
                //            s.clear();
                //        }
                //        else {
                //            //ƥ��ʧ��
                //            return false;
                //        }
                //    
                //}
                ch = sw2[++sw];
               
                cout << "---------" << endl;
                cout << "����" << sw << endl;
                cout << "�¸�ch�ǣ�" << ch << endl;
                cout << "s��:" << s << endl;
                cout << "��ǰ״̬�ǣ�" << state << endl;
                cout << "�¸�״̬�ǣ�" << T[state][input(ch)] << endl;
            }
        }
       
    
           if( !dealState(state))
               return false;
            state = 0;
            ch = sw2[sw];
            if (ch == ' '||ch =='\t'|| ch=='\n') {
              
                
                if (ch == '\n')
                    Lineshow++;
                ch = sw2[++sw];
            }
            s.clear();
            /*cout << "\n��ǰ��ch�ǣ�" << ch << endl;
            cout << "�¸�ch�ǣ�" << sw2[sw + 1] << endl;
           cout << "input ch�ǣ�" << input(ch) << endl;
            cout << "��ǰ״̬��" << state << endl;
           cout << "�¸�״̬��" << T[state][input(ch)] << endl;
            cout << "�ַ����ǣ�" << s << endl;
            cout << "��ǰ�ַ����ĳ���" << s.size() << endl;
            cout << "sw��" << sw << endl;*/
        }
        return true;
    }

LexType exchangeLex(char c) {
   if(c=='(') return LPAREN;
   if (c == ')')  return RPAREN;
   if (c == '[')  return LMIDPAREN;//�����������ȷ���������������һ���в���
   if (c == ']')  return RMIDPAREN;
   if (c == ',')  return COMMA;
   if (c == ';') return SEMI;
   if (c == '+')  return PLUS;
   if (c == '-') return  MINUS;
   if (c == '*') return TIMES;
   if (c == '/') return  DIVIDE;
   if (c == '<')  return LT;
    if(c == '=')  return ASSIGN;
}
string Tokens::str_lex(string x) {
    if (x == "program") { Lex = PROGRAM; return "PROGRAM"; }
    else if (x == "type") { Lex = TYPE; return "TYPE"; }
    else if (x == "var") { Lex = VAR; return "VAR"; }
    else if (x == "procedure") { Lex = PROCEDURE; return "PROCEDURE"; }
    else if (x == "begin") { Lex = BEGIN; return "BEGIN"; }
    else if (x == "end") { Lex = END; return "END"; }
    else if (x == "array") { Lex = ARRAY; return "ARRAY"; }
    else if (x == "of") { Lex = OF; return "OF"; }
    else if (x == "record") { Lex = RECORD; return "RECORD"; }
    else if (x == "if") { Lex = IF; return "IF"; }
    else if (x == "then") { Lex = THEN; return "THEN"; }
    else if (x == "else") { Lex = ELSE; return "ELSE"; }
    else if (x == "fi") { Lex = FI; return "FI"; }
    else if (x == "while") { Lex = WHILE; return "WHILE"; }
    else if (x == "do") { Lex = DO; return "DO"; }
    else if (x == "endwh") { Lex = ENDWH; return "ENDWH"; }
    else if (x == "read") { Lex = READ; return "READ"; }
    else if (x == "write") { Lex = WRITE; return "WRITE"; }
    else if (x == "return") { Lex = RETURN; return "RETURN"; }
    else if (x == "integer") { Lex = INTEGER; return "INTEGER"; }
    else if (x == "char") { Lex = CHAR; return "CHAR"; }
    else { Lex = ID; return "ID"; }
}
bool Tokens::dealState(int state) {
    Token tok; //sem lex
    if (s.empty())
        return true;
    if (state == 1) {
        Lex = INTC;
        sem = s;
    }
    else {
        if (state == 6||state == 2) {
            string str2 = str_lex(s);
            if (str2 != "ID") {
                sem = "NULL";
            }
            else { sem = s; }
        }
        else {
            if (state == 7) {
                return false;
            }
            else {
                if (state == 8)
                {

                    if (s[s.length() - 1] == '.') {//11212.
                        state = 0;
                        s.pop_back();
                        sw--;
                        if (isdigit(s[0])) {
                            Lex = INTC;
                            sem = s;
                        }
                        else {
                            string str2 = str_lex(s);
                            if (str2 != "ID") {
                                sem = "NULL";
                            }
                            else { sem = s; }
                        }
                    }

                    else
                    {
                        if (s[0] == '{')//ע��
                    {
                            
                        s.clear();
                        return true;
                    }
                    else {
                        if (s.size() == 1) {//������+-=
                           
                                Lex = exchangeLex(s[0]);
                                sem = "NULL";
                            
                        }
                        else 
                        {
                            if (s[s.size()-2] == ':') {//����:=
                                Lex = exchangeLex(s[s.size() - 1]);
                                sem = "Null";
                            }
                            else {//����123+����a+
                                state = 0;
                                s.pop_back();
                                cout << "opppppppppppppppppppppp" << endl;
                                sw--;                   
                                if (isdigit(s[0])) {
                                    Lex = INTC;
                                    sem = s;
                                }
                                else {
                                    string str2 = str_lex(s);
                                    if (str2 != "ID") {
                                        sem = "NULL";
                                    }
                                    else { sem = s; }

                                }
                            }
                        }

                    }
                     }

                    //�����ֿո�ʱ
                    if (s[s.length() - 1] == ' ') {
                        cout << "\t\t\tsssss" << endl;
                       //������ַ���
                        if (isalnum(s[0])) {
                            int lenth = s.length();
                            int flag=1;
                            int xb = 0;
                            while (flag) {
                                if (!isdigit(s[xb]))
                                    flag = 0;
                                xb++;
                            }
                            //����Ǵ�����
                            if (flag)
                            {
                                Lex = INTC;
                                sem = s;
                            }
                            else {//�Ǵ�����
                                string str2 = str_lex(s);
                                if (str2 != "ID") {
                                    sem = "NULL";
                                }
                                else { sem = s; }
                            }
                                
                        }
                        //�����+-
                        if (input(s[s.length() - 2]) == 2) {
                            Lex = exchangeLex(s[0]);
                            sem = "NULL";
                        }
                        //������ֵ����Ŀո�
                        if (s.size() == 1)
                            return true;
                    }

                 }

                else {
                    if (state == 4)
                        return false;
                }
                }
            
        }
       
    } 
        tok.Lex = Lex;
        tok.Lineshow = Lineshow;
        tok.Sem = sem;
        tokens.push_back(tok);
       cout << "\t\t\t��ǰ��ɵ�token�ǣ�" << tok.Sem << endl;
      //  cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
        
        
        return true;
   return true;
}


