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
    LBrace,
    RBrace,
    Comma,
    Newline,
    EndOfFile,
    SColon,
    FStarter,
    FType,
    Return,
    LBracket,
    RBracket,
    DataType,

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
    int column;

    Token(TokenType t, const string& val, int ln, int col)
        : type(t), value(val), line(ln), column(col) {} //member intializer list for constructor above
};

//helper function

bool isSymbol(char c) {
    const std::string symbols = "+-*/(){}[],;=<>!&|^%~:.?";
    return symbols.find(c) != std::string::npos;
}

extern vector<Token> tokens;

/* function that reads the source code and produce a vector/list of tokens */
vector<Token> tokenize(const string& source){
    

    int i = 0;
    int line = 1;
    int column = 1;

    while (i < source.size()){
        // reading whitespace token type 
        if (isspace(source[i])){
            if (source[i] == '\n'){
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

            //make sure to classify which identifiers/keyword 

            string ident = source.substr(start, i - start);

            if (ident == "fxn"){
                tokens.push_back({TokenType::FStarter, "", line, column});
            } 
            else if(ident == "->"){
                tokens.push_back({TokenType::Return, "", line, column});
            }
            else if(ident == "int"){
                tokens.push_back({TokenType::DataType, ident, line, column});
            } 
            else if(ident == "bool"){
                tokens.push_back({TokenType::DataType, ident, line, column});
            }
            else if(ident == "string"){
                tokens.push_back({TokenType::DataType, ident, line, column});
            }
            else if(ident == "float"){
                tokens.push_back({TokenType::DataType, ident, line, column});
            }
            else{
                tokens.push_back(Token(TokenType::Identifier,ident,line,column)); 
            }
        
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
            continue;
        }

        char c = source[i];

        if (isSymbol(c)) {
            // Check for multi-char symbols first
            if (c == '-' && i + 1 < (int)source.size() && source[i + 1] == '>') {
                tokens.push_back(Token(TokenType::Return, "->", line, column));
                i += 2;
                column += 2;
                continue;
            }
            
            
            //single-character tokens
            switch(source[i]){
                case ('+'):{
                    std::string op(1, c);
                    tokens.push_back(Token(TokenType::Operator,op, line, column));
                    break;
                }
                case ('-'):{
                    std::string op(1, c);
                    tokens.push_back(Token(TokenType::Operator,op, line, column));
                    break;
                }
                case ('%'):{
                    std::string op(1, c);
                    tokens.push_back(Token(TokenType::Operator,op, line, column)); 
                    break; 
                }
                case ('('):{
                    std::string op(1, c);
                    tokens.push_back(Token(TokenType::LParenthesis,"(", line, column));
                    break;
                }
                case (')'):{
                    std::string op(1, c);
                    tokens.push_back(Token(TokenType::LParenthesis,")", line, column));
                    break;
                }
                case ('['):{
                    std::string op(1, c);
                    tokens.push_back(Token(TokenType::LBracket, "[", line, column));
                    break;
                }
                case (']'):{
                    std::string op(1, c);
                    tokens.push_back(Token(TokenType::RBracket, "]", line, column));
                    break;
                }
                case ('{'):{
                    std::string op(1, c);
                    tokens.push_back(Token(TokenType::LBrace, "{", line, column));
                    break;
                }
                case ('}'):{
                    std::string op(1, c);
                    tokens.push_back(Token(TokenType::RBrace, "}", line, column));
                    break;
                }
                case (';'):{
                    std::string op(1, c);
                    tokens.push_back(Token(TokenType::SColon, ";", line, column));
                    break;
                }
                case (','):{
                    std::string op(1, c);
                    tokens.push_back(Token(TokenType::Comma, ",", line, column));
                    break;
                }
                case ('='):{
                    std::string op(1, c);
                    tokens.push_back(Token(TokenType::Assign, "=", line, column)); 
                    break;
                }
                case ('/'):{
                    std::string op(1, c);
                    tokens.push_back(Token(TokenType::Operator,op, line, column));
                    break;
                }
                default:
                    std::cerr << "ERROR DETECTED: UNKNOWN CHARACTER '" << c
                    << "' AT LINE " << line << ", COLUMN " << column << std::endl;
                    i++;
                    column++;
                    break;
            }

            i++;
            column++;
            continue;
        }
        
        printf("ERROR DETECTED: UNKNOWN CHARACTER '%c' AT LINE %d, COLUMN %d\n", source[i], line, column);
        i++;
        column++;
        
    }

    tokens.push_back(Token(TokenType::EndOfFile, "", line, column));
    return tokens;
}

