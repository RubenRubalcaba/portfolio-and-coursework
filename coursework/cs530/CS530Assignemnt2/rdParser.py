# Ruben Rubalcaba
# CS 530
# Professor Shen
# November 25 2021
#RedID: 820565766
import re
from functools import *

"""

Assignment 2 - 
A LL(1) recursive descent parser for validating simple expressions.

# Task A:
You would need to first write the grammar rules (non-terminal) in EBNF 
according to the token patterns and grammar rules specified in the prompt,
put the rules in a separate PDF file, see prompt. 
(Refer to the EBNF example in Figure 5.15)

# Task B:
You would then write the recursive descent parsing procedures for the 
validation parsing according to the rules from Task A. 
(Refer to the parsing algorithm in Figure 5.17)

It implements one parsing procedure for each one of the 
non-terminals (grammar rules), starting from the top of the parse tree, 
then drilling into lower hierachical levels.

The procedures work together to handle all combinations of the grammar 
rules, and they automatically handle the nested compositions of terms 
with multi-level priority brackets. 

----------------------------------------------------------------------------
Usage (Refer to the prompt for more examples - both positive and negative cases)

r = recDecsent('7 - 17')
print(r.validate()) # will print True as '7 - 17' is a valid expression

r = recDecsent('7 - ')
print(r.validate()) # will print False as '7 - ' is an invalid expression

"""


class recDescent:

    # IMPORTANT:
    # You MUST NOT change the signatures of
    # the constructor, lex(self) and validate(self)
    # Otherwise, autograding tests will FAIL

    # constructor to initialize and set class level variables
    def __init__(self, expr=""):
        # string to be parsed
        self.expr = expr

        # tokens from lexer tokenization of the expression
        self.tokens = []
        self.index = 0
        self.loperator = ["and","or","nand","xor","xnor"]
        self.reloperator = ["<",">","<=",">=","=","!=","not"]

    # lexer - tokenize the expression into a list of tokens
    # the tokens are stored in an list which can be accessed by self.tokens
    # do not edit any piece of code in this function
    def lex(self):
        self.tokens = re.findall("[-\(\)=]|[!<>]=|[<>]|\w+|[^ +]\W+", self.expr)
        # transform tokens to lower case, and filter out possible spaces in the tokens
        self.tokens = list(filter((lambda x: len(x)),
                                  list(map((lambda x: x.strip().lower()), self.tokens))))

        # parser - determine if the input expression is valid or not

    # validate() function will return True if the expression is valid, False otherwise
    # do not change the method signature as this function will be called by the autograder
    def exp(self):

        var = self.term()

        return var
    def term(self):
        #If first token is an integer begin
        var = False
        if self.tokens[self.index].isdigit():
            self.index+=1
            if self.index == len(self.tokens):
                var = True
                return var
            #Descend to Logical operator
            if self.tokens[self.index] == "-":
                var = True
                self.index += 1
                if self.index == len(self.tokens):
                    var = False
                    return var
                elif self.tokens[self.index].isdigit():
                    self.index+=1
                    return var
                elif self.tokens[self.index].isdigit()==False:
                    var = False
                    self.index = len(self.tokens)
                    return var
                # else:
                #     self.index+=1
                #     return var
            elif self.relop() and self.tokens[self.index]:
                self.index+=1
                var = True
        elif self.tokens[self.index] == "(":
            #If we get a parenthesis go back to expression function and descend again
            self.index += 1
            if self.exp():
                var = True
                if self.index > len(self.tokens) - 1:
                    var = False
                    return var
                if self.tokens[self.index] == ")":
                    var = True
                    if self.index == len(self.tokens)-1:
                        return var
                    elif self.index+1 == len(self.tokens)-1:
                        var = False
                        return False
                    self.index += 1
                    self.exp()
                elif self.exp():
                    var = True
                    if self.index == len(self.tokens):
                        var = False
                        return False
                    self.index += 1
                    self.exp()
                else:
                    var = False
                    return False
        else:
            if self.relop():
                var = True
                if self.index == len(self.tokens):
                    var = False
                elif not(self.tokens[self.index].isdigit()):
                    var = False
                    self.index+=1
                else:
                    self.index+=1
            else:
                self.index = len(self.tokens)
                var = False
        return var

    def relop(self):
        var = self.lop()

        if self.index == len(self.tokens):
            var = False
            return var
        for i in range(0,len(self.reloperator)):
            if self.tokens[self.index] == self.reloperator[i]:
                self.index+=1
                var = True
                break

        return var

    def lop(self):
        var = False
        if self.index == len(self.tokens):
            var = False
            return var
        for x in range(0,len(self.loperator)):
            if self.tokens[self.index] == self.loperator[x]:
                self.index+=1
                var = True
                break

        return var
    def descend(self):
        var = self.exp()
        if self.index < len(self.tokens)-1:
            var = self.exp()
        return var

    def validate(self):
        # Using the tokens from lex() tokenization,
        # your validate would first call lex() to first tokenize the expression
        # then call the top level parsing procedure and go from there

        self.lex()
        return self.descend()

    # parsing procedures corresponding to the grammar rules - follow Figure 5.17
if __name__ == "__main__":
    r = recDescent('< 9')
    print(r.validate())