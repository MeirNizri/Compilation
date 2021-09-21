D			[0-9]
L			[a-zA-Z_]
E			[Ee][+-]?{D}+
WS  			[ \t\n]

%{
#include "tokentype.h"
%}

%%

 /* insert reserved words in symbol table */
"auto"			{ return(AUTO); }
"break"		{ return(BREAK); }
"case"			{ return(CASE); }
"char"			{ return(CHAR); }
"const"		{ return(CONST); }
"continue"		{ return(CONTINUE); }
"default"		{ return(DEFAULT); }
"do"			{ return(DO); }
"double"		{ return(DOUBLE); }
"else"			{ return(ELSE); }
"enum"			{ return(ENUM); }
"extern"		{ return(EXTERN); }
"float"		{ return(FLOAT); }
"for"			{ return(FOR); }
"goto"			{ return(GOTO); }
"if"			{ return(IF); }
"int"			{ return(INT); }
"long"			{ return(LONG); }
"register"		{ return(REGISTER); }
"return"		{ return(RETURN); }
"short"		{ return(SHORT); }
"signed"		{ return(SIGNED); }
"sizeof"		{ return(SIZEOF); }
"static"		{ return(STATIC); }
"struct"		{ return(STRUCT); }
"switch"		{ return(SWITCH); }
"typedef"		{ return(TYPEDEF); }
"union"		{ return(UNION); }
"unsigned"		{ return(UNSIGNED); }
"void"			{ return(VOID); }
"volatile"		{ return(VOLATILE); }
"while"		{ return(WHILE); }

{L}({L}|{D})*		{ return(IDENTIFIER); }

[1-9]{D}*		{ return(CONSTANT); }		10
{D}+{E}		{ return(CONSTANT); }		123E4
{D}*"."{D}+{E}?	{ return(CONSTANT); }		.123
{D}+"."{D}*{E}?	{ return(CONSTANT); }		123.

\'[^\']\'		{ return(CONSTANT); }		'a'
\"[^\"]*\"		{ return(STRING_LITERAL); }	"abc"

"++"			{ return(INC_OP); }
"--"			{ return(DEC_OP); }
"->"			{ return(PTR_OP); }
"&&"			{ return(AND_OP); }
"||"			{ return(OR_OP); }
"<="			{ return(LE_OP); }
">="			{ return(GE_OP); }
"=="			{ return(EQ_OP); }
"!="			{ return(NE_OP); }

";"			{ return(';'); }
"{"			{ return('{'); }
"}"			{ return('}'); }
","			{ return(','); }
":"			{ return(':'); }
"="			{ return('='); }
"("			{ return('('); }
")"			{ return(')'); }
"["			{ return('['); }
"]"			{ return(']'); }
"."			{ return('.'); }
"&"			{ return('&'); }
"!"			{ return('!'); }
"~"			{ return('~'); }
"-"			{ return('-'); }
"+"			{ return('+'); }
"*"			{ return('*'); }
"/"			{ return('/'); }
"%"			{ return('%'); }
"<"			{ return('<'); }
">"			{ return('>'); }
"^"			{ return('^'); }
"|"			{ return('|'); }
"?"			{ return('?'); }

{WS}+			{ /* skip whitespace */ }
"/*"			{ comment(); /* skip comment */ }	/* comment */
"//"[^\n]*		{ /* skip // comment */ }		// comment
.			{ return(ERROR); }

%%

comment() /* adapt the following code */
{
	char c, prev = 0; 
	while (c = input())
	{
		if (c == '/' && prev == '*')
			return;
		prev = c;
	}
}

