#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Token.h"
#include "DatalogProgram.h"
#include "Predicate.h"
#include "Parameter.h"
#include "Rule.h"

using namespace std;

enum DatalogSection {

    SCHEME, FACT, RULE, QUERY

};

class Parser {
    
    private:
        vector<Token> tokenList;
        DatalogProgram datalogProgramObject();
        DatalogSection section;
        
    public:
        Parser(const vector<Token> tokens) {
            tokenList = tokens;
            section = SCHEME;
        }

        TokenType tokenType() const {
            return tokenList.at(0).getType();
        }

        void advanceToken() {
            tokenList.erase(tokenList.begin());
        }

        void throwError(Token t) {
            try {
                throw t;
            } catch (Token token) {
                cout << "Failure!" << endl << "  " << token.toString();
                exit(1);
            }
            cout << "Error" << endl;
        }

        bool match(TokenType t) {
            cout << "Match: " << t << endl;
            if (tokenType() == t) {
                if (t == FACTS) {
                    section = FACT;
                } else if (t == RULES) {
                    section = RULE;
                } else if (t == QUERIES) {
                    section = QUERY;
                }
                advanceToken();
                return true;        
            } else   {
                throwError(tokenList[0]);
                return false;
            }  
        }

         bool match(TokenType t) {
            cout << "Match: " << t << endl;
            if (tokenType() == t) {
                if (t == FACTS) {
                    section = FACT;
                } else if (t == RULES) {
                    section = RULE;
                } else if (t == QUERIES) {
                    section = QUERY;
                }
                advanceToken();
                return true;        
            } else   {
                throwError(tokenList[0]);
                return false;
            }  
        }

        //0 - COMMA
        //1 - PERIOD
        //2 - Q_MARK
        //3 - LEFT_PAREN
        //4 - RIGHT_PAREN
        //5 - COLON
        //6 - COLON_DASH
        //7 - MULTIPLY
        //8 - ADD
        //9 - SCHEMES
        //10 - FACTS
        //11 - RULES
        //12 - QUERIES
        //13 - ID
        //14 - STRING
        //15 - COMMENT
        //16 - UNDEFINED
        //17 - EOF

      

        void datalogProgramBegin() {

            //Catch error?

            if (tokenType() == SCHEMES) {
                match(SCHEMES);
                match(COLON);
                scheme();
                schemeList();
                match(FACTS);
                match(COLON);
                factList();
                cout << "This is first" << endl;
                match(RULES);
                cout << "This is second" << endl;
                match(COLON);
                ruleList();
                match(QUERIES);
                match(COLON);
                query();
                queryList();
                match(ENDFILE);
            }

        }

        void schemeList() {
            if (scheme() == true) {
                schemeList();
            } else {
                //Lambda
            }
        }

        void factList() {
            if (fact()) {
                factList();
            } else {
                //Lambda
            }
        }

        void ruleList() {
            if (rule()) {
                ruleList();
            } else {
                //Lambda
            }
        }

        void queryList() {
            if (query()) {
                queryList();
            } else {
                //Lambda
            }
        }

        bool scheme() {
            if (tokenType() == ID) {
                Predicate addedScheme;
                if (match(ID) == false)
                    return false;
                if (match(LEFT_PAREN) == false)
                    return false;
                if (match(ID) == false)
                    return false;
                if (idList() == false)
                    return false;
                if (match(RIGHT_PAREN) == false)
                    return false;
                return true;
            }
            return false;     
        }

        bool fact() {
            if(tokenType() == ID) {
                if (match(ID) == false)
                    return false;
                if (match(LEFT_PAREN) == false) 
                    return false;
                if (match(STRING) == false) 
                    return false;
                if (stringList() == false)
                    return false;
                if (match(RIGHT_PAREN) == false)
                    return false;
                if (match(PERIOD) == false)
                    return false;
                return true;
            }
            return false;
        }

        bool rule() {
            if (headPredicate() == false)
                return false;
            if (match(COLON_DASH) == false)
                return false;
            if (predicate() == false) 
                return false;
            if (predicateList() == false) 
                return false;
            if (match(PERIOD) == false) 
                return false;
            return true;
        }

        bool query() {
            if (predicate() == true) {
                if (match(Q_MARK) == false)
                    return false;
                return true;
            }
            return false;
        }


        bool headPredicate() {
            if (tokenType() == ID) {
                if (match(ID) == false)
                    return false;
                if (match(LEFT_PAREN) == false)
                    return false;
                if (match(ID) == false)
                    return false;
                if (idList() == false) 
                    return false;
                if (match(RIGHT_PAREN) == false) {
                    return false;
                }
                return true;
            }
            return false;
        }

        bool predicate() {

            if (tokenType() == ID) {
                if (match(ID) == false) 
                    return false;
                if (match(LEFT_PAREN) == false)
                    return false;
                if (parameter() == false) 
                    return false;
                if (parameterList() == false) 
                    return false;
                if (match(RIGHT_PAREN) == false)
                    return false;

                return true;
            }
            return false;
        }


        bool predicateList() {
            if (tokenType() == COMMA) {
                if (match(COMMA) == false)
                    return false;
                if (predicate() == false)
                    return false;
                if (predicateList() == false) 
                    return false;
                return true;
            } else {
                return true;
            }
        }


        bool parameterList() {
            if(tokenType() == COMMA) {
                if (match(COMMA) == false)
                    return false;
                if (parameter() == false)
                    return false;
                if (parameterList() == false)
                    return false;
                
                return true;
            } else {
                return true;
            }
        }


        bool stringList() {
            if (tokenType() == COMMA) {
                if (match(COMMA) == false)
                    return false;
                if (match(STRING) == false)
                    return false;
                if (stringList() == false)
                    return false;
                return true;
            } else {
                //Lambda
                return true;
            }
        }


        bool idList() {
            if (tokenType() == COMMA) {
                if (match(COMMA) == false)
                    return false;
                if (match(ID) == false) 
                    return false;
                if (idList() == false)
                    return false;
                return true;
            } else {
                //Lambda
                return true;
            }
        }


        bool parameter() {
            if (tokenType() == STRING) {
                if (match(STRING) == false)
                    return false;
                else 
                    return true;
            } else {
                if (match (ID) == false)
                    return false;
                else
                    return true;
            }
        }
        




};