//Vongsprache interpreter
//Copyright (C) 2018  Arc676/Alessandro Vinciguerra <alesvinciguerra@gmail.com>

///Permission is hereby granted, free of charge, to any person obtaining
//a copy of this software and associated documentation files (the "Software"),
//to deal in the Software without restriction, including without limitation the
//rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
//sell copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:

//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.

//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
//FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
//COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
//IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
//CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "token.h"

TokenData* createTokenData(TokenType type, float floatVal,
    char* charVal, Token* tokenVal) {
    TokenData* data = (TokenData*)malloc(sizeof(TokenData));
    switch (type) {
        case NUMBER:
            data->floatVal = floatVal;
            break;
        case STRING:
        case KEYWORD:
        case PUNCTUATION:
        case IDENTIFIER:
		case OPERATOR:
            data->charVal = charVal;
            break;
        case BINARY:
        case CALL:
        case ASSIGN:
        case IF:
		case PROGRAM:
            data->tokenVal = tokenVal;
            break;
    }
    return data;
}

Token* createToken(TokenType type) {
	Token* token = (Token*)malloc(sizeof(Token));
    token->type = type;
	token->tokenData = (hashtable_t*)malloc(sizeof(hashtable_t));
    ht_create(token->tokenData, NULL, NULL);
	return token;
}

char* tokenTypeToString(TokenType type) {
	switch (type) {
		case PUNCTUATION:
			return "punctuation";
	    case NUMBER:
			return "numerical";
	    case STRING:
			return "string";
	    case KEYWORD:
			return "keyword";
	    case IDENTIFIER:
			return "identifier";
		case OPERATOR:
			return "operator";
	    case CALL:
			return "function call";
	    case BINARY:
			return "binary expression";
	    case IF:
			return "if-block";
	    case ASSIGN:
			return "assignment";
		case PROGRAM:
			return "statement sequence";
	}
}

void tokenToString(Token* token, char* str) {
	sprintf(str, "%s token", tokenTypeToString(token->type));
	TokenData* data = ht_find(token->tokenData, VALUE);
	switch (token->type) {
        case NUMBER:
            sprintf(str, "%s (%f)", str, data->floatVal);
            break;
        case STRING:
        case KEYWORD:
        case PUNCTUATION:
        case IDENTIFIER:
		case OPERATOR:
            sprintf(str, "%s (%s)", str, data->charVal);
            break;
        case BINARY:
        case CALL:
        case ASSIGN:
        case IF:
		case PROGRAM:
        {
            char sub[200];
			tokenToString(data->tokenVal, sub);
			sprintf(str, "%s (%s)", str, sub);
            break;
        }
    }
}
