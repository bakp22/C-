#include <string>

using namespace std;

enum class TokenType {
    Identifier,
    Number,
    String,
    Keyword,
    Operator,
    Assign,
    LParenthesis,
    RParenthesis,
    LBracket,
    RBracket,
    Comma,
    Newline,
    EndOfFile,
};


/*
 token object creator for each individual thing. 

 example: x = 5

    Token(type=Identifier, value="x", line=1, column=1)
    Token(type=Assign, value="=", line=1, column=3)
    Token(type=Number, value="5", line=1, column=5)
*/
struct Token {
    TokenType type; 
    string value;
    int line;
    int column

    Token(TokenType t; const string& val, int ln, int col)
        : type(t), value(val), line(ln), column(col) {} //member intializer list for constructor above
}

/* function that reads the source code and produce a vector/list of tokens */
vector<Token> tokenize(const string& source){
    vector<Token> tokens;

    i = 0

    while (i < source.size()){

        int line = 1;

    
        // reading whitespace token type 
        if (isspace(source[i])){
            if (c == '\n'){
                line++;
                column = 1;
            } else {
                column++;
            }
            i++;
            continue;

        } 
        
        // reading Identifier/keyword token type
        if (isalpha(source[i])){
            int start = i;
            //while the character alphanumerics, the loop advances i and a column
            while (i < source.size() && isalnum(source[i])){
                i++;
                column++;
            }
            string ident = source.substr(start, i - start);
            tokens.push_back(Token(TokenType::Identifier,ident,line,column)); 
            continue;
        } 
        
        //reading number token type
        if (isdigit(source[i])){
            int start = i;
            while (i < source.size() && isalnum(source[i])){
                i++;
                column++;
            }
            string number = source.substr(start,i-start);
            tokens.push_back(Token(TokenType::Number, number, line, column)); 
        }

        //single-character tokens
        switch(source[i]):
            case ("+"):
                string operator(1,c);
                tokens.push_back(Token(TokenType::Operator,operator, line, column));
            case ("-"):
                string operator(1,c);
                tokens.push_back(Token(TokenType::Operator,operator, line, column));
            case ("%"):
                string operator(1,c);
                tokens.push_back(Token(TokenType::Operator,operator, line, column));  
            case ("("):
                tokens.push_back(Token(TokenType::LParenthesis,"(", line, column));
            case (")"):

            case ("["):

            case ("]"):

            case ("{"):
            
            case ("}"):

            case (";"):
            
            case (","):

            case ("="):

            case ("/"):
                string operator(1,c);
                tokens.push_back(Token(TokenType::Operator,operator, line, column));
            default:
                printf("ERROR DETECTED: UNKNOWN CHARACTER " + source[i] + "AT LINE " + line);
        
    }

    // characters to check for "()", "[]", ";", " "" ", " '' ", "/", "+", "-", "%", "=", "==", ","

    
    return tokens;
}

