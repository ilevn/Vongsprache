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

#ifndef PARSER_H
#define PARSER_H

#include <stdarg.h>

#include "lexer.h"

#define INITIAL_STATEMENT_COUNT 100
#define INITIAL_DELIM_COUNT 10
#define INITIAL_FUNCTION_STATEMENT_COUNT 10

/**
 * Top-level parse function to parse the whole script
 * @param fp FILE* from which to read
 * @return Program token containing the script
 */
Token* parseTopLevel(FILE* fp);

/**
 * Parse a function from the token stream
 * @param fp FILE* from which to read
 * @return Function token containing the defined function
 */
Token* parseFunction(FILE* fp);

/**
 * Parse an if-block from the token stream
 * @param fp FILE* from which to read
 * @return Conditional token defining the block
 */
Token* parseIf(FILE* fp);

/**
 * Parse a function call from the token stream
 * @param fp FILE* from which to read
 * @return Call token indicating the called function and passed arguments
 */
Token* parseCall(FILE* fp);

/**
 * Parse a sequence of statements
 * @param fp FILE* from which to read
 * @return Program token containing statements
 */
Token* parseProg(FILE* fp);

/**
 * Parse the token stream for a variable name
 * @param fp FILE* from which to read
 * @return Identifier of the variable
 */
char* parseVariableName(FILE* fp);

/**
 * Parse the next expression contained in the token stream
 * @param fp FILE* from which to read
 * @return Token representing the next expression in the stream
 */
Token* parseExpression(FILE* fp);

/**
 * Parse the stream for a potential binary expression
 * @param fp FILE* from which to read
 * @param token Given token that might start an expression
 * @param prec Precedence of the given token
 * @return The given token or another token representing the expression
 */
Token* potentialBinary(FILE* fp, Token* token, int prec);

/**
 * Parse the stream for a list of tokens between specified start and end
 * characters delimited by the specified separator
 * @param fp FILE* from which to read
 * @param start Starting character for the list (as string)
 * @param end Ending character for the list (as string)
 * @param sep Delimiter character for the list (as string)
 * @param count Pointer to int in which to store parsed token count 
 * @param parse Parse function to parse the delimited tokens
 * @return An array containing the parsed tokens
 */
Token** parseDelimited(FILE* fp, char* start, char* end, char* sep, int* count,
	Token* (*parse)(FILE*));

/**
 * Check whether the current token is of a given type and contains a given
 * string in the TokenData charVal of data stored with the VALUE key
 * @param fp FILE* from which to read
 * @param type Desired token type
 * @param value Desired string value
 * @return Whether the current token matches
 */
int parser_isValue(FILE* fp, TokenType type, char* value);

/**
 * Confirm that the next tokens match the corresponding is* function and
 * remove them from the stream. Only values with matching token types can be
 * searched for and removed with a single function call.
 * @param fp FILE* from which to read
 * @param type Desired token type
 * @param count Number of tokens to search for and skip
 * @param ... Variadic list of desired values
 */
void skipValue(FILE* fp, TokenType type, int count, ...);

/**
 * Throw an error if the current token is an unexpected token
 * @param token The unexpected token
 */
void unexpected(Token* token);

#endif
