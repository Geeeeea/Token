#pragma once
#include<string>
#include<iostream>
#include<map>
#include<vector>
#include<fstream>
#define MAXRESERVED 21
using namespace std;
//保留字
typedef enum
{
    /*薄记单词符号*/
    ENDFILE, ERROR,
    /*保留字*/
    PROGRAM, PROCEDURE, TYPE, VAR, IF,
    THEN, ELSE, FI, WHILE, DO,
    ENDWH, BEGIN, END, READ, WRITE,
    ARRAY, OF, RECORD, RETURN, INTEGER, CHAR,
    /*类型*/
    INTEGER_T, CHAR_T,
    /*多字符单词序号*/
    ID, INTC, CHARC, INTC_VAL, CHARC_VAL,
    /*特殊符号*/
    ASSIGN, EQ, LT, PLUS, MINUS,
    TIMES, DIVIDE, LPAREN, RPAREN, DOT,//÷书上是OVER
    COLON, SEMI, COMMA, LMIDPAREN, RMIDPAREN,
    UNDERRANGE,

    Program, ProgramHead, ProgramName, DeclarePart,
    TypeDec, TypeDeclaration, TypeDecList, TypeDecMore,
    TypeId, TypeName, BaseType, StructureType,//TypeName其实真正应该是TypeDef
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

//对应保留字的字典
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

//一个token
struct Token
{
    int Lineshow;//在源程序出现的行数
    LexType Lex;//词法信息
    string Sem;//语义信息
};

//toekn序列
class Tokens {
 
public:
	//当前token序列是否合法
	int flag;

	//当前处理到的位置
	int Lineshow;

	//当前处理的内容
    LexType Lex;
    string sem;//标识符的值

    //token序列
    vector<Token>tokens;

    Tokens() {
        flag = 0;
        Lineshow = 0;
    }
    //得到token序列
    
    bool f();
   bool isBlank(char a);
    bool getTokenlist(string str);  
    void addToken(LexType lex, string name);
    string readStr();
    bool isNum(string str);
    bool isString(string str);//保留字
    bool isSeparator(char ch);//判断分隔符
    string str_lex(string x);
    bool dealState(int state);

	
};

enum state { s0, s1, s2,s3, s4, s5,s6,s7,s8 };//0是初始状态,1是数字,2是字母,3是+-，4是:,5是=,6是{,7是}.8是,
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
                0,0,0,0,0,0,0,0,0,//失败
                0,0,0,0,0,0,0,0,0//成功
};
char ch;
int state = s0;
string s;//存储当前处理的token
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
                   // cout << Lineshow << " 程序结束符以及出现，但是后面还有程序" << endl;
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
           // cout << "进入-------------------\n";
            while ((T[state][input(ch)] != s0) && sw < l)
            {
                state = T[state][input(ch)];
                //cout << "\nch是：" << ch << endl;
               // cout << "state是:" << state << endl;
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
                //    //cout << "现在是k" << k << "sw " << sw2[k] << endl;
                //        if (flag == 1) {//成功完成了注释
                //            state = 0;
                //            sw = k;
                //            ch = sw2[sw];
                //            s.clear();
                //        }
                //        else {
                //            //匹配失败
                //            return false;
                //        }
                //    
                //}
                ch = sw2[++sw];
               
                cout << "---------" << endl;
                cout << "次数" << sw << endl;
                cout << "下个ch是：" << ch << endl;
                cout << "s是:" << s << endl;
                cout << "当前状态是：" << state << endl;
                cout << "下个状态是：" << T[state][input(ch)] << endl;
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
            /*cout << "\n当前的ch是：" << ch << endl;
            cout << "下个ch是：" << sw2[sw + 1] << endl;
           cout << "input ch是：" << input(ch) << endl;
            cout << "当前状态：" << state << endl;
           cout << "下个状态：" << T[state][input(ch)] << endl;
            cout << "字符串是：" << s << endl;
            cout << "当前字符串的长度" << s.size() << endl;
            cout << "sw是" << sw << endl;*/
        }
        return true;
    }

LexType exchangeLex(char c) {
   if(c=='(') return LPAREN;
   if (c == ')')  return RPAREN;
   if (c == '[')  return LMIDPAREN;//这里更加让我确定了书和资料总有一个有病！
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
                        if (s[0] == '{')//注释
                    {
                            
                        s.clear();
                        return true;
                    }
                    else {
                        if (s.size() == 1) {//单独的+-=
                           
                                Lex = exchangeLex(s[0]);
                                sem = "NULL";
                            
                        }
                        else 
                        {
                            if (s[s.size()-2] == ':') {//出现:=
                                Lex = exchangeLex(s[s.size() - 1]);
                                sem = "Null";
                            }
                            else {//出现123+或者a+
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

                    //当出现空格时
                    if (s[s.length() - 1] == ' ') {
                        cout << "\t\t\tsssss" << endl;
                       //如果是字符串
                        if (isalnum(s[0])) {
                            int lenth = s.length();
                            int flag=1;
                            int xb = 0;
                            while (flag) {
                                if (!isdigit(s[xb]))
                                    flag = 0;
                                xb++;
                            }
                            //如果是纯数字
                            if (flag)
                            {
                                Lex = INTC;
                                sem = s;
                            }
                            else {//非纯数字
                                string str2 = str_lex(s);
                                if (str2 != "ID") {
                                    sem = "NULL";
                                }
                                else { sem = s; }
                            }
                                
                        }
                        //如果是+-
                        if (input(s[s.length() - 2]) == 2) {
                            Lex = exchangeLex(s[0]);
                            sem = "NULL";
                        }
                        //如果出现单独的空格
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
       cout << "\t\t\t当前完成的token是：" << tok.Sem << endl;
      //  cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
        
        
        return true;
   return true;
}


